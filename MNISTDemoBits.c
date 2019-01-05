#include "MultiClassTsetlinMachineBits.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define EPOCHS 400
#define NUMBER_OF_TRAINING_EXAMPLES 60000
#define NUMBER_OF_TEST_EXAMPLES 10000

unsigned int X_train[NUMBER_OF_TRAINING_EXAMPLES][LA_CHUNKS];
int y_train[NUMBER_OF_TRAINING_EXAMPLES];

unsigned int X_test[NUMBER_OF_TEST_EXAMPLES][LA_CHUNKS];
int y_test[NUMBER_OF_TEST_EXAMPLES];

unsigned int X_training_2[NUMBER_OF_TEST_EXAMPLES][LA_CHUNKS];
int y_training_2[NUMBER_OF_TEST_EXAMPLES];

void read_file(void)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;

	const char *s = " ";
	char *token = NULL;

	// Training Dataset

	for (int i = 0; i < NUMBER_OF_TRAINING_EXAMPLES; i++) {
		for (int j = 0; j < LA_CHUNKS; j++) {
			X_train[i][j] = 0;
		}
	}

	fp = fopen("MNISTTraining.txt", "r");
	if (fp == NULL) {
		printf("Error opening\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMBER_OF_TRAINING_EXAMPLES; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < FEATURES; j++) {
			if (atoi(token) == 1) {
				int chunk_nr = j / INT_SIZE;
				int chunk_pos = j % INT_SIZE;
				X_train[i][chunk_nr] |= (1 << chunk_pos);
			} else {
				int chunk_nr = (j + FEATURES) / INT_SIZE;
				int chunk_pos = (j + FEATURES) % INT_SIZE;
				X_train[i][chunk_nr] |= (1 << chunk_pos);
			}
			token=strtok(NULL,s);
		}
		y_train[i] = atoi(token);
	}
	fclose(fp);

	// Test Dataset I

	for (int i = 0; i < NUMBER_OF_TEST_EXAMPLES; i++) {
		for (int j = 0; j < LA_CHUNKS; j++) {
			X_test[i][j] = 0;
		}
	}

	fp = fopen("MNISTTest.txt", "r");
	if (fp == NULL) {
		printf("Error opening\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMBER_OF_TEST_EXAMPLES; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < FEATURES; j++) {
			if (atoi(token) == 1) {
				int chunk_nr = j / INT_SIZE;
				int chunk_pos = j % INT_SIZE;
				X_test[i][chunk_nr] |= (1 << chunk_pos);
			} else {
				int chunk_nr = (j + FEATURES) / INT_SIZE;
				int chunk_pos = (j + FEATURES) % INT_SIZE;
				X_test[i][chunk_nr] |= (1 << chunk_pos);
			}
			token=strtok(NULL,s);
		}
		y_test[i] = atoi(token);
	}
	fclose(fp);

	// Sample of training dataset for speed

	for (int i = 0; i < NUMBER_OF_TEST_EXAMPLES; i++) {
		for (int j = 0; j < LA_CHUNKS; j++) {
			X_training_2[i][j] = 0;
		}
	}

	fp = fopen("MNISTTrainingSampled.txt", "r");
	if (fp == NULL) {
		printf("Error opening\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUMBER_OF_TEST_EXAMPLES; i++) {
		getline(&line, &len, fp);

		token = strtok(line, s);
		for (int j = 0; j < FEATURES; j++) {
			if (atoi(token) == 1) {
				int chunk_nr = j / INT_SIZE;
				int chunk_pos = j % INT_SIZE;
				X_training_2[i][chunk_nr] |= (1 << chunk_pos);
			} else {
				int chunk_nr = (j + FEATURES) / INT_SIZE;
				int chunk_pos = (j + FEATURES) % INT_SIZE;
				X_training_2[i][chunk_nr] |= (1 << chunk_pos);
			}
			token=strtok(NULL,s);
		}
		y_training_2[i] = atoi(token);
	}
	fclose(fp);
}

void output_digit(unsigned int Xi[])
{
	for (int y = 0; y < 28; y++) {
		for (int x = 0; x < 28; x++) {
			int chunk_nr = (x + y*28) / INT_SIZE;
			int chunk_pos = (x + y*28) % INT_SIZE;

			if ((Xi[chunk_nr] & (1 << chunk_pos)) > 0) {
				printf("@");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}

int main(void)
{	
	srand(time(NULL));

	read_file();

	int example = (int)(NUMBER_OF_TEST_EXAMPLES-1) * 1.0*rand()/RAND_MAX;
	printf("\nExample of Digit %d\n\n", y_test[example]);
	output_digit(X_test[example]);

	struct MultiClassTsetlinMachine *mc_tm = CreateMultiClassTsetlinMachine();

	for (int i = 0; i < EPOCHS; i++) {
		printf("\nEPOCH %d\n", i+1);

		clock_t start_total = clock();
		mc_tm_fit(mc_tm, X_train, y_train, NUMBER_OF_TRAINING_EXAMPLES, 1, S);
		clock_t end_total = clock();
		double time_used = ((double) (end_total - start_total)) / CLOCKS_PER_SEC;

		printf("Training Time: %.1f s\n", time_used);

		start_total = clock();
		float test_accuracy = mc_tm_evaluate(mc_tm, X_test, y_test, NUMBER_OF_TEST_EXAMPLES);
		end_total = clock();
		time_used = ((double) (end_total - start_total)) / CLOCKS_PER_SEC;

		printf("Evaluation Time: %.1f s\n", time_used);
		printf("Test Accuracy: %.1f\n", 100*test_accuracy);

		float training_2_accuracy = mc_tm_evaluate(mc_tm, X_training_2, y_training_2, NUMBER_OF_TEST_EXAMPLES);
		printf("Training Accuracy: %.1f\n", 100*training_2_accuracy);
	}

	return 0;
}
