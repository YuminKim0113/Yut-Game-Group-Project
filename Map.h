#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
#include <map>
#include <utility> 
#include "Station.h"
#include "MapChartDisplay.h"
using namespace std;

class Map {
private:
    string mapChart[60][77]; // 2D array representing the map chart
    Station mapPlayerLocation[7][7]; // 2D array representing the player's location on the map
    pair<int, int> mapPlayerLocation_to_mapChart(int row, int col); // Private method to convert player location to map chart indices

public:
    Map(); // Default constructor
    Map(Station mapPlayerLocation[7][7]); // Constructor that initializes the map with the given player locations
    Station getPlayerLocation(int row, int col); // Method to get player location at a given row and column
    string mapPlayerLocation_to_station(int row, int col); // Method to convert player location to a station
    void removeMal(int row, int col, bool finish); // Method to remove Mal from the map at a given row and column
    void addMal(int row, int col, string mal[3][3]);  // Method to add Mal to the map at a given row and column
    void moveMal(int previRow, int previCol, int row, int col, string mal[3][3], bool finish); // Method to move Mal from one location to another
    void movePlayerLocation(int previRow, int previCol, int row, int col); // Method to move player location from one place to another
    void removePlayerLocation(int row, int col, int playerNum); // Method to remove player location from the map
    void addPlayerLocation(int row, int col, int playerNum, int malNum); // Method to add player location to the map
    void UpdatePlayerLocation(int previRow, int previCol, int row, int col, int playerNum, int malNum); // Method to update player location on the map
    void printMap(); // Method to print the map
    
};

#endif
