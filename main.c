#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"wincurse.h"
#include<string.h>
#include <ctype.h>

#ifdef __unix__
#define CLEAR system("clear");
#define BUFFER_FLUSH flushBuffer()
#define PAUSE getchar();
#else defined _WIN32
#define CLEAR system("cls");
#define BUFFER_FLUSH fflush(stdin);
#define PAUSE system("pause");
	enum D_CHARS {
		VERT = 124,
		HORIZ = 205,
		L_T_CORN = 201,
		R_T_CORN = 187,
		L_B_CORN = 200,
		R_B_CORN = 188,
		T_TEE = 203,
		B_TEE = 202,
		L_TEE = 204,
		R_TEE = 185,
		CROSS = 206
	};
#endif

typedef struct card 
{
    unsigned short face:4,
            suit:2,
            dealt:1;
} CARD;

char * face[14] = {"","1","2","3","4","5","6","7","8","9","10","J","Q","K"};
char * suit[4] = {"H","D","C","S"};

void buildDeck(CARD []);
void deal(CARD [], CARD []);
void discard(CARD [], CARD *);
void flushBuffer(void);
void printHand(void);

main()
{
    int i = 0;
    int h = 0;//hand

    CARD deck[52];
    CARD hand[5];
    srand(time(NULL));

    buildDeck(deck);
    deal(deck,hand);

    //discard(deck,&hand[h]);

    /*for(i=0;i<52;i++) 
    {
        printf("\n%s of %s",face[deck[i].face],suit[deck[i].suit]);
    }
    for(h=0; h<5;h++)
    {
        printf("\n%s of %s",face[hand[h].face],suit[hand[h].suit]);
    }
    for(h=0; h<5;h++)
    {
        discard(deck,&hand[h]);
    }
    printf("\n\n");
    for(h=0; h<5;h++)
    {
        printf("\n%s of %s",face[hand[h].face],suit[hand[h].suit]);
    }
	deal(deck,hand);
    for(h=0; h<5;h++)
    {
        printf("\n%s of %s",face[hand[h].face],suit[hand[h].suit]);
    }*/


	printf("Press any key to continue . . .");
    BUFFER_FLUSH
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

	printHand(deck, hand);

}
void discard(CARD deck[], CARD * card)
{
    int i;
    while(1)
    {
        i = rand()%52;
        if(!deck[i].dealt)
        {
        deck[i].dealt = 1;
        *card = deck[i];
        break;
        }
    }

}
void printHand(CARD deck[], CARD hand[])
{
	int x = 0;
	int y = 0;


	box(30, 1, 12, 13);

	box(30, 15, 12, 13);

	box(30, 29, 12, 13);

	box(30, 43, 12, 13);

	box(30, 58, 12, 13);

	


	//	int i;
	//int x, y;

	//printf("%c", L_T_CORN);
	//for(y=0; y<5; y++) {
	//	for(x = 0; x<8; x++) { printf("%c", HORIZ); }
	//	if(y<4) { printf("%c", T_TEE); }
	//}
	//printf("%c\n", R_T_CORN);

	//printf("%c   1    %c   2    %c   3    %c   4    %c   5    %c\n", VERT, VERT, VERT, VERT, VERT, VERT);

	//printf("%c", L_TEE);
	//for(y=0; y<5; y++) {
	//	for(x = 0; x<8; x++) { printf("%c", HORIZ); }
	//	if(y<4) { printf("%c", CROSS); }
	//}
	//printf("%c\n", R_TEE);

	//for(i=0;i<5;i++)printf("%c %c%2s    ", VERT, suit[hand[i].suit], face[hand[i].face]);
	//printf("%c\n", VERT);
	//printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	//printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	//printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	//printf("%c        %c        %c        %c        %c        %c\n", VERT, VERT, VERT, VERT, VERT, VERT);
	//for(i=0;i<5;i++){ printf("%c    %-2s%c ", VERT, face[hand[i].face], suit[hand[i].suit]); }
	//printf("%c\n", VERT);

	//printf("%c", L_B_CORN);
	//for(y=0; y<5; y++) {
	//	for(x = 0; x<8; x++) { printf("%c", HORIZ); }
	//	if(y<4) { printf("%c", B_TEE); }
	//}
	//printf("%c\n", R_B_CORN);

	//printf("\n");
}
void flushBuffer(void)
{
	char c;
	while( (c = fgetc(stdin)) != '\n' && c != EOF);
}
