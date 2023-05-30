// UMBC - CMSC 341 - Spring 2023 - Proj0
/********************************************************
** File: checkers.cpp
** Project: CMSC 341 Project 0
** Author: Matthew Green
** Date: 14/02/2021
** Email: mgreen11@umbc.edu
**
** Description: Defines the functions set in the .h file
**********************************************************/

#include "checkers.h" // include header

Checkers::Checkers() { // base constructor
    // initialize variables to nothing
    m_numColumns = 0;
    m_numRows = 0;
    m_whiteDisks = 0;
    m_blackDisks = 0;
    m_currPlayer = NONE;
    m_game = nullptr;
}

Checkers::Checkers(int rows, int columns) { // overloaded constructor
    // initialize variables to nothing if it does not pass certain parameters
    if (((rows < DEFBOARDSIZE) || (columns < DEFBOARDSIZE)) || (rows != columns) || (columns % 2 != 0)) {
        m_numColumns = 0;
        m_numRows = 0;
        m_whiteDisks = 0;
        m_blackDisks = 0;
        m_currPlayer = NONE;
        m_game = nullptr;
    } else {
        // initialize variables
        m_numColumns = columns;
        m_numRows = rows;
        m_whiteDisks = floor(double(((m_numColumns / 2)) * 3)); // floor double for odd dimension
        m_blackDisks = floor(double(((m_numColumns / 2)) * 3)); // above
        // create the 2d array
        m_game = new CELL*[rows];
        for (int i = 0; i < rows; i++) {
            m_game[i] = new CELL[columns];
        }
        m_currPlayer = NONE; // will be set in initGame
        initBoard(); // calss function
        initGame(); // calls function
    }
}

Checkers::~Checkers() { // destructor
    clear();
}

void Checkers::clear() { // clears all memory
    // clear memory from rows
    for (int i = 0; i < m_numRows; i++){
        delete[] m_game[i];
    }
    delete[] m_game; // clear remaining memory
    // set all values to default
    m_game = nullptr;
    m_currPlayer = NONE;
    m_numRows = 0;
    m_numColumns = 0;
    m_whiteDisks = 0;
    m_blackDisks = 0;
}

void Checkers::initBoard() { // creates the checkerboard
    if ((m_numColumns < 8) || (m_numRows < 8) || (m_numColumns != m_numRows) || (m_game == nullptr) || (m_numColumns % 2 != 0)) {
        cout << "Can not generate cells as board is not correct size" << endl;
    } else {
        for (int i = 0; i < m_numRows; i++) {
            for (int j = 0; j < m_numColumns; j++) {
                // set indexes in array to be specific color to be checkerboard
                if (((i % 2) == 0) && ((j % 2) == 0)) {
                    m_game[i][j] = WCELL;
                } else if (((i % 2) == 1) && ((j % 2) == 1)) {
                    m_game[i][j] = WCELL;
                } else {
                    m_game[i][j] = BCELL;
                }
            }
        }
    }
}

void Checkers::reportLostDisks() { // prints how many disks each player has lost
    int disks = floor(double(((m_numColumns / 2)) * 3)); // formula for how many disks each side started with
    cout << "White player lost disks: " << (disks - m_whiteDisks) << endl;
    cout << "Black player lost disks: " << (disks - m_blackDisks) << endl;
}

void Checkers::initGame() { // adds the pieces to the board
if ((m_numColumns < 8) || (m_numRows < 8) || (m_numColumns != m_numRows) || (m_game == nullptr) || (m_numColumns % 2 != 0)) { // don't add pieces if board is not allowed
    cout << "Can not add pieces to board as board is not correct size" << endl;
} else {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < m_numColumns; j++) {
                if (m_game[i][j] == BCELL) { // adds pieces only to the black squares
                    m_game[i][j] = WDISK; // add white disk pieces, top of board
                    m_game[m_numRows - (1 + i)][m_numColumns - (1 + j)] = BDISK; // add black disk pieces, bottom of board
                }
            }
        }
        if (m_currPlayer == NONE) { // set player if not set
            m_currPlayer = BPLAYER;
        }
    }
}

