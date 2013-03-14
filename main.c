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
    #define HEART 72
    #define DIAMOND 68
    #define SPADE 67
    #define CLUB 83
#endif
#ifdef _WIN32
    #include "wincurs.h"
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
                   discard:2;//Needs more than one bit
} CARD;

char * face[14] = {"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};//Changed 1 to Ace
char suit[4] = {HEART, CLUB, SPADE, DIAMOND};

int maximum = 500;
int wager;

void buildDeck(CARD []);
void deal(CARD [], CARD []);
void discard(CARD [], CARD []);
void flushBuffer(void);
void printHand(CARD[], CARD[]);
void printScore(int);
int score(CARD[]);
void discardCards(CARD[]);
main()
{
    int i = 0;
    int h = 0;//hand
	int count = 0;
	int e = 6;

	char choice = 'Y';

    CARD deck[52];
    CARD hand[5];
    srand(time(NULL));

    buildDeck(deck);


	while(toupper(choice) == 'Y' && maximum > 0 && wager <= maximum)
	{
	   choice = 0;
	   deal(deck,hand);

           CLEAR;
           xya(1, 30);

           printf("Welcome to video poker!");
           box(3, 1, 3, 80);

		printf("\n\n Funds available: %d", maximum);
	    printf("\n\nEnter amount you'd like to bet: ");
		scanf("%d", &wager);
	    BUFFER_FLUSH;

	    xya(5, 27);

            printf(" Please choose a card to discard: ");

	    printHand(deck,hand);

	    while(count < 5)
		 {
		 	xya(26, e);
			printf("[  ]");
			count++;
			e = e+14;
		 }count = 0;e = 6;
		

	    discardCards(hand);
            discard(deck,hand);
	    CLEAR;
	    printHand(deck,hand);
	    xya(26, 1);
	    printScore(score(hand));
            printf("\nPlay again?");
	    scanf("%c", &choice);
            BUFFER_FLUSH;
	    CLEAR;
	    wager = 0;
	
	}

    printf("Thanks for playing!");
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
    int check = 0;


    for(i=0;i<5;i++)
    {
		check += hand[i].discard;	
    }
	if(check == 10)
	{
        hand[0] = deck[9];
        hand[1] = deck[10];
        hand[2] = deck[11];
        hand[3] = deck[12];
        hand[4] = deck[0];
		return;
	}

	for(h = 0; h<5; h++)
    {
      if(hand[h].discard == 1)
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
int score(CARD * hand)
{
    /*  return values
    *
    *  0: nothing
    *  1: pair, jacks or better
    *  2: two-pair
    *  3: three-of-a-kind
    *  4: straight
    *  5: flush
    *  6: full house
    *  7: four-of-a-kind
    *  8: straight flush
    *  9: royal flush
    */

    int values[14] = {0};
    int i;
    int flag = 0;
    int isStraight = 0;
    int isFlush = 0;

    // go through the hand and record the cards that we have
    for(i=0; i<5; i++)
    {
        (values[hand[i].face])++;
    }

    // check for flush
    flag = 1;
    for(i=0; i<4; i++)
    {
        if(!(hand[i].suit == hand[i+1].suit))
        {
            flag = 0;
            break;
        }
    }
    if(flag)
    {
        isFlush = 1;
    }

    // check for straight
    flag = 0;
    for(i=1; i<14; i++)
    {
        if(values[i] == 1)
        {
            flag++;
            if(flag == 5)
            {
                break;
            }
        }
        else
        {
            flag = 0;
        }
    }
    if(flag == 5)
    {
        isStraight = 1;
    }

    // check for royal flush
    if(values[1] && values[10] && values[11] && values[12] && values[13])
    {
        if(isFlush)
        {
            return(9);
        }
    }

    // check for straight flush
    if(isStraight && isFlush)
    {
        return(8);
    }

    // check for four-of-a-kind
    for(i=1; i<14; i++)
    {
        if(values[i] == 4)
        {
            return(7);
        }
    }

    // check for full house
    flag = 0;
    for(i=1; i<14; i++)
    {
        if(values[i] == 3 || values[i] == 2)
        {
            flag = values[i];
        }
        if((values[i] == 2 && flag == 3) || (values[i] == 3 && flag == 2))
        {
            return(6);
        }
    }

    // check for flush
    if(isFlush)
    {
        return(5);
    }

    // check for straight
    if(isStraight)
    {
        return(4);
    }

    // check for three-of-a-kind
    for(i=1; i<14; i++)
    {
        if(values[i] == 3)
        {
            return(3);
        }
    }

    // check for two pair
    flag = 0;
    for(i=1; i<14; i++)
    {
        if(values[i] == 2)
        {
            flag++;
        }
    }
    if(flag > 1)
    {
        return(2);
    }

    // check for a pair of Jacks or better
    if(values[1] == 2 || values[11] == 2 || values[12] == 2 || values[13] == 2)
    {
        return(1);
    }

    return(0);
}
void printScore(int score)
{
    if(score < 1)
    {
        maximum -= wager;
    }
    else
    {
        maximum += wager*score;
    }

    switch(score)
    {
        case 0: printf("You got nothing!");
                break;

        case 1: printf("You got a pair of jacks or better!");
                break;

        case 2: printf("You got two-pair!");
                break;

        case 3: printf("You got three-of-a-kind!");
                break;

        case 4: printf("You got a straight!");
                break;

        case 5: printf("You got a flush!");
                break;

        case 6: printf("You got a full-house!");
                break;

        case 7: printf("You got four-of-a-kind!");
                break;

        case 8: printf("You got a straight flush!");
                break;

        case 9: printf("You got a royal flush!");
                break;

        default: printf("You got an invalid score! (%d) ", score);
                 printf("How is that even possible?");
                 break;
    }
}
void discardCards(CARD * hand)
{
	int i;
	int width = 7;
	char choice = 0;
	
    for(i=0;i<5;i++, width+=14)
	{
		xya(26, width);
		scanf("%c", &choice);
		BUFFER_FLUSH;

		if(toupper(choice) == 'X')
			{
				hand[i].discard = 1;
			}
		if(toupper(choice) == 'W')
			{
				hand[i].discard = 2;
			}
	}

}
