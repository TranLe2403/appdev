#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include <signal.h>
#include "sound.h"
#include <stdio.h>
int main(){
	FILE *f;
	short sd[RATE];
	for(;;){
		int ret = system(RCMD);
		if (ret == SIGINT) break;
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
		displayWAVDATA(sd);
	}
	reset_color();
	//getchar();
}