bool Checkers::play(pair<int,int> origin, pair<int,int> destination) { // determines if a play is legal and goes throguh with it if it was
    bool pass = false; // bool to decde
    // checks for all invalid cases, out of bounds, current player piece not selected, invalid moves, etc.
    if ((m_blackDisks == 0) || (m_whiteDisks == 0)) {
        cout << "Game is over, one side is out of pieces" << endl;
        cout << "You are now out of your misery" << endl;
    } else if ((origin.first > m_numRows || origin.second > m_numColumns || origin.first < 0 || origin.second < 0)) {
        cout << "Origin of piece does not exist" << endl;
    } else if ((destination.first > m_numRows) || (destination.second > m_numColumns) || (destination.first < 0 || destination.second < 0)) {
        cout << "Destination of piece does not exist" << endl;
    } else if ((m_currPlayer == BPLAYER) && ((m_game[origin.first][origin.second] != BDISK) && (m_game[origin.first][origin.second] != BKING))) {
        cout << "Current player piece was not selected" << endl;
    } else if ((m_currPlayer == WPLAYER) && ((m_game[origin.first][origin.second] != WDISK) && (m_game[origin.first][origin.second] != WKING))) {
        cout << "Current player piece was not selected" << endl;
    } else if (m_game[destination.first][destination.second] == WCELL) {
        cout << "Can not move to a white space" << endl;
    } else if (m_game[destination.first][destination.second] != BCELL) {
        cout << "Destination of selected piece is already occupied" << endl;
    }
    // checks for all valid moves and execute them
    else if (m_game[origin.first][origin.second] == BDISK) { // moves for black disk
        pass = true;

        if (((origin.first - 2) == destination.first) && ((origin.second - 2) == destination.second) && ((m_game[origin.first - 1][origin.second -1] ==  WDISK )|| (m_game[origin.first - 1][origin.second -1] == WKING))) { // attempt to move up left with enemy in way
            m_game[origin.first][origin.second] = BCELL; // remove position you were just on
            m_game[origin.first - 1][origin.second - 1] = BCELL; // remove enemy disk
            m_game[destination.first][destination.second] = BDISK; // put your disk on new position
            if (destination.first == 0) { // get king since at end
                m_game[destination.first][destination.second] = BKING;
            }
            m_whiteDisks--;
        } else if (((origin.first - 2) == destination.first) && ((origin.second + 2) == destination.second) && ((m_game[origin.first - 1][origin.second + 1] == WDISK) || (m_game[origin.first - 1][origin.second + 1] == WKING))) { // attempt to move up right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first - 1][origin.second + 1] = BCELL;
            m_game[destination.first][destination.second] = BDISK;
            if (destination.first == 0) { // get king since at end
                m_game[destination.first][destination.second] = BKING;
            }
            m_whiteDisks--;
        } else if (((origin.first - 1) == destination.first) && ((origin.second - 1) == destination.second)) { // attempt to move up left
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = BDISK;
            if (destination.first == 0) { // get king since at end
                m_game[destination.first][destination.second] = BKING;
            }
        } else if (((origin.first - 1) == destination.first) && ((origin.second + 1) == destination.second)) { // attempt to move up right
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = BDISK;
            if (destination.first == 0) { // get king since at end
                m_game[destination.first][destination.second] = BKING;
            }
        } else {
            cout << "Not a legal move" << endl;
            pass = false;
        }
        
    } else if (m_game[origin.first][origin.second] == BKING) { // moves for black king
        pass = true;
        if ((((origin.first - 2) == destination.first) && ((origin.second - 2) == destination.second)) && ((m_game[origin.first - 1][origin.second - 1] == WDISK) || (m_game[origin.first - 1][origin.second - 1] == WKING))) { // attempt to move up left with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first - 1][origin.second - 1] = BCELL;
            m_game[destination.first][destination.second] = BKING;
            m_whiteDisks--;
        } else if ((((origin.first + 2) == destination.first) && ((origin.second - 2) == destination.second)) && ((m_game[origin.first + 1][origin.second - 1] == WDISK) || (m_game[origin.first + 1][origin.second - 1] == WKING))) { // attempt to move down left with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first + 1][origin.second - 1] = BCELL;
            m_game[destination.first][destination.second] = BKING;
            m_whiteDisks--;
        } else if ((((origin.first - 2) == destination.first) && ((origin.second + 2) == destination.second)) && ((m_game[origin.first - 1][origin.second + 1] == WDISK) || (m_game[origin.first - 1][origin.second + 1] == WKING))) { // attempt to move up right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first - 1][origin.second + 1] = BCELL;
            m_game[destination.first][destination.second] = BKING;
            m_whiteDisks--;
        } else if ((((origin.first + 2) == destination.first) && ((origin.second + 2) == destination.second)) && ((m_game[origin.first + 1][origin.second + 1] == WDISK) || (m_game[origin.first + 1][origin.second + 1] ==  WKING))) { // attempt to move down right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first + 1][origin.second + 1] = BCELL;
            m_game[destination.first][destination.second] = BKING;
            m_whiteDisks--;
        } else if (((origin.first - 1) == destination.first) && ((origin.second - 1) == destination.second)) { // attempt to move up left
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = BKING;
        } else if (((origin.first + 1) == destination.first) && ((origin.second - 1) == destination.second)) { // attempt to move down left
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = BKING;
        } else if (((origin.first - 1) == destination.first) && ((origin.second + 1) == destination.second)) { // attempt to move up right
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = BKING;
        } else if (((origin.first + 1) == destination.first) && ((origin.second + 1) == destination.second)) { // attempt to move down right
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = BKING;
        } else {
            cout << "Not a legal move" << endl;
            pass = false;
        }

    } else if (m_game[origin.first][origin.second] == WDISK) { // moves for white disk
        pass = true;
        if ((((origin.first + 2) == destination.first) && ((origin.second + 2) == destination.second)) && ((m_game[origin.first + 1][origin.second + 1] ==  BDISK) || (m_game[origin.first + 1][origin.second + 1] == BKING))) { // attempt to move down right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first - 1][origin.second - 1] = BCELL;
            m_game[destination.first][destination.second] = WDISK;
            if (destination.first == (m_numRows - 1)) {
                m_game[destination.first][destination.second] = WKING;
            }
            m_blackDisks--;
        } else if ((((origin.first + 2) == destination.first) && ((origin.second - 2) == destination.second)) && ((m_game[origin.first + 1][origin.second - 1] == BDISK) || (m_game[origin.first + 1][origin.second - 1] == BKING))){ // attempt to move down left with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first + 1][origin.second - 1] = BCELL;
            m_game[destination.first][destination.second] = WDISK;
            if (destination.first == (m_numRows - 1)) {
                m_game[destination.first][destination.second] = WKING;
            }
            m_blackDisks--;
        } else if (((origin.first + 1) == destination.first) && ((origin.second + 1) == destination.second)) { // attempt to move down right
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = WDISK;
            if (destination.first == (m_numRows - 1)) {
                m_game[destination.first][destination.second] = WKING;
            }
        } else if (((origin.first + 1) == destination.first) && ((origin.second - 1) == destination.second)) { // attempt to move down left
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = WDISK;
            if (destination.first == (m_numRows - 1)) {
                m_game[destination.first][destination.second] = WKING;
            }
        } else {
            cout << "Not a legal move" << endl;
            pass = false;
        }

    } else if (m_game[origin.first][origin.second] == WKING) { // moves for white king
        pass = true;
        if ((((origin.first + 2) == destination.first) && ((origin.second + 2) == destination.second)) && ((m_game[origin.first + 1][origin.second + 1] == BDISK) || (m_game[origin.first + 1][origin.second + 1] == BKING))) { // attempt to move down right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first - 1][origin.second - 1] = BCELL;
            m_game[destination.first][destination.second] = WKING;
            m_blackDisks--;
        } else if ((((origin.first + 2) == destination.first) && ((origin.second - 2) == destination.second)) && ((m_game[origin.first - 1][origin.second + 1] == BDISK) || (m_game[origin.first - 1][origin.second + 1] == BKING))) { // attempt to move up right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first + 1][origin.second - 1] = BCELL;
            m_game[destination.first][destination.second] = WKING;
            m_blackDisks--;
        } else if ((((origin.first - 2) == destination.first) && ((origin.second + 2) == destination.second)) && ((m_game[origin.first - 1][origin.second + 1] == BDISK) || (m_game[origin.first - 1][origin.second + 1] == BKING))) { // attempt to move down left with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first - 1][origin.second + 1] = BCELL;
            m_game[destination.first][destination.second] = WKING;
            m_blackDisks--;
        } else if ((((origin.first + 2) == destination.first) && ((origin.second + 2) == destination.second)) && ((m_game[origin.first - 1][origin.second + 1] == BDISK) || (m_game[origin.first - 1][origin.second + 1] == BKING))) { // attempt to move up right with enemy in way
            m_game[origin.first][origin.second] = BCELL;
            m_game[origin.first + 1][origin.second + 1] = BCELL;
            m_game[destination.first][destination.second] = WKING;
            m_blackDisks--;
        } else if (((origin.first + 1) == destination.first) && ((origin.second + 1) == destination.second)) { // attempt to move down right
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = WKING;
        } else if (((origin.first - 1) == destination.first) && ((origin.second + 1) == destination.second)) { // attempt to move up right
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = WKING;
        } else if (((origin.first + 1) == destination.first) && ((origin.second - 1) == destination.second)) { // attempt to move down left
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = WKING;
        } else if (((origin.first - 1) == destination.first) && ((origin.second - 1) == destination.second)) { // attempt to move up left
            m_game[origin.first][origin.second] = BCELL; 
            m_game[destination.first][destination.second] = WKING;
        } else {
            cout << "Not a legal move" << endl;
            pass = false;
        }
    } else {
        cout << "Something is not right" << endl;
        pass = false;
    }

    if (pass) { // change who turn it is
        if (m_currPlayer == BPLAYER) {
            m_currPlayer = WPLAYER;
        } else if (m_currPlayer == WPLAYER) {
            m_currPlayer = BPLAYER;
        } else {
            cout << "How'd you get this" << endl;
        }
    }
    return pass;
}

