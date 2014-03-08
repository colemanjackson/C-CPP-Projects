#include "keyvaluefinder.h"
#include "durationcalc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void keyValueFinder229(FILE *cs229File,  AUDIO *varStore){
	if (varStore == NULL){ // ERROR CHECK
	fprintf(stderr, "bad mallac. Mem not allocated for AUDIO Struct. Declare and try again");
	exit(1);
}
	char line[128];   
	char keyWord[10];
	char * str;
	int sampleFlag1 = 0; // if this remains 0, then Samples was not declared and do not display Samples when printing
	int sampleFlag2 =0; // 0 if sample rate has yet to be hit in the file. 
	int startDataFlag =0; //0 if start data has not been hit, 1 after.
	int clockCalc =0; //0 if data has NOT been calculated from the samples/sampleSize
	int sampleCounter; //counts the samples from start data
	double mathNumSamples;
	double mathSampleRate;


	while( fgets(line, sizeof(line), cs229File) != NULL){
	           int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal); 
	 	if(keyWord[0] == 'C' && keyWord[1] == 'S'){
			continue;
		}
		if(keyWord[0] == ' '  || keyWord[0]== '#'){ // checking to see if the line is a comment or whitespace
			continue;
		}
	
		if(keyWord[0] == 'C' && keyWord[1] == 'h' && keyWord[2] =='a' && keyWord[3] == 'n'){
			varStore->numChannels = keyWordVal;
			continue;
		}

		if(keyWord[0] == 'S' && keyWord[1] == 'a' && keyWord[2] =='m' && keyWord[3] == 'p' && keyWord[4] =='l' && keyWord[5] =='e' && keyWord[6] =='s'){
			varStore->numSamples = keyWordVal;
			mathNumSamples = keyWordVal;
			sampleFlag1 = 1;
			continue;
		}

		if(keyWord[0] == 'B' && keyWord[1] == 'i' && keyWord[2] =='t' && keyWord[3] == 'D'){
			varStore->numBitDepth = keyWordVal;
			continue;
		}

		if(keyWord[0] == 'S' && keyWord[1] == 'a' && keyWord[2] =='m' && keyWord[3] == 'p' && keyWord[4] =='l' && keyWord[5] =='e' && keyWord[6] =='R'){
			varStore->SampleRate = keyWordVal;
			mathSampleRate = keyWordVal;
			sampleFlag2 = 1;
			continue;
		}	 
	 
		if(sampleFlag1 == 1 && sampleFlag2 ==1 && clockCalc == 0){//if the numSamples is not -1, then we have a real value for samples and you can find the duration of seconds by taking samples/sample rate
			double secondsWithDecimals = ((mathNumSamples) / (mathSampleRate));
			durationCalc(secondsWithDecimals, varStore);  //calls durationCalc to calcuate duration of the audio file
			clockCalc = 1; //set so  this if statement won't execute again.
		}

		if(keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] =='a' && keyWord[3] == 'r' && keyWord[4] =='t' && sampleFlag1 == 0 ){ //This will only execute if Samples has not been specified, calculates # of samples from the startdata
			
			startDataFlag = 1; // sets the StartData flag to 1 so the program knows the Samples should be calculated from the StartData
			continue;
		}	
		
		if(startDataFlag == 1){  
			sampleCounter++; //assumes startdata is all valid, but this will count the number of samples following startData

	        	varStore->numSamples = sampleCounter;
			mathNumSamples = sampleCounter;
	 	}
	}

	if(startDataFlag == 1){ //If samples is not declared, then after the while loop executes, calculate the duration from the startData count
		double secondsWithDecimals = ((mathNumSamples) / (mathSampleRate));
		durationCalc(secondsWithDecimals, varStore);
	}
	
}

