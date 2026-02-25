
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
#include <array>
#include <unordered_map>
#include <random>
#include <cctype>
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

namespace {

bool TryParsePositiveInt(const std::string &s, int &out) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!std::isdigit(static_cast<unsigned char>(ch))) return false;
    }
    try {
        out = std::stoi(s);
    } catch (...) {
        return false;
    }
    return out > 0;
}

using Pattern = std::array<std::array<const char *, 3>, 3>;

const std::unordered_map<std::string, Pattern> &MalPatterns() {
    static const std::unordered_map<std::string, Pattern> k = {

        {"A1",   {{{"A","1","A"},{"1"," ","1"},{"A","1","A"}}}},
        {"A2",   {{{"A","2","A"},{"2"," ","2"},{"A","2","A"}}}},
        {"A3",   {{{"A","3","A"},{"3"," ","3"},{"A","3","A"}}}},
        {"A12",  {{{"A","1","2"},{"1"," ","A"},{"A","2","1"}}}},
        {"A13",  {{{"A","1","3"},{"1"," ","A"},{"A","3","1"}}}},
        {"A23",  {{{"A","2","3"},{"2"," ","A"},{"A","3","2"}}}},
        {"A123", {{{"A","1","2"},{"3"," ","3"},{"2","1","A"}}}},

        {"B1",   {{{"B","1","B"},{"1"," ","1"},{"B","1","B"}}}},
        {"B2",   {{{"B","2","B"},{"2"," ","2"},{"B","2","B"}}}},
        {"B3",   {{{"B","3","B"},{"3"," ","3"},{"B","3","B"}}}},
        {"B12",  {{{"B","1","2"},{"1"," ","B"},{"B","2","1"}}}},
        {"B13",  {{{"B","1","3"},{"1"," ","B"},{"B","3","1"}}}},
        {"B23",  {{{"B","2","3"},{"2"," ","B"},{"B","3","2"}}}},
        {"B123", {{{"B","1","2"},{"3"," ","3"},{"2","1","B"}}}},
    };
    return k;
}

bool FillMalPattern(const std::string &malSign, std::string out[3][3]) {
    auto it = MalPatterns().find(malSign);
    if (it == MalPatterns().end()) return false;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            out[i][j] = it->second[i][j];
        }
    }
    return true;
}

}

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

void typingEffect(string outputText){
    cout << "\033[1m";
    for (int i = 0; i < outputText.length(); i++) {
        char c = outputText[i];
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(20));
    }
    cout << "\033[0m";
}

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

void save_game(string filename, Map gameMap, Player player1, Player player2) {
    ofstream outFile;
    outFile.open((filename + ".txt").c_str());

    if (outFile.fail()) {
        cout << "Error opening file for saving game state." << endl;
        return;
    }

    outFile << player1.getName() << endl;
    outFile << player2.getName() << endl;

    for (int i = 1; i <= 3; i++) {
        outFile << i << endl;
        outFile << player1.getMal(i).row << endl;
        outFile << player1.getMal(i).column << endl;
        outFile << player1.getMal(i).can_finish << endl;
        outFile << player1.getMal(i).finished << endl;
        outFile << player1.getMal(i).carried << endl;
    }

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

}

