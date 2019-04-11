#include <stdlib.h>
//#include <time.h>
#include "screen.h"
#include <signal.h>
#include "sound.h"
#include <stdio.h>
#include "comm.h"

int main(int argc, char **argv){
	if(argc>1){	//if the user has given some command line argument
		printf("Test tone generator\n");
		int fR, fL, ch;
		float duration;
		printf("No. of channels (1 or 2): ");
		scanf("%d", &ch);
		if(ch==1){
			printf("Normal frequency: ");
			scanf("%d", &fL);
		}
		else if(ch==2){
			printf("Give me left and right frequency: ");
			scanf("%d %d", &fL, &fR)
		}
		else{
			printf("Wrong num of channels");
			return 1;
		}
		printf("Duration of sound: ");
		scanf("%f", &duration)
		testTone(ch, fL, fR, duration);
		return 0;
	}
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
		struct WAVHDR hdr;
		fread(&hdr, sizeof(hdr), 1, f);	// read WAV header
		fread(&sd, sizeof(sd), 1, f);	//read wav data
		fclose(f);
		displayWAVHDR(hdr);
		displayWAVDATA(sd);
		sendDATA(sd);
	}
	reset_color();
	//getchar();
}
