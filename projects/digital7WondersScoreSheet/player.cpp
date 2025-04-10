#include "player.h"

using namespace std;


//setIfInputPositive will set the variable parameter to the input parameter 
//if the input parameter is positive
//parameters: input - the integer to set the other parameter to
//variable - the integer to set if the input is positive
//returns: if the variable was set or not
bool Player::setIfInputPositive(int input, int & variable)
{
    if(input >= 0)
    {
        variable = input;
        return true;
    }
    
    return false;
}

//default constructor
//sets name to "" (rest of the attributes stay at default)
Player::Player() { name = ""; }

//parameterized constructor
//sets name to new_name parameter (rest of the attributes stay at default)
Player::Player(string new_name) { name = new_name; }

//mutator for name
void Player::setName(string new_name) { name = new_name; }

//accessor for name
string Player::getName() const { return name; }

//mutator for card_scores array
//parameters:  new_card_score - the value to set one of the card scores to
//score_type - the index of the score in the array to set
void Player::setCardScore(int new_card_score, int score_type) { card_scores[score_type] = new_card_score; }

//accessor for card_scores array
int* Player::getCardScores() { return card_scores; }

//mutator for num_coins
//returns: whether num_coins could be set to the parameter
//set by calling setIfInputPositive since 
//the player can't have a negative number of coins
bool Player::setNumCoins(int new_num_coins) { return setIfInputPositive(new_num_coins, num_coins); }

//accessor for num_coins
int Player::getNumCoins() const { return num_coins; }

//mutator for num_gears
//returns: whether num_gears could be set to the parameter
//set by calling setIfInputPositive since 
//the player can't have a negative number of gear symbols
bool Player::setNumGears(int new_num_gears) { return setIfInputPositive(new_num_gears, num_gears); }

//accessor for num_gears
int Player::getNumGears() const { return num_gears; }

//mutator for num_compasses
//returns: whether num_compasses could be set to the parameter
//set by calling setIfInputPositive since 
//the player can't have a negative number of compass symbols
bool Player::setNumCompasses(int new_num_compasses) { return setIfInputPositive(new_num_compasses, num_compasses);  }

//accessor for num_compasses
int Player::getNumCompasses() const { return num_compasses; }

//mutator for num_tablets
//returns: whether num_tablets could be set to the parameter 
//set by calling setIfInputPositive since 
//the player can't have a negative number of tablet symbols
bool Player::setNumTablets(int new_num_tablets) { return setIfInputPositive(new_num_tablets, num_tablets); }

//accessor for num_tablets
int Player::getNumTablets() const { return num_tablets; }


//calcScienceScore calculates the points this player gets from their science symbols
//returns: the points this player gets from their science symbols
int Player::calcScienceScore() const
{
    
    //create an int to store the total number of points this Player
    //gets from their science symbols
    
    //for each of the three types of symbols,
    //the player gets points equal to the number of symbols they have of that type squared
    int science_points = num_gears * num_gears + num_compasses * num_compasses
    + num_tablets * num_tablets;
    
    //for each set of three different science symbols,
    //the player scores an additional 7 points
    
    //make copies of num_gears, num_compasses and num_tablets that can be altered
    int temp_num_gears = num_gears;
    int temp_num_compasses = num_compasses;
    int temp_num_tablets = num_tablets;
    
    //repeatedly remove one gear, one compass and one tablet from the player
    //for each time this is done, add 7 points to the total
    //as soon as the player runs out of gears, compasses or tablets to remove, we stop looping
    while(--temp_num_gears >= 0 && --temp_num_compasses >= 0 && --temp_num_tablets >= 0) { science_points += 7; }
    
    //return to the total number of points this player gets from their science symbols
    return science_points;
}


//calcTotal calculates the total score for this player 
//by adding up the scores from all catagories
//returns: the total score for this player
int Player::calcTotal() const
{
    //create an int to store the total score for this player
    int total_score = 0;
    
    //add this player's scores from their Red, Blue, Yellow and Purple Cards
    //and from their Wonder Board to the total
    for(int i = 0; i < 5; i++)
    {

        total_score += card_scores[i];
    }
    
    //every 3 coins is worth one points
    //add this player's points from the coins they have to the total
    total_score += num_coins / 3;
    
    //call calcScienceScore to get the number of points this player
    //gains from their science symbols
    //add that to the total
    total_score += calcScienceScore();
    
    //return the total
    return total_score;
}
