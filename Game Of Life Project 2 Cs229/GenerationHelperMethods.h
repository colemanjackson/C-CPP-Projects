#ifndef GENERATIONHELPERMETHODS_H
#define GENERATIONHELPERMETHODS_H





#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "InfoHolder.h"
#include "InfoParser.h"
#include "CellParser.h"
#include "WireWorldParser.h"
#include "WireInfo.h"


using namespace std;


/*
* This set of functions generates the terrain for each of the three different file types, and updates the board every generation.
* A better implementation would have been to include this as a part of the information holder set and use inheritance, but no time.
* God functions update the board from generation n to n+1, getInitialVector functions grab generation 0 and build the initial terrain board. 
*/

// Named as such because this function simulates the generations of life passing.
// It kills things
// It makes them live.
// It makes them think a $60,000/year starting salary is worth this class. (Spolier: No it doesn't.)
vector<vector<bool> > god(vector<vector<bool> > terrain, InfoHolder &info);
// Gets generation 0 for the life simulation
vector<vector<bool> > getInitialVector(InfoHolder &info);
vector< vector<char> > getInitialWWVector(WireInfo &info);
vector< vector<char> > godWW(WireInfo &info, vector < vector<char> > & terrain);
vector< vector<bool> > getInitialCellVector(CellInfo &info);
vector < vector<bool> > godCell(vector<vector<bool> > terrain, CellInfo &info);

#endif