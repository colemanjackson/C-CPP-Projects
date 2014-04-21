#include "cstoa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "keyvaluefinderaiff.h"
#include "keyvaluefinder.h"
#include "durationcalc.h"


void FlipLong(unsigned char * ptr);
int startDataFinder(FILE* CS229File, AUDIO *SoundVar, FILE *outputFile);
void StoreFloat(unsigned char * buffer, unsigned long value);
void StoreLong(unsigned long val, unsigned long * ptr);



void cstoa(FILE *outputFile, FILE *CS229File, AUDIO *SoundVar){

	fwrite("FORM", 1, 4, outputFile);
	keyValueFinder229(CS229File, SoundVar);


	rewind(CS229File);

	int numBytes = 4 + 18 + 4 + 4 + 4 + 8 + 4 + (((SoundVar->numBitDepth * SoundVar->numSamples)/8) * SoundVar->numChannels);
	printf("%d\n", numBytes);
	char numBytesArray[4];

	numBytesArray[0]= (numBytes >> 24);
	numBytesArray[1] =(numBytes>>16);
	numBytesArray[2] = (numBytes>>8);
	numBytesArray[3] = numBytes; 

	fwrite(numBytesArray, 1, 4, outputFile);
	fwrite("AIFF", 1, 4, outputFile);


//COMM chunk Building



	fwrite("COMM", 1, 4, outputFile);
	char commChunkBytes[4];
	int commChunk = 18;
	commChunkBytes[0] = (commChunk >>24);
	commChunkBytes[1] = (commChunk >>16);
	commChunkBytes[2] = (commChunk >>8);
	commChunkBytes[3] = (commChunk);
	fwrite(commChunkBytes, 1, 4, outputFile);


	int numChannels = SoundVar->numChannels;
	char numChannelsArray[2];

	numChannelsArray[0] = numChannels >>8;
	numChannelsArray[1] = numChannels;
	
	fwrite(numChannelsArray, 1, 2, outputFile);


	int numSamples = SoundVar->numSamples;
	unsigned char numSamplesArray[4];

	numSamplesArray[0] = (numSamples >>24);
	numSamplesArray[1] = (numSamples >>16);
	numSamplesArray[2] = (numSamples >>8);
	numSamplesArray[3] = (numSamples);

	fwrite(numSamplesArray, 1, 4, outputFile);

	
	int sampleSize = SoundVar->numBitDepth;

	char sampleSizeArray[2];

		sampleSizeArray[0] = (sampleSize >>8);
		sampleSizeArray[1] = sampleSize;

	fwrite(sampleSizeArray, 1, 2, outputFile);
	

	unsigned long sampleRate = SoundVar->SampleRate;
	unsigned long buffer[10];
	
	StoreFloat(buffer, sampleRate); // not outputting correctly.
	fwrite(buffer, 1, 10, outputFile);



	//SSND block building
	fwrite("SSND", 1,4, outputFile);
	


	char ssndChunkBytes[4];

	int ssndChunk = 8 + (((SoundVar->numBitDepth * SoundVar->numSamples)/8) * SoundVar->numChannels);
	ssndChunkBytes[0] = (ssndChunk >>24);
	ssndChunkBytes[1] = (ssndChunk >>16);
	ssndChunkBytes[2] = (ssndChunk >>8);
	ssndChunkBytes[3] = (ssndChunk);
	fwrite(ssndChunkBytes, 1, 4, outputFile);
	int offset = 0;
	int blockSize =0;
	fwrite(&offset, 4,1, outputFile); //offset
	fwrite(&blockSize, 4,1, outputFile); //BlockSize
	

	rewind(CS229File);
	
	
	startDataFinder(CS229File, SoundVar, outputFile); // see below.








}

//Finds the start Data from the CS229 file
int startDataFinder(FILE* CS229File, AUDIO *SoundVar, FILE *outputFile){
	char keyWord[33];
	char line[100];
while( fgets(line, sizeof(line), CS229File) != NULL){
		
	           int keyWordVal;
		sscanf(line, "%s %d", keyWord, &keyWordVal); 
		if(keyWord[0] == 'S' && keyWord[1] == 't' && keyWord[2] =='a' && keyWord[3] == 'r' && keyWord[4] =='t' ){
			
				break;
		}	
}
	int i = 0;
	
	while(i < SoundVar->numSamples){
		int j = 0;
		while(j< SoundVar->numChannels){ //make sure in range for part 2
			int data;
			fscanf(CS229File, "%d", &data);
		
			if(SoundVar->numBitDepth == 8){
				fputc(data, outputFile);
			}
			if(SoundVar->numBitDepth == 16){
				unsigned char returnVal[2];
				returnVal[0] =  data>>8;
				returnVal[1] = data;
			
				fwrite(returnVal, 1, 2, outputFile);

			}

			if(SoundVar->numBitDepth ==32){
				unsigned char returnVal[4];
				returnVal[0] =  (data>>24);
				returnVal[1] = data>>16;
				returnVal[2] = data>>8;
				returnVal[3] = data;
				fwrite(returnVal, 1, 4, outputFile);
			}
			j++;
		}
	i++;
	}



}

void FlipLong(unsigned char * ptr)
	{
	   register unsigned char val;

	   /* Swap 1st and 4th bytes */
	   val = *(ptr);
	   *(ptr) = *(ptr+3);
	   *(ptr+3) = val;

	   /* Swap 2nd and 3rd bytes */
	   ptr += 1;
	   val = *(ptr);
	   *(ptr) = *(ptr+1);
	   *(ptr+1) = val;
	}

void StoreLong(unsigned long val, unsigned long * ptr)
	{
	   *ptr = val;
	}


void StoreFloat(unsigned char * buffer, unsigned long value) 
	{
	   unsigned long exp;
	   unsigned char i;

	   memset(buffer, 0, 10);

	   exp = value;
	   exp >>= 1;
	   for (i=0; i<32; i++) { exp>>= 1;
	      if (!exp) break;
	   }
	   *(buffer+1) = i;

	   for (i=32; i; i--)
	   {
	      if (value & 0x80000000) break;
	      value <<= 1; } StoreLong(value, buffer+2);  FlipLong((unsigned long *)(buffer+2));  } 