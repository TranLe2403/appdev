
#include <stdio.h>
#include "sound.h"
#include <math.h>
#include "screen.h"

void fillID(char *d, const char *s){
	for(int i=0; i<4; i++)	*d++ = *s++;
}

void testTone(int c, int fl, int fr, float d){
	if(c<1 || c>2){
		printf("Wrong num of channels.\n");
		return;
	}
	if(fl<50 || fl>16000){
		printf("Frequency is out of range\n");
		return;
	}
	if(d<1.0 || d>10.0){
		printf("Wrong duration\n");
		return;
	}

	//All the argument are okay, the rest of code is to
		//1) make a correct wave header
		//2) generate correct samples
		//3) write both header and samples to a file

	struct WAVHDR h;
	int samples = 44100*d, i;
	fillID(h.ChunkID, "RIFF");
	fillID(h.Format, "WAVE");
	fillID(h.Subchunk1ID, "fmt ");
	fillID(h.Subchunk2ID, "data");
	h.Subchunk1Size = 16; 	//constant value
	h.AudioFormat = 1;
	h.SampleRate = 44100;
	h.BitsPerSample = 16;
	h.BlockAlign = c*16/8;
	h.NumChannels = c;
	h.ByteRate = 44100*c*16/8;
	h.Subchunk2Size = samples*c*16000/8;
	h.ChunkSize = h.Subchunk2Size + 36;
	FILE *fp = fopen ("testTone.wav", "w");
	if(fp == NULL){
		printf("Cannot open a file\n");
		return;
	}
	fwrite(&h, sizeof(h), 1, fp);	// write rhe  header to file
		// generate samples and write to file
	for(i=0; i<samples; i++){
		short sL = 32767.0*sin(2*PI*fl*i/44100);
		fwrite(&sL, sizeof(short), 1, fp);
		if(c==2){
			short sR = 32767.0*sin(2*PI*fr*i/44100);
			fwrite(&sR, sizeof(short), 1 ,fp);
		}
	}	//end of for
	fclose(fp);	//close the file
	printf("testTone is generated!\n");
}
void showID(char *idname,char *id){
	int i;
	printf("%s : ", idname);
	for(i=0; i<4; i++)	printf("%c", id[i]);
	puts("");
}
int findpeaks(int d[]){
	int c = 0;
	for(int i=1; i<80; i++){
		if(d[i]>=75 && d[i-1]<75) c++;
	}
	if(d[0]>75) c++;
	return c;
}

	//this function gets 1 sec of sample (16000), and cal 80 pieces of db value
	//we know we need to cal one db value 
	//from 200 samples, db value is cal by RMS formula
void displayWAVDATA(short s[]){
	double rms[80];
	int dB[80]; 	//used to send db val ti barchart
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
#ifdef DEBUG
		printf("rms[%d] = %f\n", i, rms[i]);
#endif
		dB[i]=20*log10(rms[i]);
	}
#ifndef DEBUG
	bar_chart(dB);
	int peaks = findpeaks(dB);
	colors(WHITE, bg(BLACK));
	printf("\033[1;61H");
	printf("Peaks: %d           \n", peaks);
#endif
}
//this function is only called by displayWAVDATA(), so no need to put 
//a declaration in sound.h. The function finds how many peaks from 80-pieces of db values
void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
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
#else
	colors(WHITE, bg(RED));
	printf("\033[1;1H");
	printf("test.wav            ");

	colors(YELLOW, bg(BLUE));
	printf("\033[1;21H");
	printf("Sample rate:%dHz    ", h.SampleRate);

	colors(CYAN, bg(MAGENTA));
	printf("\033[1;41H");
	printf("Duration:%.2fsec    ",(float)h.Subchunk2Size/h.ByteRate);
	colors(RED, bg(YELLOW));
#endif
}
