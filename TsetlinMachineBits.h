/*

Copyright (c) 2019 Ole-Christoffer Granmo

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

#include "TsetlinMachineBitsConfig.h"

#define INT_SIZE 32

#define LA_CHUNKS (((2*FEATURES-1)/INT_SIZE + 1))
#define CLAUSE_CHUNKS ((CLAUSES-1)/INT_SIZE + 1)

#if ((FEATURES*2) % 32 != 0)
#define FILTER (~(0xffffffff << ((FEATURES*2) % INT_SIZE)))
#else
#define FILTER 0xffffffff
#endif

#define PREDICT 1
#define UPDATE 0

struct TsetlinMachine { 
	unsigned int ta_state[CLAUSES][LA_CHUNKS][STATE_BITS];
	unsigned int clause_output[CLAUSE_CHUNKS];
	unsigned int feedback_to_la[LA_CHUNKS];
	int feedback_to_clauses[CLAUSE_CHUNKS];
};

struct TsetlinMachine *CreateTsetlinMachine();

void tm_initialize(struct TsetlinMachine *tm);

void tm_update(struct TsetlinMachine *tm, unsigned int Xi[], int target);

int tm_score(struct TsetlinMachine *tm, unsigned int Xi[]);

int tm_get_state(struct TsetlinMachine *tm, int clause, int la);

int tm_action(struct TsetlinMachine *tm, int clause, int la);
