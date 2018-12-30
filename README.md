# fast-tsetlin-machine-with-mnist-demo
An implementation of the Tsetlin Machine (https://arxiv.org/abs/1804.01508) using bitwise operations for increased learning- and classification speed.

On the MNIST dataset, the bit manipulation leads to
* about 10 times smaller memory footprint,
* about 8 times quicker classification, and
* approx. 3.5 times faster learning,

compared to the vanilla C implementation (https://github.com/cair/TsetlinMachineC). 
