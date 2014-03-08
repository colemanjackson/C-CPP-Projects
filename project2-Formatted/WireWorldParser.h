
#ifndef WIREWORLDPARSER_H
#define WIREWORLDPARSER_H

/*
*
*This Class is meant to help parse all Elements of a WireWorld file
*(Yes, I know, Duplicated code. Pay me and I'll do better.)
*
*/
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "WireInfo.h"

using namespace std;




class WireWorldParser {

public:
WireWorldParser();

void parseName(WireInfo&, istream&);
void parseWindow(WireInfo&, istream&);
void parseTerrain(WireInfo&, istream&);
void parseChars(WireInfo&, istream&);
void parseColors(WireInfo&, istream&);
void parseInitial(WireInfo&, istream&);




};

#endif
