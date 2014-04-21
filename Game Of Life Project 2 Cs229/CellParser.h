#ifndef CELLPARSER_H
#define CELLPARSER_H

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
#include "CellInfo.h"

using namespace std;

class CellParser {

public:
	CellParser();
	void parseName(CellInfo&, istream&);
	void parseWindow(CellInfo&, istream&);
	void parseTerrain(CellInfo&, istream&);
	void parseChars(CellInfo&, istream&);
	void parseColors(CellInfo&, istream&);
	void parseInitial(CellInfo&, istream&);
	void parseRule(CellInfo&, istream&);

};

#endif
