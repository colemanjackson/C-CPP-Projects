#include "CellInfo.h"

CellInfo::CellInfo() {
	name = "Untitled";
	window.xlower = -1;
	window.xupper = -1;
	window.ylower = -1;
	window.yupper = -1;
}
void CellInfo::setTerrain(int xlow, int xhigh, int ylow, int yhigh) {
	terrain.xlower = xlow;
	terrain.xupper = xhigh;
	terrain.ylower = ylow;
	terrain.yupper = yhigh;
}

CellInfo::Terrain CellInfo::getTerrain() {
	return terrain;
}

void CellInfo::setxTerrain(int xlow, int xhigh){
	terrain.xlower = xlow;
	terrain.xupper= xhigh;
}

void CellInfo::setyTerrain(int ylow, int yhigh){
	terrain.ylower = ylow;
	terrain.yupper = yhigh;
}

void CellInfo::setWindow(int xlow, int xhigh, int ylow, int yhigh) {
	window.xlower = xlow;
	window.xupper = xhigh;
	window.ylower = ylow;
	window.yupper = yhigh;
}

void CellInfo::setxWindow(int xlow, int xhigh){
	window.xlower = xlow;
	window.xupper = xhigh;
}

void CellInfo::setyWindow(int ylow, int yhigh){
	window.ylower = ylow;
	window.yupper = yhigh;
}

CellInfo::Terrain CellInfo::getWindow() {
	return window;
}

void CellInfo::setChars(int one, int zero) {
	chars.Zero = zero;
	chars.One = one;
}

CellInfo::Chars CellInfo::getChars() {
	return chars;
}

CellInfo::Colors CellInfo::getocColors() {
	return oc;
}

CellInfo::Colors CellInfo::getzcColors() {
	return zc;
}

void CellInfo::setocColors(int one, int two, int three) {
	oc.color1 = one;
	oc.color2 = two;
	oc.color3 = three;
}

void CellInfo::setzcColors(int one, int two, int three) {
	zc.color1 = one;
	zc.color2 = two;
	zc.color3 = three;

}

void CellInfo::addInitialOneVals(int x, int y) {
	initialOneVals.push_back(CellInfo::Coordinate(x, y));
}

vector<CellInfo::Coordinate> CellInfo::getInitialOneVals() {
	return initialOneVals;
}

void CellInfo::setName(std::string newName) {
	name = newName;
}

std::string CellInfo::getName() {
	return name;
}

void CellInfo::setRule(int newRule) {
	rule = newRule;
}

int CellInfo::getRule() {
	return rule;
}
