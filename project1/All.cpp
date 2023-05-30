// UMBC - CMSC 341 - Spring 2023 - Proj0
#ifndef CHECKERS_H
#define CHECKERS_H
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class Grader;//this class is for grading purposes, no need to do anything
class Tester;//this is your tester class, you add your test functions in this class

// the following define statemetns are used for graphical representation
#define WDISK   "\033[7mWD\033[0m" // represents white disk
#define BDISK   "\033[7mBD\033[0m" // represents black disk
#define WKING   "\033[7mWK\033[0m" // represents white king
#define BKING   "\033[7mBK\033[0m" // represents black king
#define WCELL   "  "               // represents white cell
#define BCELL   "\033[7m  \033[0m" // represents black cell
#define DEFBOARDSIZE 8             // default board size is 8 x 8
enum PLAYER {WPLAYER, BPLAYER, NONE};
typedef string CELL;

class Checkers{
    public:
    friend class Grader;
    friend class Tester;
    Checkers();
    Checkers(int rows, int columns);
    ~Checkers();
    void clear();
    void initBoard();   // creates the board
    void initGame();    // creates the initial state of disks
    // the following creates a board with the provided state of disks
    void setGameState(CELL game[], int n, PLAYER player);
    bool play(pair<int,int> origin, pair<int,int> destination);
    void dumpGame();  // for debugging purposes
    void reportLostDisks();  // reports current number of lost disks per player
    
    private:
    int m_numRows;// can be any sizes
    int m_numColumns;//can be any sizes
    CELL ** m_game;// the 2d structure to store game information
    PLAYER m_currPlayer;//must be toggled at every turn
    int m_whiteDisks;//number of current white disks, must be updated at every capture
    int m_blackDisks;//number of current black disks, must be updated at every capture

    /******************************************
    * Private function declarations go here! *
    ******************************************/
    
};
#endif

Checkers::Checkers(){
    m_numColumns = 0;
    m_numRows = 0;
    m_whiteDisks = 0;
    m_blackDisks = 0;
    m_currPlayer = NONE;
    m_game = nullptr;
}

Checkers::Checkers(int rows, int columns){
    if ((rows < 8) || (columns < 8) || (rows != columns)) {
        m_numColumns = 0;
        m_numRows = 0;
        m_whiteDisks = 0;
        m_blackDisks = 0;
        m_currPlayer = NONE;
        m_game = nullptr;
        cout << "nothing";
    } else {
        m_numColumns = columns;
        m_numRows = rows;
        m_whiteDisks = (m_numColumns/2) * 3;
        m_blackDisks = (m_numColumns/2) * 3;
        m_game = new CELL*[rows];
        for (int i = 0; i < rows; i++) {
            m_game[i] = new CELL[columns];
        }
        initBoard();
        initGame();
    }
}

Checkers::~Checkers(){
    clear();
}

void Checkers::clear(){
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

void Checkers::initBoard(){
    for (int i = 0; i < m_numRows; i++) {
        for (int j = 0; j < m_numColumns; j++) {
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

void Checkers::reportLostDisks(){
    
}

void Checkers::initGame(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < m_numColumns; j++) {
            if (m_game[i][j] == BCELL) {
                m_game[i][j] = WDISK;
                m_game[m_numRows-(1+i)][m_numColumns-(1+j)] = BDISK;
            }
        }
    }
    m_currPlayer = BPLAYER;
}

bool Checkers::play(pair<int,int> origin, pair<int,int> destination){
    return false;
}

void Checkers::setGameState(CELL game[], int n, PLAYER player){
    
}

void Checkers::dumpGame(){
    if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr){
        cout << "  ";
        for (int k=0;k<m_numColumns;k++){
            cout << k << " ";
        }
        cout << endl;
        for (int i=1;i <= m_numRows;i++){
            cout << i-1 << " ";
            for (int j=1;j<=m_numColumns;j++){
                cout << m_game[i-1][j-1];
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main() {
    Checkers checkers(10,10);
    checkers.dumpGame();
}
