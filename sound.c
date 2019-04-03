#include <stdio.h>
#include "sound.h"
#include <math.h>
void showID(char *idname,char *id){
	int i;
	printf("%s : ", idname);
	for(i=0; i<4; i++)	printf("%c", id[i]);
	puts("");
}
	//this function gets 1 sec of sample (16000), and cal 80 pieces of db value
	//we know we need to cal one db value 
	//from 200 samples, db value is cal by RMS formula
void displayWAVDATA(short s[]){
	double rms[80];
	short *ptr = s;	//we used a pointer, pointing to the beginning of array
	int i, j; 	//for nested loop counters, outer loop repeats 80times
				//inner loop repeats 200times
	for(i=0; i<80; i++){
		double sum = 0;	//accumulate sum of squares
		for(j=0; j<200; j++){
			sum += (*ptr) * (*ptr);
			ptr++; 	//pointing to the next sample
		}
		rms [i] = sqrt(sum/200);
		printf("rms[%d] = %f\n", i, rms[i]);
	}
}
void displayWAVHDR(struct WAVHDR h){
	showID("ChunkID", h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	showID("Format", h.Format);
	showID("SubchunkID", h.Subchunk1ID);
	printf("Subchunk1 size: %d\n", h.Subchunk1Size);
	printf("Audio Format: %d\n", h.AudioFormat);
	printf("Num. of Channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.SampleRate);
	printf("Byte rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits per sample: %d\n", h.BitsPerSample);
	showID("Subchunk2ID", h.Subchunk2ID);
	printf("Subchunk2 Size: %d\n", h.Subchunk2Size);
	// to be continue for other fields
}
