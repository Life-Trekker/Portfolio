# Description:

For this project, I created a program to represent a digital score sheet for the board game *7 Wonders*.
*7 Wonders* has 7 different methods for players to earn points.  Whoever has the most points total by the end wins.
There are 4 kinds of cards that grant points directly. They come in Red, Blue, Yellow and Purple.
Players also gain points from their individual boards, coins and the collection of science symbols they have.
(For more information, go here: https://www.rprod.com/en/games/7-wonders)

# How It Works:

Player.h and Player.cpp contain the definition and implimentation of the Player class,
which contains all the information needed to determine someone's final score

Playerlist.h and Playerlist.cpp contain the definitions and implimentation of the PlayerNode and PlayerList classes.
These are used to make a singly linked list of Player objects and from this list, we can determine who won the game as well as everyone's scores in each catagory

main.cpp contains a simple command line interface that inputs for all the information needed to make a score sheet and then outputs that sheet and the winner.  It is also capable of breaking ties if multiple players have the same final score.