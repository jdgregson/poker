/**********************************************************/
/*PROGRAM:     unixcurs.h                                 */
/*AUTHOR:      Jonathan Gregson                           */
/*DESCRIPTION: Imitation of wincurs.h designed to provide */
/*             a few of the same screen access routines   */
/*             to the Unix/Linux BASH shell.              */
/* DATE:       March, 2013                                */
/**********************************************************/

#include <stdio.h>
#include <stdlib.h>

void cls(void);
void xya(int, int);
void box(int, int, int, int);
char GETCH(void);
char GETCHE(void);
void TextColor(short);

#define TEXT_BLACK 30
#define TEXT_RED 31
#define TEXT_GREEN 32
#define TEXT_YELLOW 33
#define TEXT_BLUE 34
#define TEXT_MAGENTA 35
#define TEXT_CYAN 36
#define TEXT_WHITE 37
#define BG_BLACK 40
#define BG_RED 41
#define BG_GREEN 42
#define BG_YELLOW 43
#define BG_BLUE 44
#define BG_MAGENTA 45
#define BG_CYAN 46
#define BG_WHITE 47

#define FORE_BLACK    0x0000
#define FORE_BLUE     0x0001
#define FORE_GREEN    0x0002
#define FORE_CYAN     0x0003
#define FORE_RED      0x0004
#define FORE_MAGENTA  0x0005
#define FORE_YELLOW   0x0006
#define FORE_WHITE    0x0007
#define FORE_BRIGHT   0x0008
#define BACK_BLACK    0x0000
#define BACK_BLUE     0x0010
#define BACK_GREEN    0x0020
#define BACK_CYAN     0x0030
#define BACK_RED      0x0040
#define BACK_MAGENTA  0x0050
#define BACK_YELLOW   0x0060
#define BACK_WHITE    0x0070
#define BACK_BRIGHT   0x0080
#define DEFAULT       0x0007


// FUNCTION: cls()
// PURPOSE:  Clears the console using an ASCII escape sequence.
void cls(void)
{
    printf("\033[2J");
    return;
}


// FUNCTION: xya(int row, int col)
// PURPOSE:  Position the cursor at row and col of the
//           console. Uses ASCII escape codes for cursor
//           position manipulation.
void xya(int row, int col)
{
    printf("\033[%d;%dH", row, col);
    return;
}


// FUNCTION: box(int r, int c, int l, int w)
// PURPOSE:  Draw a box to the screen using text
// INPUTS:   int r: start drawing at row r
//           int c: start drawing at col c
//           int l: the box is to be l long
//           int w: the box is to be w wide
void box(int r, int c, int l, int w)
{
    int i;
    w += w*.30;

    xya(r, c+1);
    for(i=1; i<w-1; i++)
    {
        putchar('_');
        xya(r, c+i);
    }

    for(i=1; i<l-1; i++)
    {
        xya(r+i, c);
        putchar('|');
        xya(r+i, c+w-2);
        putchar('|');
    }

    xya(r+l-1, c+1);
    for(i=1; i<w-1; i++)
    {
        putchar('-');
        xya(r+l-1, c+i);
    }

    return;
}


// FUNCTION: GETCH()
// PURPOSE : Get a single character from the standard input buffer
// RETURNS : The char received from the console
char GETCH(void)
{
    char character = getchar();
    return(character);
}


//FUNCTION: GETCHE()
//PURPOSE : Get a single character from the standard input buffer
//          and echo to screen
//RETURNS : The char received from the console
char GETCHE(void)
{
    char character = getchar();
    putchar(character);
    return(character);
}


//FUNCTION: TextColor(short color)
//PURPOSE : Set the console text color
void TextColor(short color)
{
    printf("\033[0;%dm", color);
    return;
}
