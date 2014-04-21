#include "InfoParser.h"
#include <sstream>

InfoParser::InfoParser() {

}

void InfoParser::parseName(InfoHolder &info, istream &file) {
	cerr << "---In Parse Name---\n";
	char equal = file.get(); //should be an equal sign
	char quotation = file.get(); // should be a quotation
	char endSemiC;
	string retVal;
	if (equal != '=' || quotation != '"') {
		throw 20;  // Not correct file format, throw an error
	}

	while (file.good()) {
		char c = file.get();
		if (c == '"')
			break;
		if (file.eof()) {
			throw 20;
		} //didn't find ending " so throw an error
		retVal = retVal + c; // I love C++.... look at that string addition!
	}
	endSemiC = file.get();
	if (endSemiC != ';') {
		throw 20;
	} // Name doesn't have ending ;, so throw an error
	info.setName(retVal);
	info.updateNameSet(true); // name is now set
	string test = info.getName();
	cerr << "The name parsed is: " << test << '\n';
	cerr << "---Out of Parse Name---\n";

}

void InfoParser::parseTerrain(InfoHolder &info, istream &file) {
	cerr << "---In Parse Terrain---\n";
	char ch;
	char gett;
	bool gotyrange = false;
	bool gotxrange = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{') {
		throw 20;  // Not correct file format, throw an error
	}

	while (true) {
		if (file.eof())
			throw 20; // File should never be end of file in this loop.
		string rangType = "";
		if (gotyrange && gotxrange) {
			gett = file.get();
			ch = file.get();
			if (gett != '}' && ch != ';')
				throw 20;
			else
				return;
		}

		for (int i = 0; i < 6; i++) {            //WILL NEED TO CHANGE LATER
			char cur = file.get();
			rangType = rangType + cur;
		}

		if (rangType.compare("Xrange") == 0) {
			gett = file.get();
			if (gett != '=')
				throw 20;

			string values;
			while (gett != ';') {
				gett = file.get();
				if (gett == ';')
					break;
				if (file.eof())
					throw 20;
				values += gett;
			}
			const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering
			int low;
			int high;
			int check = sscanf(c, "%d..%d;", &low, &high);
			cerr << " Terrain xrange low is: " << low
					<< "and Terrain xrange high is " << high << '\n';
			info.setxTerrainLowerBound(low);
			info.setxTerrainHigherBound(high);
			gotxrange = true;
		}

		if (rangType.compare("Yrange") == 0) { // if it is Yrange
			gett = file.get();
			if (gett != '=')
				throw 20; // MUST be equal, another check can't hurt
			string values;

			while (gett != ';') {
				gett = file.get();
				if (gett == ';')
					break;
				if (file.eof())
					throw 20;
				values += gett;
			}

			const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering
			//sscanf();
			int low;
			int high;
			int check = sscanf(c, "%d..%d;", &low, &high);
			info.setyTerrainLowerBound(low);

			info.setyTerrainHigherBound(high);
			cerr << " Terrain yrange low is: " << info.getxTerrainLowerBound()
					<< "and Terrain yrange high is "
					<< info.getxTerrainHigherBound() << '\n';

			gotyrange = true; // set to true so that if both gotx and goty are true, to break and search for the end bit.

		}

	}

}

