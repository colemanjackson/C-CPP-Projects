make: all
all:sndedit sndinfo sndconv sndcat sndcut sndshow
clean: 	
	rm -rf sndshowmain.o sndshow sndinfomain.o sndcatmain.o parser.o keyvaluefinder.o keyvaluefinderaiff.o durationCalc.o sndinfo sndconv sndcat  sndconvmain.o sndchecklib.o atocs.o cstoa.o sndcutmain.o sndcut sndedit sndeditmain.o

tarball: proj1.tar.gz
	

proj1.tar.gz: makefile parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c atocs.c cstoa.c sndconvmain.c sndinfomain.c sndcatmain.c sndeditmain.c
	tar -czf cjjxnproj1.tar.gz makefile sndchecklib.c sndchecklib.h parser.h keyvaluefinder.h keyvaluefinderaiff.h durationcalc.h atocs.h cstoa.h sndinfomain.c parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c atocs.c cstoa.c sndconvmain.c README.txt sndshowmain.c sndcatmain.c sndcutmain.c sndeditmain.c

sndedit: atocs.c cstoa.c durationCalc.c parser.c keyvaluefinder.c keyvaluefinderaiff.c
	 gcc -ggdb  -o  sndedit  sndeditmain.c keyvaluefinderaiff.c keyvaluefinder.c atocs.c cstoa.c durationCalc.c parser.c sndchecklib.c -lncurses -lm

sndinfo: sndinfomain.c parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c
	gcc -ggdb -o sndinfo  sndinfomain.c  parser.c keyvaluefinder.c keyvaluefinderaiff.c durationCalc.c sndchecklib.c

sndconv: atocs.c cstoa.c durationCalc.c parser.c keyvaluefinder.c keyvaluefinderaiff.c
	gcc -ggdb  -o sndconv  sndconvmain.c keyvaluefinderaiff.c keyvaluefinder.c atocs.c cstoa.c durationCalc.c parser.c sndchecklib.c


sndcut: atocs.c cstoa.c durationCalc.c parser.c keyvaluefinder.c keyvaluefinderaiff.c
	 gcc -ggdb  -o sndcut  sndcutmain.c keyvaluefinderaiff.c keyvaluefinder.c atocs.c cstoa.c durationCalc.c parser.c sndchecklib.c


sndcat: atocs.c cstoa.c durationCalc.c parser.c keyvaluefinder.c keyvaluefinderaiff.c
	gcc -ggdb  -o sndcat  sndcatmain.c keyvaluefinderaiff.c keyvaluefinder.c atocs.c cstoa.c durationCalc.c parser.c sndchecklib.c

	
sndshow: atocs.c cstoa.c durationCalc.c parser.c keyvaluefinder.c keyvaluefinderaiff.c
	gcc -ggdb  -o  sndshow  sndshowmain.c keyvaluefinderaiff.c keyvaluefinder.c atocs.c cstoa.c durationCalc.c parser.c sndchecklib.c -lm
