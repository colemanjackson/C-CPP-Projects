#include "GenerationHelperMethods.h"
#include <algorithm>
vector< vector<bool> > getInitialCellVector(CellInfo &info){	
	CellInfo::Terrain terrain = info.getTerrain();
	vector<CellInfo::Coordinate> initialOneVals = info.getInitialOneVals();
	int xlow = terrain.xlower;
	int ylow = terrain.ylower;
	vector< vector<bool> > initialVector;


	//Push back 0 val, the value of an Empty cell
	for(int x = terrain.xlower - terrain.xlower; x <= terrain.xupper - terrain.xlower; x++ ){
		vector<bool> newColumn;
		for (int y = terrain.ylower - terrain.ylower; y <= terrain.yupper - terrain.ylower; y++) {
			newColumn.push_back(false);
		}

		initialVector.push_back(newColumn);
	}

	// Load Head Values, assigned a value of 1
	for ( int count = 0; count < initialOneVals.size(); count++){
		if (initialOneVals[count].x - xlow < 0 || initialOneVals[count].y - ylow < 0) throw 20;
		initialVector[initialOneVals[count].x -xlow][initialOneVals[count].y -ylow] = true;
	}

	return initialVector;
}






//Gets the initial vector for the WW board
vector< vector<char> > getInitialWWVector(WireInfo &info){
	WireInfo::Terrain terrain = info.getTerrain();
	vector<WireInfo::Coordinate> initialHeadValues = info.getInitialHeadVals();
	vector<WireInfo::Coordinate> initialTailValues = info.getInitialTailVals();
	vector<WireInfo::Coordinate> initialWireValues = info.getInitialWireVals();
	int xlow = terrain.xlower;
	int ylow = terrain.ylower;
	vector< vector<char> > initialVector;


	//Push back 0 val, the value of an Empty cell
	for(int x = terrain.xlower - terrain.xlower; x <= terrain.xupper - terrain.xlower; x++ ){
		vector<char> newColumn;
		for (int y = terrain.ylower - terrain.ylower; y <= terrain.yupper - terrain.ylower; y++) {
			newColumn.push_back(0);
		}

		initialVector.push_back(newColumn);
	}


	// Load Head Values, assigned a value of 1
	for ( int count = 0; count < initialHeadValues.size(); count++){
		if(initialHeadValues[count].x - xlow < 0 || initialHeadValues[count].y - ylow < 0) throw 20;
		initialVector[initialHeadValues[count].x - xlow][initialHeadValues[count].y - ylow] = 1;
	}

	// Load Tail Values, value 2
	for (int count = 0; count < initialTailValues.size(); count++){
		if(initialTailValues[count].x - xlow < 0 || initialTailValues[count].y - ylow < 0) throw 20;
		initialVector[initialTailValues[count].x - xlow][initialTailValues[count].y - ylow] = 2;
	}

	// Load Wire Vals, 3
	for (int count = 0; count < initialWireValues.size(); count++){
		if(initialWireValues[count].x - xlow < 0 || initialWireValues[count].y - ylow < 0) throw 20;

		initialVector[initialWireValues[count].x - xlow][initialWireValues[count].y - ylow] = 3;
	}

	return initialVector;
}

// vector< vector<bool> > getInitialEleVector(CellInfo &info){
// 	vector< 	
// }

// Gets generation 0 for the life simulation
vector<vector<bool> > getInitialVector(InfoHolder &info) {
	int yLow = info.getyTerrainLowerBound();
	int yHigh = info.getyTerrainHigherBound();
	int xLow = info.getxTerrainLowerBound();
	int xHigh = info.getxTerrainHigherBound();
	vector<vector<bool> > terrain;
	vector<int> initialx = info.getInitialXVals();
	vector<int> initialy = info.getInitialYVals();
	vector<int> a = info.getInitialXVals();
	vector<int> b = info.getInitialYVals();
	for (int i = 0; i < a.size(); i++) {
		cerr << a.at(i) << ',' << b.at(i) << " ";

	}
	cerr << "yLow: " << yLow << '\n';
	cerr << "yHigh: " << yHigh << '\n';
	for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {
		vector<bool> a;
		for (int x = xLow - xLow; x < xHigh - xLow + 1; x++) {
			a.push_back(false);
		}
		terrain.push_back(a);

	}
	//fill initial values
	int count = 0;
	for (count; count < initialx.size(); count++) {
		cerr << "Setting y: " << initialy[count] << " x: " << initialx[count]
				<< '\n';
		terrain[initialy[count] - yLow][initialx[count] - xLow] = true;

	}

	return terrain;
}





