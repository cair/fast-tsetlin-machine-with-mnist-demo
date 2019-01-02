/*

Copyright (c) 2018 Ole-Christoffer Granmo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

This code implements a multiclass version of the Tsetlin Machine from paper arXiv:1804.01508
https://arxiv.org/abs/1804.01508

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "TsetlinMachineBits.h"

struct TsetlinMachine *CreateTsetlinMachine()
{
	/* Set up the Tsetlin Machine structure */

	struct TsetlinMachine *tm = (void *)malloc(sizeof(struct TsetlinMachine));

	if(tm) tm_initialize(tm);

	return tm;
}

void tm_initialize(struct TsetlinMachine *tm)
{
	/* Set up the Tsetlin Machine structure */

	for (int j = 0; j < CLAUSES; ++j) {
		TsetlinMachineStateBits_t *la_chunks = tm->ta_state[j];
		for (int k = 0; k < LA_CHUNKS; ++k) {
			unsigned int *state_bits = la_chunks[k];
			for (int b = 0; b < STATE_BITS-1; ++b) {
				state_bits[b] = ~0;
			}
			state_bits[STATE_BITS-1] = 0;
		}
	}
}

static inline void tm_initialize_random_streams(struct TsetlinMachine *tm, float s)
{
	for (int k = 0; k < LA_CHUNKS; ++k) {
		for (int b = 0; b < INT_SIZE; ++b) {
			if  (1.0*rand()/RAND_MAX <= 1.0/s) {
				tm->feedback_to_la[k] |= (1 << b);
			} else {
				tm->feedback_to_la[k] &= ~(1 << b);
			}
		}
	}
}

// Increment the states of each of those 32 Tsetlin Automata flagged in the active bit vector.
static inline void tm_inc(struct TsetlinMachine *tm, int clause, int chunk, unsigned int active)
{
	unsigned int carry, carry_next;

	carry = active;
	unsigned int *la_chunk = tm->ta_state[clause][chunk];
	for (int b = 0; b < STATE_BITS; ++b) {
		if (carry == 0)
			break;

		carry_next = la_chunk[b] & carry; // Sets carry bits (overflow) passing on to next bit
		la_chunk[b] ^= carry; // Performs increments with XOR
		carry = carry_next;
	}

	if (carry > 0) {
		for (int b = 0; b < STATE_BITS; ++b) {
			la_chunk[b] |= carry;
		}
	}
}

// Decrement the states of each of those 32 Tsetlin Automata flagged in the active bit vector.
static inline void tm_dec(struct TsetlinMachine *tm, int clause, int chunk, unsigned int active)
{
	unsigned int carry, carry_next;

	carry = active;
	unsigned int *la_chunk = tm->ta_state[clause][chunk];
	for (int b = 0; b < STATE_BITS; ++b) {
		if (carry == 0)
			break;

		carry_next = (~la_chunk[b]) & carry; // Sets carry bits (overflow) passing on to next bit
		la_chunk[b] ^= carry; // Performs increments with XOR
		carry = carry_next;
	}

	if (carry > 0) {
		for (int b = 0; b < STATE_BITS; ++b) {
			la_chunk[b] &= ~carry;
		}
	}
}

/* Sum up the votes for each class (this is the multiclass version of the Tsetlin Machine) */
static inline int sum_up_class_votes(struct TsetlinMachine *tm)
{
	int class_sum = 0;

	for (int j = 0; j < CLAUSE_CHUNKS; j++) {
		class_sum += __builtin_popcount(tm->clause_output[j] & 0x55555555); // 0101
		class_sum -= __builtin_popcount(tm->clause_output[j] & 0xaaaaaaaa); // 1010
	}

	class_sum = (class_sum > THRESHOLD) ? THRESHOLD : class_sum;
	class_sum = (class_sum < -THRESHOLD) ? -THRESHOLD : class_sum;

	return class_sum;
}

/* Calculate the output of each clause using the actions of each Tsetline Automaton. */
/* Output is stored an internal output array. */

static inline void tm_calculate_clause_output(struct TsetlinMachine *tm, unsigned int Xi[], int predict)
{
	for (int j = 0; j < CLAUSE_CHUNKS; j++) {
		tm->clause_output[j] = 0;
	}

	for (int j = 0; j < CLAUSES; j++) {
		unsigned int output = 1;
		unsigned int all_exclude = 1;
		TsetlinMachineStateBits_t *la_chunks = tm->ta_state[j];
		for (int k = 0; k < LA_CHUNKS-1; k++) {
            unsigned int state_bit = la_chunks[k][STATE_BITS-1];
			output = output && (state_bit & Xi[k]) == state_bit;

			if (!output) {
				break;
			}
			all_exclude = all_exclude && (state_bit == 0);
		}

        unsigned int state_bit = la_chunks[LA_CHUNKS-1][STATE_BITS-1];
		output = output &&
			(state_bit & Xi[LA_CHUNKS-1] & FILTER) == (state_bit & FILTER);

		all_exclude = all_exclude && (state_bit == 0);

		output = output && !(predict == PREDICT && all_exclude == 1);

		if (output) {
			unsigned int clause_chunk = j / INT_SIZE;
			unsigned int clause_chunk_pos = j % INT_SIZE;

 			tm->clause_output[clause_chunk] |= (1 << clause_chunk_pos);
 		}
 	}
}

