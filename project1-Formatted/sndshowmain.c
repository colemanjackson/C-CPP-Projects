#include <stdio.h>
#include <stdlib.h>
#include "parser.h" 
#include "keyvaluefinder.h"
#include "durationcalc.h"
#include "keyvaluefinderaiff.h"
#include "sndchecklib.h"
#include <math.h>

void sndshowsnapshot(FILE *inputFile, AUDIO *sound, int width, int valToStop);
void sndshow(FILE *inputFile, AUDIO *sound, int width);
int main(int argc, char **argv) {
AUDIO *sound = malloc(sizeof(AUDIO));
char width1[4];
int width;
int i;
int valToStop;
int z;
int wFlag = 0;
int cFlag = 0;
int channel;
char channel1[4];

if (argv[1]== NULL || (argv[1]!= NULL && strcmp(argv[1], "-w") == 0 && argv[2] != NULL) || (argv[3]!= NULL && strcmp(argv[3], "-w") == 0 && argv[4] != NULL)) {
	 //SET WIDTH FIRST
	//for(z = 0; z < argc-1; z++ ){
	//	printf("argv is: %s", argv[z]);}

	for(z = 0; z < argc-1; z++ ){
		if (argv[z]!= NULL && strcmp(argv[z], "-w") == 0){ // if you have a -w flag
			
			if (argv[z]!= NULL && strcmp(argv[z], "-w") == 0 && argv[z+1] != NULL){ //making sure you dont scan something dumb in f
				sscanf(argv[z+1], "%s", width1);
				width= atoi (width1);
				//printf("width: %d\n", width);
				wFlag = 1; // saves you because when wFlag is not flagged due to null value width just defaults to 80.
			//	printf(" width flag is: %d\n", wFlag);
			
		}
	}

		if (argv[z]!= NULL && strcmp(argv[z], "-c") == 0){ // if you have a -c flag
			
			if (argv[z]!= NULL && strcmp(argv[z], "-c") == 0 && argv[z+1] != NULL){ //making sure you dont scan something dumb in f
				sscanf(argv[z+1], "%s\n", channel1);
				channel= atoi (channel1);
			//	printf("channel to cut: %d \n", channel);
				cFlag = 1; // saves you because when wFlag is not flagged due to null value width just defaults to 80.
				//printf(" channel flag is: %d\n", cFlag);
				
		}

	}
}
	 if (wFlag == 0){width = 80;} // if width is not specified, just set width to 80.
	// if (argv[1]!= NULL && strcmp(argv[1], "-w") == 0 && argv[2] != NULL){
		//sscanf(argv[2], "%s", width1);
		//width= atoi (width1);
		//width = (int) width1;
		
	//	printf("width1 is: %s\n", width1);
	//	printf("width is: %d\n", width);
	 if (width == NULL || width <20 || width%2 != 0){ fprintf(stderr, "ERROR. Check switches or width and try again.\n"); return 1;}
	 
	 
	 
	//GET FILE
	FILE* currentFile = fopen("stdinbuffer", "w");	// get the inital file
	int c;
		while((c=fgetc(stdin)) !=EOF){ // NOT GRABBING AIFF FILES CORRECTLY!!!!!!!!!!!!!!!! RUN
									   // USING AIFF to STDIN THEN RUN vi stdinbuffer IT IS NEARLY BLANK.
									   // THIS IS WHY IT IS WRONG WITH SNDCATMAIN, SAME PLACE.
        fputc(c, currentFile);
    }
	if(currentFile == NULL){ // null check the intial file
				fprintf(stderr, "ERROR. One of the files passed is NULL. Program Ended\n");
				return 1;
		}
		fclose(currentFile);
		currentFile = fopen("stdinbuffer", "r");
		rewind(currentFile);
		int fileType = fileNameParser(currentFile); //current file is not null, therefore can be used
		rewind(currentFile);
		
		
		
		
		//229 FORMAT
		if (fileType ==1){
			keyValueFinder229(currentFile, sound);
			rewind(currentFile);
			if(cFlag ==1){
				if(sound->numChannels < channel){
				fprintf(stderr, "value of Channels bigger than the number of channels in the file. Exiting Program.\n");
				return 1;
			}
				sndshowsnapshot(currentFile,sound, width, channel);
				return 0;
			}
			sndshow(currentFile, sound, width);
			fprintf(stderr, "\n Show Complete from CS229 file.\n");

			return 0;
		}
		
		//AIFF FORMAT
		if (fileType ==2){
			FILE *cs229Output = fopen("output", "w"); //convert to cs229
			atocs(cs229Output, currentFile, sound);
			fclose(cs229Output);
			cs229Output = fopen("output", "r");
			keyValueFinder229(cs229Output, sound);
			rewind(cs229Output);

			if(cFlag ==1){
				if(sound->numChannels < channel){
				fprintf(stderr, "value of Channels bigger than the number of channels in the file. Exiting Program.\n");
				return 1;
			}
				sndshowsnapshot(cs229Output,sound, width, channel);
				return 0;
			}
			sndshow(cs229Output, sound, width);
			fprintf(stderr, "\n Show Complete from AIFF file.\n");
			return 0;
		}
		
		
}	
	

if (argv[1]!= NULL && strcmp(argv[1], "-h") == 0) {  // checks for the -h switch
		fprintf(stderr, "\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "SNDSHOW, By Coleman Jackson\n");
		fprintf(stderr,
				"This program reads a sound file passed from STDIN, and writes an ASCII text representation of the file\n ");
		fprintf(stderr,
				"This prgram supports passing of files and switches in the following format: sndshow [switch switcharg] stdin \n");
		fprintf(stderr, "The following switches are supported: \n");
		fprintf(stderr,
				"-h: will display the help message you are now reading. :)\n");
		fprintf(stderr,
				"-c c: Shows only the output for one line c, for 1 <= c <= #channels\n");
		fprintf(stderr,
				"-w w: specify the total output width w, in number of characters. If not specified, the default is 80.\n");
		fprintf(stderr,
				"-z: Zoom out by a factor of n. ( NOT IMPLEMENTED) (\n");
		fprintf(stderr,
				"You MUST give a switch as an argument to the executable, but if you choose to not give a file, then sndcat will read from stdin\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "\n");
		return 0;

	
	}
	
	
	
	
	fprintf(stderr, "Error. Check Arguments and try again.");
	return 1;
	
}






void sndshow(FILE *inputFile, AUDIO *sound, int width){
double dwidth = width *1.0;
//printf("dwidth = %lf\n", dwidth);
int bitDepth = sound->numBitDepth;
//printf("bithdepth: %d\n" ,bitDepth);
int channels = sound->numChannels;
double outputSpace = (dwidth-9-3)/2.0;
//printf("Your maxput for dashes: %lf\n", outputSpace);
double conVal = bitDepth-1.0;
//printf("value you are ^ to 2: %lf\n", conVal);
double maxSampleValue = pow(2.0, conVal);

//printf("Your maxSampleValue: %lf\n", maxSampleValue);
int val;
char keyWord[10];
char line[128];
while(fgets(line, sizeof(line), inputFile) != NULL){
	    int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal); 
 		if(keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] =='a' && keyWord[3] == 'r' && keyWord[4] =='t'){
			break;
		
		
		}
	}
		int sampleCount = 0;
	while(!feof (inputFile)){
		int channelCount = 0;
		while (channelCount < channels){
			if(channelCount == 0){printf("%9d", sampleCount);} 
			else{printf("         ");} //nine spaces and a pipe.
			fscanf(inputFile, "%d", &val);
			double dval = val -1.0;
			double count;
			double decimals;
			
		//	printf(" d val is %lf ", dval);
			double numDashToPrint = outputSpace*(dval/maxSampleValue);
			//printf("numDashToPrint: %lf\n", numDashToPrint);
			decimals = modf(numDashToPrint, &count);
			if (decimals < 0 && decimals <= -.43){
				count--;	
			}
			
			if(decimals > 0 && decimals >= .43){
				count++;
			}
			
			if(count == -0){
				count =0;
			}
			//printf("number of dashes: %lf\n", count);

			int size = dwidth - 9.0; //                       \/ see here
			//printf("size of array is: %d\n", size);
			char retVal[size+1 ]; //Taking into account you have already printed the first 9 digits.
			int c;
			for(c=0; c < size; c++){
			retVal[c] = ' ';

			}
			retVal[0] = '|'; //print first position
			retVal[(size-1)] = '|'; // print last
			retVal[(size/2)] = '|'; // print middle
                        retVal[size] = 0;
			int see;
			count = (int) count;
			int absCount=abs(count); //absolute value of count for array looping
				

			if (count <= 0){


				for(see = ((size/2)-1); see > ((outputSpace) - absCount); see--){

				retVal[see] = '-';
			}

			}
			if(count > 0){
			for(see = ((size/2) +1); see <= (( size/2) +  absCount); see++){
				retVal[see] = '-';
			 


			}
			
			}
			//for(see = ((size/2)-1); see > 0; see--){

			//	retVal[see] = '0';
			//}

			fprintf(stdout, "%s\n", retVal);
		//	fprintf(stdout, "%s %lf \n", retVal, count );
            			channelCount++;
			
		}
		sampleCount++;
	}







}


