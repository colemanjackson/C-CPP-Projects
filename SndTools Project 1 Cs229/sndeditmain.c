#include <stdio.h>
#include <stdlib.h>
#include "keyvaluefinder.h"
#include "keyvaluefinderaiff.h"
#include "atocs.h"
#include "cstoa.h"
#include "sndchecklib.h"
#include <math.h>
#include <ncurses.h>
int paste(FILE* inputFile, int markedStartData[], int ch, int a, int b, AUDIO* sound, int arrayit);
void sndshow(FILE *inputFile, AUDIO *sound, int width, int index, int a, int b);
int gotoHelper(int rows, int columns, AUDIO * soundVar);
int sndinfobuilder(FILE* inputFile, AUDIO* soundVar, char* name, int fileType);
void catcutHelper(FILE* currentFile, AUDIO * sound, int a, int b, int markedStartData[], int ch);

int main(int argc, char **argv) {
	AUDIO *sound = malloc(sizeof(AUDIO));

	FILE *currentFile = fopen(argv[1], "r"); //open the current file

	if (currentFile == NULL) { // null check the current file
		fprintf(stderr,
				"ERROR. One of the files passed is NULL. Program Ended\n");
		return 1;
	}

	int fileType = fileNameParser(currentFile);

	if (fileType == 1) {

		keyValueFinder229(currentFile, sound);
		rewind(currentFile);
		int ret = sndinfobuilder(currentFile, sound, argv[1], fileType);
		if (ret == -1) {
			fprintf(stderr, "ERROR. Screen Size not of dim 40x24\n");
			return 1;
		}
		return 0;
	}

	if (fileType == 2) {
		FILE *cs229Output = fopen("output", "w+"); //convert to cs229
		atocs(cs229Output, currentFile, sound);
		//keyValueFinder229(cs229Output, sound);
		rewind(cs229Output);
		int ret = sndinfobuilder(cs229Output, sound, argv[1], fileType);
		rewind(cs229Output);
		keyValueFinder229(cs229Output, sound);
		rewind(cs229Output);

	 fclose(currentFile); 
	 currentFile = fopen(argv[1], "w+"); //clobber old aiff input file and make a new one of same name.
	 	cstoa(currentFile, cs229Output, sound); // convert the cs229 output to the new aiff file of the same name as the input
		if (ret == -1) { //error check
			fprintf(stderr, "ERROR. Screen Size not of dim 40x24\n");
			return 1;
		}
		return 0;
	}

	if (fileType == -1) {

		fprintf(stderr, "ERROR. One of the files is invalid. Ending Program\n");
		return 1;
	}

	fprintf(stderr, "Error, Check Argument and try again.\n");
	return 1;

}





/*
 * This is the function that is used to actually build the editing utility. It's a hodge podge of terrible code and in line variable declarations
 * that somehow manages to work.
 * May God have mercy on my soul.
 *
 */


