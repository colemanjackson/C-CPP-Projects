#include "InfoHolder.h"
#include "WireInfo.h"
#include "CellInfo.h"
#include "InfoParser.h"
#include "ParserUtil.h"
#include "GenerationHelperMethods.h"
#include "DisplayHelperMethods.h"
#include <fstream>


/*
* 
*Do not judge me. 
*/
int updateSwitchInformation(InfoHolder &h, WireInfo& wireInfo, CellInfo& cellInfo, int argc,
		char* argv[], bool& formatFlag, int& generation, bool& visualFlag, int howToProceed) {
	int low;
	int high;
	int check;
	for (int i = 1; i < argc; i++) {
		string charCheck(argv[i]);

		if (charCheck.compare("-f") == 0) {
			formatFlag = true;
		}

		if (charCheck.compare("-g") == 0 && i < argc - 1) {
			sscanf(argv[i + 1], "%d", &generation);
		}

		if (charCheck.compare("-tx") == 0) {
			if (!(i < argc - 1)) {
				cerr << "Error: Bad Argument Format\n";
				return 1;
			}
			check = sscanf(argv[i + 1], "%d..%d", &low, &high);
			if (check != 2) {

				cerr << "Error: Check arguments and try again.\n";
				return 1;
			}

			if(howToProceed == 1){
				h.setxTerrainLowerBound(low);
				h.setxTerrainHigherBound(high);
				h.updateWindowXSet(true);
			}

			if(howToProceed == 2){
				wireInfo.setxTerrain(low, high);
			}

			if(howToProceed == 3){
				cellInfo.setxTerrain(low, high);
			}
		}
		if (charCheck.compare("-ty") == 0) {

			if (!(i < argc - 1)) {
				cerr << "Error: Bad Argument Format\n";
				return 1;
			}
			check = sscanf(argv[i + 1], "%d..%d", &low, &high);
			if (check != 2) {
				cerr << "Error: Check arguments and try again.\n";
				return 1;
			}

			if( howToProceed == 1){
				h.setyTerrainLowerBound(low);
				h.setyTerrainHigherBound(high);
				h.updateWindowYSet(true);
			}

			if(howToProceed == 2){
				wireInfo.setyTerrain(low, high);
			}

			if (howToProceed == 3){
				cellInfo.setyTerrain(low, high);
			}
		}

		if (charCheck.compare("-v") == 0) {
			visualFlag = true;

		}

		if (charCheck.compare("-wx") == 0) {
			if (!(i < argc - 1)) {
				cerr << "Error: Bad Argument Format\n";
				return 1;
			}
			check = sscanf(argv[i + 1], "%d..%d", &low, &high);
			if (check != 2) {
				cerr << "Error: Check arguments and try again.\n";
				return 1;
			}


			if (howToProceed == 1){
				h.setxWindowLowerBound(low);
				h.setxWindowHigherBound(high);
				h.updateWindowXSet(true);
			}

			if (howToProceed == 2){
				wireInfo.setxWindow(low, high);
			}

			if( howToProceed == 3){
				cellInfo.setxWindow(low, high);
			}

		}
		if (charCheck.compare("-wy") == 0) {
			if (!(i < argc - 1)) {
				cerr << "Error: Bad Argument Format\n";
				return 1;
			}
			check = sscanf(argv[i + 1], "%d..%d", &low, &high);
			if (check != 2) {
				cerr << "Error: Check arguments and try again.\n";
				return 1;
			}
			if (howToProceed == 1){
				h.setyWindowLowerBound(low);
				h.setyWindowHigherBound(high);
				h.updateWindowYSet(true);
			}

			if (howToProceed == 2){
				wireInfo.setyWindow(low, high);
			}

			if( howToProceed == 3){
				cellInfo.setyWindow(low, high);
			}
		} else {
			continue;
		}

	}
}

