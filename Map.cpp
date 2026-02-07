#include <iostream>
#include <string>
#include <map>
#include <utility> 
#include "Map.h"
#include "Station.h"
#include "MapChartDisplay.h"
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
using namespace std;

// Purpose: Initializes the Map class, setting player locations and copying an external map.
// Input: None. Uses predefined mapPlayerLocation and external_map arrays.
// Output: No return value. Modifies class state.
Map::Map() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            mapPlayerLocation[i][j].Playerone_first = false;
            mapPlayerLocation[i][j].Playerone_second = false;
            mapPlayerLocation[i][j].Playerone_third = false;
            mapPlayerLocation[i][j].Playertwo_first = false;
            mapPlayerLocation[i][j].Playertwo_second = false;
            mapPlayerLocation[i][j].Playertwo_third = false;
        }
    }
    mapPlayerLocation[6][0].Playerone_first = true;
    mapPlayerLocation[6][0].Playerone_second = true;
    mapPlayerLocation[6][0].Playerone_third = true;
    mapPlayerLocation[6][0].Playertwo_first = true;
    mapPlayerLocation[6][0].Playertwo_second = true;
    mapPlayerLocation[6][0].Playertwo_third = true;

    for (int i = 0; i < 60; i++){
        for (int j = 0; j< 77; j++){
            mapChart[i][j] = external_map[i][j];
        }
    }
}
// Constructor with parameter: initializes the map with provided player locations
// Input: a 7x7 array of Station objects representing the player's locations
// Output: No return value. Modifies class state.
Map::Map(Station mapPlayerLocation[7][7]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            this->mapPlayerLocation[i][j] = mapPlayerLocation[i][j];
        }
    }
}

// Returns the Station object at the specified row and column in the map
// Input: row and column of the desired Station object
// Output: the Station object at the specified row and column
Station Map::getPlayerLocation(int row, int col){
    return mapPlayerLocation[row][col];
}
// Converts a map player location to its corresponding station name
// Input: row and column of the player location
// Output: the corresponding station name as a string
string Map::mapPlayerLocation_to_station(int row, int col){
    typedef pair<int, int> rowCol;
    map< rowCol, string > rowColMatch;
    rowColMatch.insert(make_pair(make_pair(6, 0), "HKU"));
    rowColMatch.insert(make_pair(make_pair(6, 1), "Disneyland"));
    rowColMatch.insert(make_pair(make_pair(6, 2), "Ocean Park"));
    rowColMatch.insert(make_pair(make_pair(6, 4), "Man Mo"));
    rowColMatch.insert(make_pair(make_pair(6, 5), "Western Market"));
    rowColMatch.insert(make_pair(make_pair(6, 6), "Admiralty"));
    rowColMatch.insert(make_pair(make_pair(5, 0), "Repulse Bay"));
    rowColMatch.insert(make_pair(make_pair(5, 1), "Victoria Peak"));
    rowColMatch.insert(make_pair(make_pair(5, 5), "Tai Kwun"));
    rowColMatch.insert(make_pair(make_pair(5, 6), "Tai O"));
    rowColMatch.insert(make_pair(make_pair(4, 0), "HKMOA"));
    rowColMatch.insert(make_pair(make_pair(4, 2), "Clock Tower"));
    rowColMatch.insert(make_pair(make_pair(4, 4), "Lan Kwai Fong"));
    rowColMatch.insert(make_pair(make_pair(4, 6), "Avenue of Stars"));
    rowColMatch.insert(make_pair(make_pair(3, 3), "Tsim Sha Tsui"));
    rowColMatch.insert(make_pair(make_pair(2, 0), "HKMOH"));
    rowColMatch.insert(make_pair(make_pair(2, 2), "Elements Mall"));
    rowColMatch.insert(make_pair(make_pair(2, 4), "Promenade"));
    rowColMatch.insert(make_pair(make_pair(2, 6), "Lagham Place"));
    rowColMatch.insert(make_pair(make_pair(1, 0), "HKSM"));
    rowColMatch.insert(make_pair(make_pair(1, 1), "Wong Tai Sin"));
    rowColMatch.insert(make_pair(make_pair(1, 5), "Night Market"));
    rowColMatch.insert(make_pair(make_pair(1, 6), "Golden Computer Arcade"));
    rowColMatch.insert(make_pair(make_pair(0, 0), "Kowloon"));
    rowColMatch.insert(make_pair(make_pair(0, 1), "Sympony of Lights"));
    rowColMatch.insert(make_pair(make_pair(0, 2), "Mong Kok"));
    rowColMatch.insert(make_pair(make_pair(0, 4), "Ladies' Market"));
    rowColMatch.insert(make_pair(make_pair(0, 5), "Soho"));
    rowColMatch.insert(make_pair(make_pair(0, 6), "North Point"));

    return rowColMatch[make_pair(row, col)];

}

