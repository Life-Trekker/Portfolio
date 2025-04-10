#ifndef PLAYER_H
#define PLAYER_H



#include <string>  //for string
using namespace std;

//Player Class has all the data needed to calculate the score for a given Player
class Player{
private:

    //attributes:
    
    //name | name of this player
    string name;
    
    //card_scores | the points this player has from their different types of cards and their wonder board
    //card_scores[0] | points from Military (Red) Cards
    //card_scores[1] | points from Wonder Board
    //card_scores[2] | points from Civil (Blue) Cards
    //card_scores[3] | points from Commercial (Yellow) Cards
    //card_scores[4] | points from Guild (Purple) Cards
    int card_scores[5] = {0, 0, 0, 0, 0};
    
    //num_coins | the number of coins this player has
    int num_coins = 0;
    
    //num_gears | the number of gears icons this player has on their cards and board
    int num_gears = 0;
    
    //num_compasses | the number of compasses icons this player has on their cards and board
    int num_compasses = 0;
    
    //num_tablets | the number of tablets icons this player has on their cards and board
    int num_tablets = 0;
    
    
    
    //helper functions:
    
    //setIfInputPositive will set the variable parameter to the input parameter 
    //if the input parameter is positive
    //parameters: input - the integer to set the other parameter to
    //variable - the integer to set if the input is positive
    //returns: if the variable was set or not
    bool setIfInputPositive(int input, int & variable);
    
public:

    //default constructor
    //sets name to "" (rest of the attributes stay at default)
    Player();
    
    //parameterized constructor
    //sets name to new_name parameter (rest of the attributes stay at default)
    Player(string new_name);
    
    //mutator for name
    void setName(string new_name);
    
    //accessor for name
    string getName() const;
    
    //mutator for card_scores array
    //parameters:  new_card_score - the value to set one of the card scores to
    //score_type - the index of the score in the array to set
    void setCardScore(int new_card_score, int score_type);
    
    //accessor for card_scores array
    int* getCardScores();
    
    //mutator for num_coins
    //returns: whether num_coins could be set to the parameter
    bool setNumCoins(int new_num_coins);
    
    //accessor for num_coins
    int getNumCoins() const;
    
    //mutator for num_gears
    //returns: whether num_gears could be set to the parameter
    bool setNumGears(int new_num_gears);
    
    //accessor for num_gears
    int getNumGears() const;
    
    //mutator for num_compasses
    //returns: whether num_compasses could be set to the parameter
    bool setNumCompasses(int new_num_compasses);
    
    //accessor for num_compasses
    int getNumCompasses() const;
    
    //mutator for num_tablets
    //returns: whether num_tablets could be set to the parameter 
    bool setNumTablets(int new_num_tablets);
    
    //accessor for num_tablets
    int getNumTablets() const;
    
    //calcScienceScore calculates the points this player gets from their science symbols
    //returns: the points this player gets from their science symbols
    int calcScienceScore() const;
    
    //calcTotal calculates the total score for this player 
    //by adding up the scores from all catagories
    //returns: the total score for this player
    int calcTotal() const;
    
};

#endif