//The main method. It's pretty calculation heavy. 
int main(int argc, char* argv[]) {
	int generation = 0;
	bool formatFlag = false;
	bool visualFlag = false;
	InfoHolder lifeInfo;
	WireInfo wireInfo;
	CellInfo cellInfo;
	fstream myfile;
	int howToProceed;

	bool skipNextVal = false;

//SEARCH FOR FILE INPUT OR USE STDIN DEPENDING ON FILESTREAM, IGNORE OTHER THINGS
	for (int i = 1; i < argc; i++) {
		string charCheck(argv[i]);

		if (skipNextVal == true) {
			cout << " skipping value: " << i << '\n';
			skipNextVal = false;
			continue;
		}
		if (charCheck.compare("-f") == 0) {
			continue;
		}
		if (charCheck.compare("-g") == 0) {
			skipNextVal = true;
			continue;
		}
		if (charCheck.compare("-h") == 0) {
			cerr << "Life by Coleman Jackson\n";
			cerr
					<< "This program produces a visual representation of the game of life\n";
			cerr
					<< " Switches are as follows: -f Output should be in the same file format as Appendix A.\n ";
			cerr
					<< "-g n Specify the desired generation number. If omitted, the default should be n = 0.\n";
			cerr
					<< "-h Display a help screen that describes the program.\n-tx l..h Set the x range of the terrain; overrides values specified in the input file.\n-ty l..h Set the y range of the terrain overrides values specified in the input file. \n-v Output should be visual: an ASCII display of the terrain with appropriate characters for the dead and alive cells \n-wx l..h Set the x range of the output window; otherwise this defaults to the x range of the terrain.\n-wy l..h Set the y range of the output window; otherwise this defaults to the y range of the terrain. \n";

			return 0;

		}
		if (charCheck.compare("-tx") == 0) {
			skipNextVal = true;
			continue;
		}
		if (charCheck.compare("-ty") == 0) {
			skipNextVal = true;
			continue;
		}
		if (charCheck.compare("-v") == 0) {
			continue;
		}
		if (charCheck.compare("-wx") == 0) {
			skipNextVal = true;
			continue;
		}
		if (charCheck.compare("-wy") == 0) {
			skipNextVal = true;
			continue;
		} else {
			cerr << "----Opening file given at argument # " << i << "----\n";
			myfile.open(argv[i]);
		}
		bool doNotContinue = is_empty(myfile);
		if (doNotContinue) {
			cerr << "Error: Bad File\n";
			return 1;
		}

	}
	//GET INFO FROM FILE IF POSSIBLE
	if (!myfile.is_open()) {

		fileStripper(lifeInfo, cin);
	} else {
		fileStripper(lifeInfo, myfile);
	}
	string line;
	fstream readRaw;
	readRaw.open("rawdata");
	try {
		howToProceed = fileParser(lifeInfo, wireInfo, cellInfo, readRaw);
		readRaw.close();
		myfile.close();
	}

	catch (int e) {
		cerr << "Error, Bad File given at howToProceed(), in lifemain. program terminating\n";
		return 1;
	}

//OVERRIDE ANYTHING THAT NEEDS OVERRIDING BASED ON SWITCHES
	int error = updateSwitchInformation(lifeInfo, wireInfo, cellInfo, argc, argv,
			formatFlag, generation, visualFlag, howToProceed);
	if (error == 1) {
		cerr << "Error Updating switch information, check switches and try again \n";
		return 1;
	} // screw it. I miss C and Im tired.



	if (!formatFlag && !visualFlag) {
			cerr << "Error, Please specify format of output using -f or -v\n";
			return 1;
		}


	//1 is Life, 2 is WW, 3 is ELE CA
	if (howToProceed == 1) {

		//Check to make sure format is set.
		

		//The board which will be updated and printed
		vector<vector<bool> > lifeBoard;
		lifeBoard = getInitialVector(lifeInfo); // gets the initial vector of 0th generation to run generations against
		for (int i = 0; i < generation; i++) {
			lifeBoard = god(lifeBoard, lifeInfo);
		}
		int yLow = lifeInfo.getyTerrainLowerBound();
		int yHigh = lifeInfo.getyTerrainHigherBound();
		int xLow = lifeInfo.getxTerrainLowerBound();
		int xHigh = lifeInfo.getxTerrainHigherBound();
		if (lifeInfo.isWindowYSet() == false) {
			lifeInfo.setyWindowLowerBound(yLow);
			lifeInfo.setyWindowHigherBound(yHigh);
		}

		if (lifeInfo.isWindowXSet() == false) {
			lifeInfo.setxWindowLowerBound(xLow);
			lifeInfo.setxWindowHigherBound(xHigh);
		}

		try {

			if (visualFlag) {
				visualOutput(lifeBoard, lifeInfo);
				return 0;
			}

			if (formatFlag) {
				fileOutput(lifeBoard, lifeInfo);
				return 0;
			}
		} catch (int e) {
			cerr << "Error in printing file. Program Terminating\n";
			return 1;
		}

	}


	if (howToProceed == 2){
		vector<vector<char> > wireWorldBoard;

		try {

			wireWorldBoard = getInitialWWVector(wireInfo);

			for (int i = 0; i < generation; i++) {
				wireWorldBoard = godWW(wireInfo, wireWorldBoard);
			}

		
			if (visualFlag) {
				cerr << "YOU GET TO VISUAL\n\n";
				visualOutputWW(wireWorldBoard, wireInfo);
				return 0;
			}

			if (formatFlag) {
				fileOutputWW(wireWorldBoard, wireInfo);
				return 0;
			}
		} catch (int e) {
			cerr << "Error in printing file. Program Terminating\n";
			return 1;
		}
	

	}




	if (howToProceed == 3){
		vector< vector<bool> > cellAutoBoard;
		
		try{
			 cellAutoBoard = getInitialCellVector(cellInfo);
			for (int i = 0; i <  generation; i++){
				 cellAutoBoard = godCell(cellAutoBoard, cellInfo);

			}


			if (formatFlag){
				fileOutputCell(cellAutoBoard, cellInfo);
				return 0;

			}

			if (visualFlag){
				visualOutputCell(cellAutoBoard, cellInfo);
				return 0;
			}

		} 
		catch(int e){
			cerr << "Error in updating or printing Elementary File, Program Terminating\n";
			return 1;
		}
	}
}