void load_game(string filename, Map &gameMap, Player &player1, Player &player2, int &loadfailed) {
    ifstream inFile((filename + ".txt").c_str());

    if (inFile.fail()) {
        cout << "Invalid input or Error in opening file." << endl;
        loadfailed = 1;
        return;
    }

    string player1Name, player2Name;
    getline(inFile, player1Name);
    getline(inFile, player2Name);

    if (player1Name.empty() && !inFile.eof()) getline(inFile, player1Name);
    if (player2Name.empty() && !inFile.eof()) getline(inFile, player2Name);

    if (player1Name.empty() || player2Name.empty()) {
        cout << "Save file is corrupted (missing player names)." << endl;
        loadfailed = 1;
        return;
    }

    player1.setName(player1Name);
    player2.setName(player2Name);

    int malNum = 0, row = 0, column = 0;
    int can_finish_int = 0, finished_int = 0, carried_int = 0;

    for (int i = 1; i <= 3; i++) {
        if (!(inFile >> malNum >> row >> column >> can_finish_int >> finished_int >> carried_int)) {
            cout << "Save file is corrupted (player 1 mal data)." << endl;
            loadfailed = 1;
            return;
        }

        player1.setMal(
            malNum,
            row,
            column,
            static_cast<bool>(can_finish_int),
            static_cast<bool>(finished_int),
            static_cast<bool>(carried_int)
        );
    }

    for (int i = 1; i <= 3; i++) {
        if (!(inFile >> malNum >> row >> column >> can_finish_int >> finished_int >> carried_int)) {
            cout << "Save file is corrupted (player 2 mal data)." << endl;
            loadfailed = 1;
            return;
        }

        player2.setMal(
            malNum,
            row,
            column,
            static_cast<bool>(can_finish_int),
            static_cast<bool>(finished_int),
            static_cast<bool>(carried_int)
        );
    }

    for (int i = 1; i <= 3; i++){
        Mal m = player1.getMal(i);
        if (m.can_finish && !m.finished) {
            gameMap.addPlayerLocation(m.row, m.column, 0, i);
        }
    }

    for (int i = 1; i <= 3; i++){
        Mal m = player2.getMal(i);
        if (m.can_finish && !m.finished) {
            gameMap.addPlayerLocation(m.row, m.column, 1, i);
        }
    }

    inFile.close();
    cout << "Game loaded successfully." << endl;
}

int askWhichTicket(vector<int> &tickets){
    if (tickets.empty()) {
        cout << "No tickets available." << endl;
        return 0;
    }

    if (tickets.size() == 1){
        cout << "You got " << getTicketName(tickets[0]) << " ticket." << endl;
        int ticket = tickets[0];
        tickets.clear();
        return ticket;
    }

    cout << "\nYou got " << tickets.size() << " moves.\n";
    for (size_t i = 0; i < tickets.size(); i++){
        cout << (i + 1) << ". " << getTicketName(tickets[i]) << "     ";
    }
    cout << "\nPlease choose the Ticket you want to use: ";

    while (true) {
        string inputStr;
        if (!(cin >> inputStr)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please input a proper number for ticket use: ";
            continue;
        }

        int choice = 0;
        if (!TryParsePositiveInt(inputStr, choice)) {
            cout << "Invalid input. Input must be a positive integer: ";
            continue;
        }
        if (choice < 1 || static_cast<size_t>(choice) > tickets.size()) {
            cout << "Invalid input. Please input a number between 1 and " << tickets.size() << ": ";
            continue;
        }

        int ticket = tickets[choice - 1];
        tickets.erase(tickets.begin() + (choice - 1));
        return ticket;
    }
}

vector<string> askMalMovement(int turn, Player one, Player two){
    vector<string> choices;

    Player &current = (turn == 0) ? one : two;
    const char prefix = (turn == 0) ? 'A' : 'B';

    bool used[4] = {false, false, false, false};

    for (int i = 1; i <= 3; ++i) {
        if (used[i]) continue;

        Mal mi = current.getMal(i);
        if (mi.finished) continue;

        vector<int> group;
        group.push_back(i);
        used[i] = true;

        if (mi.can_finish) {
            for (int j = i + 1; j <= 3; ++j) {
                if (used[j]) continue;
                Mal mj = current.getMal(j);
                if (mj.finished) continue;

                if (mj.can_finish && mj.row == mi.row && mj.column == mi.column) {
                    group.push_back(j);
                    used[j] = true;
                }
            }
        }

        sort(group.begin(), group.end());

        string sign;
        sign.push_back(prefix);
        for (int n : group) sign += to_string(n);

        choices.push_back(sign);
    }

    cout << "Which mal would you like to move?      ";
    for (size_t i = 0; i < choices.size(); ++i) {
        cout << (i + 1) << ". " << choices[i];
        if (i + 1 < choices.size()) cout << "      ";
    }
    cout << endl;

    return choices;
}

int getTicket(){

    static std::mt19937 rng(static_cast<unsigned>(
        chrono::high_resolution_clock::now().time_since_epoch().count()
    ));
    uniform_int_distribution<int> dist16(1, 16);
    int randNum = dist16(rng);

    if (randNum == 1) return 5;
    if (randNum == 2) return 4;
    if (randNum <= 6) return 3;
    if (randNum <= 12) return 2;

    uniform_int_distribution<int> dist4(1, 4);
    return (dist4(rng) == 1) ? -1 : 1;
}

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

