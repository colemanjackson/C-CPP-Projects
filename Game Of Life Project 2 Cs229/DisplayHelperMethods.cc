#include "DisplayHelperMethods.h"


int visualOutput(vector<vector<bool> > lifeBoard, InfoHolder &info) {
	int yLow = info.getyTerrainLowerBound();
	int yHigh = info.getyTerrainHigherBound();
	int xLow = info.getxTerrainLowerBound();
	int xHigh = info.getxTerrainHigherBound();
	char aliveChar = info.getAliveChars();
	char deadChar = info.getDeadChars();
	int winyLow = info.getyWindowLowerBound();
	int winyHigh = info.getyWindowHigherBound();
	int winxLow = info.getxWindowLowerBound();
	int winxHigh = info.getxWindowHigherBound();

	if (info.isWindowXSet() == false && info.isWindowYSet() == false) {
		for (int y = yHigh; y >= yLow; y--) {
			for (int x = xLow; x <= xHigh; x++) {

				if (lifeBoard[y - yLow][x - xLow] == true) {
					cout << aliveChar;
					continue;
				}

				else if (lifeBoard[y - yLow][x - xLow] == false) {
					cout << deadChar;
					continue;
				}

				else
					throw 20; // Error somehow and someway, throw error and terminated
			}
			cout << '\n';
		}
		return 0;
	}

	for (int y = winyHigh; y >= winyLow; y--) {
		for (int x = winxLow; x <= winxHigh; x++) {
			if ((x >= xLow && x <= xHigh) && (y >= yLow && y <= yHigh)) {
				if (lifeBoard[y - yLow][x - xLow] == true) {
					cout << aliveChar;
					continue;
				} else if (lifeBoard[y - yLow][x - xLow] == false) {
					cout << deadChar;
					continue;
				}

			}
			cout << deadChar;
		}
		cout << '\n';
	}

}

int visualOutputWW(vector< vector<char> > terrain, WireInfo &info){
	WireInfo::Terrain terrainInfo = info.getTerrain();
	int xlow = terrainInfo.xlower;
	int xhigh = terrainInfo.xupper;
	int ylow = terrainInfo.ylower;
	int yhigh = terrainInfo.yupper;
	int xLow = terrainInfo.xlower; //MAINTIAN OLD CODE... GAHHH
	int xHigh = terrainInfo.xupper;
	int yLow = terrainInfo.ylower;
	int yHigh = terrainInfo.yupper;
	WireInfo::Terrain window = info.getWindow();
	int winyHigh = window.yupper;
	int winyLow = window.ylower;
	int winxHigh = window.xupper;
	int winxLow = window.xlower;
	WireInfo::Chars chars = info.getChars();

	char wire = chars.Wire;
	char head = chars.Head;
	char empty = chars.Empty;
	char tail = chars.Tail;
	cerr << "FINAL OUTPUT: \n\n";
	//If the window values are set, then we need to process the view, else just display it to terrain
	if(!(window.xlower == -1 && window.xupper == -1 && window.ylower == -1 && window.yupper == -1)){

		for (int y = winyHigh; y >= winyLow; y--) {
			for (int x = winxLow; x <= winxHigh; x++) {
				if ((x >= xLow && x <= xHigh) && (y >= yLow && y <= yHigh)) {
					if (terrain[x - xLow][y - yLow] == 0) {
						cout << empty;
					}	

					if (terrain[x - xLow][y - yLow] == 1) {
						cout << head;
					}
					if (terrain[x - xLow][y - yLow] == 2) {
						cout << tail;
					}
					if (terrain[x - xLow][y - yLow] == 3) {
						cout << wire;
					}

				}
			}
			cout << '\n';
		}
		return 0;
	}

	for(int y = yhigh; y >= ylow ; y--){
		for(int x = xlow; x <= xhigh; x++){
			if (terrain[x - xlow][y - ylow] == 0){
				cout << empty;
			}

			if (terrain[x - xlow][y - ylow] == 1){
				cout << head;
			}
			if (terrain[x - xlow][y - ylow] == 2){
				cout << tail;
			}
			if (terrain[x - xlow][y - ylow] == 3){
				cout << wire;
			}
		}

		cout << '\n';
	}
	return 0;
}

