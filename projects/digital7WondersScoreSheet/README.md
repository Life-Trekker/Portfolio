This program creates a digital score sheet for the board game 7 Wonders
The base game of 7 Wonders has 7 different ways players can earn points
There are 4 kinds of cards that grant points directly (they come in Red, Blue, Yellow and Purple)
Players also gain points from their Wonder boards, coins and the collection of science symbols they have
(For more information, go here: https://www.rprod.com/en/games/7-wonders)

Player.h and Player.cpp contain the definition and implimentation of the Player class,
which contains all the needed information to determine a player's final score

Playerlist.h and Playerlist.cpp contain the definitions and implimentation of the PlayerNode and PlayerList classes,
these are used to make a singly linked list of Player objects
from this list, we can determine who won the game and we can output a table with everyone's scores
in each catagory

main.cpp contains functions that ask the user for all the information needed to make a score sheet
it them presents that score sheet and lets them know who the winners are