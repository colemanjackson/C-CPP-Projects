
#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"

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