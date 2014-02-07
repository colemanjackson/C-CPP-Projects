#ifndef WIREINFO_H
#define WIREINFO_H
#include <iostream>
#include <string>
#include <utility>  
#include <vector>

using namespace std;

class WireInfo {
public:
	typedef struct {
		int xlower;
		int xupper;
		int ylower;
		int yupper;

	} Terrain;

	typedef struct {
		int Empty;
		int Head;
		int Tail;
		int Wire;
	} Chars;

	typedef struct {
		int color1;
		int color2;
		int color3;
	} Colors;

	struct Coordinate {
		int x;
		int y;
		Coordinate(int paramx, int paramy) :
				x(paramx), y(paramy) {
		}
	};
private:

	Terrain terrain;
	Terrain window;
	Chars chars;
	Colors ec;
	Colors hc;
	Colors tc;
	Colors wc;
	string name;
	vector<Coordinate> initHeadVals;
	vector<Coordinate> initTailVals;
	vector<Coordinate> initWireVals;

public:

	WireInfo();
	void setTerrain(int, int, int, int);
	Terrain getTerrain();
	void setxTerrain(int, int);
	void setyTerrain(int, int);
	void setxWindow(int, int);
	void setyWindow(int, int);
	void setWindow(int, int, int, int);
	Terrain getWindow();
	void setChars(int, int, int, int);
	Chars getChars();
	Colors getHeadColors();
	Colors getEmptyColors();
	Colors getWireColors();
	Colors getTailColors();
	void setHeadColors(int, int, int);
	void setTailColors(int, int, int);
	void setEmptyColors(int, int, int);
	void setWireColors(int, int, int);
	void addInitialHeadVal(int, int);
	void addInitialTailVal(int, int);
	void addInitialWireVal(int, int);
	vector<Coordinate> getInitialHeadVals();
	vector<Coordinate> getInitialTailVals();
	vector<Coordinate> getInitialWireVals();
	void setName(std::string);
	std::string getName();
};
#endif
