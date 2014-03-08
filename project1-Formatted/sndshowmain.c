#include <stdio.h>
#include <stdlib.h>
#include "parser.h" 
#include "keyvaluefinder.h"
#include "durationcalc.h"
#include "keyvaluefinderaiff.h"
#include "sndchecklib.h"


int main(int argc, char **argv) {

if (argv[1]!= NULL && strcmp(argv[1], "-w") == 0) {
	fprintf(stderr, "this works!");

}


if (argv[1]!= NULL && strcmp(argv[1], "-h") == 0) {  // checks for the -h switch
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
				"-z: Zoom out by a factor of n. (\n");
		fprintf(stderr,
				"You MUST give a switch as an argument to the executable, but if you choose to not give a file, then sndcat will read from stdin\n");
		
		fprintf(stderr, "\n");
		return 0;

	
	}
	
	
	
}