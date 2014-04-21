#ifndef CELLINFO_H
#define CELLINFO_H
#include <iostream>
#include <string>
#include <utility>  
#include <vector>
using namespace std;



/*
* Holds all information used in order to parse cellular automata files
* author: Coleman Jackson
* version: 0.1
*/
class CellInfo {
public:
typedef struct{
		int xlower;
		int xupper;
		int ylower;
		int yupper;

	}Terrain;

	typedef struct{
    	int Zero;
    	int One;
	}Chars;

	typedef struct{
		int color1;
		int color2;
		int color3;
	}Colors;
	
	struct Coordinate{
		int x;
		int y;
		Coordinate(int paramx, int paramy) : x(paramx), y(paramy){}
	};
private:

	Terrain terrain;
	int rule;
	string name;
	Terrain window;
	Chars chars;
	Colors oc;
	Colors zc;
	vector<Coordinate> initialOneVals;
public:

	CellInfo();
	void setTerrain(int, int, int, int);
	void setxTerrain(int, int);
	void setyTerrain(int, int);
	void setxWindow(int, int);
	void setyWindow(int, int);
	Terrain getTerrain();
	void setWindow(int, int, int, int);
	Terrain getWindow();
	void setChars(int, int);
	Chars getChars();
	Colors getocColors();
	Colors getzcColors();
	void setocColors(int, int, int);
    void setzcColors(int, int, int);
	void addInitialOneVals(int, int);
	vector<Coordinate> getInitialOneVals();
	void setName(std::string);
	std::string getName();
	void setRule(int);
	int getRule();
	
};
#endif