// Converts a map player location to its corresponding map chart location
// Input: row and column of the player location
// Output: a pair of integers representing the corresponding map chart location
pair<int, int> Map::mapPlayerLocation_to_mapChart(int row, int col){
    typedef pair<int, int> rowCol;
    typedef pair<int, int> resultRowCol;
    map< rowCol, resultRowCol > rowColMatch;
    rowColMatch.insert(make_pair(make_pair(6,0), make_pair(54,2))); //HKU
    rowColMatch.insert(make_pair(make_pair(6,1), make_pair(54,16))); //Disneyland
    rowColMatch.insert(make_pair(make_pair(6,2), make_pair(54,30))); //Ocean Park
    rowColMatch.insert(make_pair(make_pair(6,4), make_pair(54,44))); //Man Mo
    rowColMatch.insert(make_pair(make_pair(6,5), make_pair(54,58))); //Western Market
    rowColMatch.insert(make_pair(make_pair(6,6), make_pair(54,72))); //Admiralty
    rowColMatch.insert(make_pair(make_pair(5,0), make_pair(44,2))); //Repulse Bay
    rowColMatch.insert(make_pair(make_pair(5,1), make_pair(46,14))); //Victoria Park
    rowColMatch.insert(make_pair(make_pair(5,5), make_pair(46,60))); //Tai Kwun
    rowColMatch.insert(make_pair(make_pair(5,6), make_pair(44,72))); //Tai O
    rowColMatch.insert(make_pair(make_pair(4,0), make_pair(33,2))); //HKMOA
    rowColMatch.insert(make_pair(make_pair(4,2), make_pair(37,26))); //Clock Tower
    rowColMatch.insert(make_pair(make_pair(4,4), make_pair(37,48))); //Lan Kwai Fong
    rowColMatch.insert(make_pair(make_pair(4,6), make_pair(33,72))); //Avenue of Stars
    rowColMatch.insert(make_pair(make_pair(3,3), make_pair(28,37))); //Tsim Sha Tsui
    rowColMatch.insert(make_pair(make_pair(2,0), make_pair(23,2))); //HKMOH
    rowColMatch.insert(make_pair(make_pair(2,2), make_pair(19,26))); //Elements Mall
    rowColMatch.insert(make_pair(make_pair(2,4), make_pair(19,48))); //Promenade
    rowColMatch.insert(make_pair(make_pair(2,6), make_pair(23,72))); //Lagham Place
    rowColMatch.insert(make_pair(make_pair(1,0), make_pair(12,2))); //HKSM
    rowColMatch.insert(make_pair(make_pair(1,1), make_pair(10,14))); //Wong Tai Sin
    rowColMatch.insert(make_pair(make_pair(1,5), make_pair(10,60))); //Night Market
    rowColMatch.insert(make_pair(make_pair(1,6), make_pair(12,72))); //Golden Computer Arcade
    rowColMatch.insert(make_pair(make_pair(0,0), make_pair(2,2))); //Kowloon
    rowColMatch.insert(make_pair(make_pair(0,1), make_pair(2,16))); //Sympony
    rowColMatch.insert(make_pair(make_pair(0,2), make_pair(2,30))); //Mong Kok
    rowColMatch.insert(make_pair(make_pair(0,4), make_pair(2,44))); //Ladies' Market
    rowColMatch.insert(make_pair(make_pair(0,5), make_pair(2,58))); //Soho
    rowColMatch.insert(make_pair(make_pair(0,6), make_pair(2,72))); //North Point

    return rowColMatch[make_pair(row,col)];
}

