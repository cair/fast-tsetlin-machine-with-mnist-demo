# fast-tsetlin-machine-with-mnist-demo
An implementation of the Tsetlin Machine (https://arxiv.org/abs/1804.01508) leveraging bitwise operations for increased learning- and classification speed.

On the MNIST dataset, this bit manipulation based implementation uses about 10 times less memory, classifies digits about 8 times quicker, and learns approx. 3.5 times faster than the vanilla C implementation (https://github.com/cair/TsetlinMachineC). 
