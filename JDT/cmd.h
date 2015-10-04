//----------------------------------------------------------------------------
// cmd.h
// 콘솔 창 제어 함수
//----------------------------------------------------------------------------

#ifndef cmdH
#define cmdH

// 폰트색
#define CC_FONT_BLACK     0   // 검정
#define CC_FONT_GRAY      7   // 회색
#define CC_FONT_BLUE      9   // 파랑
#define CC_FONT_GREEN     10  // 녹색
#define CC_FONT_RED       12  // 빨강
#define CC_FONT_YELLOW    14  // 노랑
#define CC_FONT_WHITE     15  // 흰색

// 배경색
#define CC_BACK           0
#define CC_BACK_DBLUE     16
#define CC_BACK_DGREEN    32
#define CC_BACK_DRED      64
#define CC_BACK_DYELLOW   96
#define CC_BACK_DWHITE    112

// 밝은 배경색
#define CC_BACK_GRAY      128
#define CC_BACK_BLUE      144
#define CC_BACK_GREEN     160
#define CC_BACK_RED       192
#define CC_BACK_YELLOW    224
#define CC_BACK_WHITE     240


// 콘솔 창의 화면의 모든 텍스트를 지운다
void cls();

// 콘솔 창의 커서 위치를 옴긴다
void gotoxy(int x, int y);

// 콘솔 창의 커서 위치를 얻는다
void getpos(int *x, int *y);

// 텍스트 색을 바꾼다
// text = 텍스트 색
// back = 텍스트 배경색
void textcolor(unsigned int text, unsigned int back);

// 콘솔 창의 타이틀명을 바꾼다
void cmd_title(const char *caption);

// 콘솔 창에 가로 선을 그려준다
void drawline(int x, int y, int endx);

#endif