// Removes a mal token from the specified row and column in the map chart
// Input: row and column where the mal token should be removed
// Outputs: This function does not return any value (void). It modifies the mapChart 2D array by removing the 'mal' from the specified 3x3 area.
void Map::removeMal(int row, int col, bool finish){
    pair<int, int> rowCol = mapPlayerLocation_to_mapChart(row,col);

    if ( row == 6 && col == 0 && !finish){
        return;
    }

    for (int i = rowCol.first; i < rowCol.first+3; i++){
        for (int j = rowCol.second; j < rowCol.second+3; j++){
            mapChart[i][j] = " ";
        }
    }
}

// Adds a mal token to the specified row and column in the map chart
// Input: row and column where the mal token should be added, and a 3x3 string array representing the mal token
// Outputs: This function does not return any value (void). It modifies the mapChart 2D array by adding the 'mal' to the specified 3x3 area.
void Map::addMal(int row, int col, string mal[3][3]){
    pair<int, int> rowCol = mapPlayerLocation_to_mapChart(row,col);

    for (int i = rowCol.first; i < rowCol.first+3; i++){
        for (int j = rowCol.second; j < rowCol.second+3; j++){
            mapChart[i][j] = mal[i-rowCol.first][j-rowCol.second];
        }
    }
}
// Moves a mal token from a previous location to a new location in the map chart
// Input: previous row and column, new row and column, and a 3x3 string array representing the mal token
// Output: This function does not return any value (void). It modifies the mapChart 2D array by moving the 'mal' from its previous location to the new specified location.
void Map::moveMal(int previRow, int previCol, int row, int col, string mal[3][3], bool finish) {
    removeMal(previRow, previCol, finish);
    addMal(row, col, mal);
}

// Removes a player's mal token from the specified location in the mapPlayerLocation array
// Input: row and column where the mal token should be removed, player number (0 or 1), and mal number (1, 2, or 3)
// Output: This function does not return any value (void). It modifies the mapPlayerLocation 2D array by removing the specified player's location information at the given row and column.
void Map::removePlayerLocation(int row, int col, int playerNum){
    if (playerNum == 0){
        mapPlayerLocation[row][col].Playerone_first = false;
        mapPlayerLocation[row][col].Playerone_second = false;
        mapPlayerLocation[row][col].Playerone_third = false;
    } else if (playerNum == 1){
        mapPlayerLocation[row][col].Playertwo_first = false;
        mapPlayerLocation[row][col].Playertwo_second = false;
        mapPlayerLocation[row][col].Playertwo_third = false;
    }
}

