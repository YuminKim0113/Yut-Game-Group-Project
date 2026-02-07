#ifndef MAL_H
#define MAL_H

// Struct representing a single game piece (Mal)
struct Mal {
    int row;                // The current row of the Mal on the game board
    int column;             // The current column of the Mal on the game board
    int previousRow;        // The previous row of the Mal on the game board
    int previousColumn;     // The previous column of the Mal on the game board
    bool can_finish;        // Indicates if the Mal has moved at least one time.
    bool finished;          // Indicates if the Mal has finished (reached the end point)
    bool carried;           // Indicates if the Mal is being carried by a player
};

#endif
