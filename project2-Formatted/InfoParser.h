#ifndef INFOPARSER_H
#define INFOPARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "InfoHolder.h"

using namespace std;

class InfoParser {

public:
	InfoParser();

	void parseName(InfoHolder&, istream&);
	void parseWindow(InfoHolder&, istream&);
	void parseTerrain(InfoHolder&, istream&);
	void parseChars(InfoHolder&, istream&);
	void parseColors(InfoHolder&, istream&);
	void parseInitial(InfoHolder&, istream&);

};

#endif
