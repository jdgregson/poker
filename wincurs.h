/***************************************************/
/*PROGRAM:     wincurs.h                           */
/*AUTHOR:      Steven Allyn Taylor                 */
/*DESCRIPTION: Revision of doscurs.h and curs.h    */
/*             to allow screen access routines to  */
/*             a majority of Windows platforms     */
/*REVISIONS:   (28NOV00)  Basic interface provided */
/*             to test applicationa on NT machines */
/***************************************************/
#ifndef WINCURS
#define WINCURS

#include <windows.h>

#define FORE_BLACK		0x0000
#define FORE_BLUE			0x0001
#define FORE_GREEN		0x0002
#define FORE_CYAN			0x0003
#define FORE_RED			0x0004
#define FORE_MAGENTA	0x0005
#define FORE_YELLOW   0x0006
#define FORE_WHITE    0x0007
#define FORE_BRIGHT		0x0008
#define BACK_BLACK		0x0000
#define BACK_BLUE			0x0010
#define BACK_GREEN		0x0020
#define BACK_CYAN			0x0030
#define BACK_RED			0x0040
#define BACK_MAGENTA	0x0050
#define BACK_YELLOW   0x0060
#define BACK_WHITE    0x0070
#define BACK_BRIGHT   0x0080
#define DEFAULT				0x0007



const short int _crs = 197,
                _hln = 196,
                _lte = 180,
                _tee = 194,
                _bte = 193,
                _ruc = 191,
                _llc = 192,
                _rte = 195,
                _vln = 179,
                _luc = 218,
                _rlc = 217,
                _cir = 248;

SHORT getConX(HANDLE);
SHORT getConY(HANDLE);
CHAR  GETCH(void);
CHAR	GETCHE(void);
int		PUTS(PCHAR);
void	cls(HANDLE);
void	SetText(DWORD);

void clr(void);
void xya(int ,int );
void ron(void);
void rof(void);
void bon(void);
void bof(void);
void box(int, int, int, int);
void boxEX(int, int, int, int, WORD);
void hln(int);
void vln(int);
void cdn(int);
void cup(int);
void clf(int);
void crt(int);

SHORT getConX(HANDLE hCon){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	return(csbi.dwSize.X);
}

//FUNCTION: getConY(HANDLE hCon)
//PURPOSE : To ge the current height of the console output buffer
//INPUT   : The handle to get the information for
//RETURNS : The height of the current console output buffer, in chars
SHORT getConY(HANDLE hCon){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	return(csbi.dwSize.Y);
}


//FUNCTION: xya(int row, int col)
//PURPOSE : Locate the cursor at row, col (1,1 as orgin)
//					Windows uses 0,0 as orgin.  Need to subtract 1
//					from row and col when accessing
//INPUT   : None
//RETURNS : None
void xya(int row,int col)
{
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coordScreen={0,0};
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	coordScreen.Y=(csbi.dwSize.Y<row-1)? csbi.dwSize.Y: (row>0)? row-1:0;
	coordScreen.X=(csbi.dwSize.X<col-1)? csbi.dwSize.X: (col>0)? col-1:0;
	SetConsoleCursorPosition(hConsole, coordScreen);
}


//FUNCTION: clr(HANDLE hConsole)
//PURPOSE : Clear the screen by filling it with blanks, then home cursor
//          Provided to use same interface as doscurs.h
//INPUT   : The handle of the output console
//RETURNS : None
void clr(void){
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	cls(hConsole);
}
 


//FUNCTION: cls(HANDLE hConsole)
//PURPOSE : Clear the screen by filling it with blanks, then home cursor
//INPUT   : The Console Buffer to clear
//RETURNS : None
void cls(HANDLE hConsole)
{
	COORD coordScreen={0,0};
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize=csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}

//FUNCTION: GETCH()
//PURPOSE : Get a single character from the standard input buffer
//INPUT   : None
//RETURNS : The char received from the console
CHAR GETCH(){
	HANDLE hStdIn;
	DWORD dwInputMode;
	CHAR chBuf;
	DWORD dwRead;

	hStdIn=GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdIn, &dwInputMode);
	SetConsoleMode(hStdIn, dwInputMode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
	ReadFile(hStdIn, &chBuf, sizeof(chBuf), &dwRead, NULL);
	SetConsoleMode(hStdIn, dwInputMode);
	return (chBuf);
}

//FUNCTION: GETCHE()
//PURPOSE : Get a single character from the standard input buffer and echo to screen
//INPUT   : None
//RETURNS : The char received from the console
CHAR GETCHE(){
	HANDLE hStdIn;
	DWORD dwInputMode;
	CHAR chBuf;
	DWORD dwRead;

	hStdIn=GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hStdIn, &dwInputMode);
	SetConsoleMode(hStdIn, dwInputMode & ~ENABLE_LINE_INPUT & ENABLE_ECHO_INPUT);
	ReadFile(hStdIn, &chBuf, sizeof(chBuf), &dwRead, NULL);
	SetConsoleMode(hStdIn, dwInputMode);
	return (chBuf);
}

//FUNCTION: PUTS(PCHAR s)
//PURPOSE : Write a string to the console buffer
//INPUT   : The string to write
//RETURNS : The number of characters written
int PUTS(PCHAR s){
	DWORD cCharsWritten;
	HANDLE hConsole;

	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(hConsole, s, strlen(s), &cCharsWritten, NULL);
	return((int) cCharsWritten);
}

void TextColor(WORD color){
	HANDLE hConsole;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void ron(void){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned char front;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
  front=csbi.wAttributes&0x000F;
	csbi.wAttributes>>=4;
	csbi.wAttributes|=(front<<4);
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	return;
}

void rof(void){
	ron();
}

void bon(void){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.wAttributes|=FORE_BRIGHT;
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	return;
}

void bof(void){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.wAttributes&=~FORE_BRIGHT;
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	return;
}

void box(int r,int c,int l,int w)
{
  xya(r,c);
  putchar(_luc);
  hln(w-2);
  putchar(_ruc);
	xya(r+1,c);
  vln(l-2);
  xya(r+1,c+w-1);
  vln(l-2);
  xya(r+l-1,c);
  putchar(_llc);
  hln(w-2);
  putchar(_rlc);
  xya(r+l,1);
}

void boxEX(int r,int c,int l,int w, WORD color)
{
	WORD oldColor;
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	oldColor=csbi.wAttributes;
	SetConsoleTextAttribute(hConsole, color);
  xya(r,c);
  putchar(_luc);
  hln(w-2);
  putchar(_ruc);
  xya(r+1,c);
  vln(l-2);
  xya(r+1,c+w-1);
  vln(l-2);
  xya(r+l-1,c);
  putchar(_llc);
  hln(w-2);
  putchar(_rlc);
  xya(r+l,1);
	SetConsoleTextAttribute(hConsole, oldColor);
}

void vln(int n){
	for(;n>0;n--){
    putchar(_vln);
		clf(1);
		cdn(1);
	}
	return;
}

void hln(int n){
  for(;n>0;n--)
    putchar(_hln);
}

void cdn(int n){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.Y+=n;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void cup(int n){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.Y+=n;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void crt(int n){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X+=n;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void clf(int n){
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.dwCursorPosition.X-=n;
	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void msg(int r,int c, PCHAR s, WORD color){
	WORD oldColor;
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	oldColor=csbi.wAttributes;
	SetConsoleTextAttribute(hConsole, color);
  xya(r,c);
	PUTS(s);
	SetConsoleTextAttribute(hConsole, oldColor);
}



#endif //#ifndef WINCURS