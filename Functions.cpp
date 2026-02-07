//For aesthetic purpose, and including libraries and other files
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
#include "Functions.h"
#include "Map.h"
#include "Player.h"
#include "Station.h"
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define GRAY "\033[37m"
#define BROWN "\033[0;33m"
using namespace std;

//Welcoming players with ASCII art
void WelcomeText(){
    cout << "\033[1m";
    cout<<RED<<" _    _        _                                       _   "<<endl;       
    cout<<RED<<"| |  | |      | |                                     | |  "<<endl;       
    cout<<YELLOW<<"| |  | |  ___ | |  ___   ___   _ __ ___    ___        | |_   ___  "<<endl;
    cout<<YELLOW<<"| |/\\| | / _ \\| | / __| / _ \\ | '_ ` _ \\  / _ \\       | __| / _ \\ "<<endl;
    cout<<GREEN<<"\\  /\\  /|  __/| || (__ | (_) || | | | | ||  __/       | |_ | (_) |"<<endl;
    cout<<GREEN<<" \\/  \\/  \\___||_| \\___| \\___/ |_| |_| |_| \\___|        \\__| \\___/ "<<endl;
    cout<<CYAN<<" __   __ _   _  _____  _____   ___  ___  ___ _____  _  _ "<<endl;
    cout<<CYAN<<" \\ \\ / /| | | ||_   _||  __ \\ / _ \\ |  \\/  ||  ___|| || |"<<endl;
    cout<<BLUE<<"  \\ V / | | | |  | |  | |  \\// /_\\ \\| .  . || |__  | || |"<<endl;
    cout<<BLUE<<"   \\ /  | | | |  | |  | | __ |  _  || |\\/| ||  __| | || |"<<endl;
    cout<<MAGENTA<<"   | |  | |_| |  | |  | |_\\ \\| | | || |  | || |___ |_||_|"<<endl;
    cout<<MAGENTA<<"   \\_/   \\___/   \\_/   \\____/\\_| |_/\\_|  |_/\\____/ (_)(_)"<<endl;
    cout << "\033[0m";
}
// Indication of the end of game
void EndingText(){
    cout << "\033[1m";
    cout<<RED<<" _____                             _         _       _   _               _" << endl;
    cout<<RED<<"/  __ \\                           | |       | |     | | (_)             | |" << endl;
    cout<<RED<<"| /  \\/ ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __   | |" << endl;
    cout<<RED<<"| |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\  | |" << endl;
    cout<<BLUE<<"| \\__/\\ (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | | |_|" << endl;
    cout<<BLUE<<" \\____/\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_| (_)" << endl;
    cout<<BLUE<<"                    __/ |                                                  " << endl;
    cout<<BLUE<<"                   |___/                                                   " << endl;
    cout << "\033[0m";
}

// Breif explanation of the game 
void gameRuleText(){
    cout << "Yutnori is a traditional Korean board game that has been played for hundreds of years. " << endl;
    cout << "It is a game that involves strategy, luck, and skill. The game is played on a square board " << endl;
    cout << "that has four corners and a center point. Each player has three game pieces, which are called " << endl;
    cout << "\"Mal\". They move around the board in a clockwise direction. The goal of the game is to be " << endl;
    cout << "the first player to move all of their game pieces from their starting point to the finish " << endl;
    cout << "line in the center of the board.\n" << endl;

    cout << "To start the game, each player takes turns rolling four sticks called yut, in this game it is called " << endl;
    cout << "\"Ticket\", since the game's theme is \"Train.\" The number of \"x\" in the display represents the number of " << endl;
    cout << "possible moves. There are six possible outcomes of a yut roll, which correspond to the six different types of moves:" << endl;
    cout << "1. Bronze Ticket: Move one space" << endl;
    cout << "2. Silver Ticket: Move two spaces." << endl;
    cout << "3. Gold Ticket: Move three spaces." << endl;
    cout << "4. Platinum Ticket: Move four spaces and roll again." << endl;
    cout << "5. Diamond Ticket: Move five spaces and roll again." << endl;
    cout << "6. Secret Ticket: Move one space backward.\n" << endl;

    cout << "There are some special rules in this game. If you can move to the same position with the opponent's mal, " << endl;
    cout << "then you can throw \"yut\" one more time and make the opponent's mal move back to the starting point. " << endl;
    cout << "In a similar situation, when one mal can be positioned on the same spot as another mal, the two mals need " << endl;
    cout << "is a certain path that the \"Mal\" must follow on the board. When mals are placed on the corner of the map." << endl;
    cout << "Mals will move to the center of map, and when they moved to the center of the map mals will move toward the end point." <<endl;

}


