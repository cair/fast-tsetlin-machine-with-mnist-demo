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

#include "TsetlinMachineBits.h"
#include "MultiClassTsetlinMachineConfig.h"

struct MultiClassTsetlinMachine { 
	struct TsetlinMachine *tsetlin_machines[CLASSES];
};

struct MultiClassTsetlinMachine *CreateMultiClassTsetlinMachine();

void mc_tm_initialize(struct MultiClassTsetlinMachine *mc_tm);

void mc_tm_initialize_random_streams(struct MultiClassTsetlinMachine *mc_tm);

float mc_tm_evaluate(struct MultiClassTsetlinMachine *mc_tm, unsigned int X[][LA_CHUNKS], int y[], int number_of_examples);

void mc_tm_fit(struct MultiClassTsetlinMachine *mc_tm, unsigned int X[][LA_CHUNKS], int y[], int number_of_examples, int epochs);