int fileOutputWW(vector< vector<char> > terrain, WireInfo &info){
	WireInfo::Terrain terrainInfo = info.getTerrain();
	int xLow = terrainInfo.xlower;
	int xHigh = terrainInfo.xupper;
	int yLow = terrainInfo.ylower;
	int yHigh = terrainInfo.yupper;
	WireInfo::Colors emptyColors = info.getEmptyColors();
	WireInfo::Colors headColors = info.getHeadColors();
	WireInfo::Colors tailColors = info.getTailColors();
	WireInfo::Colors wireColors = info.getWireColors();
	WireInfo::Chars chars = info.getChars();
	WireInfo::Terrain window = info.getWindow();
	string name = info.getName();

	cout << '\n';
	cout << '\n';
	cout << '\n';
	cerr << "FINAL OUTPUT: ";
	cout << '\n';
	cout << '\n';
	cout << "WireWorld = { \n";

	//if a name has been given.... print it
	if (name != "Untitled"){
		cout << "Name = " << '"'<< name <<'"'<<';' << '\n'; 
	}


	//If window has been set.... print it
	if (!(window.xlower == -1 && window.xupper == -1 && window.ylower == -1 && window.yupper == -1)){
		cout << "Window = {\n" << '\n';
		cout << "Xrange = " << window.xlower << ".." << window.xupper << "; Yrange = " << window.ylower << ".." << window.yupper << ";\n};\n";
	}


	//TERRAIN
	cout << "Terrain = { \n";
	cout << "Xrange = " << xLow <<  ".." << xHigh << "; ";
	cout << "YRange =" << yLow << ".." << yHigh << ";\n";
	cout << "};\n";

	//CHARS
	cout << "Chars = {\n";
	cout << "Empty = " << chars.Empty << "; Head = " << chars.Head << "; Tail = " << chars.Tail << "; Wire = " << chars.Wire << ";\n };\n";
	//COLORS
	cout << "Colors = {\n";
	cout << "Empty =" << '(' << emptyColors.color1 << ',' << emptyColors.color2 << ',' << emptyColors.color3 << ");\n";
	cout << "Head =" << '(' << headColors.color1 << ',' << headColors.color2 << ',' << headColors.color3 << ");\n";
	cout << "Tail =" << '(' << tailColors.color1 << ',' << tailColors.color2 << ',' << tailColors.color3 << ");\n";
	cout << "Wire =" << '(' << wireColors.color1 << ',' << wireColors.color2 << ',' << wireColors.color3 << ");\n";

	cout << "};\n";



	//INITIAL
	cout << "Initial = {\n";

	int headCount = 0;
	int tailCount = 0;
	int wireCount = 0;
	for (int x = xLow - xLow; x <= xHigh - xLow ; x++) {
		for (int y = yLow - yLow; y <= yHigh - yLow + 1; y++) {
			if (terrain[x][y] == 1){
				headCount++;
			}

			if(terrain[x][y] == 2){
				tailCount++;
			}

			if(terrain[x][y] == 3){
				wireCount++;
			}
		}
	}
	
	if(headCount != 0){
		int secondCount = 0;
		cout << "Head = ";
		for (int x = xLow - xLow; x < xHigh - xLow; x++) {
			for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {
			

				if (terrain[x][y] == 1) {

					cout << '(' << (x + xLow) << ',' << (y + yLow) << ')';
					secondCount++;
					if (secondCount == headCount) {
						cout << ';';
					} else
						cout << ',';
				}
			}

		}
		cout << '\n';

	}


	if(wireCount != 0){
		int secondCount = 0;
		cout << "Tail = ";
		for (int x = xLow - xLow; x <= xHigh - xLow; x++) {
			for (int y = yLow - yLow; y <= yHigh - yLow + 1; y++) {
			

				if (terrain[x][y] == 2) {

					cout << '(' << (x + xLow) << ',' << (y + yLow) << ')';
					secondCount++;
					if (secondCount == tailCount) {
						cout << ';';
					} else
						cout << ',';
				}
			}

		}
		cout << '\n';
	}


	if(tailCount != 0){
		int secondCount = 0;
		cout << "Wire = ";
		for (int x = xLow - xLow; x < xHigh - xLow ; x++) {
			for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {
			

				if (terrain[x][y] == 3) {

					cout << '(' << (x + xLow) << ',' << (y + yLow) << ')';
					secondCount++;
					if (secondCount == wireCount) {
						cout << ';';
					} else
						cout << ',';
				}
			}

		}

			cout << '\n';
			cout << '\n';
			cout << '\n';
		
	}

	cout << "};\n";
	cout << "};\n";
}


