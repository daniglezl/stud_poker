#include "deck.h" // provides constants, std libraries and function prototypes

// Author name: Daniel Gonzalez
// Author id:   4139989
/* I hereby certify that this collective work is my own and none
   of it is the work of any other person or entity. */

int main(int argc, char *argv[]) {

  // validates input
  if (checkInput(argc, argv) == FALSE)
    return 1;

  // declaring variables
  int nHands = atoi(argv[2]);
  Card deck[DECK];
  Card hands[nHands][N_CARDS];
  int ranks[nHands][2];

  // calling functions
  // create deck
  constructDeck(deck);

  // display deck
  printf("%s\n", "Deck: ==========================================================================");
  displayCards(deck, DECK);

  // shuffle deck
  shuffleDeck(deck);

  // display shuffled deck
  printf("%s\n", "Shuffled deck: =================================================================");
  displayCards(deck, DECK);

  // deal cards
  dealCards(hands, deck, nHands);

  /******************** Set values here to test ranks ************************/
  //  hands[0][0].face = 2;
  //  hands[0][0].suit = 1;
  //  hands[0][0].index = 1;
  //  hands[0][1].face = 3;
  //  hands[0][1].suit = 2;
  //  hands[0][1].index = 2;
  //  hands[0][2].face = 3;
  //  hands[0][2].suit = 3;
  //  hands[0][2].index = 3;
  //  hands[0][3].face = 4;
  //  hands[0][3].suit = 0;
  //  hands[0][3].index = 4;
  //  hands[0][4].face = 4;
  //  hands[0][4].suit = 1;
  //  hands[0][4].index = 5;

  // print unsorted hands
  printf("%s\n", "Unsorted hands: ================================================================");
  displayHands(hands, ranks, nHands, FALSE);

  // sort hands
  sortHands(hands, ranks, nHands);

  // display sorted hands
  printf("%s\n", "Sorted hands: ==================================================================");
  displayHands(hands, ranks, nHands, TRUE);

  // Decide and print the winner(s) of the game
  printf("%s\n", "================================================================================");
  chooseWinner(ranks, nHands);

  return 0;
}