void InfoParser::parseWindow(InfoHolder &info, istream &file) {
	cerr << "---In ParseWindow---\n";
	char ch;
	char gett;
	bool gotyrange = false;
	bool gotxrange = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{') {
		throw 20;  // Not correct file format, throw an error
	}

	while (true) {
		if (file.eof())
			throw 20; // File should never be end of file in this loop.
		string rangType = "";
		if (gotyrange && gotxrange) {
			gett = file.get();
			ch = file.get();
			if (gett != '}' && ch != ';')
				throw 20;
			else
				return;
		}

		for (int i = 0; i < 5; i++) {          //GET 6 CHARS FROM FILE
			char cur = file.get();
			rangType = rangType + cur;
		}

		if (rangType.compare("Xrange") == 0) {
			gett = file.get();
			if (gett != '=')
				throw 20;

			string values;
			while (gett != ';') {
				gett = file.get();
				if (gett == ';')
					break;
				if (file.eof())
					throw 20;
				values += gett;
			}
			const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering
			int low;
			int high;
			int check = sscanf(c, "%d..%d;", &low, &high);
			cerr << " Window xrange low is: " << low
					<< "and Window xrange high is " << high << '\n';

			info.setxWindowLowerBound(low);
			info.setxWindowHigherBound(high);
			info.updateWindowXSet(true);
			gotxrange = true;
		}

		if (rangType.compare("Yrange") == 0) { // if it is Yrange
			gett = file.get();
			if (gett != '=')
				throw 20; // MUST be equal, another check can't hurt
			string values;

			while (gett != ';') {
				gett = file.get();
				if (gett == ';')
					break;
				if (file.eof())
					throw 20;
				values += gett;
			}

			const char * c = values.c_str(); // change the values to c string for sscanf parsing of the low..high numbering
			//sscanf();
			int low;
			int high;
			int check = sscanf(c, "%d..%d;", &low, &high);
			cerr << " Window yrange low is: " << low
					<< "and Window yrange high is " << high << '\n';
			info.setyWindowLowerBound(low);
			info.setyWindowHigherBound(high);
			info.updateWindowYSet(true);
			gotyrange = true; // set to true so that if both gotx and goty are true, to break and search for the end bit.

		}

	}

	cerr << "--- Out of ParseWindow---\n";
}

void InfoParser::parseChars(InfoHolder &info, istream &file) {
	cerr << "-------------------inParsechars--------------------\n";
	char ch;
	char gett;
	bool gotAlive = false;
	bool gotDead = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{') {

		throw 20;  // Not correct file format, throw an error
	}
	while (true) {
		if (!file.good())
			throw 20; // File should never be end of file in this loop.
		string rangType = "";
		if (gotAlive && gotDead) {
			gett = file.get();
			ch = file.get();
			if (gett != '}' && ch != ';')
				throw 20;
			else {
				cerr
						<< "-------------------out of Parsechars--------------------\n";
				return;
			}
		}

		string AorD = "";
		string stringofVal = "";
		for (int i = 0; i < 5; i++) {          //GET 6 CHARS FROM FILE
			char cur = file.get();
			AorD = AorD + cur;
		}

		if (AorD.compare("Alive") == 0) {
			gett = file.get();

			if (gett != '=')
				throw 20;

			string values = "";
			while (gett != ';') {
				gett = file.get();
				if (file.eof())
					throw 20;
				if (gett == ';')
					break;
				values += gett;
			}
			const char * c = values.c_str();
			int val = 0;
			sscanf(c, "%d", &val);
			cerr << "Chars for alive is: " << val << '\n';
			info.setAliveChars(val);
			gotAlive = true;
		}

		if (AorD.compare("Dead=") == 0) {
			char current;
			string values = "";
			while (current != ';') {
				current = file.get();
				if (file.eof())
					throw 20;
				values += current;
			}

			const char * c = values.c_str();
			int val = 0;
			sscanf(c, "%d;", &val);
			cerr << "Chars for dead is: " << val << '\n';
			info.setDeadChars(val);
			gotDead = true;
		}

	}
	cerr << "----- out of parseChars------\n";
}
void InfoParser::parseColors(InfoHolder &info, istream &file) {
	cerr << "------- in of parseColors-----\n";
	char ch;
	char gett;
	bool gotAlive = false;
	bool gotDead = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{') {

		throw 20;  // Not correct file format, throw an error
	}
	while (true) {
		if (!file.good())
			throw 20; // File should never be end of file in this loop.
		string rangType = "";
		if (gotAlive && gotDead) {
			gett = file.get();
			ch = file.get();
			if (gett != '}' && ch != ';')
				throw 20;

			else {
				cerr << "------- out of parseColors-----\n";
				return;
			}
		}

		string AorD = "";
		string stringofVal = "";
		for (int i = 0; i < 5; i++) {          //GET 6 CHARS FROM FILE
			char cur = file.get();
			AorD = AorD + cur;
		}

		if (AorD.compare("Alive") == 0) {
			gett = file.get();
			if (gett != '=')
				throw 20;

			string values = "";
			while (gett != ';') {
				gett = file.get();

				if (file.eof())
					throw 20;
				if (gett == ';')
					break;
				values += gett;
			}
			const char * c = values.c_str();
			int val = 0;
			int val1 = 0;
			int val2 = 0;
			sscanf(c, "(%d, %d, %d)", &val, &val1, &val2);
			info.setAliveColors(val, val1, val2);
			gotAlive = true;
		}

		if (AorD.compare("Dead=") == 0) {
			char current;
			string values = "";
			while (current != ';') {
				current = file.get();
				if (file.eof())
					throw 20;
				if (current == ';')
					break;
				values += current;
			}

			const char * c = values.c_str();
			int val = 0;
			int val2 = 0;
			int val3 = 0;

			sscanf(c, "(%d,%d,%d)", &val, &val2, &val3);
			info.setDeadColors(val, val2, val3);
			gotDead = true;
		}

	}

}

