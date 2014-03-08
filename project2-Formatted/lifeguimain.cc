#include <QApplication>
#include <QLabel>
#include <fstream>
#include "InfoHolder.h"
#include "InfoParser.h"
#include "ParserUtil.h"
#include "iconeditor.h"
#include "DisplayHelperMethods.h"
#include "OutputHelperMethods.h"
//#include "LifeGUI.h"
using namespace std;

//The main method. It's pretty calculation heavy. 
int main(int argc, char* argv[]) {
	int generation = 0;
	bool formatFlag = false;
	bool visualFlag = false;
	InfoHolder h;
	WireInfo wireInfo;
	CellInfo cellInfo;
	fstream myfile;

	bool skipNextVal = false;

//SEARCH FOR FILE INPUT OR USE STDIN DEPENDING ON FILESTREAM, IGNORE OTHER THINGS
	for (int i = 1; i < argc; i++) {
		string charCheck(argv[i]);

		if (skipNextVal == true) {
			cout << " skipping value: " << i << '\n';
			skipNextVal = false;
			continue;
		}
		if (charCheck.compare("-s") == 0) {
			skipNextVal = false;
			continue;
		}
		if (charCheck.compare("-g") == 0) {
			skipNextVal = true;
			continue;
		}
		if (charCheck.compare("-h") == 0) {
			cerr << "Life-GUI by Coleman Jackson\n";
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

		fileStripper(h, cin);
	} else {
		fileStripper(h, myfile);
	}
	string line;
	fstream readRaw;
	readRaw.open("rawdata");
	try {
		fileParser(h, wireInfo, cellInfo, readRaw);
		readRaw.close();
		myfile.close();
	}

	catch (int e) {
		return 1;
	}

//OVERRIDE ANYTHING THAT NEEDS OVERRIDING BASED ON SWITCHES
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
			cout << "check hit!\n";
			if (!(i < argc - 1)) {
				cerr << "Error: Bad Argument Format\n";
				return 1;
			}
			check = sscanf(argv[i + 1], "%d..%d", &low, &high);
			if (check != 2) {

				cerr << "Error: Check arguments and try again.\n";
				return 1;
			}
			h.setxTerrainLowerBound(low);
			h.setxTerrainHigherBound(low);
			h.updateWindowXSet(true);
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
			h.setyTerrainLowerBound(low);
			h.setyTerrainHigherBound(high);
			h.updateWindowYSet(true);
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
			h.setxWindowLowerBound(low);
			h.setxWindowHigherBound(high);
			h.updateWindowXSet(true);

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
			h.setyWindowLowerBound(low);
			h.setyWindowHigherBound(high);
			h.updateWindowYSet(true);
		} else {
			continue;
		}

	}

//The board which will be updated and printed
	vector<vector<bool> > lifeBoard;
	lifeBoard = getInitialVector(h); // gets the initial vector of 0th generation to run generations against
	for (int i = 0; i < generation; i++) {

		lifeBoard = god(lifeBoard, h);

	}

	cerr << "FINAL OUTPUT\n\n";
	int yLow = h.getyTerrainLowerBound();
	int yHigh = h.getyTerrainHigherBound();
	int xLow = h.getxTerrainLowerBound();
	int xHigh = h.getxTerrainHigherBound();
	if (h.isWindowYSet() == false) {
		h.setyWindowLowerBound(yLow);
		h.setyWindowHigherBound(yHigh);
	}

	if (h.isWindowXSet() == false) {
		h.setxWindowLowerBound(xLow);
		h.setxWindowHigherBound(xHigh);
	}

	QApplication app(argc, argv);
	IconEditor *editor = new IconEditor(2, NULL);
	editor->show();
	return app.exec();

}

