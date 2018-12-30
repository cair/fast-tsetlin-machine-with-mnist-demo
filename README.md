# fast-tsetlin-machine-with-mnist-demo
An implementation of the Tsetlin Machine (https://arxiv.org/abs/1804.01508) using bitwise operations for increased learning- and classification speed.

On the MNIST dataset, the bit manipulation leads to approx.
* 10 times smaller memory footprint,
* 8 times quicker classification, and
* 3.5 times faster learning,

compared to the vanilla C implementation (https://github.com/cair/TsetlinMachineC). 

# MNIST Demo
```bash
make
./MNISTDemoBits 

EPOCH 1
Training Time: 202.2 s
Evaluation Time: 10.4 s
Test Accuracy: 93.9

EPOCH 2
Training Time: 148.3 s
Evaluation Time: 10.4 s
Test Accuracy: 94.9

EPOCH 3
Training Time: 141.8 s
Evaluation Time: 12.6 s
Test Accuracy: 95.8

EPOCH 4
Training Time: 122.9 s
Evaluation Time: 13.9 s
Test Accuracy: 96.1

EPOCH 5
Training Time: 118.6 s
Evaluation Time: 10.9 s
Test Accuracy: 96.2

...
EPOCH 95
Training Time: 72.9 s
Evaluation Time: 9.7 s
Test Accuracy: 98.4

EPOCH 96
Training Time: 73.7 s
Evaluation Time: 9.8 s
Test Accuracy: 98.4

EPOCH 97
Training Time: 69.5 s
Evaluation Time: 10.5 s
Test Accuracy: 98.5

EPOCH 98
Trainig Time: 75.6 s
Evaluation Time: 9.5 s
Test Accuracy: 98.4

EPOCH 99
Training Time: 69.5 s
Evaluation Time: 13.7 s
Test Accuracy: 98.3

EPOCH 100
Training Time: 71.5 s
Evaluation Time: 10.8 s
Test Accuracy: 98.3
```
