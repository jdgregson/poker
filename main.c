#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <ctype.h>

#ifdef __unix__
    #include "unixcurs.h"
    #define CLEAR system("clear")
    #define BUFFER_FLUSH flushBuffer()
    #define PAUSE getchar()
    #define HEART "H"
    #define DIAMOND "D"
    #define SPADE "C"
    #define CLUB "S"
#endif
#ifdef _WIN32
    #include "wincurse.h"
    #define CLEAR system("cls")
    #define BUFFER_FLUSH fflush(stdin)
    #define PAUSE system("pause")
    #define HEART "3"
    #define DIAMOND "4"
    #define CLUB "5"
    #define SPADE "6"

#endif

typedef struct card 
{
    unsigned short face:4,
                   suit:2,
                   dealt:1,
                   discard:1;
} CARD;

char * face[14] = {"0","1","2","3","4","5","6","7","8","9","10","J","Q","K"};
char * suit[4] = {HEART, CLUB, SPADE, DIAMOND};

void buildDeck(CARD []);
void deal(CARD [], CARD []);
void discard(CARD [], CARD []);
void flushBuffer(void);
void printDOSHand(CARD[], CARD[]);
void printHand(CARD[], CARD[]);

main()
{
    int i = 0;
    int h = 0;//hand

    CARD deck[52];
    CARD hand[5];
    srand(time(NULL));

    buildDeck(deck);
    deal(deck,hand);
    printHand(deck,hand);

    CLEAR;
    xya(1, 30);

    printf("Welcome to video poker!");
    box(3, 1, 3, 80);

    xya(5, 27);

    printf(" Please choose a card to discard: ");

    discard(deck,hand);

    printHand(deck,hand);


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
void printHand(CARD deck[], CARD hand[])
{
	int i = 0;
	int e = 2; //14 spaces between each card.

	//printf("%c%c", face[hand[i].face], suit[hand[i].suit]);

	//xya(13, 2);
	//printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug
	//xya(13, 16);i++;
	//printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug
	//xya(13, 30);i++;
	//printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug
	//xya(13, 44);i++;
	//printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug
	//xya(13, 59);i++;
	//printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug



    while(i < 5)
    {
        xya(13, e);
        printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug , hand[i].suit
        i++;
        e = e+14;
    }

    box(12, 1, 12, 13); //first card

    box(12, 15, 12, 13);// second card

    box(12, 29, 12, 13); //third card

    box(12, 43, 12, 13);//fourth card

    box(12, 57, 12, 13);//fifth card
}
void flushBuffer(void)
{
    char c;
    while( (c = fgetc(stdin)) != '\n' && c != EOF);
}
