//Author: Josh T

/*
Summary:
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
*/

#include "playerlist.h" //for PlayerList

#include <iostream> //for cout, cin and endl
#include <iomanip> //for setw and setfill

using namespace std;

//getAllNames receives the names of the players from the user and stores them in nodes in a PlayerList
//parameters: player_list - the list to put these players in
void getAllNames(PlayerList* player_list);

//getScoresFromUser receives the scores of the players from the user and updates the players in a PlayerList
//parameters: player_list - the list of players who's scores to update
void getScoresFromUser(PlayerList* player_list);

int main()
{
    //create PlayerList
    PlayerList* main_score_sheet = new PlayerList();
    
    //output introduction messages
    cout << setw(70) << setfill('-') << "" << endl;
    cout << "Welcome to the Digital 7 Wonders Score Sheet" << endl;
    cout << setw(70) << setfill('-') << "" << endl << endl;
        
    cout << setw(70) << setfill('-') << "" << endl;
    cout << "Enter the names the players below to add them to the score sheet." << endl;
    cout << "Type R to remove a name you've already added." << endl;
    cout << "Type Q when you've entered every name." << endl;
    cout << setw(70) << setfill('-') << "" << endl << endl;
    
    //get the names of the players using getAllNames
    getAllNames(main_score_sheet);
    
    //get the scores for these players using getScoresFromUser
    getScoresFromUser(main_score_sheet);
    
    //output a table with all the players and their scores
    main_score_sheet->print();
    
    //call determineWinner on the PlayerList to determine who won this game
    string winners = main_score_sheet->determineWinner();
    
    
    //if there is only one winner
    if(winners.find(" and ") == winners.npos)
    {
        //output who the winner is
        cout << endl << winners << " is the winner." << endl;
    }
    else
    {
        //output that there is a tie
        //also output all the winners
        cout << endl << "We have a tie!" << endl << winners << " are the winners." << endl;
    }
    
    
    return 0;
}


//getAllNames receives the names of the players from the user and stores them in nodes in a PlayerList
//parameters: player_list - the list to put these players in
void getAllNames(PlayerList* player_list)
{
    //create an int to store how many players the user has entered
    int num_players = 0;
    
    //create a string to store the name the user has entered
    string curr_player_name = "";
    
    //repeat until the user has quit or until they have entered 7 player names
    while(num_players < 7)
    {
        //get the player names
        getline(cin, curr_player_name);
        
        //if the user entered a Q or q,
        if(curr_player_name == "Q"  || curr_player_name == "q")
        {
            //if the user has entered at least two player names
            if(num_players >= 2){  
                
                //stop prompting for more names
                break;   
            }
            //if the user still needs to enter more names, let them know
            else
            {
                cout << "You must enter names for at least two players." << endl;
            }
        }
        //if the user entered a R or r, prompt the user for a name to remove from the PlayerList
        else if(curr_player_name == "R"  || curr_player_name == "r")
        {
            //get a name of a Player to remove from the list
            cout << "Which name do you want to remove?" << endl;
            getline(cin, curr_player_name);
            
            
            //attempt to remove a Player with this name
            
            //if a Player was removed
            if(player_list->remove(curr_player_name) )
            {
                //let the user know
                cout << curr_player_name << " has been removed." << endl << endl;
                
                //reduce the number of players entered by one
                num_players--;
            }
            //if a Player wasn't removed
            else
            {
                //let the user know nothing was removed
                cout << curr_player_name << " isn't on the score sheet." << endl << endl;
            }
            
            
        }
        //if the user entered a name,
        else
        {
            //add a Player with this name to the list
            player_list->append(curr_player_name);
            
            //increase the number of players entered by one
            num_players++;
        }
        

    }
    
    //output how many players the user entered
    cout << "Your game has " << num_players << " players." << endl;
    

}


//getScoresFromUser receives the scores of the players from the user and updates the players in a PlayerList
//parameters: player_list - the list of players who's scores to update
void getScoresFromUser(PlayerList* player_list)
{
    //create a pointer to store the current Player
    Player* curr_player = nullptr;
    
    ///create a pointer to store the number of players
    int num_players = player_list->length();
    
    //create an int to store the user's input
    int input = 0;

    //repeat the following 7 times, once for each kind of points you can gain
    for(int i = 0; i < 7; i++)
    {
        //output a heading with the kind of points being entered
            cout << setw(70) << setfill('-') << "" << endl;
            cout << "Let's calculate the " << player_list->tableHeaders(i + 1) << " scores." << endl;
            cout << setw(70) << setfill('-') << "" << endl << endl;
            
        //repeat for each player in the list
        for(int j = 0; j < num_players; j++)
        {
            //store the current Player
            curr_player = player_list->at(j)->getData();
            
            //if this is the second time around the loop
            if(i == 1)
            {
                //ask the user how many coins this Player has
                
                //keep prompting them until they enter a non negative number of coins
                while(true)
                {
                    cout << "How many coins does " << curr_player->getName() << " have?" << endl; 
                    cin >> input;
                    
                    if(curr_player->setNumCoins(input))
                    {
                        break;
                    }
                    else
                    {
                        cout << "You can't have a negative number of coins." << endl << endl;
                    }
                    
                
                }
                

            }
            //if this is the 7th time around the loop
            else if(i == 6)
            {
                //ask the user how many gear symbols this Player has
                
                //keep prompting them until they enter a non negative number of gear symbols
                while(true)
                {
                    cout << "How many gear symbols does " << curr_player->getName() << " have?" << endl; 
                    cin >> input;
                    
                    if(curr_player->setNumGears(input))
                    {
                        break;
                    }
                    else
                    {
                        cout << "You can't have a negative number of gear symbols." << endl << endl;
                    }
                }
                
                //ask the user how many compass symbols this Player has
                
                //keep prompting them until they enter a non negative number of compass symbols
                while(true)
                {
                    cout << "How many compass symbols does " << curr_player->getName() << " have?" << endl; 
                    cin >> input;
                    
                    if(curr_player->setNumCompasses(input))
                    {
                        break;
                    }
                    else
                    {
                        cout << "You can't have a negative number of compass symbols." << endl << endl;
                    }
                }
                
                //ask the user how many tablet symbols this Player has
                
                //keep prompting them until they enter a non negative number of tablet symbols
                while(true)
                {
                    cout << "How many tablet symbols does " << curr_player->getName() << " have?" << endl; 
                    cin >> input;
                    
                    if(curr_player->setNumTablets(input))
                    {
                        break;
                    }
                    else
                    {
                        cout << "You can't have a negative number of tablet symbols." << endl << endl;
                    }
                }
            }
            //if this is the first, third, 4th, 5th or 6th time around the loop
            else
            {
                //ask the user for some number of points from a given source
                cout << "How many points does " << curr_player->getName() << " have from their " 
                << player_list->tableHeaders(i + 1);
                
                //if this isn't the third time around the loop,
                //add "cards" to the end of the type
                if(i != 2)  { cout << " cards"; }
                
                cout << "?" << endl;
                
                //get the input from the user
                cin >> input;
                
                //update this player's score for the given source
                //i = 0 is Military (Red) cards
                //i = 2 is Wonder board
                //i = 3 is Civil (Blue) cards
                //i = 4 is Commercial (Yellow) cards
                //i = 5 is Guilds (Guild) cards
                if(i == 0) { curr_player->setCardScore( curr_player->getCardScores()[i] + input, i); }
                else { curr_player->setCardScore( curr_player->getCardScores()[i - 1] + input, i - 1);   }
            }
            

        }
    }
}
