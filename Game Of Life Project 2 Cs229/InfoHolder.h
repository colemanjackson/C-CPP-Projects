
#ifndef INFOHOLDER_H
#define INFOHOLDER_H
#include <iostream>
#include <string>
#include <utility>  
#include <vector>



using namespace std;



class InfoHolder {

 struct Terrain{
		int xlower;
		int xupper;
		int ylower;
		int yupper;

	};

	 struct Chars{
    	int alive;
    	int dead;
	};
	 struct Colors{
		int alive1;
		int alive2;
		int alive3;
		int dead1;
		int dead2;
		int dead3;
	};
	


	bool windowXSet;
	bool windowYSet;
	bool nameSet;
 
	Terrain terrain;
	Terrain window;
	Chars chars;
	Colors colors;
	string name; 
public:
	
	vector<int> initXVals;
	vector<int> initYVals;

public:
	InfoHolder();
    //TERRIAN AND WINDOW GETTERS AND SETTERS
    void setxTerrainLowerBound(int);
    bool isWindowXSet();
    bool isWindowYSet();
    bool isNameSet();
	void updateWindowXSet(bool);
	void updateWindowYSet(bool);
	void updateNameSet(bool);
    void setxTerrainHigherBound(int);
    void setyTerrainLowerBound(int);
    void setyTerrainHigherBound(int);
    void setxWindowLowerBound(int);
    void setxWindowHigherBound(int);
    void setyWindowLowerBound(int);
    void setyWindowHigherBound(int);
	int getxTerrainLowerBound();
	int getxTerrainHigherBound();
	int getyTerrainLowerBound();
	int getyTerrainHigherBound();
	int getxWindowLowerBound();
	int getxWindowHigherBound();
	int getyWindowLowerBound();
	int getyWindowHigherBound();
    //END OF TERRAIN AND WINDO GETTERS AND SETTERS
	void setAliveChars(int x);
	void setDeadChars( int x);
	int  getAliveChars();
	int getDeadChars();
	void setAliveColors(int, int, int);
	void setDeadColors( int, int, int);
	int getAliveColors1();
	int getAliveColors2();
	int getAliveColors3();
	int getDeadColors1();
	int getDeadColors2();
	int getDeadColors3();
	vector<int> getInitialXVals();
	vector<int> getInitialYVals();
	void setInitialVals(int, int); // passed in to construct another point to the vector
	void setName(std::string);
	std::string getName();
};


#endif
