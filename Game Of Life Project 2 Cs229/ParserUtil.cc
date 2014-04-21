#include "ParserUtil.h"
#include "WireWorldParser.h"
#include "CellParser.h"
#include "WireInfo.h"

/*
*
* THE UGLIEST CLASS IN MY CODE. INHERITANCE WOULD HAVE HELPED HERE, NO TIME.
* This class acts as the main file parser, it uses the three infoparsers of each file to accurately parse the data based off of the file type.
* The data in these files are held in the various infoHolder classes, which each of their respective infoParsers populate.
*/


//Returns 1 if there is a window, and 0 otherwise
//This function is the meat of fileParser, and parses the life statement and by default, every struct in between. It is the handler of the FileParser Object
int lifeParser(InfoHolder &info, istream &file) {
	bool windowFound = false; //true if there is a window definition in the file, false otherwise
	bool charsFound = false;
	bool terrainFound = false;
	bool colorsFound = false;
	bool nameFound = false;
	bool initialFound = false;
	InfoParser ip;
	char c = file.get();
	char d = file.get();
	if (c != '=' || d != '{') {
		throw 20;
	}
	while (!file.eof()) {
		string chars = "";
		chars.clear();
		for (int i = 0; i < 7; i++) {
			c = file.get();
			if (file.eof()) {
				c = ' ';
			}
			chars.push_back(c);
		}

		//NAME CHECK
		if (chars.at(0) == 'N' && chars.at(1) == 'a' && chars.at(2) == 'm'
				&& chars.at(3) == 'e') {
			for (int i = 4; i < chars.length(); i++) {
				file.unget(); // Ungets the extra characters so they can be parsed by the methods
			}
			ip.parseName(info, file);
			nameFound = true;
		}

		//TERRAIN CHECK
		if (chars.at(0) == 'T' && chars.at(1) == 'e' && chars.at(2) == 'r'
				&& chars.at(3) == 'r' && chars.at(4) == 'a'
				&& chars.at(5) == 'i' && chars.at(6) == 'n') {
			ip.parseTerrain(info, file);
			terrainFound = true;
		}

		//INITIAL CHECK
		if (chars.at(0) == 'I' && chars.at(1) == 'n' && chars.at(2) == 'i'
				&& chars.at(3) == 't' && chars.at(4) == 'i'
				&& chars.at(5) == 'a' && chars.at(6) == 'l') {
			ip.parseInitial(info, file);
			initialFound = true;
		}

		// WINDOW CHECK
		if (chars.at(0) == 'W' && chars.at(1) == 'i' && chars.at(2) == 'n'
				&& chars.at(3) == 'd' && chars.at(4) == 'o'
				&& chars.at(5) == 'w') {
			file.unget();
			ip.parseWindow(info, file);
			windowFound = true;
		}

		// CHARS CHECK
		if (chars.at(0) == 'C' && chars.at(1) == 'h' && chars.at(2) == 'a'
				&& chars.at(3) == 'r' && chars.at(4) == 's') {
			for (int i = 5; i < chars.length(); i++) {
				file.unget();
			}
			ip.parseChars(info, file);
			charsFound = true;
		}

		//COLORS CHECK
		if (chars.at(0) == 'C' && chars.at(1) == 'o' && chars.at(2) == 'l'
				&& chars.at(3) == 'o' && chars.at(4) == 'r'
				&& chars.at(5) == 's') {
			file.unget(); // unget the equals	
			ip.parseColors(info, file);
			colorsFound = true;
		}

		if (chars.at(0) == '}' && chars.at(1) == ';') {

			if (colorsFound && charsFound && initialFound && terrainFound) {
				return 0;
			}

			throw 20; // Error, somehow fileparsing died.

		}

	}
}

