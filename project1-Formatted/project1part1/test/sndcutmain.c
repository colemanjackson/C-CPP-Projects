#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"
#include "atocs.h"
#include "cstoa.h"
#include "sndchecklib.h"

int main(int argc, char **argv) {
	int lowerbound[argc - 1];
	int higherbound[argc - 1];
 	AUDIO *sound = malloc(sizeof(AUDIO));

	if (argv[1] != NULL && strcmp(argv[1], "-h") != 0) { //if there is no switch, get the values.
		int i;
		int lowbound;
		int highbound;
		int j = 0;
		int count;
		//GET LOW AND HIGH VALUES FOR COMP
		for (i = 1; i < argc; i++) {
			sscanf(argv[i], "%d..%d", &lowbound, &highbound);
			if(lowbound < 0) {lowbound =0;}
			if(highbound < lowbound) {fprintf(stderr, "Your numbers are bad and you should feel bad.\n"); return 1;}
			lowerbound[j] = lowbound;
			higherbound[j] = highbound;
		//	fprintf(stderr, "lowbound this round is: %d\n", lowbound);
		//	fprintf(stderr, "lowbound stored in lowerbound is %d\n",
		//			lowerbound[j]);
		//	fprintf(stderr, "highbound this round is: %d\n", highbound);
		//	fprintf(stderr, "highbound stored in higherbound is %d\n",
		//			higherbound[j]);
			j++;
			fprintf(stderr, "--------------------------\n");
		}
		int lowestValue = lowerbound[0];
		int highestValue = higherbound[0];
		//GETS HIGHEST VALUE AND LOWEST VALUE, DISCOUNTING ANY IN BETWEEN
		for(count = 0; count < j; count++){
			if (lowerbound[count] < lowestValue){ lowestValue = lowerbound[count];}
			if(higherbound[count] > highestValue) { highestValue = higherbound[count];}
		}
		//	fprintf(stderr, "The lowest value you entered was: %d\n", lowestValue);
		//	fprintf(stderr, "The highest value you entered was: %d\n", highestValue);

		// NOW GET INPUT FROM STDIN
		FILE* finalOutput = fopen("finaloutput", "w"); //open the file that will eventaully be converted to aiff and written to stdout or written to stdout without passing.
		FILE* currentFile = fopen("stdinbuffer", "w");	// get the inital file
	 int c;
		while((c=fgetc(stdin)) !=EOF){ // NOT GRABBING AIFF FILES CORRECTLY!!!!!!!!!!!!!!!! RUN
									   // USING AIFF to STDIN THEN RUN vi stdinbuffer IT IS NEARLY BLANK.
									   // THIS IS WHY IT IS WRONG WITH SNDCATMAIN, SAME PLACE.
        fputc(c, currentFile);
    }
    	//ERR CHK INPUT
		if(currentFile == NULL){ // null check the intial file
				fprintf(stderr, "ERROR. One of the files passed is NULL. Program Ended\n");
				return 1;
		}
		fclose(currentFile);
		currentFile = fopen("stdinbuffer", "r");
		rewind(currentFile);
		int fileType = fileNameParser(currentFile); //current file is not null, therefore can be used
		
		//grab the bitdepth, samplerate, and channels of the inital file. THis will be used to compare all others in the loop
	 int bitDepth = bitDepthChecker(currentFile); 
	 int numChannels =channelChecker(currentFile);
	 int sampleRate = sampleRateChecker(currentFile);
		rewind(currentFile);

		if(bitDepth == -1 || numChannels == -1 || sampleRate == -1){ //There was a problem parsing the data by one of the checkers, in which case it is not a vaild file
				fprintf(stderr, "ERROR. problem with parsing FILE data\n");
				return 1;
		}

		

		//CS229 INPUT
		if (fileType == 1){
			sndDataCutter(currentFile, stdout, lowestValue, highestValue);
			fprintf(stderr, "Cutting to CS229 file complete.\n");
			
			return 0;
		} 

		//AIFF INPUT

		if (fileType ==2){
		FILE *cs229Output = fopen("output", "w"); //convert to cs229
		FILE *finalOutput = fopen("finaloutput", "w");
			atocs(cs229Output, currentFile, sound);
			fclose(cs229Output);
			cs229Output = fopen("output", "r");
			rewind(cs229Output);
			sndDataCutter(cs229Output,finalOutput, lowestValue, highestValue);
			fclose(finalOutput);

			finalOutput = fopen("finaloutput", "r");
			cstoa(stdout, finalOutput, sound);
			fprintf(stderr, "Cutting to AIFF file complete.\n");

			return 0;
		}

		if (fileType ==-1){
			fprintf(stderr, "ERROR IN FILE");
			return 1;
		}


	}

	if (argv[1] != NULL && strcmp(argv[1], "-h") == 0) { //-h switch
		fprintf(stderr, "\n");
		fprintf(stderr, "SNDCUT, By Coleman Jackson\n");
		fprintf(stderr, " This program reads input from stdin and outputs to stdout the values not cut between the specified indexes from low to high.  \n ");
		fprintf(stderr,
				"This program supports passing of switches in the following format: sndcut [switches] [low..high] [low.. high] \n");
		fprintf(stderr, "The following switches are supported: \n");
		fprintf(stderr,
				"-h: will display the help message you are now reading. :)\n");
		fprintf(stderr,
				"if no switches are specified, the program will read from stdin, cut the data from lowest low to highest high, and output the sndfile to stdout.");
		fprintf(stderr, "\n");
		return 0;

	}
}

int sndDataCutter(FILE* inputFile, FILE* outputFile, int lowbound, int highbound) { //, AUDIO *SoundVar){
	rewind(inputFile);
	AUDIO *values = malloc(sizeof(AUDIO));
	keyValueFinder229(inputFile, values);
	rewind(inputFile);
	int sampleRate = values->SampleRate;
	int numChannels = values->numChannels;
	int bitDepth = values->numBitDepth;
	fprintf(outputFile, "CS229\n");
    fprintf(outputFile, "SampleRate %d\n", sampleRate );
	fprintf(outputFile, "Channels %d\n",  numChannels);
	fprintf(outputFile, "BitDepth %d\n",  bitDepth);
	fprintf(outputFile, "StartData\n");
	char keyWord[10];
	char line[128];
	signed long dataStore[50000];
	int arraySize = 0;

	while (fgets(line, sizeof(line), inputFile) != NULL) {
		int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal);
		if (keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] == 'a'
				&& keyWord[3] == 'r' && keyWord[4] == 't') {
			break;

		}
	}
	int lineCount =0;
	while (fgets(line, sizeof(line), inputFile) != NULL) {
		if(lineCount < lowbound || lineCount > highbound ){
			fprintf(outputFile, "%s", line);
			lineCount++;
		}
			lineCount++;
			continue;
	}
	return 0;

}

