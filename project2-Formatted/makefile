make: all
all: life 
clean: 	
	rm -rf rawdata DisplayHelperMethods.o GenerationHelperMethods.o InfoHolder.o InfoParser.o lifemain.o ParserUtil.o WireInfo.o WireWorldParser.o CellInfo.o CellParser.o life

tarball: proj2.tar.gz

	
proj2.tar.gz: 
	tar -czf cjjxnproj2.tar.gz makefile DisplayHelperMethods.h GenerationHelperMethods.h GenerationHelperMethods.cc DisplayHelperMethods.cc WireWorldParser.h WireWorldParser.cc CellParser.h CellParser.cc WireInfo.h WireInfo.cc CellInfo.h CellInfo.cc ParserUtil.h ParserUtil.cc InfoHolder.h InfoHolder.cc InfoParser.h InfoParser.cc README.txt lifemain.cc

	
life: InfoHolder.o InfoParser.o lifemain.o ParserUtil.o WireInfo.o CellInfo.o CellParser.o WireWorldParser.o DisplayHelperMethods.o GenerationHelperMethods.o
	g++ -ggdb -o life InfoHolder.o CellParser.o InfoParser.o lifemain.o ParserUtil.o WireInfo.o CellInfo.o WireWorldParser.o GenerationHelperMethods.o DisplayHelperMethods.o

lifemain.o: lifemain.cc
	g++ -ggdb -c lifemain.cc

InfoHolder.o:	InfoHolder.cc InfoHolder.h
	g++ -ggdb -c InfoHolder.cc

WireInfo.o: WireInfo.cc WireInfo.h
	g++ -ggdb -c WireInfo.cc

CellInfo.o: CellInfo.cc CellInfo.h
	g++ -ggdb -c CellInfo.cc

InfoParser.o: InfoParser.cc InfoParser.h
	g++ -ggdb -c InfoParser.cc
	
WireWorldParser.o: WireWorldParser.h WireWorldParser.cc
	g++ -ggdb -c WireWorldParser.cc

CellParser.o: CellParser.h CellParser.cc
	g++ -ggdb -c CellParser.cc
	
ParserUtil.o: ParserUtil.h ParserUtil.cc InfoParser.h InfoParser.cc InfoHolder.h InfoHolder.cc
	g++ -ggdb -c ParserUtil.cc

GenerationHelperMethods.o: GenerationHelperMethods.cc GenerationHelperMethods.h
	g++ -ggdb -c GenerationHelperMethods.cc

DisplayHelperMethods.o: DisplayHelperMethods.cc DisplayHelperMethods.h
	g++ -ggdb -c DisplayHelperMethods.cc
