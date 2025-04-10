#include "playerlist.h"
#include <iostream> //for cout and endl
#include <iomanip> //for setw, setfill and left

using namespace std;

//default constructor
//sets data to the default of the Player class
PlayerNode::PlayerNode() 
{
	data = Player();
}

//parameterized constructor
//sets the name attribute within data to player_name
//leaves the other variables as default
PlayerNode::PlayerNode(string player_name)
{
	data = Player(player_name);
}

//accessor for data
Player* PlayerNode::getData()
{
	return &data;
}



//append adds a new PlayerNode to the end of this PlayerList
//parameters: new_player_name - the name in the Player data within the new PlayerNode we want to add
void PlayerList::append(string new_player_name)
{
    //create a new PlayerNode with the parameter name
	PlayerNode* new_node = new PlayerNode(new_player_name);

    //if the list is empty
	if(!head)
	{
	    //make this new node to the first node
		head = new_node;
	}
	else
	{
	    //start an iterating pointer at the first element in list
		PlayerNode* curr_node = head;
		
		//repeat until the iterating pointer points to the last node
		while(curr_node->next)
		{
			curr_node = curr_node->next;
		}
        
        //place the new node after the last node
		curr_node->next = new_node;
	}
}


//prepend adds a new PlayerNode to the start of this PlayerList
//parameters: new_player_name - the name in the Player data within the new PlayerNode we want to add
void PlayerList::prepend(string new_player_name)
{
    //create a new PlayerNode with the parameter name
	PlayerNode* new_node = new PlayerNode(new_player_name);

    //if the list is empty
	if(!head)
	{
	    //make this new node to the first node
		head = new_node;
	}
	else
	{
	    //place the first node after the new node
		new_node->next = head;
		
		//make the new node the head of the list
		head = new_node;
	}
}


//remove removes a PlayerNode with the parameter name from this PlayerList
//if that node exists
//parameters: name_to_remove - the name in the Player data within the PlayerNode we want to remove
//returns: whether a node with that parameter name was removed
bool PlayerList::remove(string name_to_remove)
{
    //if the head has the name we want to remove
	if(head->data.getName() == name_to_remove)
	{
	    //store the head node
		PlayerNode* node_to_remove = head;
		
		//reassign the head of the list to the second node
		head = head->next;
		
		//free the memory taken up by what was the head node
		delete node_to_remove;

        //return true, the node was removed from the list
		return true;
	}
	else
	{
	    //make an iterating pointer that starts at the second node
		PlayerNode* curr_node = head->next;
		
		//make a pointer to store the node before the iterating pointer's node
		PlayerNode* successor = head;
        
        //repeat until we check every node in the list
		while(curr_node)
		{
		    //if the name of the Player in the current node
		    //is the name of the node we want to remove
			if(curr_node->data.getName() == name_to_remove)
			{
			    //remove this node from the list by changing the successor pointer's
			    //next pointer
				successor->next = curr_node->next;
				
				//free the memory taken up by this current node
				delete curr_node;

                //return true, the node was removed from the list
				return true;
			}

			successor = curr_node;
			curr_node = curr_node->next;

		}

	}

    //if every node in the list has been searched, and we didn't find
    //a node with the desired name
	//return false, no node was removed
	return false;
}


//at gives the PlayerNode that is at a specific index in the list
//if the index isn't valid, it will give nullptr
//parameters: index - the index to look at for a node
//returns: the PlayerNode at the parameter index
PlayerNode* PlayerList::at(int index)
{
    //if the index is negative
	if(index < 0)
	{
	    //return nullptr
	    //there are no nodes at indexes less than zero
		return nullptr;
	}
    
    //make an iterating pointer at the head of the list
	PlayerNode* curr_node = head;

    //loop for as many times as the index
	while(index > 0)
	{
	    //if the curr_node becomes nullptr
		if(curr_node == nullptr)
		{
		    //this index is outside the bounds of the list
			//return nullptr
			return nullptr;
		}
    
        //go to the next node in the list and subtract one from the index
		curr_node = curr_node->next;
		index--;
	}
    
    //return the current node within the list
	return curr_node;

}

