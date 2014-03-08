 #include <stdio.h>
#include <stdlib.h>
#include "parser.h" // all user defined fucntions and .h files should be in "" marks
#include "keyvaluefinder.h"
#include "durationcalc.h"
#include "keyvaluefinderaiff.h"



int main(int argc, char **argv ){
	FILE *cs229File =stdin;            /* open the file*/
	char input[50];
	int fileType = 5;
	char format[5];
	AUDIO *soundVar = malloc(sizeof(AUDIO));
	int i;

	if(strcmp(argv[1], "-1") == 0) {	  //checks for the -1 switch
     
        printf("Enter the pathname of a sound file: ");
        scanf("%s",&input);
        
        cs229File = fopen(input, "r");
        if (cs229File == NULL){       /*Null Check*/
                fprintf(stderr, "Null File, no results will be printed. Exiting Program.\n");
			return 1;
                
		}	
       		

		fileType = fileNameParser(cs229File); //function call to decide the filetype of the sound file.
		
		if (fileType == 1){
			//assign the format to the type cs229
			format[0] = 'C';
			format[1] = 'S';
			format[2] = '2';
			format[3] = '2';
			format[4] = '9';
			format[5] = '\0';
			
			//call keyValueFinder and pass in the memory locations of numSamples, numChannels, numBitDepth, and SampleRate, these values will be calculated in the method.
			keyValueFinder229(cs229File, soundVar); 
		}   
		if (fileType ==2){
			//assign the format to type AIFF
			format[0] = 'A';
			format[1] = 'I';
			format[2] = 'F';
			format[3] = 'F';
			format[4] = '\0';
			keyValueFinderAIFF(cs229File, soundVar);  
		}
			
		else if(fileType == -1){
			fprintf(stderr, "ERROR: File Type Unknown\n");
			keyValueFinderAIFF(cs229File, soundVar); //should just print zeroes.
		
		}
	

	//print the outputs
			
		printf("------------------------------------------------------------\n");
		printf("   Filename: ");
		int j =0;
		while (input[j] != '\0'){
			putchar(input[j]);
			j++;
		}
		if (input[j] =='\0'){
			printf("\n");
		}

		printf("     Format: ");  
		
		// print the format string stored in the format array
		int i =0;
		while (format[i] != '\0'){
			putchar(format[i]);
			i++;
		}
		if (format[i] =='\0'){
			printf("\n");
		}
		printf("Sample Rate: %i\n", soundVar->SampleRate);
		printf("  Bit Depth: %i\n", soundVar->numBitDepth);
		printf("   Channels: %i\n", soundVar->numChannels);
		printf("    Samples: %i\n", soundVar->numSamples);
		printf("   Duration: %01.0f:%02.0f:%05.02f\n", soundVar->hours,soundVar->minutes,soundVar->seconds);
		printf("------------------------------------------------------------\n");
		return 0;
		
	}
	
	if(strcmp(argv[1], "-h")== 0  ){  // checks for the -h switch
		fprintf(stderr, "\n");
		fprintf(stderr, "SNDINFO, By Coleman Jackson\n");
		fprintf(stderr, "This program is used to display information about a sound file, either in the AIFF or CS229 formats. \n ");
		fprintf(stderr, "This prgram supports passing of files and switches in the following format: sndinfo [switches] [file] [file] \n");
		fprintf(stderr, "The following switches are supported: \n");
		fprintf(stderr, "-h: will display the help message you are now reading. :)\n");
		fprintf(stderr, "-1: will not use the files passed into the function, and instead will prompt users for the path to the file to be read.\n");
		fprintf(stderr, "if no switches are specified, the program will read the files passed into the fuction and display the information about each file until all files are read. \n");
		fprintf(stderr, "if no files and no switches are specified, sndinfo reads from stdin.\n");
		fprintf(stderr, "\n");
		return 0;

	}

	
	
	for(i = 1; i < argc; i++){
		cs229File = fopen(argv[i], "r");
		if (cs229File == NULL){
		printf("------------------------------------------------------------\n");
		printf("Error in reading file @ argument index: %d\n", i);
			continue;
		}		
	fileType = fileNameParser(cs229File); //function call to decide the filetype of the sound file.
		
		
	if (fileType == 1){
		//assign the format to the type cs229
		format[0] = 'C';
		format[1] = 'S';
		format[2] = '2';
		format[3] = '2';
		format[4] = '9';
		format[5] = '\0';
			
		//call keyValueFinder and pass in the memory locations of numSamples, numChannels, numBitDepth, and SampleRate, these values will be calculated in the method.
		keyValueFinder229(cs229File, soundVar); 
			
		

	}   
	if (fileType ==2){
 		//assign the format to type AIFF
		format[0] = 'A';
		format[1] = 'I';
		format[2] = 'F';
		format[3] = 'F';
		format[4] = '\0';
		keyValueFinderAIFF(cs229File, soundVar);  
	}
			
	 else if(fileType == -1){
		fprintf(stderr, "File Type Unknown, Exiting Program. No results will be printed.\n");
              return 1;
			
		
	}
	


	//print the outputs
			
	printf("------------------------------------------------------------\n");
	printf("   Filename: ");
	sprintf(input, "%s", argv[i]);
	printf("%s\n", input);
	printf("     Format: ");  
		
	// print the format string stored in the format array
	int j =0;
	while (format[j] != '\0'){
		putchar(format[j]);
		j++;
	}
	if (format[j] =='\0'){
		printf("\n");
	}
	printf("Sample Rate: %i\n", soundVar->SampleRate);
	printf("  Bit Depth: %i\n", soundVar->numBitDepth);
	printf("   Channels: %i\n", soundVar->numChannels);
	printf("    Samples: %i\n", soundVar->numSamples);
	printf("   Duration: %01.0f:%02.0f:%05.02f\n", soundVar->hours,soundVar->minutes,soundVar->seconds);
	
	if(i == (argc-1)){ 
		printf("------------------------------------------------------------\n");
	}
	}
	


	
	
	
	
	
	
}