// Named as such because this function simulates the generations of life passing.
// It kills things
// It makes them live.
vector<vector<bool> > god(vector<vector<bool> > terrain, InfoHolder &info) {
	int yLow = info.getyTerrainLowerBound();
	int yHigh = info.getyTerrainHigherBound();
	int xLow = info.getxTerrainLowerBound();
	int xHigh = info.getxTerrainHigherBound();

	vector<vector<bool> > retVal;
	for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {
		vector<bool> a;
		for (int x = xLow - xLow; x < xHigh - xLow + 1; x++) {
			a.push_back(false);
		}
		retVal.push_back(a);
	}

	//Update next generation
	for (int y = yLow - yLow; y < yHigh - yLow + 1; y++) {

		for (int x = xLow - xLow; x < xHigh - xLow + 1; x++) {
			int count = 0;
			if ((x + 1 < xHigh - xLow) && terrain[y][x + 1] == true) {
				count++;

			}
			if ((x + 1 <= xHigh - xLow) && (y + 1 <= yHigh - yLow)
					&& terrain[y + 1][x + 1] == true) {
				count++;

			}

			if ((y + 1 <= yHigh - yLow) && terrain[y + 1][x] == true) {
				count++;

			}
			if ((x - 1 >= 0) && (y + 1 <= yHigh - yLow)
					&& terrain[y + 1][x - 1] == true) {
				count++;

			}

			if ((x - 1 >= 0) && terrain[y][x - 1] == true) {
				count++;

			}
			if ((x - 1 >= 0) && (y - 1 >= 0) && terrain[y - 1][x - 1] == true) {
				count++;

			}
			if ((y - 1 >= 0) && terrain[y - 1][x] == true) {
				count++;

			}

			if ((x + 1 <= xHigh - xLow) && (y - 1 >= 0)
					&& terrain[y - 1][x + 1] == true) {
				count++;

			}

			//DEAD ALREADY CHECK. POP CHECK == 3

			if (terrain[y][x] == false) {
				if (count == 3) {
					retVal[y][x] = true;
					continue;
				}
			}

			//IF THE CELL IS ALIVE IN GEN i...
			else {
				//COUNT IS LESS THAN 2 CHECK
				if (count < 2) {
					retVal[y][x] = false;
				}
				//COUNT is 2 or 3 CHECK (only one that sets true...)
				if (count >= 2 && count <= 3) {
					retVal[y][x] = true;
				}

				if (count > 3) {
					retVal[y][x] = false;
				}
			}
		}
	}
	terrain.clear();
	return retVal;
}

vector < vector<bool> > godCell(vector<vector<bool> > terrain, CellInfo &info){
	int rule = info.getRule();
	CellInfo::Terrain terrainInformation = info.getTerrain();
	int xLow = terrainInformation.xlower;
	int xHigh = terrainInformation.xupper;
	int yLow = terrainInformation.ylower;
	int yHigh = terrainInformation.yupper;
	//corresponds to (x-1, y+1)
	int firstVal = 0;
	// cooresponds to (x, y+1)
	int secondVal = 0;
	// corresponds to (x+1, y+1)
	int thirdVal = 0;



	//build return value (next board) for editing
	vector< vector<bool> > retVal;
	for(int x = terrainInformation.xlower - terrainInformation.xlower; x <= terrainInformation.xupper - terrainInformation.xlower; x++ ){
		vector<bool> newColumn;
		for (int y = terrainInformation.ylower - terrainInformation.ylower; y <= terrainInformation.yupper - terrainInformation.ylower; y++) {
			newColumn.push_back(false);
		}

		retVal.push_back(newColumn);
	}

	 // get and parse rule for accurate New State Information


	if (rule > 255) throw 20; // Too big for our operations, invalid rule.
	vector<int> binaryRule;
	//Create RetVal to return for next generation of board
	while (rule != 0){
		int zoro;
	 	zoro = rule % 2;
	 	rule/=2; //have to update rule, since mod does not affect it.
	 	binaryRule.push_back(zoro);
	}

	//may not have 8 values for the full ruleset, add them in.
	while(binaryRule.size() != 8){
		binaryRule.push_back(0);
	}
	//reverse the values, as they were stored in the incorrect order for our output.
	reverse(binaryRule.begin(), binaryRule.end());
	


	//Update RetVal and Return
	for(int x = xLow - xLow; x <= xHigh - xLow; x++ ){
		for (int y = yLow - yLow; y <= yHigh - yLow; y++) {

			if(terrain[x][y] == true){
				retVal[x][y] = true;
				continue;
			}

			if ((x - 1 >= 0) && (y + 1 <= yHigh - yLow)
					&& terrain[x - 1][y + 1] == true) {
				firstVal =1;
			}
			else{ firstVal = 0;
			}
			if ((y + 1 <= yHigh - yLow) && terrain[x][y + 1] == true) {
				secondVal = 1;
			}
			else{
				secondVal = 0;
			}
			if ((x + 1 < xHigh - xLow) && (y + 1 <= yHigh - yLow)
					&& terrain[x + 1][y + 1] == true) {
				thirdVal = 1;
			}
			else{
				thirdVal = 0;

			}

			//BEGIN CHECK NOW THAT WE HAVE THE PATTERN!
			
			if(firstVal == 1 && secondVal == 1 && thirdVal == 1){
				retVal[x][y] = binaryRule[0];
			}


			if(firstVal == 1 && secondVal == 1 && thirdVal == 0){
				retVal[x][y] = binaryRule[1];
			}

			if(firstVal == 1 && secondVal == 0 && thirdVal == 1){
				retVal[x][y] = binaryRule[2];
			}

			if(firstVal == 1 && secondVal == 0 && thirdVal == 0){
				retVal[x][y] = binaryRule[3];
			}

			if(firstVal == 0 && secondVal == 1 && thirdVal == 1){
				retVal[x][y] = binaryRule[4];
			}

			if(firstVal == 0 && secondVal == 1 && thirdVal == 0){
				retVal[x][y] = binaryRule[5];
			}

			if(firstVal == 0 && secondVal == 0 && thirdVal == 1){
				retVal[x][y] = binaryRule[6];
			}

			if(firstVal == 0 && secondVal == 0 && thirdVal == 0){
				retVal[x][y] = binaryRule[7];
			}

			firstVal = 0;
			secondVal = 0;
			thirdVal = 0;


		}
	}





	binaryRule.clear();
	return retVal;
}

