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
  int nCards = atoi(argv[1]);
  int nHands = atoi(argv[2]);

  // calling functions
  // create deck
  Card *deck;
  deck = constructDeck();

  // shuffle deck
  shuffleDeck(deck);

  // display shuffled deck
  printf("%s\n", "Shuffled deck: =================================================================");
  displayCards(deck, DECK);

  // deal cards
  Card hands[nCards * nHands + nHands - 1];
  dealCards(hands, nCards, nHands, deck);

  // print unsorted hands
  printf("%s\n", "Unsorted hands: ================================================================");
  displayHands(hands, nCards, nHands);

  // sort hands
  sortHands(hands, nCards, nHands);

  // display sorted hands
  printf("%s\n", "Sorted hands: ==================================================================");
  displayHands(hands, nCards, nHands);

  return 0;
}