void Checkers::setGameState(CELL game[], int n, PLAYER player) { 
    int row = 0; // create int for later use
    int column = 0;
    if ((sqrt(n) != floor(sqrt(n)))) { // make sure that the size pass is a square
        cout << "Gamestate can not be altered as wanted state is invalid" << endl;
    } else if (sqrt(n) != m_numColumns) { // make sure that the board dimension has not changed
        cout << "Gamestate can not be changed as dimensions of board has to stay the same" << endl;
    } else if (sqrt(n) < 8) { // make sure that the dimension being changed is not less then 8
        cout << "Gamestate can not be altered as wanted size is too small" << endl;
    } else if (int(sqrt(n)) % 2 != 0) { // make sure that the board dimension is even
        cout << "Gamestate can not be altered as columns have to be an even number" << endl;
    } else { 
        m_currPlayer = player; // set the current player as whoever was choses
        if (m_currPlayer == NONE) {
            m_currPlayer = BPLAYER;
        }
        for (int i = 0; i < n; i++) { // changes the board to be how the player wantes it
            if (game[i] == BCELL) { // set space to BCELL if it is in given array
                row = i / m_numRows; // calculate row and column position
                column = i - (row * m_numRows);
                if (m_game[row][column] == WCELL) { // can't change white tile to a black one
                    cout << "Tile can not be changed to black cell" << endl;
                } else if ((m_game[row][column] == WDISK) || (m_game[row][column] == WKING)) { // change if white disk was in space
                    m_game[row][column] = BCELL; // change value
                    m_whiteDisks--; // decrease disk
                }  else if ((m_game[row][column] == BDISK) || (m_game[row][column] == BKING)) { // change if black disk was in space
                    m_game[row][column] = BCELL; // change value
                    m_blackDisks--; // decrease disk
                }
            } else if ((game[i] == BDISK) || (game[i] == BKING)) { // set space to black disk
                row = i / m_numRows; // calculate row and column position
                column = i - (row * m_numRows);
                if ((m_game[row][column] == WCELL) || (m_blackDisks == floor(double(((m_numColumns / 2)) * 3)))) { // make sure that tile is not already occupied or is a white tile or black disks are at max
                    cout << "Piece can not be placed here" << endl;
                }  else if (((m_game[row][column] == WDISK) || (m_game[row][column] == WKING)) && (game[i] == BDISK)) { // check if space is occupied by opposite piece
                    m_game[row][column] = BDISK;
                    m_blackDisks++;
                    m_whiteDisks--;
                } else if (((m_game[row][column] == WDISK) || (m_game[row][column] == WKING)) && (game[i] == BKING)) { // check if piece is occupied by other piece
                    m_game[row][column] = BKING;
                    m_blackDisks++;
                    m_whiteDisks--;
                } else if (game[i] == BDISK) { // adds black disk to tile
                    m_game[row][column] = BDISK;
                    m_blackDisks++;
                } else if (game[i] == BKING) { // adds black king to tile
                    m_game[row][column] = BKING;
                    m_blackDisks++;
                }
            } else if ((game[i] == WDISK) || (game[i] == WKING)) { // same as above but for white player
                row = i / m_numRows;
                column = i - (row * m_numRows);
                if ((m_game[row][column] == WCELL) || (m_whiteDisks == floor(double(((m_numColumns / 2)) * 3)))) {
                    cout << "Piece can not be placed here" << endl;
                } else if (((m_game[row][column] == BDISK) || (m_game[row][column] == BKING)) && (game[i] == WDISK)) {
                    m_game[row][column] = WDISK;
                    m_whiteDisks++;
                    m_blackDisks--;
                } else if (((m_game[row][column] == BDISK) || (m_game[row][column] == BKING)) && (game[i] == WKING)) {
                    m_game[row][column] = WKING;
                    m_whiteDisks++;
                    m_blackDisks--;
                } else if (game[i] == WDISK) {
                    m_game[row][column] = WDISK;
                    m_whiteDisks++;
                } else if (game[i] == WKING) {
                    m_game[row][column] = WKING;
                    m_whiteDisks++;
                } 
            }
        }

    }
}

void Checkers::dumpGame() { // prints out what the game looks like at moment
    // not commenting this as I had nothing to do with this
    if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr){
        cout << "  ";
        for (int k=0;k<m_numColumns;k++){
            cout << k << " ";
        }
        cout << endl;
        for (int i=1;i <= m_numRows;i++){
            cout << i - 1 << " ";
            for (int j=1;j<=m_numColumns;j++){
                cout << m_game[i - 1][j - 1];
            }
            cout << endl;
        }
        cout << endl;
    }
}