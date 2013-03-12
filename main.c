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
    #define HEART "H"
    #define DIAMOND "D"
    #define SPADE "C"
    #define CLUB "S"
#endif
#ifdef _WIN32
    #define CLEAR system("cls")
    #define BUFFER_FLUSH fflush(stdin)
    #define PAUSE system("pause")
    #define HEART 3
    #define DIAMOND 4
    #define CLUB 5
    #define SPADE 6

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

	xya(1, 30);

	printf("Welcome to video poker!");
	box(3, 1, 3, 80);

	xya(5, 27);

	printf(" Please choose a card to discard: ");

	//do input for discard function here. (scanf for x's don't forget the toupper)

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
	int a = 2; //14 spaces between each card.
	int b = 10;

	while(i < 5)
	{
		xya(13, a);
		printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug , face[hand[i].face], suit[hand[i].suit]
		i++; 
		a = a+14;
	}
	i = 0;
	while(i < 5)
	{
		xya(22, b);
		printf("%s%c", face[hand[i].face], suit[hand[i].suit]); //debug , hand[i].suit
		i++; 
		b = b+14;
	}


	xya(14, 27);

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
