 #include <stdio.h>
#include <stdlib.h>
#include "parser.h" // all user defined fucntions and .h files should be in "" marks
#include "keyvaluefinder.h"
#include "durationcalc.h"
#include "keyvaluefinderaiff.h"



int main(){
        FILE *cs229File;            /* open the file*/
        char input[50];
        int fileType = 5;
        char format[5];
	 AUDIO *soundVar = malloc(sizeof(AUDIO));
		
        printf("Enter the pathname of a sound file: ");
        scanf("%s",&input);
        
        cs229File = fopen(input, "r");
        if (cs229File == NULL){       /*Null Check*/
                fprintf(stderr, "Error opening file, no results will be printed. Exiting Program.\n");
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
		fprintf(stderr, "File Type Unknown, Exiting Program. No results will be printed.\n");
              return 1;
			
		
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
		
		
		
	
}




