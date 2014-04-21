#include "WireInfo.h"



WireInfo::WireInfo() {
	name = "Untitled";
	window.xlower = -1;
	window.xupper = -1;
	window.ylower  = -1;
	window.yupper = -1;
}

void WireInfo::setTerrain(int xlow, int xhigh, int ylow, int yhigh) {
	terrain.xlower = xlow;
	terrain.xupper = xhigh;
	terrain.ylower = ylow;
	terrain.yupper = yhigh;
}

void WireInfo::setxTerrain(int xlow, int xhigh){
	terrain.xlower = xlow;
	terrain.xupper = xhigh;
}


void WireInfo::setyTerrain(int ylow, int yhigh){
	terrain.ylower = ylow;
	terrain.yupper = yhigh;
}

void WireInfo::setyWindow(int ylow, int yhigh){
	window.ylower = ylow;
	window.yupper = yhigh;
}

void WireInfo::setxWindow(int xlow, int xhigh){
	window.xlower = xlow;
	window.xupper = xhigh;
}

WireInfo::Terrain WireInfo::getTerrain() {
	return terrain;
}

void WireInfo::setWindow(int xlow, int xhigh, int ylow, int yhigh) {
	window.xlower = xlow;
	window.xupper = xhigh;
	window.ylower = ylow;
	window.yupper = yhigh;
}

WireInfo::Terrain WireInfo::getWindow() {
	return window;
}

void WireInfo::setChars(int Empty, int Head, int Tail, int Wire) {
	chars.Empty = Empty;
	chars.Head = Head;
	chars.Tail = Tail;
	chars.Wire = Wire;
}

WireInfo::Chars WireInfo::getChars() {
	return chars;
}

void WireInfo::setHeadColors(int c1, int c2, int c3) {
	hc.color1 = c1;
	hc.color2 = c2;
	hc.color3 = c3;
}
void WireInfo::setEmptyColors(int c1, int c2, int c3) {
	ec.color1 = c1;
	ec.color2 = c2;
	ec.color3 = c3;
}
void WireInfo::setTailColors(int c1, int c2, int c3) {
	tc.color1 = c1;
	tc.color2 = c2;
	tc.color3 = c3;
}
void WireInfo::setWireColors(int c1, int c2, int c3) {
	wc.color1 = c1;
	wc.color2 = c2;
	wc.color3 = c3;
}

WireInfo::Colors WireInfo::getHeadColors() {
	return hc;
}

WireInfo::Colors WireInfo::getTailColors() {
	return tc;
}

WireInfo::Colors WireInfo::getEmptyColors() {
	return ec;
}

WireInfo::Colors WireInfo::getWireColors() {
	return wc;
}

void WireInfo::addInitialHeadVal(int x, int y) {
	initHeadVals.push_back(WireInfo::Coordinate(x, y));
}

void WireInfo::addInitialTailVal(int x, int y) {
	initTailVals.push_back(WireInfo::Coordinate(x, y));
}

void WireInfo::addInitialWireVal(int x, int y) {
	initWireVals.push_back(WireInfo::Coordinate(x, y));
}

vector<WireInfo::Coordinate> WireInfo::getInitialHeadVals() {
	return initHeadVals;
}

vector<WireInfo::Coordinate> WireInfo::getInitialTailVals() {
	return initTailVals;
}

vector<WireInfo::Coordinate> WireInfo::getInitialWireVals() {
	return initWireVals;
}

void WireInfo::setName(string n) {
	name = n;
}

std::string WireInfo::getName() {
	return name;
}
