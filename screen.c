
//This file contains screen function, they are used to display 
//some level on a screen as a bar chart

#include <stdio.h>
#include "screen.h"
//#define MAX 60
void bar_chart(int db[]){
	int i, j;
	for(i=0; i<COL; i++){	// This will make 80 cols
		for(j=0; j<db[i]/3; j++){
			if(j*3 > 60 && j>20)	colors(GREEN, bg(YELLOW));
			else colors(RED, bg(YELLOW));
			printf("\033[%d;%dH", 60-j, i+1);

#ifdef UNICODE 	// conditional compilation
			printf("%s", BAR);
#else
			printf("%c", '*');
#endif
		}
	}
}

void clearscreen(void){
	printf("\033[2J");
	fflush(stdout);	// for remote terminal (such as Putty)
}

void colors(short bg, short fg){
	printf("\033[%d;%d;1m", bg, fg);
	fflush(stdout);
}

void reset_color(void){
	printf("\033[0m");
	fflush(stdout);
}