int fileOutput(vector<vector<bool> > terrain, InfoHolder &info) {
	vector<int> initialX;
	vector<int> initialY;
	int yLow = info.getyTerrainLowerBound();
	int yHigh = info.getyTerrainHigherBound();
	int xLow = info.getxTerrainLowerBound();
	int xHigh = info.getxTerrainHigherBound();

	cerr << "\n\n\n\n\n\n\n";
	cout << "Life = \n";
	cout << "{\n";

	if (info.isNameSet() == true) {
		string name = info.getName();
		cout << "Name = " << '"' << name << '"' << ';' << '\n';
	}

	if (info.isWindowXSet() || info.isWindowYSet()) {
		cout << "Window = {\n";
		if (info.isWindowXSet()) {
			cout << "   Xrange =" << info.getxWindowLowerBound() << ".."
					<< info.getxWindowHigherBound() << '\n';
		}

		if (info.isWindowYSet()) {
			cout << "   Yrange =" << info.getyWindowLowerBound() << ".."
					<< info.getyWindowHigherBound() << '\n';
		}

		cout << "\n};\n";
	}

	//COLORS
	cout << "Colors = {\n";
	cout << "   Alive = (" << info.getAliveColors1() << ','
			<< info.getAliveColors2() << ',' << info.getAliveColors3()
			<< ");\n";
	cout << "   Dead = (" << info.getDeadColors1() << ','
			<< info.getDeadColors2() << ',' << info.getDeadColors3() << ");\n";
	cout << "};\n";

//CHARS
	cout << "Chars = {\n";
	cout << "   Alive = " << info.getAliveChars() << ";\n";
	cout << "   Dead = " << info.getDeadChars() << ";\n";
	cout << "};\n";

//TERRAIN
	cout << "Terrain  {\n";
	cout << "   Xrange = " << info.getxTerrainLowerBound() << ".."
			<< info.getxTerrainHigherBound() << '\n';
	cout << "   Yrange = " << info.getyTerrainLowerBound() << ".."
			<< info.getyTerrainHigherBound() << '\n';
	cout << "};\n";

	int COUNT = 0;
	int seconCount = 0;
//Initial
	cout << "Initial = {\n";
	cout << "Alive = ";
	for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {
		for (int x = xLow - xLow; x < xHigh - xLow + 1; x++) {
			if (terrain[y][x] == 1) {
				COUNT++;
				//	cout << '(' << (x+xLow) << ','<< (y+yLow) << ')';

			}
		}
	}
	for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {
		for (int x = xLow - xLow; x < xHigh - xLow + 1; x++) {
			if (terrain[y][x] == 1) {

				cout << '(' << (x + xLow) << ',' << (y + yLow) << ')';
				seconCount++;
				if (seconCount == COUNT) {
					cout << ';';
				} else
					cout << ',';
			}
		}
	}

	cout << "\n};";
	cout << "\n};\n";
}


