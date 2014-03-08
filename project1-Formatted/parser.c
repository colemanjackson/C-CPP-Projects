
#include "parser.h"
int fileNameParser(FILE* fileToParse) {
	char line[5];
	fgets(line, 5, fileToParse);
	if (line[0] == 'C' && line[1] == 'S') {
		return 1;  // 1 = CS229 file
	} else if (line[0] == 'F' && line[1] == 'O' && line[2] == 'R'
			&& line[3] == 'M') {

		return 2; //2 = AIFF file
	}

	return -1; //error

}

