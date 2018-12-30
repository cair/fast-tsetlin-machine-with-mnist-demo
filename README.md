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
...
EPOCH 95
Training Time: 72.9 s
Evaluation Time: 9.7 s
Accuracy: 98.4

EPOCH 96
Training Time: 73.7 s
Evaluation Time: 9.8 s
Accuracy: 98.4

EPOCH 97
Training Time: 69.5 s
Evaluation Time: 10.5 s
Accuracy: 98.5

EPOCH 98
Trainig Time: 75.6 s
Evaluation Time: 9.5 s
Accuracy: 98.4

EPOCH 99
Training Time: 69.5 s
Evaluation Time: 13.7 s
Accuracy: 98.3

EPOCH 100
Training Time: 71.5 s
Evaluation Time: 10.8 s
Accuracy: 98.3
```
