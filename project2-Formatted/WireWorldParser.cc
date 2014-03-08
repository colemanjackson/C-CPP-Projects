#include "WireWorldParser.h"
#include "WireInfo.h"



/*
* ** DESCRIPTION**
* *****************************
* This is the ugliest, most disgusting excuse for a parser util ever. It is complete with code that is duplicated
* beyond belief, a design that was destined for inheritance but ended in disgusting garbled code.
* It also works. So there's that.
* *****************************
* Name: WireWorld Parser
* Use: Parses and stores the WireWorld file information
* Author: Coleman Jackson, 
* Date: 1/22/2014
*
*/
WireWorldParser::WireWorldParser(){

}

void WireWorldParser::parseName(WireInfo& info, istream& file){
	char equal = file.get(); //should be an equal sign
	char quotation = file.get(); // should be a quotation
	char endSemiC;
	string retVal;
	if (equal != '=' || quotation != '"'){
		throw 20;  // Not correct file format, throw an error
	}
	
	while(file.good()){
		char c = file.get();
		if (c == '"') break;
		if (file.eof()){throw 20;} //didn't find ending " so throw an error
		retVal = retVal + c; // I love C++.... look at that string addition!
	}
	endSemiC = file.get();
	if(endSemiC != ';'){throw 20;} // Name doesn't have ending ;, so throw an error
	info.setName(retVal); 
	//info.updateNameSet(true); // name is now set
	string test = info.getName();
}

void WireWorldParser::parseWindow(WireInfo& info, istream& file){
	char ch;
	char gett;
	int lowx = 0;
	int highx = 0;
	int lowy = 0;
	int highy = 0;
	bool gotyrange = false;
	bool gotxrange = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{'){
		throw 20;  // Not correct file format, throw an error
	}

	
	while (true){
		if (file.eof()) throw 20; // File should never be end of file in this loop.
	string rangType = "";
	if (gotyrange && gotxrange){
		info.setWindow(lowx, highx, lowy, highy);
		gett = file.get();
		ch = file.get();
		if(gett != '}' && ch != ';') throw 20;
		else return;
	}

	for (int i = 0; i < 6; i++){          //GET 6 CHARS FROM FILE
		char cur = file.get();
		rangType = rangType + cur;
	}

	if (rangType.compare("Xrange") == 0){
		gett = file.get();
		if (gett != '=') throw 20;

      string values;
      while(gett !=';'){
			gett = file.get();
			if (gett == ';') break;
			if (file.eof()) throw 20; 
			values += gett;
		}
		const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering
		
		int check =sscanf(c, "%d..%d;", &lowx, &highx);
		gotxrange = true;
	}

 
	if (rangType.compare("Yrange") == 0){ // if it is Yrange
		gett = file.get();
		if (gett != '=') throw 20; // MUST be equal, another check can't hurt
		string values;
		while(gett !=';'){
			gett = file.get();
			if (gett == ';') break;
			if (file.eof()) throw 20;
			values += gett;
		}

		const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering		
		int check =sscanf(c, "%d..%d;", &lowy, &highy);
     	gotyrange = true; // set to true so that if both gotx and goty are true, to break and search for the end bit.




	}
}
}

