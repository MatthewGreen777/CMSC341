#include "checkers.h"
using namespace std;
class Tester{
    public:
    // The following is implemented as a sample test function.
    // This function tests whether the function play(...) performs
    //  a capturing move successfully or not.
    // Please note, before calling this test function we have set 
    //  the state of the game to a certain state
    // Moreover note, After calling this test function the state 
    //  of the of the game will change 
    bool testCaptureSuccess(Checkers & checkers){
        bool result = true;
        // before play we expect a BCELL in (3,2)
        result = result && (checkers.m_game[3][2] == BCELL);
        // before play we expect a WDISK in (1,4)
        result = result && (checkers.m_game[1][4] == WDISK);
        // before play we expect that it is WPLAYER turn to play
        result = result && (checkers.m_currPlayer == WPLAYER);
        // before play we expect a BDISK in (2,3), there is an opponent disk
        result = result && (checkers.m_game[2][3] == BDISK);
        // store the ccurrent opponent number if disks
        int opponentDisks = checkers.m_blackDisks;
        // now call the play(...) function
        result = checkers.play(pair<int,int>(1,4),pair<int,int>(3,2));
        // we are trying to move (1,4) to (3,2), we expect that move is successful
        // after play we expect a BCELL in (1,4)
        result = result && (checkers.m_game[1][4] == BCELL);
        // after play we expect a WDISK in (3,2)
        result = result && (checkers.m_game[3][2] == WDISK);
        // after play we expect that it is BPLAYER turn
        result = result && (checkers.m_currPlayer == BPLAYER);
        // after play we expect a BCELL in (2,3), an opponent disk is captured
        result = result && (checkers.m_game[2][3] == BCELL);
        // after play we expect one less disk for the opponent
        result = result && (checkers.m_blackDisks == (opponentDisks-1));
        return result;
    }

    /******************************************
    * Test function declarations go here! *
    ******************************************/
};

int main(){
    Tester tester;
    Checkers checkers(DEFBOARDSIZE, DEFBOARDSIZE);
    checkers.initBoard();
    cout << "\nthe following is the rendering of the board:\n\n"; 
    checkers.dumpGame(); // render the board
    checkers.initGame();
    cout << "\nthe following shows the initial state of the game:\n\n";
    checkers.dumpGame(); // render the initial state of the game
    checkers.play(pair<int,int>(5,0),pair<int,int>(4,1));
    checkers.dumpGame();
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",};
    // set the current state of the game to a certain pre-defined state
    checkers.setGameState(game, size, WPLAYER);
    cout << "\nthe following shows the current state of the game:\n\n";
    checkers.dumpGame(); // render the current state of the game
    cout << "\nthe following tests a capturing move for which we expect success:\n\n";
    if (tester.testCaptureSuccess(checkers))
        cout << "\ttestCaptureSuccess() returned true." << endl;
    else
        cout << "\ttestCaptureSuccess() returned false." << endl;
    cout << "\nthe following shows the state of the game after the capturing move:\n\n";
    checkers.dumpGame(); // render the current state of the game
    checkers.reportLostDisks();
    cout << endl;
    return 0;
}