// Adds a player's mal token to the specified location in the mapPlayerLocation array
// Input: row and column where the mal token should be added, player number (0 or 1), and mal number (1, 2, or 3)
// Outputs: No return value. Modifies class state.
void Map::addPlayerLocation(int row, int col, int playerNum, int malNum){
    if (playerNum == 0){
        if (malNum == 1){
            mapPlayerLocation[row][col].Playerone_first = true;
        } else if(malNum == 2){
            mapPlayerLocation[row][col].Playerone_second = true;
        } else if (malNum ==3){
            mapPlayerLocation[row][col].Playerone_third = true;
        }
    } else if (playerNum == 1){
        if (malNum == 1){
            mapPlayerLocation[row][col].Playertwo_first = true;
        } else if(malNum == 2){
            mapPlayerLocation[row][col].Playertwo_second = true;
        } else if (malNum ==3){
            mapPlayerLocation[row][col].Playertwo_third = true;
        }
    }
}
// Updates a player's mal token location in the mapPlayerLocation array
// Input: previous row and column, new row and column, player number (0 or 1), and mal number (1, 2, or 3)
// Output: Modifies mapPlayerLocation array, marking the given player's piece as present at the specified location.
void Map::UpdatePlayerLocation(int previRow, int previCol, int row, int col, int playerNum, int malNum) {
    removePlayerLocation(previRow, previCol, playerNum);
    addPlayerLocation(row, col, playerNum, malNum);
}
// Prints the game map with specific elements in different colors.
// Input: None. It uses the class's mapChart 2D array for printing.
// Output: No return value. Outputs the map state to the console.
void Map::printMap(){
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 77; j++) {
            if (i > 0 && j > 0 && mapChart[i][j] == "A" && mapChart[i-1][j] == " " && mapChart[i][j-1] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 0 && j > 1 && mapChart[i][j-1] == "A" && mapChart[i-1][j-1] == " " && mapChart[i][j-2] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 0 && j > 2 && mapChart[i][j-2] == "A" && mapChart[i-1][j-2] == " " && mapChart[i][j-3] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 1 && j > 0 && mapChart[i-1][j] == "A" && mapChart[i-2][j] == " " && mapChart[i-1][j-1] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 1 && j > 1 && mapChart[i-1][j-1] == "A" && mapChart[i-2][j-1] == " " && mapChart[i-1][j-2] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 1 && j > 2 && mapChart[i-1][j-2] == "A" && mapChart[i-2][j-2] == " " && mapChart[i-1][j-3] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 2 && j > 0 && mapChart[i-2][j] == "A" && mapChart[i-3][j] == " " && mapChart[i-2][j-1] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 2 && j > 1 && mapChart[i-2][j-1] == "A" && mapChart[i-3][j-1] == " " && mapChart[i-2][j-2] == " ")
                cout << RED << mapChart[i][j] << RESET;
            else if (i > 2 && j > 2 && mapChart[i-2][j-2] == "A" && mapChart[i-3][j-2] == " " && mapChart[i-2][j-3] == " ")
                cout << RED << mapChart[i][j] << RESET;


            else if (i > 0 && j > 0 && mapChart[i][j] == "B" && mapChart[i-1][j] == " " && mapChart[i][j-1] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 0 && j > 1 && mapChart[i][j-1] == "B" && mapChart[i-1][j-1] == " " && mapChart[i][j-2] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 0 && j > 2 && mapChart[i][j-2] == "B" && mapChart[i-1][j-2] == " " && mapChart[i][j-3] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 1 && j > 0 && mapChart[i-1][j] == "B" && mapChart[i-2][j] == " " && mapChart[i-1][j-1] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 1 && j > 1 && mapChart[i-1][j-1] == "B" && mapChart[i-2][j-1] == " " && mapChart[i-1][j-2] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 1 && j > 2 && mapChart[i-1][j-2] == "B" && mapChart[i-2][j-2] == " " && mapChart[i-1][j-3] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 2 && j > 0 && mapChart[i-2][j] == "B" && mapChart[i-3][j] == " " && mapChart[i-2][j-1] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 2 && j > 1 && mapChart[i-2][j-1] == "B" && mapChart[i-3][j-1] == " " && mapChart[i-2][j-2] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else if (i > 2 && j > 2 && mapChart[i-2][j-2] == "B" && mapChart[i-3][j-2] == " " && mapChart[i-2][j-3] == " ")
                cout << BLUE << mapChart[i][j] << RESET;
            else 
                cout << mapChart[i][j];
        }
        cout << "" << endl;
    }
}
