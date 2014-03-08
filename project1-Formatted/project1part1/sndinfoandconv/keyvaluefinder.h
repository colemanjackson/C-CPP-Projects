#ifndef keyvaluefinder_h
#define keyvaluefinder_h
#include <stdio.h>

typedef struct {  //a struct used to store my variables. 
	int numSamples;
	int numChannels;
	int numBitDepth;
	long SampleRate;
	double hours;
	double minutes;
	double seconds;
} AUDIO;

void keyValueFinder229(FILE *cs229File, AUDIO *soundVar);

#endif
