#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <ctype.h>
#include"wincurse.h"

#ifdef __unix__
    #define CLEAR system("clear")
    #define BUFFER_FLUSH flushBuffer()
    #define PAUSE getchar()
    #define PRINTHAND printUNIXHand
    enum D_CHARS {
          VERT = '|',
          HORIZ = '_',
          L_T_CORN = '*',
          R_T_CORN = '*',
          L_B_CORN = '*',
          R_B_CORN = '*',
          T_TEE = '*',
          B_TEE = '*',
          L_TEE = '*',
          R_TEE = '*',
          CROSS = '+'
    };
#endif
#ifdef _WIN32
    #define CLEAR system("cls")
    #define BUFFER_FLUSH fflush(stdin)
    #define PAUSE system("pause")
    #define PRINTHAND printDOSHand
	    enum D_CHARS {
          VERT = '|',
          HORIZ = '_',
          L_T_CORN = '*',
          R_T_CORN = '*',
          L_B_CORN = '*',
          R_B_CORN = '*',
          T_TEE = '*',
          B_TEE = '*',
          L_TEE = '*',
          R_TEE = '*',
          CROSS = '+'
    };
#endif

typedef struct card 
{
    unsigned short face:4,
            suit:2,
            dealt:1,
	        discard:1;
} CARD;

char * face[14] = {"","1","2","3","4","5","6","7","8","9","10","J","Q","K"};
char * suit[4] = {"3","4","5","6"};

void buildDeck(CARD []);
void deal(CARD [], CARD []);
void discard(CARD [], CARD []);
void flushBuffer(void);
void printDOSHand(CARD[], CARD[]);
void printUNIXHand(CARD[], CARD[]);

main()
{
    int i = 0;
    int h = 0;//hand

    CARD deck[52];
    CARD hand[5];
    srand(time(NULL));

    buildDeck(deck);
    deal(deck,hand);
    PRINTHAND(deck,hand);

	discard(deck,hand);

	PRINTHAND(deck,hand);


	printf("Press any key to continue . . .");
    BUFFER_FLUSH;
	getchar();
    exit(0);
}
void buildDeck(CARD deck[])
{
    int f,s;//face suit
    int i = 0;
    
    for(s = 0; s < 4; s++)
    {	
        for(f = 1; f <= 13; f++)
            {
            deck[i].face = f;
            deck[i].suit = s;
            deck[i].dealt = 0;
			deck[i].discard = 0;
            i++;
            }
    }

}
void deal(CARD deck[], CARD hand[])
{
    int i;
    int h = 0;

    for(i = 0; i<52; i++)//clears deck 
    {
        deck[i].dealt = 0;
		deck[i].discard = 0;
    }

    while(h<5)
    {
        i = rand()%52;
        if(!deck[i].dealt)
        {
        deck[i].dealt = 1;
        hand[h] = deck[i];
        h++;
        }
    }
}
void discard(CARD deck[], CARD hand[])
{
    int i;
	int h;
	for(h = 0; h<5; h++)
    {
	  if(deck[h].discard == 1)
      {
        while(1)
        {
          i = rand()%52;
          if(!deck[i].dealt)
          {
          deck[i].dealt = 1;
          hand[h] = deck[i];
          break;
          }
		}
      }
	}
}
void printDOSHand(CARD deck[], CARD hand[])
{
	int i = 1;

	//printf("%c%c", face[hand[i].face], suit[hand[i].suit]);
	i++;

	box(12, 1, 12, 13); //first card

	box(12, 15, 12, 13);// second card

	box(12, 29, 12, 13); //third card

	box(12, 43, 12, 13);//fourth card

	box(12, 58, 12, 13);//fifth card

	xya(13, 2);

	printf("%c%c", hand[1].face, hand[2].suit); //debug
	i++;
}
void printUNIXHand(CARD deck[], CARD hand[])
{
	int i;
	int x, y;

	printf("%c", L_T_CORN);
	for(y=0; y<5; y++) {
		for(x = 0; x<8; x++) { printf("%c", HORIZ); }
		if(y<4) { printf("%c", T_TEE); }
	}
	printf("%c\n", R_T_CORN);

	printf("%c   1    %c   2    %c   3    %c   4    %c   5    %c\n", VERT, VERT, VERT, VERT, VERT, VERT);

	printf("%c", L_TEE);
	for(y=0; y<5; y++) {
		for(x = 0; x<8; x++) { printf("%c", HORIZ); }
		if(y<4) { printf("%c", CROSS); }
	}
	printf("%c\n", R_TEE);

	for(i=0;i<5;i++)printf("%c %c%2s    ", VERT, suit[hand[i].suit], face[hand[i].face]);
	printf("%c\n", VERT);
	printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	for(i=0;i<5;i++){ printf("%c    %-2s%c ", VERT, face[hand[i].face], suit[hand[i].suit]); }
	printf("%c\n", VERT);

	printf("%c", L_B_CORN);
	for(y=0; y<5; y++) {
		for(x = 0; x<8; x++) { printf("%c", HORIZ); }
		if(y<4) { printf("%c", B_TEE); }
	}
	printf("%c\n", R_B_CORN);

	printf("\n");
}
void flushBuffer(void)
{
	char c;
	while( (c = fgetc(stdin)) != '\n' && c != EOF);
}