//length determines how many nodes are in this linked list
//returns: the number of PlayerNodes in this linked list
int PlayerList::length() const
{
    //make an int to store the number of nodes in this list
    int list_length = 0;
    
    //make an iterating pointer that starts at the first node in this list
	PlayerNode* curr_node = head;
    
    //repeat for each node in this list
	while(curr_node)
	{   
	    //add one to the list length
		list_length++;
        
        //go to the next node
		curr_node = curr_node->next;
	}
	
	//return the list length
	return list_length;
}

//tableHeaders gives a specific table header based on the number given to it
//0 gives the first header, 1 gives the second header, etc.
//parameters: index - the number corresponding with the desired header
//returns: the header text the corresponds with the parameter index
string PlayerList::tableHeaders(int index) const
{
    //the header column of the table will look like this:
    //NAME:                 |
    //MILITARY (RED):       |
    //COINS:                |
    //WONDER:               |
    //CIVIL (BLUE):         |
    //COMMERCIAL (YELLOW):  |
    //GUILDS (PURPLE):      |
    //SCIENCE (GREEN):      |
    //TOTAL:                |
    
	switch(index)
	{
	case 0:
		return "NAME";
	case 1:
		return "MILITARY (RED)";
	case 2:
		return "COINS";
	case 3:
		return "WONDER";
	case 4:
		return "CIVIL (BLUE)";
	case 5:
		return "COMMERCIAL (YELLOW)";
	case 6:
		return "GUILDS (PURPLE)";
	case 7:
		return "SCIENCE (GREEN)";
	case 8:
		return "TOTAL";
	default:
		return "";
	}
}


//print outputs out a score sheet table with all the Players stored in this list and their scores
void PlayerList::print() const
{
    //first, find how wide the columns with the players' info need to be
	
	//create an int to store the length of the longest player name
	//start by assuming the longerst player name is the first name in the list
	int longest_name_length = head->data.getName().length();
	
	//create an int to store the number of players in this list
	int num_players = length();

    //make an iterating pointer that begins at the first node in the list
	PlayerNode* curr_node = head->next;

    //repeat for each node in the linked list
	while(curr_node)
	{
	    //if this node has a longer name than the longest name length stored
		if(curr_node->data.getName().length() > longest_name_length)
		{
		    //replace the longest name with the new one
			longest_name_length = curr_node->data.getName().length();
		}

		curr_node = curr_node->next;
	}
    
    //create an int to store the width of each row of the table
	int table_width = 24 + num_players * (longest_name_length + 3);

    
    //output 9 rows
	for(int i = 0; i < 9; i++)
	{
	    //set the iterating pointer back to the head node of the list
		curr_node = head;
		
		//output the header for this row in the table
		cout << endl << left << setw(22) << setfill(' ') << " " + tableHeaders(i) + ": " << " | ";
        
        //repeat for each player in the list
		while(curr_node)
		{
		    //if this is the first row,
			if(i == 0)
			{
			    //output the names of each player
				cout << setw(longest_name_length) << curr_node->data.getName() << " | ";
			}
			//if this is the second row,
			else if(i == 1)
			{
			    //output the points each player has from their military (red) cards
 			    cout << setw(longest_name_length) << curr_node->data.getCardScores()[0] << " | ";
			}
			//if this is the third row,
			else if(i == 2)
			{   
			    //output the points each player has from their coins
			    cout << setw(longest_name_length) << curr_node->data.getNumCoins() / 3 << " | ";
			}
			//if this is the 8th row,
			else if(i == 7)
			{
			    //output the points each player has from their science symbols
			    cout << setw(longest_name_length) << curr_node->data.calcScienceScore() << " | ";
			}
			//if this is the 9th and final row,
			else if(i == 8)
			{
			    //output the total score for each player
				cout << setw(longest_name_length) << curr_node->data.calcTotal() << " | ";
			}
			//if this is the 4th, 5th, 6th or 7th row,
			else
			{
			    //output the points each player has from that card type or their wonder board
			    //4th row has points from wonder boards
			    //5th row has points from Civil (blue) cards
			    //6th row has points from Commercial (yellow) cards
			    //7th row has points from Guilds (purple) cards
				cout << setw(longest_name_length) << curr_node->data.getCardScores()[i - 2] << " | ";
			}


			curr_node = curr_node->next;
		}
        
        //output a row of hyphens to divide each row of text
		cout << endl<< setw(table_width) << setfill('-') << "";

	}



}