int sndinfobuilder(FILE* currentFile, AUDIO* soundVar, char *name, int fileType) { // That feeling when you realize your function is named wrong but you are way to far in to change everything 
	 int c;
	 FILE* workingFile = fopen("workingfile", "w+");
	 rewind(currentFile);
		while((c=fgetc(currentFile)) !=EOF){  // builds the tempfile to edit
        fputc(c, workingFile);
    }						     // and you don't have an automatic refactoring util.... I know those feels right now.....
	char format[5];
	keyValueFinder229(workingFile, soundVar);
	int numChannels = soundVar->numChannels;
	int numSamples = soundVar->numSamples;
	if (fileType == 1) { // Copy and Pasted code from Sndinfo... I know, I'm basically the worst programmer ever.
		format[0] = 'C';
		format[1] = 'S';
		format[2] = '2';
		format[3] = '2';
		format[4] = '9';
		format[5] = '\0';
	}

	if (fileType == 2) {
		format[0] = 'A';
		format[1] = 'I';
		format[2] = 'F';
		format[3] = 'F';
		format[4] = '\0';
	}

	/* begin building */
	rewind(currentFile);
	initscr();
	noecho();
	keypad(stdscr, TRUE); /* build the screen to use!*/
	int ch; //character to grab and compare. Pretty much the most important thing in the history of forever for this function.
	int True = 1; // I'm evil. Kind of.
	int arrayit = 0; //array iterator
	int firstFlag = 1; //Set to TRUE;
	int x, y; // These are necessary. You know, probably. 
	int marked = 0; // the count of the what is marked
	int markedFlag = 0; //is 1 when there is a mark set, and false otherwise (used for copy, cut, paste)
	int editFlag = 0; //1 when the original file has been edited, false otherwise (used for save)
	int copycutFlag = 0; // 1 when copy and cut are available (so if markedFlag has been set), false otherwise
	int insertFlag = 0; // this flag is 1 when insert before and after is available, and false otherwise
	int a = -1;  // I am a great programmer and will make hunderds of thousands of dollars a year one day. Remember that. (these control highlighting for mark...)
	int b = -1; //     ^^ What he said ^^
	int markedStartData[1000000];
	int bbb;
	int finalCount;
	for(bbb = 0; bbb <1000000; bbb++){
		markedStartData[bbb] = 'n'; // DO NOT MODIFY. DEAD INSIDE.
	}
	while (True) { //Runs until q is recieved from getch()
		rewind(workingFile);
		keyValueFinder229(workingFile, soundVar);
		numChannels = soundVar->numChannels; // must reset every time in order to build the right sized printout
		numSamples = soundVar->numSamples;  //ditto
		int rows;
		int columns;
		int i;


		// Need x and y
		getmaxyx(stdscr, rows, columns);
		if (rows < 24 || columns < 40) {
			return -1;
		}

		int m;
		int n;
		for(m = 0; m <rows; m++){  //prints spaces every time.
			for(n = 0; n < columns; n++){
				mvprintw(m, n, " ");
			}
		} 
		getsyx(y, x);
		if (firstFlag == 0 &&( ch == 'g' || ch == 'G')) {
			int setarrayit = gotoHelper(rows, columns, soundVar);
			if(setarrayit != -1){ // if gotoHelper did not return an error
				arrayit = setarrayit * numChannels;// sets arrayit to the value of goto.
			}
		}
		
		mvprintw(0, columns / 2, "%s (%s)", name, format); //print name and format

		for (i = 0; i < columns; i++) {
			mvprintw(1, i, "=");
		}

		//Print Sndinfo
		mvprintw(2, columns - 19, "Sample Rate: %i", soundVar->SampleRate);
		mvprintw(3, columns - 17, "Bit Depth: %i", soundVar->numBitDepth);
		mvprintw(4, columns - 16, "Channels: %i", soundVar->numChannels);
		mvprintw(5, columns - 19, "Samples: %i", soundVar->numSamples);
		mvprintw(6, columns - 18, "Length: %01.0f:%02.0f:%05.02f\n",
				soundVar->hours, soundVar->minutes, soundVar->seconds);
		
		
		// Check for marked data 
		if (ch == 'm' || ch == 'M' ){
			if (markedFlag == 0){ // if there was previously no marked value...
				markedFlag =1;
				copycutFlag = 1; // set copy flag so every editing keystroke can be called
				 a = arrayit/numChannels;
			     b = a;
			}
			  else if(markedFlag == 1){ // if the previously marked value is no longer marked...
				markedFlag = 0;  
				finalCount = 0;
				a = -1;
				b = -1;
				copycutFlag = 0; 
				insertFlag = 0;
				for(bbb = 0; bbb <1000000; bbb++){
					markedStartData[bbb] = 'n';
	}
			}
		}	

	
//print sndinfo seperators and key commands based on flags
		for (i = (columns - 20); i < columns; i++) {
			mvprintw(7, i, "=");
		}
		mvprintw(8, columns - 17, "m: mark/unmark");
		if(markedFlag == 1){
			mvprintw(9, columns - 17, "c: copy");
			mvprintw(10, columns - 17, "x: cut");
		}else{ mvprintw(9, columns - 17, "        ");
			   mvprintw(10, columns - 17, "       ");
			 }
		if(markedFlag == 1 && insertFlag == 1){
			mvprintw(11, columns - 17, "^: insert before");
			mvprintw(12, columns - 17, "v: insert after");
		}else{
			mvprintw(11, columns - 17, "                ");
			mvprintw(12, columns - 17, "                 ");
		
		}
		if(editFlag == 1) {mvprintw(13, columns - 17, "s: save");}
			mvprintw(14, columns - 17, "q: quit");
			mvprintw(16, columns - 19, "Movement:");
			mvprintw(17, columns - 17, "up/dn");
			mvprintw(18, columns - 17, "pgup/pgdn");
			mvprintw(19, columns - 17, "g: goto sample   ");
		
//seperator building
		for (i = (columns - 20); i < columns; i++) {
			mvprintw((rows - 3), i, "=");
		}
		

// END OF INFOBUILDING

//START OF KEY UPDOWN  CHECKS

		//KEY UP KEY DOWN PG UP PG DOWN CHECKS
		if (ch == KEY_DOWN) { // KEY DOWN input
			arrayit--; //decriments the base variable used to display the sndshow data on screen
			if (arrayit % numChannels == 0){
				b--;
			}
			if (b < 0) b = 0;
			if (arrayit <= 0) {// prevents going to a null negative element...
				arrayit = 0;

			}
		}
		if (ch == KEY_UP) { // KEY UP input
			arrayit++; // incriments the base variable used to display the sndshow data on screen
			if (arrayit % numChannels == 0){
				b++;}
			if (b > numSamples -1) b = numSamples -1;
			if (arrayit > numSamples * numChannels) {
				arrayit = numSamples * numChannels;
				b = arrayit;
			} // prevents going over the last element


		}


		if (ch == KEY_PPAGE) { // KEY UP input
			arrayit+=100; // incriments the base variable used to display the sndshow data on screen
			if (arrayit % numChannels == 0){
				b+=100;}
			if (b > numSamples -1) b = numSamples -1;
			if (arrayit > numSamples * numChannels) {
				arrayit = numSamples * numChannels;
				b = arrayit;
			} // prevents going over the last element
		}
			if (ch == KEY_NPAGE) { // KEY DOWN input
			arrayit-=100; //decriments the base variable used to display the sndshow data on screen
			if (arrayit % numChannels == 0){
				b-=100;
			}
			if (b < 0) b = 0;
			if (arrayit <= 0) {// prevents going to a null negative element...
				arrayit = 0;

			}

		}
		
		


		 //MARK AND BUFFER READER UPDATE! 
		if (markedFlag == 1){  
			marked = a;
		 mvprintw(rows-2, columns - 17, "Marked: %d    ",  marked); // Print the Sample that is marked....
		}else{
			marked = arrayit / numChannels;  // else print the current sample the cursor is resting on.
			if (marked >numSamples-1){ marked = numSamples-1;}
		 mvprintw(rows-2, columns - 17, "Marked: %d    ", marked);
		}



		int ddd;
		finalCount= 0;
		for (ddd = 0; ddd <numSamples*numChannels; ddd++){
			if(markedStartData[ddd] == 'n') break;
			else finalCount++;
		}

		if (finalCount!= 0){
	  	 	mvprintw(rows-1, columns - 19, "Buffered: %d    ", finalCount/numChannels);
		} else mvprintw(rows-1, columns - 19, "            ");
		//END OF BUFFERD MARKED UPDATE
		//SNDSHOW WINDOW BUILDING
		int incrimentor = 0;
		int y;
		for (y = 2; y < rows; y++) {
			if ((arrayit + incrimentor) >= numSamples * numChannels) { // IF THERE ARE NO MORE LINES IN THE FILE, PRINT A SPACE
				int x;
				for (x = 0; x < columns - 20; x++) {
					mvprintw(y, x, " ");  //prints spaces for that line;

				}
				mvprintw(y, 9, "|"); //print columns of format: |               |
				mvprintw(y, columns - 21, "|");
				incrimentor++;
			} else {
				rewind(workingFile);
				sndshowEdit(workingFile, soundVar, (columns - 20),
						(arrayit + incrimentor), y, a, b);
				incrimentor++;
			} // ELSE END
		} //Y Space for loop end
		// END OF SNDSHOW BUILDING

// rest of the getCh checks down here
		move(2, (9 + columns - 20) / 2);
		refresh();

// FINAL CHECKS FOR DISPLAY

		firstFlag = 0; // no longer first time through, so can be changed to 0 so ch can be edited.
		refresh();
		ch = getch(); // Get the Char for the next round
		
		if (ch == 'q'|| ch == 'Q') {
			break;
		}

		if (insertFlag== 1 && ch == '^'|| ch == 'v' || ch == 'V') {
			paste(workingFile, markedStartData, ch, a, b, soundVar, arrayit); // call the paste function
			editFlag = 1;

		}

		if(editFlag == 1 && ch == 's' || ch == 'S'){
			editFlag =0;
			rewind(workingFile);
			fclose(currentFile);
			currentFile = fopen(name, "w+");
				while((c=fgetc(workingFile)) !=EOF){  // builds the tempfile to edit
       				 fputc(c, currentFile);
    }

		}


		 if (markedFlag ==1 && (ch =='x' || ch == 'X') ||  (ch == 'c' || ch == 'C')){
			 catcutHelper(workingFile, soundVar, a,  b, markedStartData, ch);
			 if(ch == 'x' || ch == 'X'){
			 	editFlag = 1;
			 }
			 	insertFlag = 1;
		}   
		continue;
	} //WHILE TRUE LOOP END

//EXIT CODE

	endwin();
	printf("sndedit complete!\n");

/*int ddd;
		for (ddd = 0; ddd <numSamples*numChannels; ddd++){
			if(markedStartData[ddd] == 'n') break;
			else printf("%d\n", markedStartData[ddd]);
		}
*/
	return;
}