int cellularAutoParser(CellInfo& info, istream& file) {
	for (int i = 0; i < 6; i++) {
			file.get();
		}

	bool windowFound = false; //true if there is a window definition in the file, false otherwise
	bool charsFound = false;
	bool terrainFound = false;
	bool colorsFound = false;
	bool nameFound = false;
	bool initialFound = false;
	bool ruleFound = false;
	CellParser ip;
	char c = file.get();
	char d = file.get();
	if (c != '=' || d != '{') {
		throw 20;
	}
	while (!file.eof()) {
		string chars = "";
		chars.clear();
		for (int i = 0; i < 7; i++) {
			c = file.get();
			if (file.eof()) {
				c = ' ';
			}
			chars.push_back(c);

		}

		try {
			//NAME CHECK
			if (chars.at(0) == 'N' && chars.at(1) == 'a' && chars.at(2) == 'm'
					&& chars.at(3) == 'e') {
				for (int i = 4; i < chars.length(); i++) {
					file.unget(); // Ungets the extra characters so they can be parsed by the methods
				}
				ip.parseName(info, file);
				nameFound = true;
			}

			//TERRAIN CHECK
			if (chars.at(0) == 'T' && chars.at(1) == 'e' && chars.at(2) == 'r'
					&& chars.at(3) == 'r' && chars.at(4) == 'a'
					&& chars.at(5) == 'i' && chars.at(6) == 'n') {
				ip.parseTerrain(info, file);
				terrainFound = true;
			}

			//INITIAL CHECK
			if (chars.at(0) == 'I' && chars.at(1) == 'n' && chars.at(2) == 'i'
					&& chars.at(3) == 't' && chars.at(4) == 'i'
					&& chars.at(5) == 'a' && chars.at(6) == 'l') {
				ip.parseInitial(info, file);
				initialFound = true;
			}
			//Rule CHECK
			if (chars.at(0) == 'R' && chars.at(1) == 'u' && chars.at(2) == 'l'
					&& chars.at(3) == 'e') {
				for( int i = 4; i < chars.length(); i++){
					file.unget();
				}
				ip.parseRule(info, file);

				cerr << "YOURE FREE!";
				ruleFound = true;
			}

			// WINDOW CHECK
			if (chars.at(0) == 'W' && chars.at(1) == 'i' && chars.at(2) == 'n'
					&& chars.at(3) == 'd' && chars.at(4) == 'o'
					&& chars.at(5) == 'w') {
				file.unget();
				ip.parseWindow(info, file);
				windowFound = true;
			}

			// CHARS CHECK
			if (chars.at(0) == 'C' && chars.at(1) == 'h' && chars.at(2) == 'a'
					&& chars.at(3) == 'r' && chars.at(4) == 's') {
				for (int i = 5; i < chars.length(); i++) {
					file.unget();
				}
				ip.parseChars(info, file);
				charsFound = true;
			}

			//COLORS CHECK
			if (chars.at(0) == 'C' && chars.at(1) == 'o' && chars.at(2) == 'l'
					&& chars.at(3) == 'o' && chars.at(4) == 'r'
					&& chars.at(5) == 's') {
				file.unget(); // unget the equals
				ip.parseColors(info, file);
				colorsFound = true;
			}

			if (chars.at(0) == '}' && chars.at(1) == ';') {
				if (colorsFound && charsFound && initialFound && terrainFound && ruleFound) {
					return 0;
				}

				throw 20; // Error, somehow fileparsing died.

			}
		} catch (int e) {
			throw e;
		}

	}
}

int wireInfoParser(WireInfo& info, istream& file) {

	for (int i = 0; i < 5; i++) {
			file.get();
		}
	//wireInfo.setTerrain(0,0,0,0);
	//WireInfo::Terrain ex = wireInfo.getTerrain();
	//cerr << "numbers are: " << ex.xlower << ex.xupper << '\n';
	bool windowFound = false; //true if there is a window definition in the file, false otherwise
	bool charsFound = false;
	bool terrainFound = false;
	bool colorsFound = false;
	bool nameFound = false;
	bool initialFound = false;
	WireWorldParser ip;
	char c = file.get();
	char d = file.get();
	if (c != '=' || d != '{') {
		throw 20;
	}
	while (!file.eof()) {
		string chars = "";
		chars.clear();
		for (int i = 0; i < 7; i++) {
			c = file.get();
			if (file.eof()) {
				c = ' ';
			}
			chars.push_back(c);

		}
		try {
			//NAME CHECK
			if (chars.at(0) == 'N' && chars.at(1) == 'a' && chars.at(2) == 'm'
					&& chars.at(3) == 'e') {
				for (int i = 4; i < chars.length(); i++) {
					file.unget(); // Ungets the extra characters so they can be parsed by the methods
				}
				ip.parseName(info, file);
				nameFound = true;
			}

			//TERRAIN CHECK
			if (chars.at(0) == 'T' && chars.at(1) == 'e' && chars.at(2) == 'r'
					&& chars.at(3) == 'r' && chars.at(4) == 'a'
					&& chars.at(5) == 'i' && chars.at(6) == 'n') {
				ip.parseTerrain(info, file);
				terrainFound = true;
			}

			//INITIAL CHECK
			if (chars.at(0) == 'I' && chars.at(1) == 'n' && chars.at(2) == 'i'
					&& chars.at(3) == 't' && chars.at(4) == 'i'
					&& chars.at(5) == 'a' && chars.at(6) == 'l') {
				ip.parseInitial(info, file);
				initialFound = true;
			}

			// WINDOW CHECK
			if (chars.at(0) == 'W' && chars.at(1) == 'i' && chars.at(2) == 'n'
					&& chars.at(3) == 'd' && chars.at(4) == 'o'
					&& chars.at(5) == 'w') {
				file.unget();
				ip.parseWindow(info, file);
				windowFound = true;
			}

			// CHARS CHECK
			if (chars.at(0) == 'C' && chars.at(1) == 'h' && chars.at(2) == 'a'
					&& chars.at(3) == 'r' && chars.at(4) == 's') {
				for (int i = 5; i < chars.length(); i++) {
					file.unget();
				}
				ip.parseChars(info, file);
				charsFound = true;
			}

			//COLORS CHECK
			if (chars.at(0) == 'C' && chars.at(1) == 'o' && chars.at(2) == 'l'
					&& chars.at(3) == 'o' && chars.at(4) == 'r'
					&& chars.at(5) == 's') {
				file.unget(); // unget the equals
				ip.parseColors(info, file);
				colorsFound = true;
			}

			if (chars.at(0) == '}' && chars.at(1) == ';') {
				if (colorsFound && charsFound && initialFound && terrainFound) {
					return 0;
				}

				throw 20; // Error, somehow fileparsing died.

			}
		} catch (int e) {
			throw e;
		}

	}
}

