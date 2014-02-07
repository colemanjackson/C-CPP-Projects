#include "CellParser.h"

CellParser::CellParser() {

}

void CellParser::parseName(CellInfo& info, istream& file) {
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
	
}

void CellParser::parseWindow(CellInfo& info, istream& file) {
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

void CellParser::parseTerrain(CellInfo& info, istream& file) {
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

void CellParser::parseChars(CellInfo& info, istream& file) {
char ch;

	char gett;

	bool gotOne = false;

	bool gotZero = false;

	int oneVal = 0;

	int zeroVal = 0;


	char equal = file.get(); //should be an equal sign

	char openBracket = file.get(); // should be an open bracket


	if (equal != '=' || openBracket != '{'){
		
		throw 20;  // Not correct file format, throw an error
	}

	while (true){
		if (!file.good()) throw 20; // File should never be end of file in this loop.
		string rangType = "";
		
		if ( gotOne && gotZero){
			info.setChars(oneVal, zeroVal);
			gett = file.get();
			ch = file.get();

			if(gett != '}' && ch != ';') throw 20;

			else{

				return;

			}
		}




		string AorD = "";
		string stringofVal = "";
		for (int i = 0; i < 4; i++){         
			char cur = file.get();
			AorD = AorD + cur;
		}

		if  (AorD.compare("Zero") == 0){
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
	
		sscanf(c, "%d", &zeroVal);
		gotZero = true;
		}


	
		if  (AorD.compare("One=") == 0){
			char current;
			string values = "";
			while(current != ';'){
				current = file.get();
				if(file.eof()) throw 20;
					values += current;
			}

		const char * c = values.c_str(); 
	
		sscanf(c, "%d;", &oneVal);
		gotOne = true;
		}

 
	}
}

void CellParser::parseColors(CellInfo& info, istream& file) {
	char ch;
	char gett;
	bool gotOne = false;
	bool gotZero = false;
	

	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{'){

		throw 20;  // Not correct file format, throw an error
	}
	while (true){
		if (!file.good()) throw 20; // File should never be end of file in this loop.
		string rangType = "";
		if (gotZero && gotOne){
			gett = file.get();
			ch = file.get();
			if(gett != '}' && ch != ';') throw 20;

			else {
					return;
			}
		}

	
		string AorD = "";
	string stringofVal = "";
	for (int i = 0; i < 4; i++){          //GET 6 CHARS FROM FILE
		char cur = file.get();
		AorD = AorD + cur;
	}


	if  (AorD.compare("Zero") ==0){
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
	info.setocColors(val, val1, val2);
	gotOne= true;
	}

	if  (AorD.compare("One=") == 0){
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
	info.setzcColors(val, val2, val3 );
	gotZero = true;
	}


	}
}

void CellParser::parseInitial(CellInfo& info, istream& file) {
	char ch;
	char gett;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{'){
		throw 20;  // Not correct file format, throw an error
	}

		string alive = ""; // should fill to alive

		if (!file.good()) throw 20;  // if file is in anyway problomatic, throw error
		
		for (int i = 0; i < 3; i++){
			ch = file.get();
			alive += ch;
		}


		if(alive.compare("One")== 0){
			;
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
					info.addInitialOneVals(x, y);
			
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
					cerr << x << y <<'\n';
					int correct = sscanf(c, "(%d,%d)", &x, &y);
					tmp = "";
					cerr << x << y <<'\n';
					if (correct != 2){
				 		cerr << "ERROR in parseInitial: sscanf failed, file not of proper format\n";
				 		throw 20;
				 	}
					info.addInitialOneVals(x, y);
					break;
				}

				tmp += ch; // if none of the above are met, then ch must be a part of a coordinate pair.
				cerr << tmp << '\n';
			}

		}


	ch = file.get(); // if out of the loop, should be a }
	gett = file.get(); // if out of the loop, should be a ;

	if (ch != '}' && gett != ';'){ 
		

		throw 20;

	}
		return;
	
}

void CellParser::parseRule(CellInfo& info, istream& file) {
	char equal = file.get(); //should be an equal sign
	char ch;
	string retVal = "";
	int setVal;
	if (equal != '=') {
		throw 20;  // Not correct file format, throw an error
	}
	while((ch = file.get())!= ';') {
		if(file.eof()) throw 20;
		retVal += ch;
	}
	const char * c = retVal.c_str();
	int check = sscanf(c, "%d", &setVal);
	if( check != 1) throw 20;
	info.setRule(setVal);
	return;
}