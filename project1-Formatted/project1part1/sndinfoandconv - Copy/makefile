
all: sndinfo sndconv

clean: 	
	rm -rf sndinfomain.o parser.o keyvaluefinder.o keyvaluefinderaiff.o durationCalc.o sndinfo sndconv  sndconvmain.o  atocs.o cstoa.o


tarball: proj1.tar.gz
	

proj1.tar.gz: makefile parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c atocs.c cstoa.c sndconvmain.c sndinfomain.c
	tar -czf cjjxnproj1part1.tar.gz makefile parser.h keyvaluefinder.h keyvaluefinderaiff.h durationcalc.h atocs.h cstoa.h sndinfomain.c parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c atocs.c cstoa.c sndconvmain.c README.txt


sndinfo: sndinfomain.c parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c
	gcc -ggdb -o sndinfo  sndinfomain.c  parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c

sndconv: atocs.c cstoa.c durationCalc.c parser.c keyvaluefinder.c keyvaluefinderaiff.c
	gcc -ggdb  -o sndconv  sndconvmain.c keyvaluefinderaiff.c keyvaluefinder.c atocs.c cstoa.c durationCalc.c parser.c