//head function forall parsers, this function will check the type of file and then send it off to its proper parser for info extraction and storage.
int fileParser(InfoHolder &lifeInfo, WireInfo& wireInfo, CellInfo& cellInfo,
		istream& file) {
	string chars;
	for (int i = 0; i < 4; i++) {
		char c = file.get();
		chars.push_back(c);
	}

	if (chars.at(0) == 'L' && chars.at(1) == 'i' && chars.at(2) == 'f'
			&& chars.at(3) == 'e') {
		try {
			lifeParser(lifeInfo, file);
			return 1;
		} catch (int e) {
			cerr
					<< "Error (in ParserUtil.cc, line 184):eSomething went wrong during fileparsing, check file and try again\n";
			throw e;
		}
	}

	if (chars.at(0) == 'W' && chars.at(1) == 'i' && chars.at(2) == 'r'
			&& chars.at(3) == 'e') {
	
		try {
			wireInfoParser(wireInfo, file);
			return 2;
		} catch (int e) {
			cerr
					<< "Error (in ParserUtil.cc, line 198):Something went wrong during fileparsing, check file and try again\n";
			throw e;
		}
	}

	if (chars.at(0) == 'E' && chars.at(1) == 'l' && chars.at(2) == 'e'
			&& chars.at(3) == 'm') {
		try{
			cellularAutoParser(cellInfo, file);
			return 3;
		} catch (int e){
			cerr    
					<< "Error in parserUtil @cellularAutoParser: Something went wrong during fileparsing, check file and try again\n";
			throw e;
		}
	}

	throw 20; //file was not correct.

}

//Strips the file of whitespace and comments, returned via temp.txt
void fileStripper(InfoHolder &info, istream& file) {
	bool comment = false;
	bool quotations = false;
	ofstream temp;
	temp.open("temp.txt");
	while (!file.eof()) { //while inputfile is not the  end of file
		char c = file.get();
		if (file.eof()) {
			break;
		} // if it scanned the eof bit break
		if (c == '"') {
			if (quotations == true) {
				quotations = false;
			} else {
				quotations = true;
			}
		}
		if (comment == true) { // if it is a comment...
			if (c == '\n' || c == '\r') {
				comment = false;
				continue;
			}
			continue;
		}
		if (quotations == false && c == ' ') {
			continue;
		}
		if (quotations == false && c == '#') {
			comment = true;
			continue;
		}
		temp << c; // copy the char to temp.
	}
	temp.close();

	ifstream read; //open another file.
	read.open("temp.txt");
	ofstream rawFile;
	rawFile.open("rawdata");

	while (read.good()) {
		char d = read.get();
		if (read.eof()) {
			break;
		} //basically, if the tempfile has a newline, remove it and copy all other output over to the final filebuffer
		if (d == '\n' || d == '\r') {
			continue;
		} else
			rawFile << d;
	}
	read.close();

}



//boilerplate empty file checking for bad files.
bool is_empty(std::fstream& pFile) {
	return pFile.peek() == std::fstream::traits_type::eof();
}

