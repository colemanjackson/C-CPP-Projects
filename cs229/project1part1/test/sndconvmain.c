#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"
#include "atocs.h"
#include "cstoa.h"

int main(int argc, char **argv) {
	 /* open the file*/
	char input[50];
	FILE *outputFile;
	FILE *cs229File;
	char input2[50];
	int fileType = 5;
	char format[5];
	AUDIO *soundVar = malloc(sizeof(AUDIO));



	if (argv[1] != NULL && strcmp(argv[1], "-1") == 0) {
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

	if (argv[1]== NULL) {  //No switch case.


		int i;

		fileType = fileNameParser(stdin); //function call to decide the filetype of the sound file.
		
		if (fileType == 1) {  //assign the format to the type cs229

			cstoa(stdout, stdin, soundVar);

		}
		if (fileType == 2) {

			atocs(stdout, stdin, soundVar);

		}
		return 0;


	}

	



	
	if (argv[1] != NULL && strcmp(argv[1], "-h") == 0) { //-h switch
		fprintf(stderr, "\n");
		fprintf(stderr, "SNDCONV, By Coleman Jackson\n");
		fprintf(stderr,
				"Converts a CS229 or AIFF file. \n ");
		fprintf(stderr,
				"This program supports passing of switches in the following format: sndconv [switches]  \n");
		fprintf(stderr, "The following switches are supported: \n");
		fprintf(stderr,
				"-h: will display the help message you are now reading. :)\n");
		fprintf(stderr,
				"-1: will prompt users for the input and output file to be used.\n");
		fprintf(stderr,
				"-c: converts the file to cs229, regardless of input.\n");
		fprintf(stderr,
				"-a: converts the file to aiff, regardless of input\n");
		fprintf(stderr,
				"if no switches are specified, the program will read the files passed into the fuction, and convert the file to the opposite sound file type, written to standard output. \n");
		fprintf(stderr,
				"if no files and no switches are specified, sndinfo reads from stdin and prints to standard output the converted file.\n");
		fprintf(stderr, "NOTE: if you do not assign a switch to the executable, please remember to write the output to a filetype opposite the input file!!!!");
		fprintf(stderr, "\n");
		return 0;
	
	
	
	}

	if (argv[1] != NULL && strcmp(argv[1], "-c") == 0) { //case -c is used


		int i;

		fileType = fileNameParser(stdin); //function call to decide the filetype of the sound file.
		rewind(stdin);

		if (fileType == 1) {  //assign the format to the type cs229

			 char buffer[1000000];
   	      	

            for(;;) {
            	size_t bytes = fread(buffer,  sizeof(char),100000,stdin);
        		fwrite(buffer, sizeof(char), bytes, stdout);
        		fflush(stdout);
        		if (bytes < 100000)
            	if (feof(stdin))
                break;
		}


		}
		if (fileType == 2) {
			

			atocs(stdout, stdin, soundVar);
			printf(" conversion from aiff to cs229 Done\n");

		}
		return 0;


	}



	if (argv[1] != NULL && strcmp(argv[1], "-a") == 0) { //case -a is used


		int i;

		fileType = fileNameParser(stdin); //function call to decide the filetype of the sound file.
		rewind(stdin);

		if (fileType == 1) {  //assign the format to the type cs229

			cstoa(stdout, stdin, soundVar);
		}
		if (fileType == 2) {
			
			 rewind(stdin);
			 char buffer[100000];
   	        for(;;) {
            	size_t bytes = fread(buffer,  sizeof(char),100000,stdin);
        		fwrite(buffer, sizeof(char), bytes, stdout);
        		fflush(stdout);
        		if (bytes < 100000)
            	if (feof(stdin))
                break;
		}

		}
		return 0;




	}

	
	return 1;
}

