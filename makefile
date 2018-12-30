MNISTDemoBits: MultiClassTsetlinMachineBits.c MultiClassTsetlinMachineBits.h TsetlinMachineBits.c TsetlinMachineBits.h MNISTDemoBits.c
	gcc -Wall -O3 -ffast-math -o MNISTDemoBits MNISTDemoBits.c MultiClassTsetlinMachineBits.c TsetlinMachineBits.c 

clean:
	rm *.o MNISTDemoBits
