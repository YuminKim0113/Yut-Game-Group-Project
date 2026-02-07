//Including libraries and other files
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <limits>
#include "Functions.h"
#include "Map.h"
#include "Player.h"
#include "Station.h"
#include "Mal.h"
using namespace std;

//Comments in this file explains the general flow of the game play.

int main(){
    //Defining types of variables used for the game play
    Map gameMap;
    Player player1;
    Player player2;
    int counter = -1;
    int turn;
    int TicketResult;
    int checkwin = 0;
    string input;
    int malSelect;
    vector<int> tickets;
    string outputText;
    int id;
    string idstr;
    bool valid_input;
    string malSelectstr;
    
     //For aesthetic purpose
    for (int i = 0; i < 20; i++){
        cout << endl;
    }
    
    //Welcoming ASCII art
    WelcomeText();
    this_thread::sleep_for(chrono::seconds(1));
    
    //For aesthetic purpose
    typingEffect("Welcome to Korean Traditional Yut Game (MTR EDITION) !!!! ");
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl;
    typingEffect("Press Enter to Continue and read the rule");
    getline(cin, input);

    //Rule Explaing
    cout << endl;
    gameRuleText();
    cout << endl;
    typingEffect("Press Enter to Continue");
    getline(cin, input);
    
    //If there are saved games, the system asks the player which game to load. If unsuccessful or no saved games, create a new game to play
    if (Get_Number_of_Saved_Games() > 0){
        typingEffect("You have " + to_string(Get_Number_of_Saved_Games()) + " saved games.");
        cout << endl;
        loadGameNames();
        while (true){
            typingEffect("Do you want to continue the game or to start new game?(1. Continue the saved game, 2. Start a new game): ");
            
            valid_input = false;

            while (!valid_input) {
                cin >> idstr;
                
                try {
                    id = stoi(idstr);
                    
                    if ((id != 1 && id != 2)) {
                        cout << "Invalid input. Please input the proper number to contintue: " << endl;
                    } else {
                        valid_input = true;
                    }
                } catch (...) {
                    cout << "Invalid input. Input must be an integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            if (id == 1){
                typingEffect("Type a game that you want to continue: ");
                cin >> input;
                int loadfailed = 0;
                load_game(input, gameMap, player1, player2, loadfailed);

                while(loadfailed == 1){
                    typingEffect("Failed to load game. Please input a correct name of the game: ");
                    cin >> input;
                    load_game(input, gameMap, player1, player2, loadfailed);
                    break;
                }
                if (loadfailed == 0){
                    addMalDisplay(gameMap, player1, player2);
                    break;
                }

            } else if (id == 2){
                typingEffect("New game will be started.");
                cout << endl;
                typingEffect("Press Enter to Start");
                cout << endl;
                getline(cin, input);
                typingEffect("Enter player 1's name: ");
                cin >> input;
                player1.setName(input);
                typingEffect("Enter player 2's name: ");
                cin >> input;
                player2.setName(input);
                break;
            }
        }
    } else {
        typingEffect("There are no saved games. We will start a new game!");
        cout << endl;
        typingEffect("Press Enter to Start");
        getline(cin, input);
        typingEffect("Enter player 1's name: ");
        cin >> input;
        player1.setName(input);
        typingEffect("Enter player 2's name: ");
        cin >> input;
        player2.setName(input);
    }



    //For aesthetic purpose
    typingEffect("We will start game in...");
    cout << endl;
    for (int i = 0; i < 3; i++){
        cout << "\r" << 3 - i << "..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }


    while (true) {
        //Printing map to show the game status    
        gameMap.printMap();       

        //For aesthetic purpose
        for (int i = 0; i < 100; i++) {
            cout << "-";
        }
        cout << endl;
        
        //Asks the player to continue or save the game when turn changes. Does not process until the player enters a valid input. Game will still continue after saving
        if (counter != -1 && turn == 1){
            typingEffect("Continue the Game? ('q' for exit / 's' to save / Press Enter to continue)");
            cout << endl;
            if (!input.empty()){
            cin.ignore(); 
            }
            getline(cin, input);
            while (input != "q" && input != "s" && !input.empty()){
                cout << "Invalid input. Please enter a valid character 'q' or 's' or Press Enter" << endl;
                cout << "Type here: " << endl;
                getline(cin, input);
            }
                if (input == "q"){
                    cout << "Exit the Game." << endl;
                    break;
                } else if(input == "s"){
                    if (turn == 0){
                        player1.check_Carried();
                    } else if (turn == 1) {
                        player2.check_Carried();
                    }
                    cout << "Game Name : ";
                    cin >> input;
                    save_game(input, gameMap, player1, player2);
                    saveGameName(input);
                    cout << "See you later!" << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    break;
                }
            
        }

        //Able to track which player's turn
        counter = counter + 1;

        //Showing who's turn using counter
        if(counter % 2 == 0){
            typingEffect("It is " + player1.getName() + "'s turn");
            turn = 0;
        }
        else{
            typingEffect("It is " + player2.getName() + "'s turn");
            turn = 1;
        }
        cout << endl;
        cout << endl;
        
        //For aesthetic purpose
        typingEffect("Press Enter to roll the Yut (Get the Ticket)!!");
        if (!input.empty()){
            cin.ignore();   
        }
        getline(cin, input);
        
        //For aesthetic purpose
        typingEffect("Your ticket is...");
        cout << endl;
        for (int i = 0; i < 3; i++){
            cout <<  3 - i << "..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }



        while (true){
            //Saves the tickets that players have gained until now
            TicketResult = getTicket();
            tickets.push_back(TicketResult);
            
             //Shows which ticket the player gained
            cout << getTicketName(TicketResult) << "!!!" << endl;
            displayTicket(TicketResult);
            this_thread::sleep_for(chrono::seconds(2));
            if (turn == 0){
                if (player1.no_Mal_on_Map() && TicketResult == -1){
                    break;
                }
            } else {
                if (player2.no_Mal_on_Map() && TicketResult == -1){
                    break;
                }
            }
            
            //Showing player that he or she is able to roll the Yut once more (get ticket once more) as the player picked a special ticket
            if (TicketResult < 4){
                break;
            } else if (TicketResult >= 4){
                cout << endl;
                typingEffect("Wow!! You got " + getTicketName(TicketResult) + " ticket! You can roll the Yut one more Time! Press Enter to roll the Yut.");
                getline(cin, input);
                cout << "Your ticket is..." << endl;
                for (int i = 0; i < 3; i++){
                    cout << "\r" << 3 - i << "..." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }       
            } 
        }
        if (turn == 0){
            //When player gains secret ticket when there is no mal in the board (for each player)
            if (player1.no_Mal_on_Map() && TicketResult == -1 && tickets.size() <= 1){
                cout << "You do not have any Mal to move backward!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                tickets.clear();
                continue;
            }
        } else {
            //When player gains secret ticket when there is no mal in the board (for each player)
            if (player2.no_Mal_on_Map() && TicketResult == -1 && tickets.size() <= 1){
                cout << "You do not have any Mal to move backward!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                tickets.clear();
                continue;
            }
        }
        


        while (tickets.size() != 0){
            //Showing game status during the game
            gameMap.printMap();


            //Check if the player's mal is being carried, depending on which player's turn it is
            if (turn == 0){
                player1.check_Carried();
            } else if (turn == 1) {
                player2.check_Carried();
            }
            
            //Asking which ticket to use and which mal to move to a player. Asks until the player types a correct input
            TicketResult = askWhichTicket(tickets);
            displayTicket(TicketResult);
            vector<string> malVector = askMalMovement(turn, player1, player2);

            valid_input = false;
            while (!valid_input) {
                cin >> malSelectstr;
                
                try {
                    malSelect = stoi(malSelectstr);
                    
                    if (malSelect < 1 || malSelect > malVector.size()) {
                        cout << "Invalid input. Please input an appropriate mal number in the given selection." << endl;
                    } else {
                        valid_input = true;
                    }
                } catch (...) {
                    cout << "Invalid input. Input must be an integer." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            valid_input = false;
            int count = 0;

            if (turn == 0){
                while (!valid_input) {
                    if (count != 0){
                        cin >> malSelectstr;
                    }
                    
                    try {
                        count ++;
                        malSelect = stoi(malSelectstr);
                        
                        if (malSelect < 1 || malSelect > malVector.size() || (TicketResult == -1 && !player1.getMal(stoi(malVector[malSelect-1].substr(1,1))).can_finish)) {
                            cout << "Invalid input. The selected mal did not start yet. Please input an appropriate mal number that is on the map." << endl;
                        } else {
                            valid_input = true;
                        }
                    } catch (...) {
                        cout << "Invalid input. Input must be an integer." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            } else {
                while (!valid_input) {
                    if (count != 0){
                        cin >> malSelectstr;
                    }
                    
                    try {
                        count++;
                        malSelect = stoi(malSelectstr);
                        
                        if (malSelect < 1 || malSelect > malVector.size() || (TicketResult == -1 && !player2.getMal(stoi(malVector[malSelect-1].substr(1,1))).can_finish)) {
                            cout << "Invalid input. The selected mal did not start yet. Please input an appropriate mal number that is on the map." << endl;
                        } else {
                            valid_input = true;
                        }
                    } catch (...) {
                        cout << "Invalid input. Input must be an integer." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }

            }

            int Num_in_malSign = stoi(malVector[malSelect-1].substr(1,1));

            //Showing the location of the mal selected by the player before the movement
            if (turn == 0){
                cout << "Current Position of " << malVector[malSelect-1] << " is " << gameMap.mapPlayerLocation_to_station(player1.getRow(Num_in_malSign),player1.getCol(Num_in_malSign)) << endl;
            } else if (turn == 1) {
                cout << "Current Position of " << malVector[malSelect-1] << " is " << gameMap.mapPlayerLocation_to_station(player2.getRow(Num_in_malSign),player2.getCol(Num_in_malSign)) << endl;
            }
            this_thread::sleep_for(chrono::seconds(1));
            cout << endl;

            //Save the location of the selected mal after the movement, display some features of the game (ticket, map ..etc)

            bool finish = false;
            
            if (turn == 0){
                move_or_carry_Mal(player1, 0, malVector[malSelect-1], TicketResult, gameMap, player1.getRow(Num_in_malSign), player1.getCol(Num_in_malSign));
                if (turn == 0){
                    player1.check_Carried();
                } else if (turn == 1) {
                    player2.check_Carried();
                }
                if (player1.getMal(stoi(malVector[malSelect-1].substr(1,1))).finished){
                    gameMap.removeMal(player1.getPreviousRow(Num_in_malSign), player1.getPreviousCol(Num_in_malSign), true);
                    gameMap.removeMal(player1.getRow(Num_in_malSign), player1.getCol(Num_in_malSign), true);
                    finish = true;
                } else {
                    moveMalDisplay(gameMap, player1, carriedMalNums(player1, malVector[malSelect-1]), player1.getPreviousRow(Num_in_malSign), player1.getPreviousCol(Num_in_malSign),player1.getRow(Num_in_malSign), player1.getCol(Num_in_malSign));
                }
            } else if (turn == 1) {
                move_or_carry_Mal(player2, 1, malVector[malSelect-1], TicketResult, gameMap, player2.getRow(Num_in_malSign), player2.getCol(Num_in_malSign));
                if (turn == 0){
                    player1.check_Carried();
                } else if (turn == 1) {
                    player2.check_Carried();
                }
                if (player2.getMal(stoi(malVector[malSelect-1].substr(1,1))).finished){
                    gameMap.removeMal(player2.getPreviousRow(Num_in_malSign), player2.getPreviousCol(Num_in_malSign), true);
                    gameMap.removeMal(player2.getRow(Num_in_malSign), player2.getCol(Num_in_malSign), true);
                    finish = true;
                } else {
                    moveMalDisplay(gameMap, player2, carriedMalNums(player2, malVector[malSelect-1]), player2.getPreviousRow(Num_in_malSign), player2.getPreviousCol(Num_in_malSign),player2.getRow(Num_in_malSign), player2.getCol(Num_in_malSign));
                }
            }

            //Showing the new position of the selected mal
            if (turn == 0){
                if (!finish){
                    cout << malVector[malSelect-1] << " will move to " << gameMap.mapPlayerLocation_to_station(player1.getRow(Num_in_malSign),player1.getCol(Num_in_malSign)) << endl;
                } else {
                    cout << malVector[malSelect-1] << " will finish." << endl;
                }
            } else if (turn == 1) {
                if (!finish){
                    cout << malVector[malSelect-1] << " will move to " << gameMap.mapPlayerLocation_to_station(player2.getRow(Num_in_malSign),player2.getCol(Num_in_malSign)) << endl;
                } else {
                    cout << malVector[malSelect-1] << " will finish." << endl;
                }
            }

            this_thread::sleep_for(chrono::seconds(2));

            //Explaining the location that the mal arrived, and check if the moved mal killed any opponent's mal       
            if (turn == 0 && !finish){
                PrintExplain(player1.getRow(Num_in_malSign),player1.getCol(Num_in_malSign));
            } else if (turn == 1 && !finish) {
                PrintExplain(player2.getRow(Num_in_malSign),player2.getCol(Num_in_malSign));
            }
            
            if (turn == 0){
                if (killMal(gameMap, player2, turn, player1.getRow(Num_in_malSign), player1.getCol(Num_in_malSign))){
                    typingEffect("Wow!! You killed the opponent's mal. Yut will be rolled one more Time!");
                    cout << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    cout << endl;
                    while (true){
                        gameMap.printMap();
                        this_thread::sleep_for(chrono::seconds(1));
                        typingEffect("Your ticket is...");
                        cout << endl;
                        for (int i = 0; i < 3; i++){
                            cout <<  3 - i << "..." << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        //Saves the tickets that players have gained until now
                        TicketResult = getTicket();
                        tickets.push_back(TicketResult);
                        
                        //Shows which ticket the player gained
                        cout << getTicketName(TicketResult) << "!!!" << endl;
                        displayTicket(TicketResult);
                        this_thread::sleep_for(chrono::seconds(2));
                        
                        //Showing player that he or she is able to roll the Yut once more (get ticket once more) as the player picked a special ticket
                        if (TicketResult < 4){
                            break;
                        } else if (TicketResult >= 4){
                            cout << endl;
                            typingEffect("Wow!! You got " + getTicketName(TicketResult) + " ticket! Yut will be rolled one more Time!");
                            cout << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                            cout << endl;     
                        } 
                    }
                }
            } else if (turn == 1) {
                if (killMal(gameMap, player1, turn, player2.getRow(Num_in_malSign), player2.getCol(Num_in_malSign))){
                    typingEffect("Wow!! You killed the opponent's mal. Yut will be rolled one more Time!");
                    cout << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    cout << endl;
                    while (true){
                        gameMap.printMap();
                        this_thread::sleep_for(chrono::seconds(1));
                        typingEffect("Your ticket is...");
                        cout << endl;
                        for (int i = 0; i < 3; i++){
                            cout <<  3 - i << "..." << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        //Saves the tickets that players have gained until now
                        TicketResult = getTicket();
                        tickets.push_back(TicketResult);
                        
                        //Shows which ticket the player gained
                        cout << getTicketName(TicketResult) << "!!!" << endl;
                        displayTicket(TicketResult);
                        this_thread::sleep_for(chrono::seconds(2));
                        
                        //Showing player that he or she is able to roll the Yut once more (get ticket once more) as the player picked a special ticket
                        if (TicketResult < 4){
                            break;
                        } else if (TicketResult >= 4){
                            cout << endl;
                            typingEffect("Wow!! You got " + getTicketName(TicketResult) + " ticket! Yut will be rolled one more Time!");
                            cout << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                            cout << endl;         
                        } 
                    }
                }
            }
            //Check if the game is over or not. If the game is over, change the "checkwin" variable to know if the game has ended or not
            if(turn == 0 && player1.win()){
                cout << "Game Over! Player 1 (" << player1.getName() << ") wins!!!" << endl;
                checkwin = 1;
                break;           
            } else if (turn == 1 && player2.win()){
                cout << "Game Over! Player 2 (" << player2.getName() << ") wins!!!" << endl;
                checkwin = 1;
                break;
            }

        }

        //When the game is over, the program automatically ends 
        if (checkwin == 1){
            typingEffect("Game is over. Finished game will not be saved");
            cout << endl;
            EndingText();
            cout << endl;
            typingEffect("Thank you for playing. See you in the next game!!!");
            break; 
        }
        //If the game is not over, change the turn   
        typingEffect("Press Enter to Change the turn");
        cin.ignore(); 
        getline(cin, input);
    }
    return 0;
}