void InfoParser::parseInitial(InfoHolder &info, istream &file) {
	cerr << "------ in parseInitial-------\n";
	char ch;
	char gett;
	bool gotAlive = false;
	char equal = file.get(); //should be an equal sign
	char openBracket = file.get(); // should be an open bracket
	if (equal != '=' || openBracket != '{') {
		throw 20;  // Not correct file format, throw an error
	}
	string alive = ""; // should fill to alive
	for (int i = 0; i < 5; i++) {
		ch = file.get();
		alive += ch;
	}
	if (alive.compare("Alive") != 0) {
		throw 20; // not equal to Alive, throw errors.
	}
	ch = file.get();
	if (ch != '=')
		throw 20; // if the next char after alive is not an equal, throw an error.
	string tmp = ""; //initialize a string to be used for values
	bool commaFlag = false; //true if a comma has already been passed over, meaning this comma seperates between coordinate pairs

	while (ch != ';') {
		ch = file.get();
		if (file.eof())
			throw 20;
		if (ch == ',' && commaFlag) {
			const char * c = tmp.c_str();

			int x;
			int y;
			int correct = sscanf(c, "(%d,%d)", &x, &y);
			tmp = "";
			if (correct != 2) {
				cerr
						<< "ERROR in parseInitial: sscanf failed, file not of proper format\n";
				throw 20;
			}
			info.setInitialVals(x, y);

			cerr << '\n';
			commaFlag = false;
			continue; //so you dont flip commaflag...
		}
		if (ch == ',' && !commaFlag) {
			commaFlag = true;
			tmp += ch;
			continue;
		}
		if (ch == ';') {
			const char * c = tmp.c_str();
			int x = 0;
			int y = 0;
			int correct = sscanf(c, "(%d,%d)", &x, &y);
			tmp = "";
			if (correct != 2) {
				cerr
						<< "ERROR in parseInitial: sscanf failed, file not of proper format\n";
				throw 20;
			}
			info.setInitialVals(x, y);
			vector<int> a = info.getInitialXVals();
			vector<int> b = info.getInitialYVals();
			for (int i = 0; i < a.size(); i++) {
				cerr << a.at(i) << ',' << b.at(i) << " ";

			}
			break;
		}

		tmp += ch; // if none of the above are met, then ch must be a part of a coordinate pair.
	}

	ch = file.get(); // if out of the loop, should be a }
	gett = file.get(); // if out of the loop, should be a ;

	if (ch != '}' && gett != ';')
		throw 20;
	cerr << "------ out of parseInitial-------\n";
}
