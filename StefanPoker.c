#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct card 
{
    unsigned short face:4,
            suit:2,
            dealt:1;
} CARD;

char * face[14] = {"","ACE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN","JACK","QUEEN","KING"};
char * suit[4] = {"HEARTS","DIAMONDS","CLUBS","SPADES"};

void buildDeck(CARD []);
void deal(CARD [], CARD []);
void discard(CARD [], CARD *);

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
    fflush(stdin); getchar(); 
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
