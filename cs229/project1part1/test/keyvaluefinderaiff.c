#include "keyvaluefinderaiff.h"
#include "durationcalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void keyValueFinderAIFF(FILE *cs229File, AUDIO *varStore) {
	unsigned char line[1080];
	int numChannels = 0;
	double mathSampleRate;
	double mathNumSamples;
	int numSampleFrames = 0;
	int sampleSize = 0;
	//unsigned int startData[10000]; // I'm programming hitler.
	//unsigned int startDataFinal[90000];
	long double sampleRate = 0;
	int i; //i for index
	int sampleRateExponet;
	unsigned int sampleRateExt; //sample Rate extension value, calculated with the sample rate exponet and the IEEE method to extract the actual value
	fgets(line, 1080, cs229File);
	for (i = 0; i < sizeof(line); i++) { //brute force method of getting the data. It's getting loopy up in here.
		if (line[i] == 'C' && line[(i + 1)] == 'O' && line[(i + 2)] == 'M'
				&& line[i + 3] == 'M') {
			numChannels = line[i + 8] << 8 | line[i + 9]; // shift the bits 4 to the left, and then OR the bits to add them in.
			numSampleFrames = (line[i + 10] << 24) | (line[i + 11] << 16)
					| (line[i + 12] << 8) | (line[i + 13]);
			sampleSize = line[i + 14] << 8 | line[i + 15];
			sampleRateExponet = line[i + 16] << 8 | line[i + 17];
			if (0x80 & sampleRateExponet) {
				fprintf(stderr,
						"Invalid File, Exiting Program. No results will be printed\n");
				return;
			}

			sampleRateExt = (line[i + 18] << 24) | (line[i + 19] << 16)
					| (line[i + 20] << 8) | (line[i + 21]);
			sampleRateExt >>= 31 - (sampleRateExponet - 16383); // get the sample rate using the IEEE equations

			//Set the variables.
			varStore->numSamples = numSampleFrames;
			mathNumSamples = numSampleFrames;
			varStore->numChannels = numChannels;
			varStore->numBitDepth = sampleSize;
			varStore->SampleRate = sampleRateExt;
			mathSampleRate = sampleRateExt;
			double secondsWithDecimals = mathNumSamples / mathSampleRate; //I am far too tired.
			durationCalc(secondsWithDecimals, varStore);
			break;
		}

	}

}
