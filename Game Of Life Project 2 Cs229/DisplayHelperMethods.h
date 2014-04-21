#ifndef DISPLAYHELPERMETHODS_H
#define DISPLAYHELPERMETHODS_H



#include "InfoHolder.h"
#include "WireInfo.h"
#include "CellInfo.h"
#include "InfoParser.h"
#include "ParserUtil.h"
#include <fstream>



/*
* All functions in this file have to do with displaying the generated information. 
* visual output methods display the board visually, file outputs display the output as a file.
* a better way to implement this class would have been to include it with each of the 
* informationHolders and use inheritance, but no time.
*/

int fileOutput(vector<vector<bool> > terrain, InfoHolder &info);
int visualOutput(vector<vector<bool> > lifeBoard, InfoHolder &info);
int visualOutputWW(vector< vector<char> > terrain, WireInfo &info);
int fileOutputWW(vector< vector<char> > terrain, WireInfo &info);
int fileOutputCell(vector<vector<bool> > terrain, CellInfo &info);
int visualOutputCell(vector<vector<bool> > terrain, CellInfo &info);





#endif