// Purpose: This function prints out a string to the console character by character, with a delay between each character, to simulate the effect of typing.
// Inputs: string outputText - the text to be printed to the console with the typing effect.
// Outputs: No return value. However, it prints out the input text to the console with the typing effect.
void typingEffect(string outputText){
    cout << "\033[1m"; 
    for (int i = 0; i < outputText.length(); i++) {
        char c = outputText[i];
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    cout << "\033[0m";
}

// Purpose: This function checks if a given game name (filename) already exists in the "Games.txt" file. If not, it appends the new game name to the file.
// Inputs: string filename - the name of the game to be saved.
// Outputs: No return value. However, it may modify "Games.txt" file by appending a new game name.
void saveGameName(string filename){
    ifstream inFile("Games.txt");
    bool fileExists = false;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (line == filename) {
                fileExists = true;
                break;
            }
        }
        inFile.close();
    }

    if (fileExists) {
        return;
    }

    ofstream outFile("Games.txt", ios::app);

    if (outFile.fail()) {
        cout << "Error opening file for saving game names." << endl;
        return;
    }

    outFile << filename << endl;

    outFile.close();
}

// Purpose: This function calculates and returns the total number of saved games by reading the "Games.txt" file.
// Inputs: None.
// Outputs: int - the total number of saved games. If the file cannot be opened or there is an error, it returns 0.
int Get_Number_of_Saved_Games(){
    ifstream inFile;
    inFile.open("Games.txt");

    if (inFile.fail()) {
        cout << "Error opening file for loading game names." << endl;
        return 0;
    }

    int count = 0;
    string line;

    while (getline(inFile, line)) {
        count++;
    }

    inFile.close();

    return count;
}

// Purpose: This function reads game names from the "Games.txt" file and displays them on the console.
// Inputs: None.
// Outputs: No return value. However, it prints out the game names stored in the "Games.txt" file.
void loadGameNames(){
    ifstream inFile;
    inFile.open("Games.txt");

    if (inFile.fail()) {
        cout << "Error while opening file for loading game names." << endl;
        return;
    }

    vector<string> gameNames;
    string gameName;

    while (getline(inFile, gameName)) {
        gameNames.push_back(gameName);
    }

    inFile.close();

    cout << "Saved Games: ";
    for (int i = 0; i < gameNames.size(); i++) {
        cout << gameNames[i] << "   ";
    }
    cout << endl;
}

// Purpose: This function saves the current state of the game into a file, including the players' names, and the status of each of their 'Mal' objects.
// Inputs: string filename - the name of the file to save the game state to. Map gameMap - the current state of the game map. Player player1 - the first player in the game. Player player2 - the second player in the game.
// Outputs: No return value. However, it creates/modifies a file with the given filename and saves the current game state into it.
void save_game(string filename, Map gameMap, Player player1, Player player2) {
    ofstream outFile;
    outFile.open((filename + ".txt").c_str());

    if (outFile.fail()) {
        cout << "Error opening file for saving game state." << endl;
        return;
    }

    // Save players' names and counter
    outFile << player1.getName() << endl;
    outFile << player2.getName() << endl;

    // Saving player1 data
    for (int i = 1; i <= 3; i++) {
        outFile << i << endl;
        outFile << player1.getMal(i).row << endl;
        outFile << player1.getMal(i).column << endl;
        outFile << player1.getMal(i).can_finish << endl;
        outFile << player1.getMal(i).finished << endl;
        outFile << player1.getMal(i).carried << endl;
    }


    // Saving player2 data
    for (int i = 1; i <= 3; i++) {
        outFile << i << endl;
        outFile << player2.getMal(i).row << endl;
        outFile << player2.getMal(i).column << endl;
        outFile << player2.getMal(i).can_finish << endl;
        outFile << player2.getMal(i).finished << endl;
        outFile << player2.getMal(i).carried << endl;
    }
    
    outFile.close();
    cout << "Game saved successfully." << endl;
    //Need to be finished
}

// Purpose: This function loads game data from a specified file, including players' names, 'Mal' data, and updates the game map.
// Inputs: string filename - the name of the file to load game data from.
//         Map &gameMap - reference to the game map to update.
//         Player &player1, &player2 - references to the player objects to load data into.
//         int &loadfailed - reference to an integer flag that is set to 1 if loading the game fails.
// Outputs: No return value. However, it modifies the input Map and Player objects by loading data into them from the file. If the file cannot be opened, it sets the 'loadfailed' flag to 1.
void load_game(string filename, Map &gameMap, Player &player1, Player &player2, int &loadfailed) {
    ifstream inFile;
    inFile.open((filename + ".txt").c_str());

    if (inFile.fail()) {
        cout << "Invalid input or Error in opening file." << endl;
        loadfailed = 1;
        return;
    }
    
    string player1Name, player2Name;
    int malNum, row, column;
    bool can_finish, finished, carried;
    int can_finish_int, finished_int, carried_int;

    // Load players' names and counter
    inFile >> player1Name >> player2Name;
    player1.setName(player1Name);
    player2.setName(player2Name);

    // Load player1 data
    for (int i = 1; i <= 3; i++) {
        inFile >> malNum >> row >> column >> can_finish_int >> finished_int >> carried_int;

        can_finish = static_cast<bool>(can_finish_int);
        finished = static_cast<bool>(finished_int);
        carried = static_cast<bool>(carried_int);

        player1.setMal(malNum, row, column, can_finish, finished, carried);
    }

    for (int i = 1; i<=3; i++){
        gameMap.addPlayerLocation(player1.getMal(i).row, player1.getMal(i).column, 0, i);
    }


    // Load player2 data
    for (int i = 1; i <= 3; i++) {
        inFile >> malNum >> row >> column >> can_finish_int >> finished_int >> carried_int;

        can_finish = static_cast<bool>(can_finish_int);
        finished = static_cast<bool>(finished_int);
        carried = static_cast<bool>(carried_int);

        player2.setMal(malNum, row, column, can_finish, finished, carried);
    }


     for (int i = 1; i<=3; i++){
        gameMap.addPlayerLocation(player2.getMal(i).row, player2.getMal(i).column, 0, i);
    }

    inFile.close();
    cout << "Game loaded successfully." << endl;
}