void WireWorldParser::parseTerrain(WireInfo& info, istream& file){
	char ch;
	char gett;
	bool gotyrange = false;
	bool gotxrange = false;
	int lowx;
	int highx;
	int lowy;
	int highy;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{'){
		throw 20;  // Not correct file format, throw an error
	}

	
	while (true){
		if (file.eof()) throw 20; // File should never be end of file in this loop.
	string rangType = "";
	if (gotyrange && gotxrange){
		info.setTerrain(lowx, highx, lowy, highy);
		gett = file.get();
		ch = file.get();
		if(gett != '}' && ch != ';') throw 20;
		else return;
	}

	for (int i = 0; i < 6; i++){            //WILL NEED TO CHANGE LATER
		char cur = file.get();
		rangType = rangType + cur;
	}


	if (rangType.compare("Xrange") == 0){
		gett = file.get();
		if (gett != '=') throw 20;

      string values;
      while(gett !=';'){
			gett = file.get();
			if (gett == ';') break;
			if (file.eof()) throw 20;
			values += gett;
		}
		const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering
		
		int check =sscanf(c, "%d..%d;", &lowx, &highx);

		gotxrange = true;
	}




	if (rangType.compare("Yrange") == 0){ // if it is Yrange
		gett = file.get();
		if (gett != '=') throw 20; // MUST be equal, another check can't hurt
		string values;

		while(gett !=';'){
			gett = file.get();
			if (gett == ';') break;
			if (file.eof()) throw 20;
			values += gett;
		}

		const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering		
		int check =sscanf(c, "%d..%d;", &lowy, &highy);
     	gotyrange = true; // set to true so that if both gotx and goty are true, to break and search for the end bit.




	}



}
}
void WireWorldParser::parseChars(WireInfo& info, istream& file){
	char ch;

	char gett;

	bool gotEmpty = false;

	bool gotHead= false; //hehe...

	bool gotTail = false;

	bool gotWire = false;

	int emptyVal = 0;

	int headVal = 0;

	int tailVal = 0;

	int wireVal = 0;

	char equal = file.get(); //should be an equal sign

	char openBracket = file.get(); // should be an open bracket


	if (equal != '=' || openBracket != '{'){
		
		throw 20;  // Not correct file format, throw an error
	}

	while (true){
		if (!file.good()) throw 20; // File should never be end of file in this loop.
		string rangType = "";
		
		if (gotEmpty && gotHead && gotTail && gotWire){
			info.setChars(emptyVal, headVal, tailVal, wireVal);
			gett = file.get();
			ch = file.get();

			if(gett != '}' && ch != ';') throw 20;

			else{

				return;
			}
		}




		string AorD = "";
		string stringofVal = "";
		for (int i = 0; i < 5; i++){         
			char cur = file.get();
			AorD = AorD + cur;
		}

		if  (AorD.compare("Empty") == 0){
			gett = file.get();
		
			if (gett != '=') throw 20;

			string values = "";
			while(gett != ';'){
				gett = file.get();
				if(file.eof()) throw 20;
				if(gett == ';') break;
				values += gett;
		
			}


		const char * c = values.c_str();
	
		sscanf(c, "%d", &emptyVal);
		gotEmpty = true;
		}


	
		if  (AorD.compare("Head=") == 0){
			char current;
			string values = "";
			while(current != ';'){
				current = file.get();
				if(file.eof()) throw 20;
					values += current;
			}

		const char * c = values.c_str(); 
	
		sscanf(c, "%d;", &headVal);
		gotHead = true;
		}




		if  (AorD.compare("Tail=") == 0){
			char current;
			string values = "";
			while(current != ';'){
				current = file.get();
				if(file.eof()) throw 20;
					values += current;
			}

		const char * c = values.c_str(); 
	
		sscanf(c, "%d;", &tailVal);
		gotTail = true;
		}




		if  (AorD.compare("Wire=") == 0){
			char current;
			string values = "";
			while(current != ';'){
				current = file.get();
				if(file.eof()) throw 20;
					values += current;
			}

		const char * c = values.c_str(); 
	
		sscanf(c, "%d;", &wireVal);
		gotWire = true;
		}
 
	}
}
void WireWorldParser::parseColors(WireInfo& info, istream& file){
	char ch;
	char gett;
	bool gotEmpty = false;
	bool gotHead = false;
	bool gotTail = false;
	bool gotWire = false;

	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{'){

		throw 20;  // Not correct file format, throw an error
	}
	while (true){
		if (!file.good()) throw 20; // File should never be end of file in this loop.
		string rangType = "";
		if (gotEmpty && gotHead && gotTail && gotWire){
			gett = file.get();
			ch = file.get();
			if(gett != '}' && ch != ';') throw 20;

			else {
					return;
			}
		}

	
		string AorD = "";
	string stringofVal = "";
	for (int i = 0; i < 5; i++){          //GET 6 CHARS FROM FILE
		char cur = file.get();
		AorD = AorD + cur;
	}


	if  (AorD.compare("Empty") ==0){
		gett = file.get();
		if (gett != '=') throw 20;

			string values = "";
		while(gett != ';'){
			gett = file.get();
			
			if(file.eof()) throw 20;
			if(gett == ';') break;
			values += gett;
		}
	const char * c = values.c_str();
	int val = 0;
	int val1 = 0;
	int val2 = 0;
	sscanf(c, "(%d, %d, %d)", &val, &val1, &val2);
	info.setEmptyColors(val, val1, val2);
	gotEmpty = true;
	}

	if  (AorD.compare("Head=") == 0){
		char current;
		string values = "";
		while(current != ';'){
			current = file.get();
			if(file.eof()) throw 20;
			if(current == ';') break;
				values += current;
		}

	const char * c = values.c_str(); 
	int val = 0;
	int val2 = 0;
	int val3 = 0;
	
	sscanf(c, "(%d,%d,%d)", &val, &val2, &val3);
	info.setHeadColors(val, val2, val3 );
	gotHead = true;
	}

	if  (AorD.compare("Tail=") == 0){
		char current;
		string values = "";
		while(current != ';'){
			current = file.get();
			if(file.eof()) throw 20;
			if(current == ';') break;
				values += current;
		}

	const char * c = values.c_str(); 
	int val = 0;
	int val2 = 0;
	int val3 = 0;
	
	sscanf(c, "(%d,%d,%d)", &val, &val2, &val3);
	info.setTailColors(val, val2, val3 );
	gotTail = true;
	}

	if  (AorD.compare("Wire=") == 0){
		char current;
		string values = "";
		while(current != ';'){
			current = file.get();
			if(file.eof()) throw 20;
			if(current == ';') break;
				values += current;
		}

	const char * c = values.c_str(); 
	int val = 0;
	int val2 = 0;
	int val3 = 0;
	
	sscanf(c, "(%d,%d,%d)", &val, &val2, &val3);
	info.setWireColors(val, val2, val3 );
	gotWire = true;
	}


	}

}
void WireWorldParser::parseInitial(WireInfo &info, istream &file){
	char ch;
	char gett;
	bool gotHead = false;
	bool gotTail = false;
	bool gotWire = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{'){
		throw 20;  // Not correct file format, throw an error
	}
	while(true){
		string alive = ""; // should fill to alive

		if (!file.good()) throw 20; 
		if (gotHead && gotTail && gotWire){
			ch = file.get(); // if out of the loop, should be a }
			gett = file.get(); // if out of the loop, should be a ;

		if (ch != '}' && gett != ';') throw 20;
			return;
		}
		for (int i = 0; i < 4; i++){
			ch = file.get();
			alive += ch;
		}
		if(alive.compare("Head")== 0){
	
			ch = file.get();
			if (ch != '=') throw 20; // if the next char after alive is not an equal, throw an error.
			string tmp = ""; //initialize a string to be used for values
			bool commaFlag = false; //true if a comma has already been passed over, 
									//meaning this comma seperates between coordinate pairs

			while (ch!= ';'){
				ch = file.get();
				if (file.eof()) throw 20;
				if (ch == ',' && commaFlag){
					const char * c = tmp.c_str(); 
			
					int x;
					int y;
					int correct = sscanf(c, "(%d,%d)", &x,&y);
					tmp = "";
					if (correct != 2){
			 			cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
			 			throw 20;
			 		}
					info.addInitialHeadVal(x, y);
			
					cerr << '\n';
					commaFlag = false;
					continue; //so you dont flip commaflag...
				}

				if(ch == ',' && !commaFlag){
					commaFlag = true;
					tmp += ch;
					continue;
				}

				if(ch == ';'){
					const char * c = tmp.c_str(); 
					int x = 0;
					int y = 0;
					int correct = sscanf(c, "(%d,%d)", &x, &y);
					tmp = "";
					if (correct != 2){
				 		cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
				 		throw 20;
				 	}
					info.addInitialHeadVal(x, y);
					gotHead = true;
					break;
				}

				tmp += ch; // if none of the above are met, then ch must be a part of a coordinate pair.
			}
		}

		if(alive.compare("Tail")== 0){
	
			ch = file.get();
			if (ch != '=') throw 20; // if the next char after alive is not an equal, throw an error.
			string tmp = ""; //initialize a string to be used for values
			bool commaFlag = false; //true if a comma has already been passed over, 
									//meaning this comma seperates between coordinate pairs

			while (ch!= ';'){
				ch = file.get();
				if (file.eof()) throw 20;
				if (ch == ',' && commaFlag){
					const char * c = tmp.c_str(); 
			
					int x;
					int y;
					int correct = sscanf(c, "(%d,%d)", &x,&y);
					tmp = "";
					if (correct != 2){
			 			cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
			 			throw 20;
			 		}
					info.addInitialTailVal(x, y);
			
					commaFlag = false;
					continue; //so you dont flip commaflag...
				}

				if(ch == ',' && !commaFlag){
					commaFlag = true;
					tmp += ch;
					continue;
				}

				if(ch == ';'){
					const char * c = tmp.c_str(); 
					int x = 0;
					int y = 0;
					int correct = sscanf(c, "(%d,%d)", &x, &y);
					tmp = "";
					if (correct != 2){
				 		cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
				 		throw 20;
				 	}
					info.addInitialTailVal(x, y);
					gotTail = true;
					break;
				}

				tmp += ch; // if none of the above are met, then ch must be a part of a coordinate pair.
			}
		}


		if(alive.compare("Wire")== 0){
	
			ch = file.get();
			if (ch != '=') throw 20; // if the next char after alive is not an equal, throw an error.
			string tmp = ""; //initialize a string to be used for values
			bool commaFlag = false; //true if a comma has already been passed over, 
									//meaning this comma seperates between coordinate pairs

			while (ch!= ';'){
				ch = file.get();
				if (file.eof()) throw 20;
				if (ch == ',' && commaFlag){
					const char * c = tmp.c_str(); 
			
					int x;
					int y;

					int correct = sscanf(c, "(%d,%d)", &x,&y);

					tmp = "";
					if (correct != 2){
			 			cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
			 			throw 20;
			 		}
					info.addInitialWireVal(x, y);
			
					commaFlag = false;
					continue; //so you dont flip commaflag...
				}

				if(ch == ',' && !commaFlag){
					commaFlag = true;
					tmp += ch;
					continue;
				}

				if(ch == ';'){
					const char * c = tmp.c_str(); 
					int x = 0;
					int y = 0;
					int correct = sscanf(c, "(%d,%d)", &x, &y);
					tmp = "";
					if (correct != 2){
				 		cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
				 		throw 20;
				 	}
					info.addInitialWireVal(x, y);
					gotWire = true;
					break;
				}

				tmp += ch; // if none of the above are met, then ch must be a part of a coordinate pair.
			}
		}
	}	
}