# Program Description
  The program asks the user for a number of cards per hand and the number of hands.
  Number of cards per hand should always be 5
  - It accepts and validates the user input
  - Creates a deck of 52 cards
  - Displays the deck
  - Shuffles the deck
  - Displays the shuffled deck
  - Deals cards to each hand
  - Displays the hands
  - Sorts the hands and finds ranks
  - Displays sorted hands and ranks
  - Decides on winner(s) and prints it

# Compilation
  gcc main.c deck.c -o deck

  - Execute with './deck nCards nHands' where nCards is the number of cards/hand
    and nHands is the number of hands or players
  - Make sure nCards is always 5, so './deck 5 10' would be correct
  - Requires all files to be in same directory including deck.h
