#include <stdlib.h>
#include <time.h>
#include "screen.h" 
int main(){
	int dec[COL];		//80.pieces of sound
	srand(time(NULL));
	for(int i=0; i<COL; i++) dec[i] = rand()%70+30;
	clearscreen();
	colors(RED, bg(YELLOW));
	bar_chart(dec);
//	printf("message from main\n");
	reset_color();
	getchar();	
}
