#ifndef PLAYERLIST_H
#define PLAYERLIST_H


#include "player.h"  //for Player class


//PlayerNode Class holds all the info from a Player and has a pointer
//so it can be used in a singly linked list
class PlayerNode {
private:

    //attributes:
    
    //data | the info from a Player contained in this node
	Player data;
	
	//next | the pointer to the next node in the linked list
	PlayerNode* next = nullptr;

public:

    //default constructor
    //sets data to the default of the Player class
	PlayerNode();
	
	//parameterized constructor
    //sets the name attribute within data to player_name
    //leaves the other variables as default
	PlayerNode(string player_name);
	
	//accessor for data
	Player* getData();


    //the attributes of PlayerNode can be accessed by PlayerList class
	friend class PlayerList;

};




//PlayerList Class makes a singly linked list of PlayerNodes
class PlayerList {
private:

    //attributes:
    
    //head | the first PlayerNode in this linked list
	PlayerNode* head;

public:

    //append adds a new PlayerNode to the end of this PlayerList
	//parameters: new_player_name - the name in the Player data within the new PlayerNode we want to add
	void append(string new_player_name);
	
	//prepend adds a new PlayerNode to the start of this PlayerList
	//parameters: new_player_name - the name in the Player data within the new PlayerNode we want to add
	void prepend(string new_player_name);
	
	//remove removes a PlayerNode with the parameter name from this PlayerList
	//if that node exists
	//parameters: name_to_remove - the name in the Player data within the PlayerNode we want to remove
	//returns: whether a node with that parameter name was removed
	bool remove(string name_to_remove);

	
	//at gives the PlayerNode that is at a specific index in the list
	//if the index isn't valid, it will give nullptr
	//parameters: index - the index to look at for a node
	//returns: the PlayerNode at the parameter index
	PlayerNode* at(int index);
	
	//length determines how many nodes are in this linked list
	//returns: the number of PlayerNodes in this linked list
	int length() const;
	
	//tableHeaders gives a specific table header based on the number given to it
	//0 gives the first header, 1 gives the second header, etc.
	//parameters: index - the number corresponding with the desired header
	//returns: the header text the corresponds with the parameter index
	string tableHeaders(int index) const;
	
	//print outputs out a score sheet table with all the Players stored in this list and their scores
	void print() const;
	
	//determineWinner determines the winner(s) out of the Players in this list
	//returns: the name(s) of the winning player(s)
	string determineWinner() const;

    //destructor
	~PlayerList();

};

#endif