/******************************************/
/*** Online Training of Tsetlin Machine ***/
/******************************************/

// The Tsetlin Machine can be trained incrementally, one training example at a time.
// Use this method directly for online and incremental training.

void tm_update(struct TsetlinMachine *tm, unsigned int Xi[], int target, float s)
{
	/*******************************/
	/*** Calculate Clause Output ***/
	/*******************************/

	tm_calculate_clause_output(tm, Xi, UPDATE);

	/***************************/
	/*** Sum up Clause Votes ***/
	/***************************/

	int class_sum = sum_up_class_votes(tm);

	/*********************************/
	/*** Train Individual Automata ***/
	/*********************************/

	// Calculate feedback to clauses

	for (int j = 0; j < CLAUSE_CHUNKS; j++) {
	 	tm->feedback_to_clauses[j] = 0;
	}

	for (int j = 0; j < CLAUSES; j++) {
		unsigned int clause_chunk = j / INT_SIZE;
		unsigned int clause_chunk_pos = j % INT_SIZE;

	 	tm->feedback_to_clauses[clause_chunk] |= (1.0*rand()/RAND_MAX <= (1.0/(THRESHOLD*2))*(THRESHOLD + (1 - 2*target)*class_sum)) << clause_chunk_pos;
	}

	for (int j = 0; j < CLAUSES; j++) {
		unsigned int clause_chunk = j / INT_SIZE;
		unsigned int clause_chunk_pos = j % INT_SIZE;

		if (!(tm->feedback_to_clauses[clause_chunk] & (1 << clause_chunk_pos))) {
			continue;
		}

		if ((2*target-1) * (1 - 2 * (j & 1)) == -1) {
			if ((tm->clause_output[clause_chunk] & (1 << clause_chunk_pos)) > 0) {
				// Type II Feedback

                TsetlinMachineStateBits_t *la_chunks = tm->ta_state[j];
				for (int k = 0; k < LA_CHUNKS; ++k) {
					tm_inc(tm, j, k, (~Xi[k]) & (~la_chunks[k][STATE_BITS-1]));
				}
			}
		} else if ((2*target-1) * (1 - 2 * (j & 1)) == 1) {
			// Type I Feedback

			tm_initialize_random_streams(tm, s);

			if ((tm->clause_output[clause_chunk] & (1 << clause_chunk_pos)) > 0) {
				for (int k = 0; k < LA_CHUNKS; ++k) {
					#ifdef BOOST_TRUE_POSITIVE_FEEDBACK
		 				tm_inc(tm, j, k, Xi[k]);
					#else
						tm_inc(tm, j, k, Xi[k] & (~tm->feedback_to_la[k]));
					#endif

		 			tm_dec(tm, j, k, (~Xi[k]) & tm->feedback_to_la[k]);
				}
			} else {
				for (int k = 0; k < LA_CHUNKS; ++k) {
					tm_dec(tm, j, k, tm->feedback_to_la[k]);
				}
			}
		}
	}
}

int tm_score(struct TsetlinMachine *tm, unsigned int Xi[]) {
	/*******************************/
	/*** Calculate Clause Output ***/
	/*******************************/

	tm_calculate_clause_output(tm, Xi, PREDICT);

	/***************************/
	/*** Sum up Clause Votes ***/
	/***************************/

	return sum_up_class_votes(tm);
}

int tm_get_state(struct TsetlinMachine *tm, int clause, int la)
{
	int la_chunk = la / INT_SIZE;
	int chunk_pos = la % INT_SIZE;

	int state = 0;
	unsigned int *state_bits = tm->ta_state[clause][la_chunk];
	for (int b = 0; b < STATE_BITS; ++b) {
		if (state_bits[b] & (1 << chunk_pos)) {
			state |= 1 << b;
		}
	}

	return state;
}

int tm_action(struct TsetlinMachine *tm, int clause, int la)
{
	int la_chunk = la / INT_SIZE;
	int chunk_pos = la % INT_SIZE;

	return (tm->ta_state[clause][la_chunk][STATE_BITS-1] & (1 << chunk_pos)) > 0;
}


