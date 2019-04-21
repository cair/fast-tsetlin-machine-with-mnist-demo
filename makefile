MNISTDemoBits: MultiClassTsetlinMachineBits.c MultiClassTsetlinMachineBits.h TsetlinMachineBits.c TsetlinMachineBitsConfig.h TsetlinMachineBits.h MNISTDemoBits.c
	gcc -Wall -O3 -ffast-math -o MNISTDemoBits MNISTDemoBits.c MultiClassTsetlinMachineBits.c TsetlinMachineBits.c -lm

clean:
	rm *.o MNISTDemoBits