int paste(FILE* inputFile, int markedStartData[], int ch, int a, int b, AUDIO* sound, int arrayit){
	FILE *buffer = fopen("buffer", "w+");
	rewind(inputFile);
	AUDIO *values = malloc(sizeof(AUDIO));   
	keyValueFinder229(inputFile, values);
	rewind(inputFile);
	int sampleRate = values->SampleRate;
	int numChannels = values->numChannels;
	int bitDepth = values->numBitDepth;
	int numSamples = values->numSamples;
	fprintf(buffer, "CS229\n");
    fprintf(buffer, "SampleRate %d\n", sampleRate );
	fprintf(buffer, "Channels %d\n",  numChannels);
	fprintf(buffer, "BitDepth %d\n",  bitDepth);
	fprintf(buffer, "StartData\n");
	//keyValueFinder229(inputFile, SoundVar);
	//rewind(inputFile);
	char keyWord[10];
	char line[128];
	int keyWordVal;
	int arraySize = 0;
	while( fgets(line, sizeof(line), inputFile) != NULL){
		sscanf(line, "%s %d", keyWord, &keyWordVal); 
 		if(keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] =='a' && keyWord[3] == 'r' && keyWord[4] =='t'){
			break;
		
		
		}
	}

	if(ch == '^'){
		if (arrayit == 0){  // if the cursor is on the inital value of the file.. cant go to a negative position, so write values now.
			int channelCount = 1; 
			int index = 0;
			for(index = 0; index < numChannels*numSamples; index++){
				if(markedStartData[index] == 'n'){ break; }
				else{
						fprintf(buffer, "%d ", markedStartData[index]);
						
						if(channelCount % numChannels == 0){
							fprintf(buffer, "\n");
					}
					channelCount++;
				}
			}
			while( fgets(line, sizeof(line), inputFile) != NULL){ // after values stored are written, write rest of file file as normal
				fprintf(buffer, "%s", line);
			}
		}

		else{
			int sampleCount = 0;
			while( fgets(line, sizeof(line), inputFile) != NULL){ // after values stored are written, write rest of file file as normal
				fprintf(buffer, "%s", line);
					if(sampleCount == (arrayit/numChannels)-1){ //if the samplecount equals the value before the array iterator
						int channelCount = 1; 
						int index = 0;
						for(index = 0; index < numChannels*numSamples; index++){
							if(markedStartData[index] == 'n'){ break; }
							else{
								fprintf(buffer, "%d ", markedStartData[index]);
						
								if(channelCount % numChannels == 0){
									fprintf(buffer, "\n");
								}
								channelCount++;
							}
						}

					}
				
				sampleCount++;
			}






		}


	}

	if(ch =='v'|| ch == ('V')){
		int sampleCount = 0;
		while( fgets(line, sizeof(line), inputFile) != NULL){ // after values stored are written, write rest of file file as normal
				fprintf(buffer, "%s", line);
					if(sampleCount == (arrayit/numChannels)){ //if the samplecount equals the value before the array iterator
						int channelCount = 1; 
						int index = 0;
						for(index = 0; index < numChannels*numSamples; index++){
							if(markedStartData[index] == 'n'){ break; }
							else{
								fprintf(buffer, "%d ", markedStartData[index]);
						
								if(channelCount % numChannels == 0){
									fprintf(buffer, "\n");
								}
								channelCount++;
							}
						}

					}
				
				sampleCount++;
			}

	}
	

	rewind(buffer);
	int c;
	 FILE* workingFile = fopen("workingfile", "w+");
	 rewind(buffer);
		while((c=fgetc(buffer)) !=EOF){  // builds the tempfile to edit
        fputc(c, workingFile);
    }
    rewind(workingFile);	
    keyValueFinder229(workingFile, sound);
    rewind(workingFile);
	

	/*int f = 0; //WRITE THE FILE \/\/\/
	int final;

	for(final = 0; final < arraySize; final++){

	fprintf(outputFile, "%d ", dataStore[final]);
	f++;
	if (f%(SoundVar->numChannels)==0){
	fprintf(outputFile, "\n");
	*/ //}
}