void move_or_carry_Mal(Player &player, int playerNum, string malSign, int TicketResult, Map &gameMap, int pRow, int pCol){
    if (malSign.size() < 2) return;

    for (size_t i = 1; i < malSign.size(); ++i) {
        char ch = malSign[i];
        if (!isdigit(static_cast<unsigned char>(ch))) continue;

        int malNum = ch - '0';
        player.moveMal(malNum, TicketResult);

        gameMap.UpdatePlayerLocation(
            pRow, pCol,
            player.getRow(malNum), player.getCol(malNum),
            playerNum, malNum
        );
    }
}

bool killMal(Map &gameMap, Player &opponent, int killerPlayerNum, int row, int col){
    Station st = gameMap.getPlayerLocation(row, col);

    auto opponentHere = [&](int malNum) -> bool {
        if (killerPlayerNum == 0) {
            if (malNum == 1) return st.Playertwo_first;
            if (malNum == 2) return st.Playertwo_second;
            return st.Playertwo_third;
        } else {
            if (malNum == 1) return st.Playerone_first;
            if (malNum == 2) return st.Playerone_second;
            return st.Playerone_third;
        }
    };

    vector<int> killed;
    for (int malNum = 1; malNum <= 3; ++malNum) {
        Mal m = opponent.getMal(malNum);
        if (opponentHere(malNum) && !m.finished && m.can_finish) {
            killed.push_back(malNum);
        }
    }

    if (killed.empty()) return false;

    cout << RED << "You killed the opponent's mal number:";
    const int opponentPlayerNum = (killerPlayerNum + 1) % 2;

    for (int malNum : killed) {
        gameMap.UpdatePlayerLocation(row, col, 6, 0, opponentPlayerNum, malNum);
        opponent.setRowCol(malNum, 6, 0);
        opponent.set_cannot_finish(malNum);
        opponent.set_not_Carried(malNum);
        cout << RED << " " << malNum;
    }

    cout << "." << RESET << endl;
    return true;
}

string carriedMalNums(Player &player, string malSign){
    if (malSign.size() < 2) return malSign;

    int malNum = 0;
    try {
        malNum = stoi(malSign.substr(1, 1));
    } catch (...) {
        return malSign;
    }

    Mal base = player.getMal(malNum);

    vector<int> group;
    group.push_back(malNum);

    if (base.can_finish && !base.finished) {
        for (int i = 1; i <= 3; ++i) {
            if (i == malNum) continue;
            Mal other = player.getMal(i);
            if (!other.can_finish || other.finished) continue;

            if (other.row == base.row && other.column == base.column) {
                group.push_back(i);
            }
        }
    }

    sort(group.begin(), group.end());
    group.erase(unique(group.begin(), group.end()), group.end());

    string out;
    out.push_back(malSign[0]);
    for (int n : group) out += to_string(n);
    return out;
}

void moveMalDisplay(Map &gameMap, Player player, string malSign, int previRow, int previCol, int row, int col){
    (void)player;

    string pattern[3][3];
    if (!FillMalPattern(malSign, pattern)) {

        return;
    }

    gameMap.moveMal(previRow, previCol, row, col, pattern, false);
}

void addMalDisplay(Map &gameMap, Player player1, Player player2){
    auto addForPlayer = [&](Player &p, char prefix) {
        bool used[4] = {false, false, false, false};

        for (int i = 1; i <= 3; ++i) {
            if (used[i]) continue;

            Mal mi = p.getMal(i);
            if (!mi.can_finish || mi.finished) continue;

            vector<int> group;
            group.push_back(i);
            used[i] = true;

            for (int j = i + 1; j <= 3; ++j) {
                if (used[j]) continue;
                Mal mj = p.getMal(j);
                if (!mj.can_finish || mj.finished) continue;

                if (mj.row == mi.row && mj.column == mi.column) {
                    group.push_back(j);
                    used[j] = true;
                }
            }

            sort(group.begin(), group.end());

            string sign;
            sign.push_back(prefix);
            for (int n : group) sign += to_string(n);

            string pattern[3][3];
            if (FillMalPattern(sign, pattern)) {
                gameMap.addMal(mi.row, mi.column, pattern);
            }
        }
    };

    addForPlayer(player1, 'A');
    addForPlayer(player2, 'B');
}

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

