#ifndef PARSERUTIL_H
#define PARSERUTIL_H

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

//Returns 1 if there is a window, and 0 otherwise
//This function is the meat of fileParser, and parses the life statement and by default, every struct in between. It is the handler of the FileParser Object
int lifeParser(InfoHolder &info, istream &file);
int wireInfoParser(WireInfo& wireInfo, istream& file);

//head function for life parser, this function parses a life file and returns the information stored inside of it.
int fileParser(InfoHolder &info, WireInfo &wireInfo, CellInfo &cellInfo,
		istream& file);

//Strips the file of whitespace and comments, returned via temp.txt
void fileStripper(InfoHolder &info, istream& file);

//boilerplate empty file checking for bad files.
bool is_empty(std::fstream& pFile);



#endif