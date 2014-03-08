
#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"
#include "sndchecklib.h"



/*
 The best code ever. No really. But seriously, this very small library of functions is designed to return basic information about your sndfile. expect it to grow a great deal.




*/

long sampleRateChecker(FILE *workingFile){
		rewind(workingFile); // makes sure it is at the beginning before parsing
	int fileType=fileNameParser(workingFile);
	AUDIO* soundVar1 = malloc(sizeof(AUDIO));


	if (fileType == 1){
		keyValueFinder229(workingFile, soundVar1);
		
	}

	if (fileType ==2){

		keyValueFinderAIFF(workingFile, soundVar1);

	}

	if (fileType == -1){
		return -1; //return -1 for bad data.
	}
	rewind(workingFile);
	return soundVar1->SampleRate;
}


int bitDepthChecker(FILE* workingFile){ //checks the bitDepth by
	rewind(workingFile);
	int fileType=fileNameParser(workingFile);
	AUDIO* soundVar2 = malloc(sizeof(AUDIO));

	if (fileType == 1){
		keyValueFinder229(workingFile, soundVar2);
		
	}

	if (fileType ==2){

		keyValueFinderAIFF(workingFile, soundVar2);

	}

	if (fileType == -1){
		return -1; //return -1 for bad data.
	}
	rewind(workingFile);
	return soundVar2->numBitDepth;



}

int channelChecker(FILE *workingFile){
		rewind(workingFile); // makes sure it is at the beginning before parsing
	int fileType=fileNameParser(workingFile);
	AUDIO* soundVar1 = malloc(sizeof(AUDIO));


	if (fileType == 1){
		keyValueFinder229(workingFile, soundVar1);
		
	}

	if (fileType ==2){

		keyValueFinderAIFF(workingFile, soundVar1);

	}

	if (fileType == -1){
		return -1; //return -1 for bad data.
	}
	rewind(workingFile);
	return soundVar1->numChannels;
}


