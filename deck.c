#include "deck.h"

static char *faces[14] = { ACE , ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT,
                           NINE, TEN, JACK, QUEEN, KING };

// checks the input is correct
int checkInput(int argc, char *argv[]) {
  if (argc != N_ARGS) {
    printf("Incorrect number of arguments. Try again.\n");
    return FALSE;
  }
  if (atoi(argv[1]) < MIN_CARDS_HANDS || atoi(argv[1]) > MAX_CARDS_HANDS) {
    printf("Arguments must be integers between %d - %d. Try again.\n", MIN_CARDS_HANDS, MAX_CARDS_HANDS);
    return FALSE;
  }
  if (atoi(argv[2]) < MIN_CARDS_HANDS || atoi(argv[2]) > N_VALUES) {
    printf("Arguments must be integers between %d - %d. Try again.\n", MIN_CARDS_HANDS, MAX_CARDS_HANDS);
    return FALSE;
  }
  int cards;
  if ((cards = atoi(argv[1]) * atoi(argv[2])) > DECK) {
    printf("Decks only have %d cards. Can't deal %d cards. Try again.\n", DECK, cards);
    return FALSE;
  }
  return TRUE;
}

// creates a deck and returns it. Uses the Card struct and adds cards to the deck
Card *constructDeck() {
  static Card deck[DECK];
  int i, j = 0;

  for (i = 1; i <= N_VALUES; i++) {
    Card h = { H_SYMBOL, faces[i], j };
    deck[j++] = h;

    Card c = { C_SYMBOL, faces[i], j };
    deck[j++] = c;

    Card d = { D_SYMBOL, faces[i], j };
    deck[j++] = d;

    Card s = { S_SYMBOL, faces[i], j };
    deck[j++] = s;
  }

  return deck;
}

//shuffles the deck using srand and time_t
//goes through the array swapping each card
void shuffleDeck(Card *deck) {
  int i;
  time_t t;
  srand((unsigned) time(&t));
  for (i = 0; i < DECK; i++) {
    int pos = rand() % DECK;
    swapElements(deck, i, pos);
  }
}

//displays any ammount of cards using special unicode characters
void displayCards(Card *cards, int nCards) {
  int j, r, k = 0, i = nCards / N_CARDS_LINE;
  if ((r = nCards % N_CARDS_LINE > 0))
    i++;

  //making an array with the ammount of cards per line
  int cardsPerLine[i];
  for (j = 0; j < i; j++)
    cardsPerLine[j] = N_CARDS_LINE;

  if (r)
    cardsPerLine[i - 1] = nCards % N_CARDS_LINE;

  for (j = 0; j < i; j++) {
    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s%s%s%s%s%s%s ", TOP_LEFT_CORNER, H_LINE, H_LINE, H_LINE,H_LINE, H_LINE, TOP_RIGHT_CORNER);
    }
    printf("\n");

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s%s    %s ", V_LINE, cards[k++].suit, V_LINE);
    }
    printf("\n");
    k -= cardsPerLine[j];

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s %2s  %s ", V_LINE, cards[k++].value, V_LINE);
    }
    printf("\n");
    k -= cardsPerLine[j];

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s    %s%s ", V_LINE, cards[k++].suit, V_LINE);
    }
    printf("\n");

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s%s%s%s%s%s%s ", BOT_LEFT_CORNER, H_LINE, H_LINE, H_LINE,H_LINE, H_LINE, BOT_RIGHT_CORNER);
    }
    printf("\n\n");
  }

}

// creates an array with the specified number of cards per hand
//separates them with a card with suit and value equal to 0
void dealCards(Card *hands, int nCards, int nHands, Card *deck) {
  int limit = nCards * nHands + nHands - 1;
  int i = 0, j = 0;
  for (; i < limit; i++) {
    hands[i] = deck[j];
    j++;
    if ((j) % nCards == 0) {
      Card aux = { "0", "0" };
      hands[++i] = aux;
    }
  }
}

// sorts each hand by making calls to quickSort and passing a sub array of the
// hands array each time
void sortHands(Card *hands, int nCards, int nHands) {
  int i;
  for (i = 0; i < nHands; i++) {
    int start = nCards * i + 1 * i;
    quickSort(hands, start, start + nCards - 1);
  }
}

// quickSort algorithm
void quickSort(Card *hands, int start, int end) {
  int i = start;
  int j = end;

  if (end - start > 0) {
    int p = hands[start].index;

    while (j > i) {
      while (hands[i].index <= p && i <= end && j > i)
        i++;
      while (hands[j].index > p && j >= start && j >= i)
        j--;
      if (j > i)
        swapElements(hands, i, j);
    }
    swapElements(hands, start, j);
    quickSort(hands, start, j - 1);
    quickSort(hands, j + 1, end);
  }
  else return;
}

// swaps elements in an arry
void swapElements(Card *hands, int pos1, int pos2) {
  Card aux = hands[pos1];
  hands[pos1] = hands[pos2];
  hands[pos2] = aux;
}

// displays the hands by passing sub arrays of the hands array to displayCards
void displayHands(Card *hands, int nCards, int nHands) {
  int i, j = 0, count = 0, handsCount = 1;
  Card cardsToPrint[nCards];

  for (i = 0; i < nCards * nHands + nHands - 1; i++) {
    cardsToPrint[j] = hands[i];
    j++;
    count++;
    if (count % nCards == 0) {
      i++;
      j = 0;
      printf("Hand %d:\n", handsCount);
      handsCount++;
      displayCards(cardsToPrint, nCards);
    }
  }
}