void sndshowsnapshot(FILE *inputFile, AUDIO *sound, int width, int valToStop){

double dwidth = width *1.0;
//printf("dwidth = %lf\n", dwidth);
int bitDepth = sound->numBitDepth;
//printf("bithdepth: %d\n" ,bitDepth);
int channels = sound->numChannels;
double outputSpace = (dwidth-9-3)/2.0;
//printf("Your maxput for dashes: %lf\n", outputSpace);
double conVal = bitDepth-1.0;
//printf("value you are ^ to 2: %lf\n", conVal);
double maxSampleValue = pow(2.0, conVal);

//printf("Your maxSampleValue: %lf\n", maxSampleValue);
int val;
char keyWord[10];
char line[128];
while(fgets(line, sizeof(line), inputFile) != NULL){
	    int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal); 
 		if(keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] =='a' && keyWord[3] == 'r' && keyWord[4] =='t'){
			break;
		
		
		}
	}
		int sampleCount = 0;
	while(!feof (inputFile)){
		int channelCount = 1;
		while (channelCount < channels+1){
			if(channelCount == valToStop ){printf("%9d", sampleCount);} 
			

			//if(channelCount== valToStop){printf("         ");} //nine spaces and a pipe.
			fscanf(inputFile, "%d", &val);
			double dval = val -1.0;
			double count;
			double decimals;
			
		//	printf(" d val is %lf ", dval);
			double numDashToPrint = outputSpace*(dval/maxSampleValue);
			//printf("numDashToPrint: %lf\n", numDashToPrint);
			decimals = modf(numDashToPrint, &count);
			if (decimals < 0 && decimals <= -.43){
				count--;	
			}
			
			if(decimals > 0 && decimals >= .43){
				count++;
			}
			
			if(count == -0){
				count =0;
			}
			//printf("number of dashes: %lf\n", count);

			int size = dwidth - 9.0; //                       \/ see here
			//printf("size of array is: %d\n", size);
			char retVal[size+1 ]; //Taking into account you have already printed the first 9 digits.
			int c;
			for(c=0; c < size; c++){
			retVal[c] = ' ';

			}
			retVal[0] = '|'; //print first position
			retVal[(size-1)] = '|'; // print last
			retVal[(size/2)] = '|'; // print middle
                        retVal[size] = 0;
			int see;
			count = (int) count;
			int absCount=abs(count); //absolute value of count for array looping
				

			if (count <= 0){


				for(see = ((size/2)-1); see > ((outputSpace) - absCount); see--){

				retVal[see] = '-';
			}

			}
			if(count > 0){
			for(see = ((size/2) +1); see <= (( size/2) +  absCount); see++){
				retVal[see] = '-';
			 


			}
			
			}
			//for(see = ((size/2)-1); see > 0; see--){

			//	retVal[see] = '0';
			//}
			if(channelCount == valToStop){

			fprintf(stdout, "%s\n", retVal);
			}
		//	fprintf(stdout, "%s %lf \n", retVal, count );
            			channelCount++;
			
		}
		sampleCount++;
	}







}