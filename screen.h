

#define UNICODE
enum COLORS {BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
#define bg(c) (c+10)
#define COL 80
#define BAR "\u2590"
// function declaration 

void clearscrn(void);
void colors(short, short);
void reset_color(void);
void bar_chart(int []);
