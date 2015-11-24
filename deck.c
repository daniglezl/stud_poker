#include "deck.h"

static const char *SUITS[4] = { "\xE2\x99\xA1", "\xE2\x99\xA7",
                                "\xE2\x99\xA2", "\xE2\x99\xA4" };

static const char *FACES[14] = { " ", "A", "2", "3", "4", "5", "6", "7",
                                 "8", "9", "10", "J", "Q", "K" };
static const char *RANKS[10] = { " ", "Straight Flush", "Four of a Kind",
                                 "Full House", "Flush", "Straight",
                                 "Three of a Kind", "Two Pair", "One Pair",
                                 "High Card" };

int checkInput(int argc, char *argv[]) {
  int arg1, arg2;

  if (argc != N_ARGS) {
    printf("%s\n", "Incorrect number of arguments.");
    return FALSE;
  }

  if (isdigit(*argv[1])) {
    arg1 = atoi(argv[1]);
    if (arg1 != N_CARDS) {
      printf("Number of cards has to be %d\n", N_CARDS);
      return FALSE;
    }
  } else {
    printf("Enter %d for number of cards\n", N_CARDS);
    return FALSE;
  }

  if (isdigit(*argv[2])) {
    arg2 = atoi(argv[2]);
    if (arg2 < MIN_HANDS || arg2 > MAX_HANDS) {
      printf("Number of hands has to be between %d and %d\n", MIN_HANDS,
             MAX_HANDS);
      return FALSE;
    }
  } else {
      printf("%s\n", "Number of hands has to be an integer");
      return FALSE;
  }

  return TRUE;
}


void constructDeck(Card *deck) {
  int i, j = 0;

  for (i = 1; i <= MAX_FACES; i++) {
    Card h = { HEART, i, j };
    deck[j++] = h;

    Card c = { CLUB, i, j };
    deck[j++] = c;

    Card d = { DIAMOND, i, j };
    deck[j++] = d;

    Card s = { SPADE, i, j };
    deck[j++] = s;
  }
}


// Comment from professor: Soemtimes your shuffle is not working,
// cards stay close to original order
void shuffleDeck(Card *deck) {
  int i;
  time_t t;
  srand((unsigned) time(&t));
  for (i = 0; i < DECK; i++) {
    int pos = rand() % DECK;
    swapElements(deck, i, pos);
  }
}


void swapElements(Card *hands, int pos1, int pos2) {
  Card aux = hands[pos1];
  hands[pos1] = hands[pos2];
  hands[pos2] = aux;
}


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
      printf("%s%s    %s ", V_LINE, SUITS[cards[k++].suit], V_LINE);
    }
    printf("\n");
    k -= cardsPerLine[j];

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s %2s  %s ", V_LINE, FACES[cards[k++].face], V_LINE);
    }
    printf("\n");
    k -= cardsPerLine[j];

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s    %s%s ", V_LINE, SUITS[cards[k++].suit], V_LINE);
    }
    printf("\n");

    for (r = 0; r < cardsPerLine[j]; r++) {
      printf("%s%s%s%s%s%s%s ", BOT_LEFT_CORNER, H_LINE, H_LINE, H_LINE,H_LINE, H_LINE, BOT_RIGHT_CORNER);
    }
    printf("\n\n");
  }
}


void dealCards(Card hands[][N_CARDS], Card *deck, int nHands) {
  int i, j, index = 0;
  for (i = 0; i < nHands; i++)
    for (j = 0; j < N_CARDS; j++) {
      hands[i][j] = deck[index];
      index++;
    }
}


void displayHands(Card hands[][N_CARDS], int ranks[][2], int nHands,
                  int printRank) {
  int i;
  if (printRank)
    for (i = 0; i < nHands; i++) {
      printf("Hand %d, rank: %s, high: %d\n", i + 1, RANKS[ranks[i][0]], ranks[i][1]);
      displayCards(hands[i], N_CARDS);
    }
  else
  for (i = 0; i < nHands; i++) {
    printf("Hand %d\n", i + 1 );
    displayCards(hands[i], N_CARDS);
  }
}


void quickSort(Card *hand, int start, int end) {
  int i = start;
  int j = end;

  if (end - start > 0) {
    int p = hand[start].index;

    while (j > i) {
      while (hand[i].index <= p && i <= end && j > i)
        i++;
      while (hand[j].index > p && j >= start && j >= i)
        j--;
      if (j > i)
        swapElements(hand, i, j);
    }
    swapElements(hand, start, j);
    quickSort(hand, start, j - 1);
    quickSort(hand, j + 1, end);
  }
  else return;
}


void sortHands(Card hands[][N_CARDS], int ranks[][2], int nHands) {
  int i;
  for (i = 0; i < nHands; i++) {
    quickSort(hands[i], 0, N_CARDS - 1);
    getRank(hands[i], ranks, i);
  }
}


void getRank(Card *hand, int ranks[][2], int handIndex) {
  int high, rank = 0, face, auxRank = 0;

  int nKind = getNKind(hand, &high, 0, TRUE);
  face = high;
  if (nKind == 4)
    rank = FK;
  else if (nKind == 3) {
    rank = TK;
    int aux = getNKind(hand, &high, face, FALSE);
    if (aux == 2)
      rank = FH;
  }
  else if (nKind == 2) {
    rank = OP;
    int aux = getNKind(hand, &high, face, TRUE);
    if (aux == 3)
      rank = FH;
    else if (aux == 2)
      rank = TP;
  }

  if (isStraight(hand, &high)) {
    auxRank = S;
    printf("%s\n", "xxx");
  }
  if (isFlush(hand, &high)) {
    printf("%s\n", "xxx");
    if (auxRank == S)
      auxRank = SF;
    else auxRank = F;
  }

  printf("%d\n", rank);
  printf("%d\n", auxRank);

  if (auxRank < rank && auxRank != 0)
    rank = auxRank;
  if (rank == 0)
    rank = HC;

  ranks[handIndex][0] = rank;
  ranks[handIndex][1] = high;

  printf("%d\n", rank);
}

int isFlush(Card *hand, int *high) {
  int i;
  *high = hand[0].face;

  for (i = 1; i < N_CARDS; i++) {
    if (hand[i].suit != hand[i - 1].suit)
      return FALSE;
    *high = (hand[i].face > *high) ? hand[i].face : *high;
  }

  if (hand[0].face == 1)
    *high = 1;

  return TRUE;
}

int isStraight(Card *hand, int *high) {
  int i = 1, aux = hand[0].face;

  if (hand[0].face == 1)
    *high = 1;
  else *high = hand[N_CARDS - 1].face;

  for (; i < N_CARDS; i++) {
    if (hand[i].face != aux + 1){
      if (hand[i].face == 10 && aux == 1)
        aux = hand[i].face;
      else
        return FALSE;
    } else aux = hand[i].face;
  }

  return TRUE;
}

int getNKind(Card *hand, int *high, int differentThan, int changeHigh) {
  int aux = 0;
  int i;
  int count = 0;

  for (i = 0; i < N_CARDS; i++) {
    if (aux == 0 && hand[i].face != differentThan) {
      aux = hand[i].face;
      count++;
    }
    else if (hand[i].face == aux)
      count++;
    else if (count == 1 && hand[i].face != differentThan)
      aux = hand[i].face;
  }

  if (count > 1 && aux > differentThan && changeHigh && *high != 1)
    *high = aux;

  return count;
}