// Purpose: This function allows the user to select a ticket from their ticket pool. If the player only has one ticket, it automatically selects it for them.
// Inputs: vector<int> &tickets - a reference to a vector of integers representing the player's pool of tickets.
// Outputs: int - the selected ticket. Also modifies the input vector by removing the selected ticket.
int askWhichTicket(vector<int> &tickets){
    bool valid_input = false;
    string inputstr;
    if (tickets.size() == 1){
        cout << "You got " << getTicketName(tickets[0]) << " ticket." << endl;
        int ticket = tickets[0];
        tickets.clear();
        return ticket;
    }
    int input = 0;
    cout << endl;
    cout << "You got " << tickets.size() << " moves." << endl;
    for (int i = 0; i < tickets.size(); i++){
        cout << i + 1 << ". " << getTicketName(tickets[i]) << "     ";
    }
    cout << endl;
    cout << "Please choose the Ticket you want to use: ";
    while (!valid_input) {
        cin >> inputstr;
        
        try {
            input = stoi(inputstr);
            
            if (input < 1 || input > tickets.size()) {
                cout << "Invalid input. Please input a proper number for ticket use." << endl;
            } else {
                valid_input = true;
            }
        } catch (...) {
            cout << "Invalid input. Input must be an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int ticket = tickets[input-1];
    tickets.erase(tickets.begin() + (input-1));
    return ticket;
}

// Purpose: This function allows the user to select a ticket from their ticket pool. If the player only has one ticket, it automatically selects it for them.
// Inputs: vector<int> &tickets - a reference to a vector of integers representing the player's pool of tickets.
// Outputs: int - the selected ticket. Also modifies the input vector by removing the selected ticket.
vector<string> askMalMovement(int turn, Player one, Player two){
    vector<string> choices;
    bool alreadyAdded = false;

    if (turn == 0){
        for (int i = 1; i <= 3; i++) {
            alreadyAdded = false;
            Mal currentMal = one.getMal(i);
            
            if (currentMal.finished) {
                continue;
            } else if (currentMal.carried) {
                string prefix = "A" + to_string(i);
                for (int j = i + 1; j <= 3; j++) {
                    if (one.getMal(j).carried) {
                        prefix += to_string(j);
                    }
                }
                for (int j = 0; j < choices.size(); j ++){
                    for (int a= 0; a < choices[j].length(); a++){
                        if (choices[j].substr(a,1) == to_string(i)){
                            alreadyAdded = true;
                        }
                    }
                }
                if (!alreadyAdded){
                    choices.push_back(prefix);
                }
            } else {
                choices.push_back("A" + to_string(i));
            }
        }
    } else {
        for (int i = 1; i <= 3; i++) {
            alreadyAdded = false;
            Mal currentMal = two.getMal(i);
            
            if (currentMal.finished) {
                continue;
            } else if (currentMal.carried) {
                string prefix = "B" + to_string(i);
                for (int j = i + 1; j <= 3; j++) {
                    if (two.getMal(j).carried) {
                        prefix += to_string(j);
                    }
                }
                for (int j = 0; j < choices.size(); j ++){
                    for (int a= 0; a < choices[j].length(); a++){
                        if (choices[j].substr(a,1) == to_string(i)){
                            alreadyAdded = true;
                        }
                    }
                }
                if (!alreadyAdded){
                    choices.push_back(prefix);
                }
            } else {
                choices.push_back("B" + to_string(i));
            }
        }
    }
    

    if (choices.size() == 1){
        cout << "Which mal would you like to move?      " << "1. " << choices[0] << endl;
    } else if (choices.size() == 2 ){
        cout << "Which mal would you like to move?      " << "1. " << choices[0] << "      2. " << choices[1] << endl;
    } else{
        cout << "Which mal would you like to move?      " << "1. " << choices[0] << "      2. " << choices[1] << "      3. " << choices[2] << endl;
    }
    return choices;
}

// Purpose: Simulates the drawing of a random "ticket" with various rarities.
// outputs: An integer representing the ticket. Higher numbers are rarer tickets.
int getTicket(){
    srand(time(NULL));
    int randNum = rand() % 16 + 1;
    if (randNum == 1)
        return 5; //diamond
    else if (randNum == 2)
        return 4; //platinum
    else if (randNum <= 6)
        return 3; //gold
    else if (randNum <= 12)
        return 2; //silver
    else if (randNum <= 16)
        if ((rand() % 4 + 1) == 1)
            return -1; //secret
        return 1; //bronze
    return 0;
}

// Purpose: This function translates a ticket number into a human-readable ticket name.
// inputs: An integer representing the ticket. Higher numbers are rarer tickets.
// ourputs: A string containing the name of the ticket.
string getTicketName(int ticketNum){
    if (ticketNum == 5)
        return "Diamond";
    else if (ticketNum == 4)
        return "Platinum";
    else if (ticketNum == 3)
        return "Gold";
    else if (ticketNum == 2)
        return "Silver";
    else if (ticketNum == 1)
        return "Bronze";
    else
        return "Secret";
}

// Purpose: This function moves or carries a player's 'Mal' based on the 'malSign' value. It can move or carry 1, 2, or 3 'Mal' objects depending on the length of 'malSign'.
// Inputs: Player &player - reference to the player whose 'Mal' will be moved or carried.
//         int playerNum - the player number.
//         string malSign - a string that represents the 'Mal' to be moved or carried. The length of this string determines the number of 'Mal' objects to be moved or carried.
//         int TicketResult - the result of the ticket which determines how far a 'Mal' can move.
//         Map &gameMap - reference to the game map.
//         int pRow, pCol - the row and column of the player's current position.
// Outputs: No return value. However, it modifies the input Player and Map objects by moving the 'Mal' and updating the game map.
void move_or_carry_Mal(Player &player, int playerNum, string malSign, int TicketResult, Map &gameMap, int pRow, int pCol){
    // If 'malSign' length is 2, move one 'Mal'
    if (malSign.length() == 2){
        player.moveMal(stoi(malSign.substr(1,1)), TicketResult);
        gameMap.UpdatePlayerLocation(pRow, pCol, player.getRow(stoi(malSign.substr(1,1))), player.getCol(stoi(malSign.substr(1,1))), playerNum, stoi(malSign.substr(1,1)));
    } 
    // If 'malSign' length is 3, move two 'Mal's
    else if (malSign.length() == 3){
        player.moveMal(stoi(malSign.substr(1,1)), TicketResult);
        gameMap.UpdatePlayerLocation(pRow, pCol, player.getRow(stoi(malSign.substr(1,1))), player.getCol(stoi(malSign.substr(1,1))), playerNum, stoi(malSign.substr(1,1)));

        player.moveMal(stoi(malSign.substr(2,1)), TicketResult);
        gameMap.UpdatePlayerLocation(pRow, pCol, player.getRow(stoi(malSign.substr(2,1))), player.getCol(stoi(malSign.substr(2,1))), playerNum, stoi(malSign.substr(2,1)));
    } 
    // If 'malSign' length is more than 3, move three 'Mal's
    else {
        player.moveMal(stoi(malSign.substr(1,1)), TicketResult);
        gameMap.UpdatePlayerLocation(pRow, pCol, player.getRow(stoi(malSign.substr(1,1))), player.getCol(stoi(malSign.substr(1,1))), playerNum, stoi(malSign.substr(1,1)));

        player.moveMal(stoi(malSign.substr(2,1)), TicketResult);
        gameMap.UpdatePlayerLocation(pRow, pCol, player.getRow(stoi(malSign.substr(2,1))), player.getCol(stoi(malSign.substr(2,1))), playerNum, stoi(malSign.substr(2,1)));

        player.moveMal(stoi(malSign.substr(3,1)), TicketResult);
        gameMap.UpdatePlayerLocation(pRow, pCol, player.getRow(stoi(malSign.substr(3,1))), player.getCol(stoi(malSign.substr(3,1))), playerNum, stoi(malSign.substr(3,1)));
    }
}

// Purpose: Checks if an opponent's mal is present at the given location and, if so, kills the mal(s) and moves them back to the starting position.
// Inputs: Map &gameMap - a reference to the game map object.
//         Player &opponent - a reference to the opponent's Player object.
//         int killerPlayerNum - the number of the player who may kill the mal (0 or 1).
//         int row, int col - the row and column of the location to check for the opponent's mal.
// Outputs: bool - returns true if any opponent mal(s) are killed, false otherwise.
bool killMal(Map &gameMap, Player &opponent, int killerPlayerNum, int row, int col){
    bool killFirst = false;
    bool killSecond = false;
    bool killThird = false;

    if (killerPlayerNum == 0){
        if (gameMap.getPlayerLocation(row, col).Playertwo_first && !opponent.getMal(1).finished && opponent.getMal(1).can_finish){
            killFirst = true;
        }
        if (gameMap.getPlayerLocation(row, col).Playertwo_second && !opponent.getMal(2).finished && opponent.getMal(2).can_finish){
            killSecond = true;
        }
        if (gameMap.getPlayerLocation(row, col).Playertwo_third && !opponent.getMal(3).finished && opponent.getMal(3).can_finish){
            killThird = true;
        }
    } else if (killerPlayerNum == 1){
        if (gameMap.getPlayerLocation(row, col).Playerone_first && !opponent.getMal(1).finished && opponent.getMal(1).can_finish){
            killFirst = true;
        }
        if (gameMap.getPlayerLocation(row, col).Playerone_second && !opponent.getMal(2).finished && opponent.getMal(2).can_finish){
            killSecond = true;
        }
        if (gameMap.getPlayerLocation(row, col).Playerone_third && !opponent.getMal(3).finished && opponent.getMal(3).can_finish){
            killThird = true;
        }
    }

    if (!killFirst && !killSecond && !killThird){
        return false;
    }

    cout << RED << "You killed the opponent's mal number:";

    if (killFirst){
        gameMap.UpdatePlayerLocation(row, col, 6, 0, (killerPlayerNum + 1)%2, 1);
        opponent.setRowCol(1,6,0);
        opponent.set_cannot_finish(1);
        opponent.set_not_Carried(1);
        cout << RED << " 1";
    }
    if (killSecond){
        gameMap.UpdatePlayerLocation(row, col, 6, 0, (killerPlayerNum + 1)%2, 2);
        opponent.setRowCol(2,6,0);
        opponent.set_cannot_finish(2);
        opponent.set_not_Carried(2);
        cout << RED << " 2";
    }
    if (killThird){
        gameMap.UpdatePlayerLocation(row, col, 6, 0, (killerPlayerNum + 1)%2, 3);
        opponent.setRowCol(3,6,0);
        opponent.set_cannot_finish(3);
        opponent.set_not_Carried(3);
        cout << RED << " 3";
    }

    cout << "." << RESET << endl;
    return true;
}

// Purpose: To find and return a string of mals (game pieces) that can be carried by the mal (game piece) whose number is passed in the malSign string. 
// Inputs: Reference to a Player object for whom to find the carried mals. A string 'malSign' which contains the sign of the mal in the first character and the number of the mal as the rest of the string.
// Returns: A string 'malSign' which contains the sign of the mal in the first character and the numbers of the mals that can be carried as the rest of the string.
string carriedMalNums(Player &player, string malSign){
    int malNum = stoi(malSign.substr(1,1));
    for (int i = 1; i <= 3; i++){
        if (player.getMal(malNum).row == player.getMal(i).row &&  player.getMal(malNum).column == player.getMal(i).column && malNum != i && player.getMal(i).can_finish){
            malSign += to_string(i);
        }
    }
    vector<int> malNums;
    for (int i = 1; i< malSign.length(); i++){
        malNums.push_back(stoi(malSign.substr(i,1)));
    }
    sort(malNums.begin(), malNums.end());
    vector<int>::iterator duplicate = unique(malNums.begin(), malNums.end());
    malNums.erase(duplicate, malNums.end());
    string numString;
    for (int i = 0; i < malNums.size(); i++){
        numString += to_string(malNums[i]);
    }
    
    malSign = malSign.substr(0,1) + numString;

    return malSign;
}

// Purpose: Updates the game map to display the specified player's mal at the new position, and removes it from the previous position.
// Inputs: Map &gameMap - a reference to the game map object.
//         Player player - the Player object of the player whose mal is being moved.
//         string malSign - a string representing the mal's unique identifier (e.g., "A1", "A2", "A3").
//         int previRow, int previCol - the previous row and column of the mal's location.
//         int row, int col - the new row and column of the mal's location.
// Outputs: No return value. Display mals on the game graphic Array[3][3]
void moveMalDisplay(Map &gameMap, Player player, string malSign, int previRow, int previCol, int row, int col){
    if (malSign == "A1"){
        string arrA1[3][3] = {
            {"A", "1", "A"},
            {"1", " ", "1"},
            {"A", "1", "A"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA1, false);
    }
    
    if (malSign == "A2"){
        string arrA2[3][3] = {
            {"A", "2", "A"},
            {"2", " ", "2"},
            {"A", "2", "A"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA2, false);
    };
   if (malSign == "A3"){
        string arrA3[3][3] = {
            {"A", "3", "A"},
            {"3", " ", "3"},
            {"A", "3", "A"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA3, false);
    };
   if (malSign == "A12"){
        string arrA12[3][3] = {
            {"A", "1", "2"},
            {"1", " ", "A"},
            {"A", "2", "1"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA12, false);
    };
   if (malSign == "A23"){
        string arrA23[3][3] = {
            {"A", "2", "3"},
            {"2", " ", "A"},
            {"A", "3", "2"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA23, false);
    };

   if (malSign == "A13"){
        string arrA13[3][3] = {
            {"A", "1", "3"},
            {"1", " ", "A"},
            {"A", "3", "1"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA13, false);
    };
   if (malSign == "A123"){
        string arrA123[3][3] = {
            {"A", "1", "2"},
            {"3", " ", "3"},
            {"2", "1", "A"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrA123, false);
    };


   if (malSign == "B1"){
        string arrB1[3][3] = {
            {"B", "1", "B"},
            {"1", " ", "1"},
            {"B", "1", "B"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB1, false);
    };

   if (malSign == "B2"){
        string arrB2[3][3] = {
            {"B", "2", "B"},
            {"2", " ", "2"},
            {"B", "2", "B"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB2, false);
    };
   if (malSign == "B3"){
        string arrB3[3][3] = {
            {"B", "3", "B"},
            {"3", " ", "3"},
            {"B", "3", "B"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB3, false);
    };

   if (malSign == "B12"){
        string arrB12[3][3] = {
            {"B", "1", "2"},
            {"1", " ", "B"},
            {"B", "2", "1"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB12, false);
    };

   if (malSign == "B23"){
        string arrB23[3][3] = {
            {"B", "2", "3"},
            {"2", " ", "B"},
            {"B", "3", "2"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB23, false);
    };

   if (malSign == "B13"){
        string arrB13[3][3] = {
            {"B", "1", "3"},
            {"1", " ", "B"},
            {"B", "3", "1"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB13, false);
    };

   if (malSign == "B123"){
        string arrB123[3][3] = {
            {"B", "1", "2"},
            {"3", " ", "3"},
            {"2", "1", "B"}
            };
        gameMap.moveMal(previRow, previCol, row, col, arrB123, false);
    };


}


// Purpose: Add mal display when loading the game
// Inputs: Map &gameMap - a reference to the game map object.
//         Player player1 - the Player object of player1 in the main
//         Player player2 - the Player object of player2 in the main
// Outputs: No return value. Add mal display to gameMap
void addMalDisplay(Map &gameMap, Player player1, Player player2){
    string arrA1[3][3] = {
        {"A", "1", "A"},
        {"1", " ", "1"},
        {"A", "1", "A"}
        };
    string arrA2[3][3] = {
        {"A", "2", "A"},
        {"2", " ", "2"},
        {"A", "2", "A"}
        };
    string arrA3[3][3] = {
        {"A", "3", "A"},
        {"3", " ", "3"},
        {"A", "3", "A"}
        };
    string arrA12[3][3] = {
        {"A", "1", "2"},
        {"1", " ", "A"},
        {"A", "2", "1"}
        };
    string arrA23[3][3] = {
        {"A", "2", "3"},
        {"2", " ", "A"},
        {"A", "3", "2"}
        };
    string arrA13[3][3] = {
        {"A", "1", "3"},
        {"1", " ", "A"},
        {"A", "3", "1"}
        };
    string arrA123[3][3] = {
        {"A", "1", "2"},
        {"3", " ", "3"},
        {"2", "1", "A"}
        };
    string arrB1[3][3] = {
        {"B", "1", "B"},
        {"1", " ", "1"},
        {"B", "1", "B"}
        };
    string arrB2[3][3] = {
        {"B", "2", "B"},
        {"2", " ", "2"},
        {"B", "2", "B"}
        };
    string arrB3[3][3] = {
        {"B", "3", "B"},
        {"3", " ", "3"},
        {"B", "3", "B"}
        };
    string arrB12[3][3] = {
        {"B", "1", "2"},
        {"1", " ", "B"},
        {"B", "2", "1"}
        };
    string arrB23[3][3] = {
        {"B", "2", "3"},
        {"2", " ", "B"},
        {"B", "3", "2"}
        };
    string arrB13[3][3] = {
        {"B", "1", "3"},
        {"1", " ", "B"},
        {"B", "3", "1"}
        };
    string arrB123[3][3] = {
        {"B", "1", "2"},
        {"3", " ", "3"},
        {"2", "1", "B"}
        };
    map<string, string[3][3]> malSign_to_malDisplay;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["A1"][i][j] = arrA1[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["A2"][i][j] = arrA2[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["A3"][i][j] = arrA3[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["A12"][i][j] = arrA12[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["A23"][i][j] = arrA23[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["A123"][i][j] = arrA123[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["B1"][i][j] = arrB1[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["B2"][i][j] = arrB2[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["B3"][i][j] = arrB3[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["B12"][i][j] = arrB12[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["B23"][i][j] = arrB23[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            malSign_to_malDisplay["B123"][i][j] = arrB123[i][j];
        }
    }

    if (player1.getMal(1).can_finish && !player1.getMal(1).finished){
        gameMap.addMal(player1.getRow(1), player1.getCol(1), malSign_to_malDisplay[carriedMalNums(player1, "A1")]);
    } 
    if (player1.getMal(2).can_finish && !player1.getMal(2).finished){
        gameMap.addMal(player1.getRow(2), player1.getCol(2), malSign_to_malDisplay[carriedMalNums(player1, "A2")]);
    } 
    if (player1.getMal(3).can_finish && !player1.getMal(3).finished) {
        gameMap.addMal(player1.getRow(3), player1.getCol(3), malSign_to_malDisplay[carriedMalNums(player1, "A3")]);
    }

    if (player2.getMal(1).can_finish && !player2.getMal(1).finished){
        gameMap.addMal(player2.getRow(1), player2.getCol(1), malSign_to_malDisplay[carriedMalNums(player2, "B1")]);
    } 
    if (player2.getMal(2).can_finish && !player2.getMal(2).finished){
        gameMap.addMal(player2.getRow(2), player2.getCol(2), malSign_to_malDisplay[carriedMalNums(player2, "B2")]);
    } 
    if (player2.getMal(3).can_finish && !player2.getMal(3).finished) {
        gameMap.addMal(player2.getRow(3), player2.getCol(3), malSign_to_malDisplay[carriedMalNums(player2, "B3")]);
    }

}

// Purpose: to display the ticket players recieve
// Inputs: number of moves avaliable for the player
// Outputs: No return value. Ticket display how many numbers of moves are avaliable
void displayTicket(int moves){
    if (moves == 4)
    {
        cout << CYAN << "   _________ _________ _________ _________ _________ _________ _________ _________" << RESET << "\n";
        cout << CYAN << "  /         |         |         |         |         |         |         |         |" << RESET << "\n";
        cout << CYAN << " /    P    /    L    /    A    /    T    /    I    /    N    /    U    /    M    /" << RESET << "\n";
        cout << CYAN << "/_________/_________/_________/_________/_________/_________/_________/_________/" << RESET << "\n";
        cout << CYAN << "┌─────────┐\n";
        cout << CYAN << "│ x     x │\n";
        cout << CYAN << "│         │\n";
        cout << CYAN << "│         │\n";
        cout << CYAN << "│         │\n";
        cout << CYAN << "│ x     x │\n";
        cout << CYAN << "└─────────┘\n\n";
        cout << endl;
    }
    
    else if (moves == 3)
    {
        cout << YELLOW << "   _________ _________ _________ _________ " << RESET << "\n";
        cout << YELLOW << "  /         |         |         |        |" << RESET << "\n";
        cout << YELLOW << " /    G    /    O    /    L    /    D    /" << RESET << "\n";
        cout << YELLOW << "/_________/_________/_________/_________/" << RESET << "\n";
        cout << YELLOW << "┌─────────┐\n";
        cout << YELLOW << "│ x       │\n";
        cout << YELLOW << "│         │\n";
        cout << YELLOW << "│    x    │\n";
        cout << YELLOW << "│         │\n";
        cout << YELLOW << "│       x │\n";
        cout << YELLOW << "└─────────┘\n\n";
    }
    else if (moves == 2)
    {
        cout << GRAY << "   _________ _________ _________ _________ _________ _________ " << RESET << "\n";
        cout << GRAY << "  /         |         |         |         |         |        |" << RESET << "\n";
        cout << GRAY << " /    S    /    I    /    L    /    V    /    E    /    R    /" << RESET << "\n";
        cout << GRAY << "/_________/_________/_________/_________/_________/_________/" << RESET << "\n";
        cout << GRAY << "┌─────────┐\n";
        cout << GRAY << "│ x       │\n";
        cout << GRAY << "│         │\n";
        cout << GRAY << "│         │\n";
        cout << GRAY << "│         │\n";
        cout << GRAY << "│       x │\n";
        cout << GRAY << "└─────────┘\n\n";
    }
    else if (moves == 1)
    {
        cout << BROWN << "   _________ _________ _________ _________ _________ _________" << RESET << "\n";
        cout << BROWN << "  /         |         |         |         |         |        |" << RESET << "\n";
        cout << BROWN << " /    B    /    R    /    O    /    N    /    Z    /    E    /" << RESET << "\n";
        cout << BROWN << "/_________/_________/_________/_________/_________/_________/" << RESET << "\n";
        cout << BROWN << "┌─────────┐\n";
        cout << BROWN << "│         │\n";
        cout << BROWN << "│         │\n";
        cout << BROWN << "│    x    │\n";
        cout << BROWN << "│         │\n";
        cout << BROWN << "│         │\n";
        cout << BROWN << "└─────────┘\n\n";
    }
    else if (moves == 5)
    {
        cout << BLUE << "   _________ _________ _________ _________ _________ _________ _________" << RESET << "\n";
        cout << BLUE << "  /         |         |         |         |         |        |         |" << RESET << "\n";
        cout << BLUE << " /    D    /    I    /    A    /    M    /    O    /    N    /    D    /" << RESET << "\n";
        cout << BLUE << "/_________/_________/_________/_________/_________/_________/_________/" << RESET << "\n";
        cout << BLUE << "┌─────────┐\n";
        cout << BLUE << "│ x     x │\n";
        cout << BLUE << "│         │\n";
        cout << BLUE << "│    x    │\n";
        cout << BLUE << "│         │\n";
        cout << BLUE << "│ x     x │\n";
        cout << BLUE << "└─────────┘\n\n";
    }
    else if (moves == -1)
    {
        cout << MAGENTA << "   _________ _________ _________ _________ _________ _________" << RESET << "\n";
        cout << MAGENTA << "  /         |         |         |         |         |         |" << RESET << "\n";
        cout << MAGENTA << " /    S    /    E    /    C    /    R    /    E    /    T    /" << RESET << "\n";
        cout << MAGENTA << "/_________/_________/_________/_________/_________/_________/" << RESET << "\n";
        cout << MAGENTA <<  "┌─────────┐\n";
        cout << MAGENTA <<  "│ ?     ? │\n";
        cout << MAGENTA <<  "│         │\n";
        cout << MAGENTA <<  "│    ?    │\n";
        cout << MAGENTA <<  "│         │\n";
        cout << MAGENTA <<  "│ ?     ? │\n";
        cout << MAGENTA <<  "└─────────┘\n\n";
    }

    cout << RESET << endl;
}

// Purpose: This function is used to print an explanation message based on the current position of the player on the game map.
// Inputs: row is an integer representing the row number of the player's current position, and col is an integer representing the column number of the player's current position.
// Outputs: This function does not return a value, but it prints a message to the console explaining the significance of the player's current position on the game map.
void PrintExplain(int row, int col){
    if (row == 0 && col == 0)
    {
        cout << "You have arrived at Kowloon. There is a Kowloon Park, which is large park with gardens, lakes, and a swimming pool." << endl;
    }
    else if (row == 0 && col == 1)
    {
        cout << "You have arrived at Symphony of Lights. It is a light and sound show that illuminates the skyline every night." << endl;
    }
    else if (row == 0 && col == 2)
    {
        cout << "You have arrived at Mong Kok. It is a bustling neighborhood with markets, street food, and nightlife." << endl;
    }
    else if (row == 0 && col == 4)
    {
        cout << "You have arrived at Ladies' Market. It is a street market in Mong Kok that sells clothes, accessories, and souvenirs." << endl;
    }
    else if (row == 0 && col == 5)
    {
        cout << "You have arrived at Soho. It is a neighborhood in Central with trendy bars and restaurants." << endl;
    }
    else if (row == 0 && col == 6)
    {
        cout << "You have arrived at North Point. It is a densely populated area that is known for its vibrant local atmosphere, with a mix of residential, commercial, and industrial spaces." << endl;
    }
    else if (row == 1 && col == 0)
    {
        cout << "You have arrived at Hong Kong Science Museum. It is a museum with interactive exhibits on science and technology." << endl;
    }
    else if (row == 1 && col == 1)
    {
        cout << "You have arrived at Wong Tai Sin Temple. It is a Taoist temple in Kowloon that is known for granting wishes." << endl;
    }
    else if (row == 1 && col == 5)
    {
        cout << "You have arrived at Temple Street Night Market. It is a bustling night market in Yau Ma Tei that sells a variety of goods." << endl;
    }
    else if (row == 1 && col == 6)
    {
        cout << "You have arrived at Golden Computer Arcade. It is a shopping center in Sham Shui Po that sells electronics and computer components." << endl;
    }
    else if (row == 2 && col == 0)
    {
        cout << "You have arrived at Hong Kong Museum of History. It is a museum that traces the history of Hong Kong." << endl;
    }
    else if (row == 2 && col == 2)
    {
        cout << "You have arrived at Elements Mall. It is a shopping mall in Kowloon with luxury brands and fine dining restaurants." << endl;
    }
    else if (row == 2 && col == 4)
    {
        cout << "You have arrived at Tsim Sha Tsui Promenade. It is a waterfront promenade with stunning views of the harbor." << endl;
    }
    else if (row == 2 && col == 6)
    {
        cout << "You have arrived at Langham Place. It is a shopping mall in Mong Kok with a variety of stores and a cinema." << endl;
    }
    else if (row == 3 && col == 3)
    {
        cout << "You have arrived at Tsim Sa Tsui. It is a popular tourist and shopping district located in the southern part of Kowloon Peninsula in Hong Kong." << endl;
    }
    else if (row == 4 && col == 0)
    {
        cout << "You have arrived at Hong Kong Museum of Art. It is a museum showcasing Chinese art and culture." << endl;
    }
    else if (row == 4 && col == 2)
    {
        cout << "You have arrived at The Clock Tower. It is a historic landmark in Tsim Sha Tsui." << endl;
    }
    else if (row == 4 && col == 4)
    {
        cout << "You have arrived at Lan Kwai Fong. It is a nightlife district in Central known for its bars and clubs." << endl;
    }
    else if (row == 4 && col == 6)
    {
        cout << "You have arrived at Avenue of Stars. It is a promenade dedicated to Hong Kong's film industry." << endl;
    }
    else if (row == 5 && col == 0)
    {
        cout << "You have arrived at Repulse Bay. It is a beach with stunning views and plenty of water sports activities." << endl;
    }
    else if (row == 5 && col == 1)
    {
        cout << "You have arrived at Victoria Peak. It is a popular tourist destination with a spectacular view of Hong Kong's skyline." << endl;
    }
    else if (row == 5 && col == 5)
    {
        cout << "You have arrived at Tai Kwun. It is a heritage site that houses art galleries, restaurants, and shops." << endl;
    }
    else if (row == 5 && col == 6)
    {
        cout << "You have arrived at Tai O. It is a fishing village on Lantau Island with traditional stilt houses and a peaceful atmosphere" << endl;
    }
    else if (row == 6 && col == 0)
    {
        cout << "You have arrived at HKU. Located on Hong Kong Island, HKU has a beautiful campus that features a blend of modern and historic buildings, as well as green spaces and cultural landmarks." << endl;
    }
    else if (row == 6 && col == 1)
    {
        cout << "You have arrived at Hong Kong Disneyland. It is a theme park with attractions for all ages." << endl;
    }
    else if (row == 6 && col == 2)
    {
        cout << "You have arrived at Ocean Park. It is a marine-life theme park with thrilling rides and animal exhibits." << endl;
    }
    else if (row == 6 && col == 4)
    {
        cout << "You have arrived at Man Mo Temple. It is a historic temple in Sheung Wan dedicated to the gods of literature and martial arts." << endl;
    }
    else if (row == 6 && col == 5)
    {
        cout << "You have arrived at Western Market. It is a restored Edwardian-style building with shops selling souvenirs and handicrafts." << endl;
    }
    else if (row == 6 && col == 6)
    {
        cout << "You have arrived at Admiralty. It is a major commercial and financial hub in Hong Kong, and is home to many important government buildings, including the Central Government Complex and the Legislative Council Complex." << endl;
    }
}
