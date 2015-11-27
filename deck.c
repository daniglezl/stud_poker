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
  {
    for (i = 0; i < nHands; i++) {
      printf("Hand %d, rank: %s, high: %s\n", i + 1, RANKS[ranks[i][0]], FACES[ranks[i][1]]);
      displayCards(hands[i], N_CARDS);
    }
  }
  else
  {
    for (i = 0; i < nHands; i++) {
      printf("Hand %d\n", i + 1 );
      displayCards(hands[i], N_CARDS);
    }
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


void getRank(Card *hand, int ranks[][2], int handIndex) 
{
  int rank[2], *rankF, *rankS, *rankM; 

  rankF = isFlush(hand);
  rankS = isStraight(hand);	
  rankM = getMatch(hand);
  //printf("%d %d and ",rankF[1],rankM[1]);
  if (*rankF == TRUE && *rankS == TRUE)
  {
    rank[0] = SF;
    rank[1] = *(rankS + 1);
  }
  else if (*rankF == TRUE && F < *rankM)
  {
    rank[0] = F;
    rank[1] = *(rankF + 1);
  }
  else if (*rankS == TRUE && S < *rankM)
  {
    rank[0] = S;
    rank[1] = *(rankS + 1);
  }
  else 
  {
    rank[0] = *rankM; 
    rank[1] = *(rankM + 1);
  }

  ranks[handIndex][0] = rank[0];
  ranks[handIndex][1] = rank[1];
}

int * isFlush(Card *hand) 
{
  int i;
  int *rank;
  rank = (int *)malloc(2 * sizeof(int));
  rank[0] = TRUE;
  rank[1] = hand[N_CARDS-1].face;

  for (i = 1; i < N_CARDS; i++) 
  {
    if (hand[i].suit != hand[i - 1].suit)
    {
      rank[0] = FALSE;
    }
  }
  return rank;
}

int * isStraight(Card *hand) 
{
  int i; 
  int *rank;
  rank = (int *)malloc(2 * sizeof(int));
  rank[0] = TRUE;
  rank[1] = hand[N_CARDS-1].face;

  for (i = 1; i < N_CARDS; i++) 
  {
    if (hand[i].face != hand[i-1].face + 1)
    {
      if(hand[i].face == ACE && hand[i-1].face == 5)
      {
        rank[1] = 5;
      }
      else
      {
	rank[0] = FALSE;
      }
    } 
  }
  return rank;
}

int * getMatch(Card *hand) 
{
  int i, j = 1;
  int two = 0; 
  int three = 0; 
  int four = 0;
  int count, match;
  int *rank;
  rank = (int *)malloc(2 * sizeof(int));

  for (i = 0; i < N_CARDS - 1; i++) 
  {
    count = 1;
    match = 1;
    i = j - 1;
    for(j = i + 1; j < N_CARDS && match == 1; j++)
    {
      if (hand[i].face == hand[j].face)
      {
	count++;
      }
      else
      {
	match = 0;
      }
    }
    if(count == 4)
    {
      four = 1;
      rank[1] = hand[i].face;
    }
    if(count == 3)
    {
      three = 1;
      rank[1] = hand[i].face;
    }
    if(count == 2)
    {
      two++;
      if(three == 0)
	rank[1] = hand[i].face;
    }  
  }
  if (four == 1)
  {
    rank[0] = FK;
  }
  else if (two == 1 && three == 1)
  {
    rank[0] = FH;
  }
  else if (three == 1)
  {
    rank[0] = TK;
  }
  else if (two == 2)
  {
    rank[0] = TP;
  }
  else if (two == 1)
  {
    rank[0] = OP;
  }
  else
  { 
    rank[0] = HC;
    rank[1] = hand[N_CARDS-1].face;
  }
  return rank;
}