void catcutHelper(FILE* inputFile, AUDIO * sound, int a, int b, int markedStartData[], int ch){
	int numChannels = sound->numChannels;
	int numSamples = sound->numSamples;
	int bitDepth = sound->numBitDepth;
	int channels = sound->numChannels;
	int indexCount = 0;
	int val;
	char keyWord[10];
	char line[128];
	int keyWordVal;
	rewind(inputFile);
	if(ch == 'c' || ch == 'C' || ch == 'x' || ch == 'X'){ // if the user inputted c for copy or x for cut do this.
	
	while (fgets(line, sizeof(line), inputFile) != NULL) {
		
		sscanf(line, "%s %d", keyWord, &keyWordVal);
		if (keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] == 'a'
				&& keyWord[3] == 'r' && keyWord[4] == 't') {
			break;

		}
	}
		int arrayIterator = 0;
	while (!feof(inputFile)) { //cycle through the file until the value we want printed is built
 		
		fscanf(inputFile, "%d", &val);
		if(a == b){
 			if (indexCount/numChannels >=a && indexCount/numChannels <a+1){ // if the index formatted as a sample number is greater than a and less than b put the value in the array.
 				markedStartData[arrayIterator]	= val;
 				arrayIterator++; // increases only when the array stores a value.
 			}

 		}

 		if(a < b){
 			if (indexCount/numChannels >=a && indexCount/numChannels <=b){ // if the index formatted as a sample number is greater than a and less than b put the value in the array.
 				markedStartData[arrayIterator]	= val;
 				arrayIterator++; // increases only when the array stores a value.
 			}


 		 }
 			if(a > b){
 			if (indexCount/numChannels >=b && indexCount/numChannels <=a){ // if the index formatted as a sample number is greater than a and less than b put the value in the array.
 				markedStartData[arrayIterator]	= val;
 				arrayIterator++; // increases only when the array stores a value.
 			}
 		}
 			indexCount++;
 		}
		

		if(arrayIterator!=numSamples * numChannels){  // the thought process is, on every time a call to copy or cut 
			int i;					//is made, the user may not copy as many values as they did the
														// time before, leading to data remaining from previous uses. 
														//this will prevent that
			

			for(i=arrayIterator;i<1000000; i++){
				markedStartData[i] = 'n'; // will make sure all former data copied into the array is overwritten


			}
		}
	}

  /*


  	Copied Code from sndcut. it is glorious. 
  */

	if(ch =='x' || ch == 'X'){  // if the user inputted c for paste, do this additional block of code
		FILE *buffer = fopen("buffer", "w+");
	rewind(inputFile);
	AUDIO *values = malloc(sizeof(AUDIO));   
	keyValueFinder229(inputFile, values);
	rewind(inputFile);
	int sampleRate = values->SampleRate;
	int numChannels = values->numChannels;
	int bitDepth = values->numBitDepth;
	fprintf(buffer, "CS229\n");
    fprintf(buffer, "SampleRate %d\n", sampleRate );
	fprintf(buffer, "Channels %d\n",  numChannels);
	fprintf(buffer, "BitDepth %d\n",  bitDepth);
	fprintf(buffer, "StartData\n");
	int arraySize = 0;

	while (fgets(line, sizeof(line), inputFile) != NULL) {
	
		sscanf(line, "%s %d\n", keyWord, &keyWordVal);
		if (keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] == 'a'
				&& keyWord[3] == 'r' && keyWord[4] == 't') {
			break;

		}
	}
	int lineCount =0;
	while (fgets(line, sizeof(line), inputFile) != NULL) {
		if (a < b){
			if(lineCount < a || lineCount >b ){
				fprintf(buffer, "%s", line);
				lineCount++;
				continue;
			}
		}

		if(a == b){
			if(lineCount < a || lineCount >b ){
				fprintf(buffer, "%s", line);
				lineCount++;
				continue;
			}
		}

		if(a > b){
			if(lineCount < b || lineCount >a ){
				fprintf(buffer, "%s", line);
				lineCount++;
				continue;
			}
		}
			lineCount++;
			continue;
	}

	rewind(buffer);
	int c;
	 FILE* workingFile = fopen("workingfile", "w+");
	 rewind(buffer);
		while((c=fgetc(buffer)) !=EOF){  // builds the tempfile to edit
        fputc(c, workingFile);
    }
    rewind(workingFile);	
	}

				
	return;   //Else return and end this function call
}