//God Function for WireWorld
vector< vector<char> > godWW(WireInfo &info, vector < vector<char> > & terrain) {
	WireInfo::Terrain terrainInformation = info.getTerrain();
	int xLow = terrainInformation.xlower;
	int xHigh = terrainInformation.xupper;
	int yLow = terrainInformation.ylower;
	int yHigh = terrainInformation.yupper;

	vector< vector<char> > retVal;
	for(int x = terrainInformation.xlower - terrainInformation.xlower; x <= terrainInformation.xupper - terrainInformation.xlower; x++ ){
		vector<char> newColumn;
		for (int y = terrainInformation.ylower - terrainInformation.ylower; y <= terrainInformation.yupper - terrainInformation.ylower; y++) {
			newColumn.push_back(0);
		}

		retVal.push_back(newColumn);
	}
	for(int x = xLow - xLow; x <= xHigh - xLow; x++ ){
		for (int y = yLow - yLow; y <= yHigh - yLow; y++) {
			int count = 0;
			if(terrain[x][y] == 0){
				retVal[x][y] = 0;
				continue;
			}
			//BEGIN CHECK OF SURROUNDING CELLS TO SEE IF THEY ARE ELECTRON HEADS
			if ((x + 1 < xHigh - xLow) && terrain[x+1][y] == 1) {
				count++;

			}
			if ((x + 1 < xHigh - xLow) && (y + 1 <= yHigh - yLow)
					&& terrain[x + 1][y + 1] == 1) {
				count++;

			}

			if ((y + 1 <= yHigh - yLow) && terrain[x][y + 1] == 1) {
				count++;

			}
			if ((x - 1 >= 0) && (y + 1 <= yHigh - yLow)
					&& terrain[x - 1][y + 1] == 1) {
				count++;

			}

			if ((x - 1 >= 0) && terrain[x - 1][y] == 1) {
				count++;

			}
			if ((x - 1 >= 0) && (y - 1 >= 0) && terrain[x - 1][y - 1] == 1) {
				count++;

			}
			if ((y - 1 >= 0) && terrain[x][y-1] == 1) {
				count++;

			}

			if ((x + 1 < xHigh - xLow) && (y - 1 >= 0)
					&& terrain[x + 1][y - 1] == 1) {
				count++;

			}

			//END OF CHECK FOR ELECTRON HEADS
			//BEGIN UPDATING CURRENT CELL

	

			//1 is Electron Head, so its now an electron tail
			if ( terrain[x][y] == 1){
				retVal[x][y] = 2;
				continue;
			}

			if (terrain[x][y] == 2) {
				retVal[x][y] = 3;
				continue;
			}

			if (terrain[x][y] == 3){
				if (count == 1 || count == 2){
					retVal[x][y] = 1;
				}
				// one or two neighbors were NOT electron
				else retVal[x][y] = 3;
			}

		}
	}




	return retVal;


}
