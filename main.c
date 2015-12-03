/*
  Authors:
    Drhumel Shah
    Antonio Riverol - 4023394
    Daniel Gonzalez - 4139989

  “We hereby certify that this collective work is our own and none of it is
  the work of any other person or entity.“
*/

#include "deck.h" // provides constants, std libraries and function prototypes

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

  // print unsorted hands
  printf("%s\n", "Unsorted hands: ================================================================");
  displayHands(hands, ranks, nHands, FALSE);

  // sort hands
  sortHands(hands, ranks, nHands);

  // display sorted hands and ranks
  printf("%s\n", "Sorted hands: ==================================================================");
  displayHands(hands, ranks, nHands, TRUE);

  // Decide and print the winner(s) of the game
  printf("%s\n", "================================================================================");
  chooseWinner(ranks, nHands);

  return 0;
}