int gotoHelper(int rows, int columns, AUDIO * soundVar) {
	int retVal = 0;
	int ch = 0;
	mvprintw(19, columns - 17, "                ");
	mvprintw(19, columns - 17, " goto: %d", retVal);
	while (1) { //while
		refresh();
		ch = getch();
		if (ch == '\n')
			break;
		ch = ch - '0';
		retVal = retVal * 10 + ch;
		mvprintw(19, columns - 17, " goto: %d", retVal);

	}
	if (retVal >= 0 && retVal < soundVar->numSamples) {
		return retVal;
	}

	return -1; // means an invalid number has been entered for goto

}

int sndshowEdit(FILE *inputFile, AUDIO *sound, int width, int index, int y, int a, int b ) {
	double dwidth = width * 1.0;
	int numChannels = sound->numChannels;
	int numSamples = sound->numSamples;
	int bitDepth = sound->numBitDepth;
	int channels = sound->numChannels;
	double outputSpace = (dwidth - 9 - 3) / 2.0; //output space for each side
	double conVal = bitDepth - 1.0;
	double maxSampleValue = pow(2.0, conVal);

	int indexCount = 0;
	int val;
	char keyWord[10];
	char line[128];
	while (fgets(line, sizeof(line), inputFile) != NULL) {
		int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal);
		if (keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] == 'a'
				&& keyWord[3] == 'r' && keyWord[4] == 't') {
			break;

		}
	}

	while (!feof(inputFile)) { //cycle through the file until the value we want printed is built
		if (index % channels == 0 && indexCount == index) {
			mvprintw(y, 0, "%9d", index / channels);
		}  // print the samplenumber if it is the proper channel
		else {
			if (indexCount == index) {
				mvprintw(y, 0, "         ");
			}
		} //nine spaces
		fscanf(inputFile, "%d", &val);
		double dval = val - 1.0;
		double count;
		double decimals;
		double numDashToPrint = outputSpace * (dval / maxSampleValue);
		decimals = modf(numDashToPrint, &count);
		if (decimals < 0 && decimals <= -.43) {
			count--;
		}

		if (decimals > 0 && decimals >= .43) {
			count++;
		}

		if (count == -0) {
			count = 0;
		}
		//printf("number of dashes: %lf\n", count);

		int size = dwidth - 9.0; //                       \/ see here
		//printf("size of array is: %d\n", size);
		char retVal[size + 1]; //Taking into account you have already printed the first 9 digits.
		int c;
		for (c = 0; c < size; c++) {
			retVal[c] = ' ';

		}
		retVal[0] = '|'; //print first position
		retVal[(size - 1)] = '|'; // print last
		retVal[(size / 2)] = '|'; // print middle
		retVal[size] = 0;
		int see;
		count = (int) count;
		int absCount = abs(count); //absolute value of count for array looping

		if (count <= 0) {

			for (see = ((size / 2) - 1); see > ((outputSpace) - absCount);
					see--) {

				retVal[see] = '-';
			}

		}
		if (count > 0) {
			for (see = ((size / 2) + 1); see <= ((size / 2) + absCount);
					see++) {
				retVal[see] = '-';

			}

		}

		if (indexCount == index) {

			if(a != -1 && b != -1){ // This isn't clear at all, so let me: This entire block of code checks
				int i;              // to see if marked has been pressed and  reverse colors the text accordingly
			  if (a == b){
			  	for(i = a*numChannels; i < (((b+1)*numChannels)); i++){
			  		if (i == index){ attron(A_REVERSE);}
			  	}

			  }
			  if (a < b){
				for(i = a*numChannels; i < (((b+1)*numChannels)); i++){
			  		if (i == index){ attron(A_REVERSE);}
			  	}
			  }

			  if (a > b){
			    for(i = b *numChannels; i <(((a+1)*numChannels)); i++){
			    	 if (i == index){ attron(A_REVERSE);}
			    }
			  }

			}

			mvprintw(y, 9, "%s", retVal);
			attroff(A_REVERSE);
			return indexCount;
		}
		indexCount++;
	}

}
