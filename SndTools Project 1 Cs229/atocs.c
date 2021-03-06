#include "atocs.h"
#include <stdio.h>
#include "parser.h"
#include "keyvaluefinderaiff.h"
#include "durationcalc.h"
void atocs(FILE *outputFile, FILE *CS229File, AUDIO *SoundVar){
	unsigned char line[10800];
	
	
	keyValueFinderAIFF(CS229File, SoundVar);
	
	//PRINT CS229 FILE
	fprintf(outputFile, "CS229\n");
	fprintf(outputFile, "SampleRate %d\n", SoundVar->SampleRate);
	fprintf(outputFile, "Channels %d\n", SoundVar->numChannels);
	fprintf(outputFile, "BitDepth %d\n", SoundVar->numBitDepth);
	fprintf(outputFile, "Samples %d\n", SoundVar->numSamples);
	fprintf(outputFile, "StartData\n");
	
	rewind(CS229File);
	int i;
	fgets(line, 108000, CS229File);
		for(i=0; i < sizeof(line); i++){  //brute force method of getting the data. It's getting loopy up in here.
			if (line[i] =='S' && line[(i+1)] == 'S' && line[(i+2)] =='N' && line[i+3] == 'D'){
				break;
			}
	
		}
		unsigned char placeholder[2];
		unsigned char  placeholder2[4];
		fseek(CS229File, i+16, SEEK_SET);
		int numberChannels = SoundVar->numChannels;
		int f = 0;
		while(f != (SoundVar->numSamples * numberChannels)){
			if (SoundVar->numBitDepth == 8){
			 
				char c = fgetc(CS229File);
				fprintf(outputFile, "%d ", c);
				f++;
				if (f%numberChannels == 0){
				fprintf(outputFile, "\n");

				}

			}
			if(SoundVar->numBitDepth ==16){
				char c = fgetc(CS229File) << 8 | fgetc(CS229File);
				fprintf(outputFile, "%d ", c);
				f++;	
				if (f%numberChannels == 0){
					fprintf(outputFile, "\n");

				}	
		
			} 
			if(SoundVar->numBitDepth ==32){
				
				
				unsigned int c  = fgetc(CS229File) << 24| fgetc(CS229File)<< 16| fgetc(CS229File) << 8|fgetc(CS229File);
				fprintf(outputFile, "%d ", c);
				f++;	
				if (f%numberChannels == 0){
					fprintf(outputFile, "\n");

				}


			}

		
		}



}


