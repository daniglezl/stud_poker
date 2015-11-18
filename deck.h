#include <stdio.h>
#include <stdlib.h> // allows the use of srand, rand and atoi
#include <time.h>   // allows the use of time_t

// Program Defines
// Booleans
#define TRUE 1
#define FALSE 0

// Number of arguments
#define N_ARGS 3

// Number of suits and faces
#define N_SUITS 4
#define N_VALUES 13

#define DECK N_SUITS * N_VALUES           // Total n of cards in deck
#define MIN_CARDS_HANDS 1                 // Min number of cards in deck
#define MAX_CARDS_HANDS 13                // Min number of cards in deck

// Suits symbols
#define H_SYMBOL "\xE2\x99\xA1"
#define C_SYMBOL "\xE2\x99\xA7"
#define D_SYMBOL "\xE2\x99\xA2"
#define S_SYMBOL "\xE2\x99\xA4"

// Used to draw cards in screen
#define TOP_LEFT_CORNER   "\xE2\x94\x8C"
#define TOP_RIGHT_CORNER  "\xE2\x94\x90"
#define BOT_LEFT_CORNER   "\xE2\x94\x94"
#define BOT_RIGHT_CORNER  "\xE2\x94\x98"
#define H_LINE            "\xE2\x94\x80"
#define V_LINE            "\xE2\x94\x82"

#define N_CARDS_LINE 10                   // Max number of cards to be printed per line

// Faces
#define ACE   "A"
#define JACK  "J"
#define QUEEN "Q"
#define KING  "K"
#define TWO "2"
#define THREE "3"
#define FOUR "4"
#define FIVE "5"
#define SIX "6"
#define SEVEN "7"
#define EIGHT "8"
#define NINE "9"
#define TEN "10"

// Representation of a card
typedef struct card {
  char *suit;
  char *value;
  int index;
} Card;

//Function Protoypes
int checkInput(int argc, char *argv[]);
Card *constructDeck();
void displayCards(Card *cards, int nCards);
void displayHands(Card *hands, int nCards, int nHands);
void shuffleDeck(Card *deck);
void dealCards(Card *hands, int nCards, int nHands, Card *deck);
void quickSort(Card *hands, int start, int end);
void swapElements(Card *hands, int pos1, int pos2);
void sortHands(Card *hands, int nCards, int nHands);
