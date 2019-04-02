#include <stdlib.h>
#include <time.h>
#include "screen.h" 
#include "sound.h"
#include <stdio.h>
int main(){
	FILE *f;
	short sd[80000];
	for(;;){
		system(RCMD);
		f = fopen("test.wav", "r");
		if(f==NULL){
			printf("cannot open the file\n");
			return 1;
		}
		clearscreen();
		colors(RED, bg(YELLOW));
		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1, f);	// read WAV header
		fread(&sd, sizeof(sd), 1, f);	//read wav data
		fclose(f);
		displayWAVHDR(hdr);
		//displayWAVDATA();
	}
	reset_color();
	getchar();	
}
