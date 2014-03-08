#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"
#include "atocs.h"
#include "cstoa.h"




int main(){
	FILE *outputFile;
        FILE *cs229File;            /* open the file*/
        char input[50];
        char input2[50];
        int fileType = 5;
        char format[5];
	AUDIO *soundVar = malloc(sizeof(AUDIO));
        printf("Enter the name of a sound file (remember extensions!): ");
        scanf("%s",&input);
        cs229File = fopen(input,"r");

        if (cs229File == NULL){       /*Null Check*/

       	 
                fprintf(stderr, "Error opening file, no results will be printed. Exiting Program.\n");
                return 1;
	}	
       		

	int i;

	fileType = fileNameParser(cs229File); //function call to decide the filetype of the sound file.
		printf("Enter the name of the output file. remember extensions should not be the same as input file!: ");

		scanf("%s",&input2);
		
	if (fileType == 1){  //assign the format to the type cs229

		
		for(i=0; i < 48; i++){
			if ( input2[i] =='.' && input2[i+1] == 'c' && input2[i+2] == 's'){
				fprintf(stderr, "invalid conversion, must be to AIFF filetype. exiting program \n");
				return 1; 
			}
		}
		outputFile= fopen(input2, "w");
		printf("%s\n", input2);
		cstoa(outputFile, cs229File, soundVar);
		printf(" conversion from cs229 to aiff Done");

		

	}   
	if (fileType == 2){
		for(i=0; i < 48; i++){
			if ( input2[i] =='.' && input2[i+1] == 'a' && input2[i+2] == 'i'){
				fprintf(stderr, "invalid conversion, must be to AIFF filetype. exiting program \n");
				return 1; 
			}
		}
		outputFile= fopen(input2, "w");
		atocs(outputFile, cs229File, soundVar);
		printf(" conversion from aiff to cs229 Done\n");

	}
return 0;	
}



