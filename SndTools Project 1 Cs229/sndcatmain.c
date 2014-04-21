#include <stdio.h>
#include <stdlib.h>
#include "parser.h" 
#include "keyvaluefinder.h"
#include "durationcalc.h"
#include "keyvaluefinderaiff.h"
#include "sndchecklib.h"
#define MAX 1000000

int sndDataCatter(FILE* inputFile, FILE* outputFile);// AUDIO* soundVar);
int main(int argc, char **argv) {
	AUDIO *sound = malloc(sizeof(AUDIO));
	FILE *currentFile;
	int i;
	int bitDepth;
	int numChannels; 
	int sampleRate;
	int numSamples;
fprintf(stderr, "argv is: %s\n", argv[2]);
	if (argv[1] == NULL){ //Improper usecase, returns error message due to no switch being specified.
		fprintf(stderr, "Error. You must specify a switch and files to go with that switch. This program will now terminate.\n");
		return 1;
	}
	

	if (argv[1]!= NULL && strcmp(argv[1], "-h") == 0) {  // checks for the -h switch
		fprintf(stderr, "SNDCAT, By Coleman Jackson\n");
		fprintf(stderr,
				"This program reads all sound files passed as arguments, and writes a single sound file where the sample data is the concatenation of the sample data of the inputs\n ");
		fprintf(stderr,
				"This prgram supports passing of files and switches in the following format: sndcat [switches] [file] [file] \n");
		fprintf(stderr, "The following switches are supported: \n");
		fprintf(stderr,
				"-h: will display the help message you are now reading. :)\n");
		fprintf(stderr,
				"-a: Will Convert to AIFF sound format\n");
		fprintf(stderr,
				"-c: will convert to CS299 file format.\n");
		fprintf(stderr,
				"You MUST give a switch as an argument to the executable, but if you choose to not give a file, then sndcat will read from stdin\n");
		
		fprintf(stderr, "\n");
		return 0;

	
	}
	if ( argv[1]!= NULL && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-a") == 0 ) && argv[2] != NULL) {  // if there are files passed in and a switch has been declared
		FILE* finalOutput = fopen("finaloutput", "w"); //open the file that will eventaully be converted to aiff and written to stdout or written to stdout without passing.
		currentFile = fopen(argv[2], "r");	// get the inital file

		if(currentFile == NULL){ // null check the intial file
				fprintf(stderr, "ERROR. One of the files passed is NULL. Program Ended\n");
				return 1;
		}
		// grab the bitdepth, samplerate, and channels of the inital file. THis will be used to compare all others in the loop
		bitDepth = bitDepthChecker(currentFile); 
		numChannels =channelChecker(currentFile);
		sampleRate = sampleRateChecker(currentFile);
		

		if(bitDepth == -1 || numChannels == -1 || sampleRate == -1){ //There was a problem parsing the data by one of the checkers, in which case it is not a vaild file
				fprintf(stderr, "ERROR. problem with parsing data\n");
				return 1;
		}

			//BUILD THE INITAL PART OF THE RETURNED FILE USING THE FIRST FILES BASIC INFORMATION AS A GUIDE, DEFAULT IS CS229, will CONVERT TO AIFF LATER IF THE SWITCH is -a.
		fprintf(finalOutput, "CS229\n");
		fprintf(finalOutput, "SampleRate %d\n", sampleRate );
		fprintf(finalOutput, "Channels %d\n",  numChannels);
		fprintf(finalOutput, "BitDepth %d\n",  bitDepth);
		fprintf(finalOutput, "StartData\n");

		fclose(currentFile);

		if (strcmp(argv[1], "-c") == 0){
		fprintf(stdout, "CS229\n");
		fprintf(stdout, "SampleRate %d\n", sampleRate );
		fprintf(stdout, "Channels %d\n",  numChannels);
		fprintf(stdout, "BitDepth %d\n",  bitDepth);
		fprintf(stdout, "StartData\n");


		}
		currentFile = NULL; //reset the current file information
		//enter the loop to get the startdata information.

		for(i=2; i < argc; i++){
			
			currentFile = fopen(argv[i], "r"); //open the current file
			
	
			
			if(currentFile == NULL){ // null check the current file
				fprintf(stderr, "ERROR. One of the files passed is NULL. Program Ended\n");
				return 1;
			}

			int fileType = fileNameParser(currentFile); //current file is not null, therefore can be used
			rewind(currentFile);
			if(i == 2){ // only do this on the first run, grab the bitdepth and numchannels to compare to
				bitDepth = bitDepthChecker(currentFile); 
				numChannels =channelChecker(currentFile);
				sampleRate = sampleRateChecker(currentFile);
			}
			rewind(currentFile);
			//fprintf(stderr, "bitdepth is: %d\n", bitDepth);
			//fprintf(stderr, "numchannels is: %d\n", numChannels);


			if(bitDepth == -1 || numChannels == -1 || sampleRate == -1){ //Problem with Parsing the filename, means incorrect file
				fprintf(stderr, "ERROR. problem with parsing data\n");
				return 1;
			}
			
			if(bitDepth != bitDepthChecker(currentFile) || numChannels != channelChecker(currentFile) || sampleRate != sampleRateChecker(currentFile)){ // checks the numchannels, bitdepth, and sample rate are the same.
				fprintf(stderr, "ERROR. All files must share a common bitDepth, sampleRate, and number of channels\n");
				return 1;
			}
			


			rewind(currentFile);
			
			if (fileType == 1){ //if the file is already a cs229 file, then just call sndcatter on it
				sndDataCatter(currentFile, finalOutput);
				continue;
			}

			if(fileType == 2){
				FILE *cs229Output = fopen("output", "w"); //convert to cs229
				atocs(cs229Output, currentFile, sound);
				sndDataCatter(cs229Output, finalOutput); //pass converted cs229 file to snddatacatter
				continue;

			}
			if(fileType == -1){ //bad file
				fprintf(stderr, "badFile at index %d, program terminating.", i);
				return 1;
			}



		}
		fclose(finalOutput);
		if (strcmp(argv[1], "-c") == 0){ // if it is a CS229 file, because finaloutput is stored in the CS229 format, simply write the completed file to Stdout.
			finalOutput= fopen("finaloutput", "r");
			

			sndDataCatter(finalOutput, stdout); //since snddatacatter is dependent on a cs229file, just send the built cs229 file through to stdout.
			fprintf(stderr, "Concatenation Complete to CS229 format.\n" );
			return 0;

 		}
		if (strcmp(argv[1], "-a") == 0){
		finalOutput= fopen("finaloutput", "r");
			//fprintf(stderr, "Passed for loop\n");
			rewind(finalOutput);
			cstoa(stdout, finalOutput, sound );
			fprintf(stderr, "Concatenation Complete to AIFF format.\n" );
			return 0;
		}


	}
	
	if ( argv[1]!= NULL && (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-a") == 0 ) && argv[2] == NULL) { // if there are no files passed in but a switch has been declared
	FILE* finalOutput = fopen("finaloutput", "w"); //open the file that will eventaully be converted to aiff and written to stdout or written to stdout without passing.
	currentFile = fopen("stdinbuffer", "w");	// get the inital file
	 int  c;
		while((c=fgetc(stdin)) !=EOF){
        fputc(c, currentFile);
    }
		if(currentFile == NULL){ // null check the intial file
				fprintf(stderr, "ERROR. One of the files passed is NULL. Program Ended\n");
				return 1;
		}
		fclose(currentFile);
		currentFile = fopen("stdinbuffer", "r");
		int fileType = fileNameParser(currentFile); //current file is not null, therefore can be used
		
		// grab the bitdepth, samplerate, and channels of the inital file. THis will be used to compare all others in the loop
		bitDepth = bitDepthChecker(currentFile); 
		numChannels =channelChecker(currentFile);
		sampleRate = sampleRateChecker(currentFile);
		rewind(currentFile);

		if(bitDepth == -1 || numChannels == -1 || sampleRate == -1){ //There was a problem parsing the data by one of the checkers, in which case it is not a vaild file
				fprintf(stderr, "ERROR. problem with parsing data\n");
				return 1;
		}
		
		

			//BUILD THE INITAL PART OF THE RETURNED FILE USING THE FIRST FILES BASIC INFORMATION AS A GUIDE, DEFAULT IS CS229, will CONVERT TO AIFF LATER IF THE SWITCH is -a.
		fprintf(finalOutput, "CS229\n");
		fprintf(finalOutput, "SampleRate %d\n", sampleRate );
		fprintf(finalOutput, "Channels %d\n",  numChannels);
		fprintf(finalOutput, "BitDepth %d\n",  bitDepth);
		fprintf(finalOutput, "StartData\n");

		fclose(currentFile);

		if (strcmp(argv[1], "-c") == 0){
		fprintf(stdout, "CS229\n");
		fprintf(stdout, "SampleRate %d\n", sampleRate );
		fprintf(stdout, "Channels %d\n",  numChannels);
		fprintf(stdout, "BitDepth %d\n",  bitDepth);
		fprintf(stdout, "StartData\n");


		}

	currentFile = fopen("stdinbuffer", "r"); //reset currentFile back to Start.


			
		if (fileType == 1){ //if the file is already a cs229 file, then just call sndcatter on it
			sndDataCatter(currentFile, finalOutput);
			
		}

		if(fileType == 2){
			FILE *cs229Output = fopen("output", "w"); //convert to cs229
			atocs(cs229Output, currentFile, sound);
			sndDataCatter(cs229Output, finalOutput); //pass converted cs229 file to snddatacatter
			

		}
		if(fileType == -1){ //bad file
			fprintf(stderr, "Bad File. program terminating.");
			return 1;
		}

		fclose(finalOutput);
		if (strcmp(argv[1], "-c") == 0){ // if it is a CS229 file, because finaloutput is stored in the CS229 format, simply write the completed file to Stdout.
			finalOutput= fopen("finaloutput", "r");
			

			sndDataCatter(finalOutput, stdout); //since snddatacatter is dependent on a cs229file, just send the built cs229 file through to stdout.
			fprintf(stderr, "Concatenation Complete to CS229 format.\n" );
			return 0;

 		}
		if (strcmp(argv[1], "-a") == 0){
			finalOutput= fopen("finaloutput", "r");
			rewind(finalOutput);
			cstoa(stdout, finalOutput, sound);
			fprintf(stderr, "Concatenation Complete to AIFF format.\n" );
			return 0;
		}

	}
	

	fprintf(stderr, "Error, check sndcut switch arguments and try again.\n"); // prints if there are files passed in but no switch is specified.
	return 1;
}	

/*

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

*/
int sndDataCatter(FILE* inputFile, FILE* outputFile){//, AUDIO *SoundVar){
	rewind(inputFile);
	//keyValueFinder229(inputFile, SoundVar);
	//rewind(inputFile);
	char keyWord[10];
	char line[128];
	 signed long dataStore[50000];	
	int arraySize = 0;
	while( fgets(line, sizeof(line), inputFile) != NULL){
	    int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal); 
		fprintf(stderr, "Keyword value is: %s", keyWord);
 		if(keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] =='a' && keyWord[3] == 'r' && keyWord[4] =='t'){
 			fprintf(stderr, "THIS WORKS!!!!!!!");
			break;
		
		
		}
	}
	
	while( fgets(line, sizeof(line), inputFile) != NULL){
		int channelCount = 0;
		fprintf(outputFile, "%s", line);

		/*while (channelCount < SoundVar->numChannels){
		signed int t;
			fscanf(inputFile, "%d", &t);
			dataStore[arraySize] = t;
			arraySize++;
			channelCount++;
		*/
		//}

	}

	/*int f = 0; //WRITE THE FILE \/\/\/
	int final;

	for(final = 0; final < arraySize; final++){

	fprintf(outputFile, "%d ", dataStore[final]);
	f++;
	if (f%(SoundVar->numChannels)==0){
	fprintf(outputFile, "\n");
	*/ //}
}



