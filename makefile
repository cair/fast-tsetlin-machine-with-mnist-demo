MNISTDemoBits: MultiClassTsetlinMachineBits.c MultiClassTsetlinMachineBits.h TsetlinMachineBits.c TsetlinMachineBitsConfig.h TsetlinMachineBits.h MNISTDemoBits.c
	gcc -Wall -O3 -march=native -funroll-loops -ffast-math -o MNISTDemoBits \
	MNISTDemoBits.c MultiClassTsetlinMachineBits.c TsetlinMachineBits.c

clean:
	rm *.o MNISTDemoBits
