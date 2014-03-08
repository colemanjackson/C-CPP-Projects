#include "InfoHolder.h"

InfoHolder::InfoHolder() {
	updateWindowXSet(false);
	updateWindowYSet(false);
	updateNameSet(false);

}
bool InfoHolder::isNameSet() {
	return nameSet;
}
bool InfoHolder::isWindowXSet() {
	return windowXSet;
}

bool InfoHolder::isWindowYSet() {
	return windowYSet;
}
void InfoHolder::updateWindowXSet(bool updateVal) {
	windowXSet = updateVal;
}
void InfoHolder::updateWindowYSet(bool updateVal) {
	windowYSet = updateVal;
}
void InfoHolder::updateNameSet(bool updateVal) {
	nameSet = updateVal;
}

void InfoHolder::setxTerrainLowerBound(int low) {
	(terrain.xlower) = low;
}
void InfoHolder::setxTerrainHigherBound(int high) {
	(terrain.xupper) = high;
}
void InfoHolder::setyTerrainLowerBound(int low) {
	terrain.ylower = low;
}
void InfoHolder::setyTerrainHigherBound(int high) {
	terrain.yupper = high;
}
void InfoHolder::setxWindowLowerBound(int low) {
	window.xlower = low;
}
void InfoHolder::setxWindowHigherBound(int high) {
	window.xupper = high;
}
void InfoHolder::setyWindowLowerBound(int low) {
	window.ylower = low;
}
void InfoHolder::setyWindowHigherBound(int high) {
	window.yupper = high;

}
int InfoHolder::getxTerrainLowerBound() {
	return terrain.xlower;
}
int InfoHolder::getxTerrainHigherBound() {
	return terrain.xupper;
}
int InfoHolder::getyTerrainLowerBound() {
	return terrain.ylower;
}
int InfoHolder::getyTerrainHigherBound() {
	return terrain.yupper;
}
int InfoHolder::getxWindowLowerBound() {
	return window.xlower;
}
int InfoHolder::getxWindowHigherBound() {
	return window.xupper;
}
int InfoHolder::getyWindowLowerBound() {
	return window.ylower;
}
int InfoHolder::getyWindowHigherBound() {
	return window.yupper;
}
//END OF TERRAIN AND WINDO GETTERS AND SETTERS
void InfoHolder::setAliveChars(int x) {
	chars.alive = x;
}
void InfoHolder::setDeadChars(int x) {
	chars.dead = x;
}
int InfoHolder::getAliveChars() {
	return chars.alive;
}
int InfoHolder::getDeadChars() {
	return chars.dead;
}
void InfoHolder::setAliveColors(int c1, int c2, int c3) {
	colors.alive1 = c1;
	colors.alive2 = c2;
	colors.alive3 = c3;
}
void InfoHolder::setDeadColors(int c1, int c2, int c3) {
	colors.dead1 = c1;
	colors.dead2 = c2;
	colors.dead3 = c3;

}
int InfoHolder::getAliveColors1() {
	return colors.alive1;

}
int InfoHolder::getAliveColors2() {
	return colors.alive2;

}
int InfoHolder::getAliveColors3() {
	return colors.alive3;

}
int InfoHolder::getDeadColors1() {
	return colors.dead1;

}
int InfoHolder::getDeadColors2() {
	return colors.dead2;

}
int InfoHolder::getDeadColors3() {
	return colors.dead3;

}

vector<int> InfoHolder::getInitialXVals() {
	return initXVals;

}
vector<int> InfoHolder::getInitialYVals() {
	return initYVals;

}
void InfoHolder::setInitialVals(int x, int y) {
	initXVals.push_back(x);
	initYVals.push_back(y);

}

void InfoHolder::setName(std::string n) {
	name.assign(n);

}

std::string InfoHolder::getName() {
	return name;

}