int fileOutputCell(vector<vector<bool> > terrain, CellInfo &info){
 CellInfo::Terrain terrainInfo = info.getTerrain();
	int xLow = terrainInfo.xlower;
	int xHigh = terrainInfo.xupper;
	int yLow = terrainInfo.ylower;
	int yHigh = terrainInfo.yupper;
	CellInfo::Colors oneColors = info.getocColors();
	CellInfo::Colors zeroColors = info.getzcColors();
	CellInfo::Chars chars = info.getChars();
	CellInfo::Terrain window = info.getWindow();
	string name = info.getName();

	cout << '\n';
	cout << '\n';
	cout << '\n';
	cerr << "FINAL OUTPUT: ";
	cout << '\n';
	cout << '\n';
	cout << "Elementary = { \n";

	//if a name has been given.... print it
	if (name != "Untitled"){
		cout << "Name = " << '"'<< name <<'"'<<';' << '\n'; 
	}

	cout << "Rule = " << info.getRule() << ";\n"; 


	//If window has been set.... print it
	if (!(window.xlower == -1 && window.xupper == -1 && window.ylower == -1 && window.yupper == -1)){
		cout << "Window = {\n" << '\n';
		cout << "Xrange = " << window.xlower << ".." << window.xupper << "; Yrange = " << window.ylower << ".." << window.yupper << ";\n};\n";
	}


	//TERRAIN
	cout << "Terrain = { \n";
	cout << "Xrange = " << xLow <<  ".." << xHigh << "; ";
	cout << "YRange =" << yLow << ".." << yHigh << ";\n";
	cout << "};\n";

	//CHARS
	cout << "Chars = {\n";
	cout << "Zero = " << chars.Zero << "; One = " << chars.One << ";\n };\n";
	//COLORS
	cout << "Colors = {\n";
	cout << "Zero =" << '(' << oneColors.color1 << ',' << oneColors.color2 << ',' << oneColors.color3 << ");\n";
	cout << "One =" << '(' << zeroColors.color1 << ',' << zeroColors.color2 << ',' << zeroColors.color3 << ");\n";
	cout << "};\n";



	//INITIAL
	cout << "Initial = {\n";

	int oneCount = 0;
	for (int x = xLow - xLow; x <= xHigh - xLow ; x++) {
		for (int y = yLow - yLow; y <= yHigh - yLow; y++) {
			if (terrain[x][y] == true){
				oneCount++;
			}
			
		}
	}
	
	
		int secondCount = 0;
		cout << "One = ";
		for (int x = xLow - xLow; x < xHigh - xLow; x++) {
			for (int y = yLow - yLow; y < yHigh - yLow; y++) {
			

				if (terrain[x][y] == true) {

					cout << '(' << (x) << ',' << (y) << ')';
					secondCount++;
					if (secondCount == oneCount) {
						cout << ';';
					} else
						cout << ',';
				}
			}

		}
		cout << "\n};";
	cout << "\n};\n";
}
int visualOutputCell(vector<vector<bool> > terrain, CellInfo &info){

CellInfo::Terrain terrainInfo = info.getTerrain();
	int xlow = terrainInfo.xlower;
	int xhigh = terrainInfo.xupper;
	int ylow = terrainInfo.ylower;
	int yhigh = terrainInfo.yupper;
	int xLow = terrainInfo.xlower; //MAINTIAN OLD CODE... GAHHH
	int xHigh = terrainInfo.xupper;
	int yLow = terrainInfo.ylower;
	int yHigh = terrainInfo.yupper;
	CellInfo::Terrain window = info.getWindow();
	int winyHigh = window.yupper;
	int winyLow = window.ylower;
	int winxHigh = window.xupper;
	int winxLow = window.xlower;
	CellInfo::Chars chars = info.getChars();

	char zero = chars.Zero;
	char one = chars.One;

	cerr << "FINAL OUTPUT: \n\n";
	//If the window values are set, then we need to process the view, else just display it to terrain
	if(!(window.xlower == -1 && window.xupper == -1 && window.ylower == -1 && window.yupper == -1)){

		for (int y = winyHigh; y >= winyLow; y-- ){
			for (int x = winxLow; x <= winxHigh; x++) {
				if ((x >= xLow && x <= xHigh) && (y >= yLow && y <= yHigh)) {
					if (terrain[x - xLow][y - yLow] == true) {
						cout << one;
					}	

					if (terrain[x - xLow][y - yLow] == false) {
						cout << zero;
					}
				}
			}
			cout << '\n';
		}
		return 0;
	}

	for(int y = yhigh; y >= ylow; y--){
		for(int x = xlow; x <= xhigh; x++){
			if (terrain[x - xlow][y - ylow] == true){
				cout << one;
			}

			if (terrain[x - xlow][y - ylow] == false){
				cout << zero;
			}
		}

		cout << '\n';
	}
	return 0;
}
