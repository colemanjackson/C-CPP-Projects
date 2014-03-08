#ifndef sndchecklib_h
#define sndchecklib_h
#include <stdio.h>

long sampleRateChecker(FILE *workingFile);
int bitDepthChecker(FILE* workingFile);
int channelChecker(FILE *workingFile);

#endif
