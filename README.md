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
Training Time: 178.6 s
Evaluation Time: 13.4 s
Test Accuracy: 94.8
Validation Accuracy: 95.2

EPOCH 2
Training Time: 130.8 s
Evaluation Time: 15.4 s
Test Accuracy: 95.4
Validation Accuracy: 95.7

EPOCH 3
Training Time: 121.7 s
Evaluation Time: 16.0 s
Test Accuracy: 96.2
Validation Accuracy: 96.7

EPOCH 4
Training Time: 105.7 s
Evaluation Time: 15.6 s
Test Accuracy: 96.5
Validation Accuracy: 96.7

EPOCH 5
Training Time: 100.5 s
Evaluation Time: 15.3 s
Test Accuracy: 96.8
Validation Accuracy: 97.0
...

EPOCH 195
Training Time: 61.1 s
Evaluation Time: 17.2 s
Accuracy: 98.4

EPOCH 196
Training Time: 60.0 s
Evaluation Time: 16.2 s
Test Accuracy: 98.0
Accuracy: 98.3

EPOCH 197
Training Time: 61.4 s
Evaluation Time: 14.6 s
Accuracy: 98.3

EPOCH 198
Training Time: 61.2 s
Evaluation Time: 13.1 s
Accuracy: 98.2

EPOCH 199
Training Time: 61.3 s
Evaluation Time: 12.9 s
Accuracy: 98.3

EPOCH 200
Training Time: 62.4 s
Evaluation Time: 12.8 s
Accuracy: 98.3

