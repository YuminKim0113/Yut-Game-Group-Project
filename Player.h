#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "Mal.h"
#include "Map.h"
using namespace std;

class Player {
  private:
    string name;  // Declare name 
    vector<Mal> Mals; // Declare vector Mals in Mal class
    void only_six_positions_in_edges(Mal &playerMal); //Declare function when mal is in edges
    void moveStraight(Mal &playerMal, int &moveNum); //Declare function for moving straight
    void corner_and_diagonal(Mal &playerMal, int &moveNum); // Declare a function for corner and diagonal
    void center(Mal &playerMal, int &moveNum); // Declare a function when mal is in center
    void Back(Mal &playerMal); //Declare a function when mal move backward

  public:
    Player(); //Declare constructor
    Player(string name, int first1, int first2, int second1, int second2, int third1, int third2); // Specify the constructor
    string getName(); //Function for getting name
    void setName(string name); //Function for setting a name
    int getRow(int malNum); //Function for getRow
    int getCol(int malNum);// Function for getting column
    void setRowCol(int malNum, int row, int col); //Function for setting col and row for given mal
    int getPreviousRow(int malNum); //Function for getting previous row
    int getPreviousCol(int malNum); //Fucntion for getting previous column
    void setPreviousRowCol(int malNum, int row, int col); // Function for setting previous row and column
    Mal getMal(int malNum); //Function for getting a mal return the mal type.
    void setMal(int malNum, int row, int col, bool can_finish, bool finished, bool carried); //Function for set a mal
    void set_cannot_finish(int malNum); // Function to set mal to not 'can_finish'
    bool win(); //Function for distinguishing end of game
    void check_Carried(); //Function for checking carried mals
    void set_not_Carried(int malNum); //Function to set mal to not 'carried'
    bool no_Mal_on_Map(); //Function for checking if there are any mals on the game map
    void moveMal(int malNum, int moveNum); //Function for moving mal
    void newRowCol (Mal &playerMal, int &moveNum); //Function for setting new location of mal after moving
    void can_finish(Mal &playerMal); //Function when able to finish
    void finish(Mal &playerMal, int &moveNum); //Function to finish 
};

#endif
