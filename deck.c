#include "deck.h"

static const char *SUITS[N_SUITS] = { "\xE2\x99\xA1", "\xE2\x99\xA7",
                                      "\xE2\x99\xA2", "\xE2\x99\xA4" };

static const char *FACES[MAX_FACES + 2] = { " ", " ", "2", "3", "4", "5", "6",
                                            "7", "8", "9", "10", "J", "Q", "K",
                                            "A" };
static const char *RANKS[N_RANKS + 1] = { " ", "Straight Flush",
                                           "Four of a Kind", "Full House",
                                           "Flush", "Straight",
                                           "Three of a Kind", "Two Pair",
                                           "One Pair", "High Card" };

// checks user input from the command line, rejecting invalid input
// and advising the user about valid input
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
      printf("%s\n", "Number of hands has to be a positive integer");
      return FALSE;
  }

  return TRUE;
}

// Fills the 'deck' array of all necessary cards
void constructDeck(Card *deck) {
  int i, j = 0;

  for (i = 1; i <= MAX_FACES; i++) {
    Card h = { HEART, i + 1, j };
    deck[j++] = h;

    Card c = { CLUB, i + 1, j };
    deck[j++] = c;

    Card d = { DIAMOND, i + 1, j };
    deck[j++] = d;

    Card s = { SPADE, i + 1, j };
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

// Helper function to swap the positions of 2 cards
void swapElements(Card *hands, int pos1, int pos2) {
  Card aux = hands[pos1];
  hands[pos1] = hands[pos2];
  hands[pos2] = aux;
}

// Print out representations of each card in the deck
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

// Assigns the wanted number of cards to each hand from the current 'deck' array
void dealCards(Card hands[][N_CARDS], Card *deck, int nHands) {
  int i, j, index = 0;
  for (i = 0; i < nHands; i++)
    for (j = 0; j < N_CARDS; j++) {
      hands[i][j] = deck[index];
      index++;
    }
}

// Print out representations of each card from each hand in play
void displayHands(Card hands[][N_CARDS], int ranks[][2], int nHands,
                  int printRank) {
  int i;
  if (printRank)
    for (i = 0; i < nHands; i++) {
      printf("Hand %d, rank: %s, high: %s\n", i + 1, RANKS[ranks[i][0]], FACES[ranks[i][1]]);
      displayCards(hands[i], N_CARDS);
    }
  else
    for (i = 0; i < nHands; i++) {
      printf("Hand %d\n", i + 1 );
      displayCards(hands[i], N_CARDS);
    }
}

// Helper function to sort cards in a hand in the correct order using
// quick sort
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

// Puts each hand in order by using quickSort and gets the hand's rank
void sortHands(Card hands[][N_CARDS], int ranks[][2], int nHands) {
  int i;
  for (i = 0; i < nHands; i++) {
    quickSort(hands[i], 0, N_CARDS - 1);
    getRank(hands[i], ranks, i);
  }
}

/*
  Author: Drhumel Shah
  Fills the 'ranks' array with the rank and high card of each
  hand in play
*/
void getRank(Card *hand, int ranks[][2], int handIndex) {
  int rank[2], *rankF, *rankS, *rankM;

  rankF = isFlush(hand);
  rankS = isStraight(hand);
  rankM = getMatch(hand);
  if (*rankF && *rankS) {
    rank[0] = SF;
    rank[1] = *(rankS + 1);
  }
  else if (*rankF && F < *rankM) {
    rank[0] = F;
    rank[1] = *(rankF + 1);
  }
  else if (*rankS && S < *rankM) {
    rank[0] = S;
    rank[1] = *(rankS + 1);
  }
  else {
    rank[0] = *rankM;
    rank[1] = *(rankM + 1);
  }

  ranks[handIndex][0] = rank[0];
  ranks[handIndex][1] = rank[1];
}

/*
  Author: Daniel Gonzalez
  Handles Flushes since they do not rely on face value
*/
int *isFlush(Card *hand) {
  int i;
  int *rank = (int *)malloc(2 * sizeof(int));
  rank[0] = TRUE;
  rank[1] = hand[N_CARDS - 1].face;

  for (i = 1; i < N_CARDS; i++)
    if (hand[i].suit != hand[i - 1].suit)
      rank[0] = FALSE;

  return rank;
}

/*
  Author: Daniel Gonzalez
  Handles straights because they do not rely on multiples
*/
int *isStraight(Card *hand) {
  int i;
  int *rank = (int *)malloc(2 * sizeof(int));
  rank[0] = TRUE;
  rank[1] = hand[N_CARDS - 1].face;

  for (i = 1; i < N_CARDS; i++)
    if (hand[i].face != hand[i - 1].face + 1) {
      if(hand[i].face != ACE || hand[i - 1].face != 5) // takes care of A-5
        rank[0] = FALSE;
      else rank[1] = 5;
    }

  return rank;
}

/*
  Author: Drhumel Shah
  Handles all other ranks because all others rely on
  the appearance of multiples of one or more face value
*/
int *getMatch(Card *hand) {
  int i, j = 1;
  int two = 0;
  int three = 0;
  int four = 0;
  int count, match;
  int *rank = (int *)malloc(2 * sizeof(int));

  for (i = 0; i < N_CARDS - 1; i = j - 1) {
    count = 0;
    match = TRUE;

    for(; j <= N_CARDS && match; j++) {
      count++;
      if (hand[i].face != hand[j].face)
      	match = FALSE;
    }

    if(count == 4) {
      rank[0] = FK;
      rank[1] = hand[i].face;
      return rank;
    }
    if(count == 3) {
      three = 1;
      rank[1] = hand[i].face;
    }
    else if(count == 2) {
      two++;
      if(three == 0)
        rank[1] = hand[i].face;
    }
  }

  if (two == 1 && three == 1) {
    rank[0] = FH;
  }
  else if (three == 1) {
    rank[0] = TK;
  }
  else if (two == 2) {
    rank[0] = TP;
  }
  else if (two == 1) {
    rank[0] = OP;
  }
  else {
    rank[0] = HC;
    rank[1] = hand[N_CARDS - 1].face;
  }

  return rank;
}

/*
  Author: Antonio Riverol
  Reads the 'ranks' 2-d array and decides the winner of
  the poker game with 1 level of tie breaking.
*/
void chooseWinner(int ranks[][2], int nHands) {
   int winners[nHands];
   int winpointer = 0;
   int rank = HC;
   int i = 0;
   int high = 0;

// Finds the highest rank that appears in this particular game
   for(i = 0; i < nHands; i++)
      if(ranks[i][0] < rank)
        rank = ranks[i][0];

// Checks all players that have the winning rank and from these
// players, finds the high card among them
   for(i = 0; i < nHands; i++)
      if(ranks[i][0] == rank && ranks[i][1] > high)
        high = ranks[i][1];

// Enters all players who have the winning rank and high card
// into their own 'winners' array
   for(i = 0; i < nHands; i++)
      if(ranks[i][0] == rank && ranks[i][1] == high)
      {
         winners[winpointer] = i + 1;
         winpointer++;
      }

   printf("Winner(s): ");

// Prints names of winners
   for(i = 0; i < winpointer; i++)
   {
      if (i != winpointer - 1)
        printf("Player %d, ", winners[i]);
      else
        printf("Player %d", winners[i]);
   }
   printf("\n");
}