//determineWinner determines the winner(s) out of the Players in this list
//returns: the name(s) of the winning player(s)
string PlayerList::determineWinner() const
{
    //if this list has no players
    if(!head) { return "List Is Empty";  }
    
    //make an array to hold the winners
    PlayerNode* winners[length()];
    
    //set all the elements in this array to nullptr
    for(int i = 0; i < length(); i++)    { winners[i] = nullptr; }
    
    //assume that the first node is a winner
    //add it to the first spot in the array
    winners[0] = head;
    
    //make an int to store the next available index in the winners array
    int winners_next_index = 1;
    
    //create an int to store the highest score
    //assume the score of the first node
    int highest_score = head->getData()->calcTotal();
    
    //make an iterating pointer that starts at the second node
    PlayerNode* curr_node = head->next;

    //repeat for each node in the list
	while(curr_node)
	{
		
		//if this current node has a higher score than the stored highest score
		//or if this current node has a score equal to the stored highest score
		//and this current node have more coins than the other winning players
        if(curr_node->getData()->calcTotal() > highest_score
        || (curr_node->getData()->calcTotal() == highest_score && 
            curr_node->getData()->getNumCoins() > winners[0]->getData()->getNumCoins() ) )
        {
            //this player has beated the other winners
            
            //clear the winners array
            for(int i = 0; i < length(); i++)    { winners[i] = nullptr; }
            
            //add the current node to the first spot in the winners array
            winners[0] = curr_node;
            
            //set the next available index in the winners array to 1
            winners_next_index = 1;
            
            //change the highest score to this new score
            highest_score = winners[0]->getData()->calcTotal();
            
        }
        //if this current node has a score equal to the stored highest score
		//and this current node have the same amount of coins as the other winning players
        else if (curr_node->getData()->calcTotal() == highest_score && 
            curr_node->getData()->getNumCoins() == winners[0]->getData()->getNumCoins() )
        {
            //this player ties with the other winners
            
            //add this current node to the winners array
            winners[winners_next_index] = curr_node;
            
            //increment the next available index
            winners_next_index++;
            
        }

		curr_node = curr_node->next;
	}
	
	//make a string to store the names of the winners
	//start by adding the name of the first winner
	string winner_names = winners[0]->getData()->getName();
	
	//repeat for each element of the array
	for(int i = 1; i < length(); i++)
	{
	    //or until we reach a nullptr in the array
	    if(!winners[i])
	    {
	        break;
	    }
	    
	    //add " and " and the winner's name to the end of the string
	    winner_names += " and " + winners[i]->getData()->getName();
	}
    
    //return the names of the winners
    return winner_names;
		
}

//destructor
PlayerList::~PlayerList()
{
    //start iterating pointer at head of list
	PlayerNode* curr_node = head;
	
	//make another pointer to hold the node to delete
	PlayerNode* node_to_delete = nullptr;

    //repeat until we reach the end of the list
	while(curr_node)
	{
	    //save the current node
		node_to_delete = curr_node;
		
		//move to the next node in the list
		curr_node = curr_node->next;
		
		//free the memory taken up by the saved node
		delete node_to_delete;
	}
}
