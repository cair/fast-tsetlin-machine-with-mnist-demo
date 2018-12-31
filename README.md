# fast-tsetlin-machine-with-mnist-demo
An implementation of the Tsetlin Machine (https://arxiv.org/abs/1804.01508) using bitwise operations for increased learning- and classification speed.

On the MNIST dataset, the bit manipulation leads to approx.
* 10 times smaller memory footprint,
* 8 times quicker classification, and
* 3.5 times faster learning,

compared to the vanilla C implementation (https://github.com/cair/TsetlinMachineC). 

## MNIST Demo
```bash
make
./MNISTDemoBits 

EPOCH 1
Training Time: 178.6 s
Evaluation Time: 13.4 s
Accuracy Dataset I: 94.8
Accuracy Dataset II: 95.2

EPOCH 2
Training Time: 130.8 s
Evaluation Time: 15.4 s
Accuracy Dataset I: 95.4
Accuracy Dataset II: 95.7

EPOCH 3
Training Time: 121.7 s
Evaluation Time: 16.0 s
Accuracy Dataset I: 96.2
Accuracy Dataset II: 96.7

EPOCH 4
Training Time: 105.7 s
Evaluation Time: 15.6 s
Accuracy Dataset I: 96.5
Accuracy Dataset II: 96.7

EPOCH 5
Training Time: 100.5 s
Evaluation Time: 15.3 s
Accuracy Dataset I: 96.8
Accuracy Dataset II: 97.0
...

EPOCH 246
Training Time: 60.8 s
Evaluation Time: 14.1 s
Accuracy Dataset I: 98.2
Accuracy Dataset II: 98.3

EPOCH 247
Training Time: 61.6 s
Evaluation Time: 14.5 s
Accuracy Dataset I: 98.2
Accuracy Dataset II: 98.4

EPOCH 248
Training Time: 60.1 s
Evaluation Time: 15.4 s
Accuracy Dataset I: 98.3
Accuracy Dataset II: 98.3

EPOCH 249
Training Time: 59.5 s
Evaluation Time: 15.3 s
Accuracy Dataset I: 98.1
Accuracy Dataset II: 98.2

EPOCH 250
Training Time: 61.4 s
Evaluation Time: 16.1 s
Accuracy Dataset I: 98.2
Accuracy Dataset II: 98.2
```
## Data Preparation

The included dataset is a binarized version of the MNIST dataset (http://yann.lecun.com/exdb/mnist/), downloaded from https://github.com/mnielsen/neural-networks-and-deep-learning/tree/master/data. First, we extended the training data with 50 000 additional images - warped and translated versions of the original training images. Secondly, the complete dataset was binarized by replacing pixel values larger than 0.3 with 1 (with the original pixel values ranging from 0 to 1). Pixel values below or equal to 0.3 were replaced with 0. The following image is an example of the images produced.

```bash
............................
............................
............................
............................
............................
............................
............@@..............
...........@@.....@@@.......
...........@@.....@@........
..........@@......@@........
.........@@@......@@........
.........@@.......@@........
.........@@......@@@........
........@@@.@@@..@@@........
........@@@@@@@@@@@@........
.......@@@@@@@@@@@@.........
.......@@........@@.........
.................@@.........
................@@@.........
................@@@.........
................@@@.........
................@@@.........
................@@@.........
................@@@.........
................@@@.........
................@@@.........
............................
............................
```

## Further Work

* Perform a more extensive hyper-parameter search (manipulating THRESHOLD, CLAUSES, STATE_BITS, and S in TsetlinMachineBitsConfig.h).
* Evaluate different binarization and data augmentation approaches for MNIST.
* Investigate effect of using an ensemble of Tsetlin Machines.
* Optimize code base further.

## Licence

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

