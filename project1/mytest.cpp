/********************************************************
** File: mytest.cpp
** Project: CMSC 341 Project 0
** Author: Matthew Green
** Date: 14/02/2021
** Email: mgreen11@umbc.edu
**
** Description: Tests everything in the project 
**********************************************************/

#include "checkers.h"

class Tester {
    public:
    bool testNormalConstructor(Checkers &checkers);
    bool testCreateUnderSize(Checkers &checkers);
    bool testMinimumSize(Checkers &checkers);
    bool testGiantSize(Checkers &checkers);
    bool testIncorrectSize(Checkers &checkers);
    bool testNegativeSizee(Checkers &checkers);
    bool testOddSize(Checkers &Checkers);
    bool testClear(Checkers &checkers);
    bool testNonSquareInItBoard(Checkers &checkers);
    bool testEmptyBoardInItBoard(Checkers &checkers);
    bool testUnderSizedInItBoard(Checkers &checkers);
    bool testMinimumBoardSizeInItBoard(Checkers &checkers);
    bool testLargeBoardSizeInItBoard(Checkers &checkers);
    bool testOddSizeInItBoard(Checkers &checkers);
    bool testEmptyBoardInItGame(Checkers &checkers);
    bool testUnderSizeBoardInItGame(Checkers &checker);
    bool testMinimumBoardSizeInItGame(Checkers &checkers);
    bool testLargeBoardSizeInItGame(Checkers &checkers);
    bool testNonSquareInItGame(Checkers &checkers);
    bool testOddSizeInItGame(Checkers &checkers);
    bool testNegativeSetGameState(Checkers &checkers);
    bool testOddSetGameState(Checkers &checkers);
    bool testNotSquareSetGameState(Checkers &checkers);
    bool testNotCorrectCellAmountSetGameState(Checkers &checkers); // this test can not work, see comment next to actual test
    bool testNoPlayerSetGameState(Checkers &checkers);  
    bool testCorrectSizeSetGameState(Checkers &checkers);
    bool testIncorrectPlayerMove(Checkers &checkers);
    bool testIncorrectVerticalMovePlay(Checkers &checkers);
    bool testIncorrectHorizontalMovePlay(Checkers &checkers);
    bool testIncorrectAttemptedJump(Checkers &checkers);
    bool testCorrectForwardMovementWhite(Checkers &checkers);
    bool testCorrectForwardMovementBlack(Checkers &checkers);
    bool testCorrectLeap(Checkers &checkers);
    bool testBecomingKingWhite(Checkers &checkers);
    bool testBecomingKingBlack(Checkers &checkers);
    bool testCorrectBackwardMovement(Checkers &checkers);
    bool testCorrectBackwardMovementLeap(Checkers &checkers);
    bool testMovingToOccupiedSpce(Checkers &checkers);
    bool testMovingOutOfBounds(Checkers &checkers);
    bool testChoosingEmptySpace(Checkers&checkers);
    bool testChoosingNonExistantSpace(Checkers &checkers);
    bool testFailingToGoBackwards(Checkers &checkers);
};

int main() {
    Tester tester;
    {
        //test creating a game with normal constructor, nothing should appear
        Checkers check;
        cout << "Test case, Normal Constructor: Expecting no board" << endl;
        if (tester.testNormalConstructor(check)) {
            cout << "Normal Constructor Passed" << endl;
        } else {
            cout << "Normal Constructor Failed" << endl;
        }
    }
    {
        // test creating a board that is smaller then the minimum
        cout << "\nTest case, Overloaded Constructor Under Sized: No board should be made" << endl;
        Checkers check(6,6);
        if (tester.testCreateUnderSize(check)) {
            cout << "Overloaded Constructor Under Sized Passed" << endl;
        } else {
            cout << "Overloaded Constructor Under Sized Filed" << endl;
        }
    }
    {
        // test creating a minimum size board, 8x8
        cout << "\nTest case, Overloaded Constructor Minimum: Minimum size board should be made" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testMinimumSize(check)) {
            cout << "Overloaded Constructor Minimum Passed" << endl;
        } else {
            cout << "OVerloaded Constructor Minimum Failed" << endl;
        }
    }
    {
        // test creating a large board, 10x10
        cout << "\nTest case, Overloaded Constructor Large: Larger then minimum size board should be made" << endl;
        Checkers check(10,10);
        if (tester.testGiantSize(check)) {
            cout << "OVerloaded Constructor Large Passed" << endl;
        } else {
            cout << "Overloaded Constructor Large Failed" << endl;
        }
    }
    {
        // test creating a non sqare board
        cout << "\nTest case, Overloaded Constructor Not Square:  No board should be made as width and length are not the same" << endl;
        Checkers check(9,10);
        if (tester.testIncorrectSize(check)) {
            cout << "Overloaded Constructor Not Square Passed" << endl;
        } else {
            cout << "Overloaded Constructor Not Sqauare Faiiled" << endl;
        }
    }
    {
        // test creating a board with negative dimension
        cout << "\nTest case, Overloaded Constructor Negative Size: No board should be made with negative dimension" << endl;
        Checkers check(4, -2);
        if (tester.testNegativeSizee(check)) {
            cout << "Overloaded Constructor Negative Size Passed" << endl;
        } else {
            cout << "OVerloaded Constructor Negative Size Failed" << endl;
        }
    }
    {
        // test creating a board with odd size dimention
        cout << "\nTest case, Overloaded Constructor Odd Size: set the width and legth to be odd" << endl;
        Checkers check(11,11);
        if (tester.testOddSize(check)) {
            cout << "Overloaded Constructor Odd Size Passed" << endl;
        } else {
            cout << "Overloaded Constructor Odd Size Failed" << endl;
        }
    }
    {
        // test the clear function
        cout << "\nTest case, Clear Function: Function should delete all memory" << endl;
        Checkers check (8,8);
        if (tester.testClear(check)) {
            cout << "Clear Function Passed" << endl;
        } else {
            cout << "Clear Function Failed" << endl;
        }
    }
    {
        // test adding cells to an non square board
        cout << "\nTest case, InItBoard Non Square: Make sure cells are not added" << endl;
        Checkers check(3, 2);
        if (tester.testNonSquareInItBoard(check)) {
            cout << "InItBoard Non Square Passed" << endl;
        } else {
            cout << "InItBoard Non Square Failed" << endl;
        }
    }
    {
        // test adding cells an empty board
        cout << "\nTest case, InItBoard Empty: Make sure that no board is made" << endl;
        Checkers check;
        if (tester.testEmptyBoardInItBoard(check)) {
            cout << "InItBoard Empty Passed" << endl;
        } else {
            cout << "InItBoard Empty Passed" << endl;
        }
    }
    {
        // test adding cells an undersized board
        cout << "\nTest case, InItBoard Undersized: Make sure that no board is made" << endl;
        Checkers check(4,4);
        if (tester.testUnderSizedInItBoard(check)) {
            cout << "InItBoard Undersized Passed" << endl;
        } else {
            cout << "InItBoard Undersized Failed" << endl;
        }
    }
    {
        // test adding cells minimum size board
        cout << "\nTest case, InItBoard Default Size: Make default size board, 8x8" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testMinimumBoardSizeInItBoard(check)) {
            cout << "InItBoard Default Size Passed" << endl;
        } else {
            cout << "InItBoard Default Size Failed" << endl;
        }
    }
    {
        // test adding cells to large size board
        cout << "\nTest case, InItBoard Large Size: Make board that is large" << endl;
        Checkers check(10,10);
        if (tester.testLargeBoardSizeInItBoard(check)) {
            cout << "InItBoard Large Size Passed" << endl;
        } else {
            cout << "InItBoard Large Sized Passed" << endl;
        }
    }
    {
        // test adding cells to an odd size board
        cout << "\nTest case, InItBoard Odd Size: make the board that has odd dimension" << endl;
        Checkers check(11,11);
        if (tester.testOddSizeInItBoard(check)) {
            cout << "InItBoard Odd Size Passed" << endl;
        } else {
            cout << "InItBoard Odd Size Failed" << endl;
        }
    }
    {
        // test adding pieces to empty board
        cout << "\nTest case, InItGame Empty: No Pieces should be added" << endl;
        Checkers check;
        if(tester.testEmptyBoardInItGame(check)) {
            cout << "InItGame Empty Passed" << endl;
        } else {
            cout << "InItGame Empty Failed" << endl;
        }
    }
    {
        // test adding pieces to undersized  board
        cout << "\nTest Case, InItGame Undersized: try adding pieces to an undersized board" << endl;
        Checkers check(6, 6);
        if (tester.testUnderSizeBoardInItGame(check)) {
            cout << "InItGame Undersized Passed" << endl;
        } else {
            cout << "InItGame Undersized Failed" << endl;
        }
    }
    {
        // test minimum size board 8x8
        cout << "\nTest case, InItGame Minimum Size: Put pieces on minimum size board" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testMinimumBoardSizeInItGame(check)) {
            cout << "InItGame Minimum Size Passed" << endl;
        } else {
            cout << "InItGame Minimum Size Failed" << endl;
        }
    }
    {
        // test a large board size
        cout << "\nTest case, InItGame Large Size: Put pieces on a large board" << endl;
        Checkers check(10, 10);
        if (tester.testLargeBoardSizeInItGame(check)) {
            cout << "InItGame Large Size Passed" << endl;
        } else {
            cout << "InItGame Large Sized Failed" << endl;
        }
    }
    {
        // test non square board adding pieces
        cout << "\nTest case, InItGame Non Square: No Pieces should be put on board" << endl;
        Checkers check(9,10);
        if (tester.testNonSquareInItGame(check)) {
            cout << "InItGame Non Square Passed" << endl;
        } else {
            cout << "InItGame Non Square Failed" << endl;
        }
    }
    {
        // test adding pieces to odd square board
        cout << "\nTest case, InItGame Odd Dimension: try adding pieces to an odd size board" << endl;
        Checkers check(11,11);
        if (tester.testOddSizeInItGame(check)) {
            cout << "InItGame Odd Dimension Passed" << endl;
        } else {
            cout << "InItGame Odd Dimension Failed" << endl;
        }
    }
    {
        // test making a negative square board
        cout << "\nTest Case, SetGameState Negative:tries to make a negative board" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester. testNegativeSetGameState(check)) {
            cout << "SetGameState Negative Passed" << endl;
        } else {
            cout << "SetGameState Negative Failed" << endl;
        }
    }
    {
        // test making an odd size square board
        cout << "\nTest case, SetGameState Odd Size: try to make a board with odd dimension" << endl;
        Checkers check(DEFBOARDSIZE,DEFBOARDSIZE);
        if (tester.testOddSetGameState(check)) {
            cout << "SetGameState Odd Size Passed" << endl;
        } else {
            cout << "SetGameState Odd Size Failed" << endl;
        }
    }
    {
        // test making non square board using set game state
        cout << "\nTest case, SetGameState Non Square: tries to create a non square board" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testNotSquareSetGameState(check)) {
            cout << "SetGameState Non Square Passed" << endl;
        } else {
            cout << "SetGameState Non Square Failed" << endl;
        }
    }
    /*
    {
        // test not correct amount of cells
        cout << "\nTest case, SetGameState Incorrect Cell Count: cell count is different from board size" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testNotCorrectCellAmountSetGameState(check)) {
            cout << "SetGameState Incorrect Cell Count Passed" << endl;
        } else {
            cout << "SetGameState Incorrect Cell Count Failed" << endl;
        }
    }
    */
    {
    
        // test none player
        cout << "\nTest case, SetGameState None Player Chosen: none player is chosen which should make it blacks turn" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testNoPlayerSetGameState(check)) {
            cout <<"SetGameState None Player Chosen Passed" << endl;
        } else {
            cout << "SetGameState None Player Chosen Failed" << endl;
        }
    }
    {
        // test correctly modifying board
        cout << "\nTest case, SetGameState Normal: alter game state correclty" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testCorrectSizeSetGameState(check)) {
            cout << "SetGameState Normal Passed" << endl;
        } else {
            cout << "SetGameState Normal Failed" << endl;
        }
    }
    {
        // try moving wrong player
        cout << "\nTest case, Move Incorrect Player Piece: trying moving the wrong player piece" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testIncorrectPlayerMove(check)) {
            cout << "Move Incorrect Player Piece Passed" << endl;
        } else {
            cout << "Move Incorrect Player Piece Failed" << endl;
        }
    }
    {
        // test trying to move vertically
        cout << "\nTest case, Move Vertically: try moving a piece vertically" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testIncorrectVerticalMovePlay(check)) {
            cout << "Move Vertically Pasesed" << endl;
        } else {
            cout << "Move Vertically Passed" << endl;
        }
    } {
        // test trying to move horizontaly
        cout << "\nTest case, Move Horitzontally: try to move a piece horizontally, should not happen" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testIncorrectHorizontalMovePlay(check)) {
            cout << "Move Horizontally Passed" << endl;
        } else {
            cout << "Move Horizontal Failed" << endl;
        }
    }
    {
        // test tyring to jump an opponent, but a piece is already on destination
        cout << "\nTest case, Move Attempt Jump Fail: try capturing an enemy piece but can not happen as destination is blocked" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testIncorrectAttemptedJump(check)) {
            cout << "Move Attempt Jump Fail Passed" << endl;
        } else {
            cout << "Move Attempt Jump Fail Failed" << endl;
        }
    }
    {
        // test movement for white
        cout << "\nTest case, Move White: try moving white disk correctly" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testCorrectForwardMovementWhite(check)) {
            cout << "Move White Passed" << endl;
        } else {
            cout << "Move White Failed" << endl;
        }
    }
    {
        //test movement for black
        cout << "\nTest case, Move Black: try moving black disk correctly" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testCorrectForwardMovementBlack(check)) {
            cout << "Move Black Passed" << endl;
        } else {
            cout << "Move Black Failed" << endl;
        }
    }
    {
        // test a correct capture
        cout << "\nTest case, Move Capture: successfully capture an emey piece" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testCorrectLeap(check)) {
            cout << "Move Capture Passed" << endl;
        } else {
            cout << "Move Capture Failed" << endl;
        }
    }
    {
        // test white piece becoming king
        cout << "\nTest case, Move White To King: turn a white disk to a white king" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testBecomingKingWhite(check)) {
            cout << "Move White To King Passed" << endl;
        } else {
            cout << "Move White To King Failed" << endl;
        }
    }
    {
        // test black disk becoming king
        cout << "\nTest case, Move Black To King: turn a black disk to a black king" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testBecomingKingBlack(check)) {
            cout << "Move Black to King Passed" << endl;
        } else {
            cout << "Move Black to King Faled" << endl;
        }
    }
    {
        // test a king moving backward
        cout << "\nTest case, Move King Backward: move king backward" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testCorrectBackwardMovement(check)) {
            cout << "Move King Backward Passed" << endl;
        } else {
            cout << "Move King Backward Failed" << endl;
        }
    }
    {
        // test a king capture backward
        cout << "\nTest case, Move King Backward Capture: capture an enemy that is behind" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testCorrectBackwardMovementLeap(check)) {
            cout << "Move King Backward Capture Passed" << endl;
        } else {
            cout << "Move King Backward Capture Failed" << endl;
        }
    }
    {
        // test trying to move a piece to an already occupied space
        cout << "\nTest case, Move to Occupied Space: try to move a piece to a space already occupied" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testMovingToOccupiedSpce(check)) {
            cout << "Move to Occupied Space Passed" << endl;
        } else {
            cout << "Move to Occupied Space Failed" << endl;
        }
    }
    {
        // test tying to go out of bounds
        cout << "\nTest case, Move Out of Bounds: try to move a piece out of bounds" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testMovingOutOfBounds(check)) {
            cout << "Move Out of Bounds Passed" << endl;
        } else {
            cout << "Move Out of Bounds Failed" << endl;
        }
    }
    {
        // test trying to move an empty space
        cout << "\nTest case, Move Air: try to any empty space" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testChoosingEmptySpace(check)) {
            cout << "Move Air Passed" << endl;
        } else {
            cout << "Move Air Failed" << endl;
        }
    }
    {
        // test trying to move an nonexistant space
        cout << "\nTest case, Move Invisible Object: try to move an object that is out of bounds" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testChoosingNonExistantSpace(check)) {
            cout << "Move Invisible Object Passed" << endl;
        } else {
            cout << "Move Invisible Object Failed" << endl;
        }
    }
    {
        // try to move backward withoout being a king
        cout << "\nTest Case, Move Normal Piece Backward: try to move a normal piece backward like a king" << endl;
        Checkers check(DEFBOARDSIZE, DEFBOARDSIZE);
        if (tester.testFailingToGoBackwards(check)) {
            cout << "Move Normal Piece Backward Passed" << endl;
        } else {
            cout << "Move Normal Piece Backward Failed" << endl;
        }
    }

    return 0;
}

bool Tester::testNormalConstructor(Checkers &checkers) {
    bool pass = true;
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCreateUnderSize(Checkers &checkers) {
    bool pass = true;
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}
bool Tester::testMinimumSize(Checkers &checkers) {
    bool pass = true;
    int track = 0; // cell counter
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testGiantSize(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd otherwise the formula is one below the number of pieces due to rounding errors
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testIncorrectSize(Checkers &checkers) {
    bool pass = true;
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testNegativeSizee(Checkers &checkers) {
    bool pass = true;
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testOddSize(Checkers &checkers) {
    bool pass = true;
    try {
        // checks to make sure member variable were initiazlied
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return true;
}

bool Tester::testClear(Checkers &checkers) {
    bool pass = true;
    int track;
    try {
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd otherwise the formula is one below the number of pieces due to rounding errors
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
        checkers.clear(); // clear the board
        // check that all variable were reset
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testNonSquareInItBoard(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initBoard();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testEmptyBoardInItBoard(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initBoard();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testUnderSizedInItBoard(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initBoard();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
        checkers.m_numColumns = 5;
        checkers.m_numRows = checkers.m_numColumns;
        checkers.initBoard();
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
        checkers.m_numRows = 0;
        checkers.m_numColumns = checkers.m_numRows;
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testMinimumBoardSizeInItBoard(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        checkers.initBoard();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = true;
    }
    return pass;
}

bool Tester::testLargeBoardSizeInItBoard(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        checkers.initBoard();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testOddSizeInItBoard(Checkers &checkers) {
        bool pass = true;
    try {
        checkers.initBoard();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testEmptyBoardInItGame(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initGame();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
        checkers.initGame();
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testUnderSizeBoardInItGame(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initGame();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testMinimumBoardSizeInItGame(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        checkers.initBoard();
        checkers.initGame();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd otherwise the formula is one below the number of pieces due to rounding errors
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testLargeBoardSizeInItGame(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        checkers.initBoard();
        checkers.initGame();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game != nullptr);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && (checkers.m_numColumns == checkers.m_numRows);
        // Note: for comparing the number of disks to the formula used, converting the formula to a doulbe and then flooring it is required for when the dimension of board are odd otherwise the formula is one below the number of pieces due to rounding errors
        pass = pass && (checkers.m_whiteDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        pass = pass && (checkers.m_blackDisks == int(floor((double(checkers.m_numColumns) / 2) * 3)));
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testNonSquareInItGame(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initBoard();
        checkers.initGame();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testOddSizeInItGame(Checkers &checkers) {
    bool pass = true;
    try {
        checkers.initBoard();
        checkers.initGame();
        // checks to make sure member variables were intiazed properly
        pass = pass && (checkers.m_game == nullptr);
        pass = pass && (checkers.m_currPlayer == NONE);
        pass = pass && (checkers.m_numColumns == 0);
        pass = pass && (checkers.m_numRows == 0);
        pass = pass && (checkers.m_whiteDisks == 0);
        pass = pass && (checkers.m_blackDisks == 0);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testNegativeSetGameState(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        // game should start as standard
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
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
        checkers.setGameState(game, -size, WPLAYER); // pass a negative size board
        // game should not have changed and remained in the state it was before
        track = 0;
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testOddSetGameState(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        // game should start as standard
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    const int wrongSize = 11 * 11;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",};
        checkers.setGameState(game, wrongSize, WPLAYER); // pass a non square size board
        // game should not have changed and remained in the state it was before
        track = 0;
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testNotSquareSetGameState(Checkers &checkers) {
    bool pass = true;
    int track = 0;
    try {
        // game should start as standard
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    const int wrongSize = 9 * 10;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",};
        checkers.setGameState(game, wrongSize, WPLAYER); // pass a non square size board
        // game should not have changed and remained in the state it was before
        track = 0;
        for (int i = 0; i < checkers.m_numRows; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (((i % 2 == 0) && (j % 2 == 0)) || (((i % 2 == 1) && (j % 2 ==1)))) { // check if even cell is white
                    pass = pass && (checkers.m_game[i][j] == WCELL);
                } else { // check that odd cell is either black or has a player piece
                    pass = pass && (checkers.m_game[i][j] == BCELL || BDISK || WDISK);
                } 
                track++; // increase counter
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < checkers.m_numColumns; j++) {
                if (checkers.m_game[i][j] != WCELL) { // checks the first and last three row to make sure player pieces are on them
                    pass = pass && (checkers.m_game[i][j] == WDISK);
                    pass = pass && (checkers.m_game[checkers.m_numRows - (1 + i)][checkers.m_numColumns - (1 + j)] == BDISK);
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

// according to resources I have read online, this test can not be done as when
// passing an array to a function, the array is passed as a pointer.
// So using sizeof or any other methods can not get the size of the array.
// This is why we have to pass the size of the array also to the function.
// Otherwise knowing the size of the array is not possible.
// If it is possible, please let me know how
bool Tester::testNotCorrectCellAmountSetGameState(Checkers &check) {
    bool pass = true;
    try {
        
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}










bool Tester::testNoPlayerSetGameState(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.m_currPlayer = WPLAYER;
        pass = pass && (checkers.m_currPlayer == WPLAYER);
        checkers.setGameState(game, size, NONE);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCorrectSizeSetGameState(Checkers &checkers) {
    bool pass = true;
    int row = 0;
    int column = 0;
    try {
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
        checkers.m_currPlayer = WPLAYER;
        pass = pass && (checkers.m_currPlayer == WPLAYER);
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_currPlayer == BPLAYER);
        pass = pass && ((checkers.m_numColumns == DEFBOARDSIZE) && (checkers.m_numRows == DEFBOARDSIZE) && (checkers.m_numColumns == checkers.m_numRows));
        for (int i = 0; i < size; i++) {
            row = i / checkers.m_numRows;
            column = i - (row * checkers.m_numRows);
            if (row < 3) {
                if ((((row % 2) == 0) && ((column % 2) == 0)) || (((row % 2) == 1) && ((column % 2) == 1))) {
                    pass = pass && (checkers.m_game[row][column] == WCELL);
                } else if (game[i] == "") {
                    pass = pass && (checkers.m_game[row][column] == WDISK);
                } else if (game[i] == BKING) {
                    pass = pass && (checkers.m_game[row][column] == BKING);
                } else if (game[i] == BDISK) {
                    pass = pass && (checkers.m_game[row][column] == BDISK);
                } else if (game[i] == WKING) {
                    pass = pass && (checkers.m_game[row][column] == WKING);
                } else if (game[i] == BCELL) {
                    pass = pass && (checkers.m_game[row][column] == BCELL);
                } else {
                    pass = false;
                }
            } else if (row >= (checkers.m_numRows - 3)) {
                if ((((row % 2) == 0) && ((column % 2) == 0)) || (((row % 2) == 1) && ((column % 2) == 1))) {
                    pass = pass && (checkers.m_game[row][column] == WCELL);
                } else if (game[i] == "") {
                    pass = pass && (checkers.m_game[row][column] == BDISK);
                } else if (game[i] == BKING) {
                    pass = pass && (checkers.m_game[row][column] == BKING);
                } else if (game[i] == WDISK) {
                    pass = pass && (checkers.m_game[row][column] == WDISK);
                } else if (game[i] == WKING) {
                    pass = pass && (checkers.m_game[row][column] == WKING);
                } else if (game[i] == BCELL) {
                    pass = pass && (checkers.m_game[row][column] == BCELL);
                } else {
                    pass = false;
                }
            } else {
                if (((((row % 2) == 0) && ((column % 2) == 0)) || ((((row % 2) == 1)) && ((column % 2) == 1))) && (game[i] == "")) {
                    pass = pass && (checkers.m_game[row][column] == WCELL);
                } else if (game[i] == "") {
                    pass = pass && (checkers.m_game[row][column] == BCELL);
                } else if (game[i] == BKING) {
                    pass = pass && (checkers.m_game[row][column] == BKING);
                } else if (game[i] == BDISK) {
                    pass = pass && (checkers.m_game[row][column] == BDISK);
                } else if (game[i] == WKING) {
                    pass = pass && (checkers.m_game[row][column] == WKING);
                } else if (game[i] == WDISK) {
                    pass = pass && (checkers.m_game[row][column] == WDISK);
                } else {
                    pass = false;
                }
            }
        }
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testIncorrectPlayerMove(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[5][0] == BDISK);
        pass = pass && !(checkers.play(pair<int,int>(5,0), pair<int,int>(4,1)));
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testIncorrectVerticalMovePlay(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[1][6] == WDISK);
        pass = pass & !(checkers.play(pair<int,int>(1,6), pair<int, int>(2,6)));
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testIncorrectHorizontalMovePlay(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[1][6] == WDISK);
        pass = pass & !(checkers.play(pair<int,int>(1,6), pair<int, int>(1,7)));
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testIncorrectAttemptedJump(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[1][0] == WDISK);
        pass = pass && (checkers.m_game[3][2] == BCELL);
        pass = pass && !(checkers.play(pair<int,int>(1,0), pair<int, int>(3,2)));
        pass = pass && (checkers.m_game[1][0] == WDISK);
        pass = pass && (checkers.m_game[3][2] == BCELL);
        
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCorrectForwardMovementWhite(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[1][0] == WDISK);
        pass = pass && (checkers.m_game[2][1] == BCELL);
        pass = pass && (checkers.play(pair<int,int>(1,0), pair<int,int>(2,1)));
        pass = pass && (checkers.m_game[1][0] == BCELL);
        pass = pass && (checkers.m_game[2][1] == WDISK);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCorrectForwardMovementBlack(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[5][0] == BDISK);
        pass = pass && (checkers.m_game[4][1] == BCELL);
        pass = pass && (checkers.play(pair<int,int>(5,0), pair<int,int>(4,1)));
        pass = pass && (checkers.m_game[5][0] == BCELL);
        pass = pass && (checkers.m_game[4][1] == BDISK);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCorrectLeap(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[1][4] == WDISK);
        pass = pass && (checkers.m_game[2][3] == BDISK);
        pass = pass && (checkers.play(pair<int,int>(1,4),pair<int,int>(3,2)));
        pass = pass && (checkers.m_game[3][2] == WDISK);
        pass = pass && (checkers.m_game[2][3] == BCELL);
        pass = pass && (checkers.m_game[1][4] == BCELL);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testBecomingKingWhite(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[6][5] == WDISK);
        pass = pass && (checkers.m_game[7][6] == BCELL);
        pass = pass && (checkers.play(pair<int,int>(6,5), pair<int,int>(7,6)));
        pass = pass && (checkers.m_game[7][6] == WKING);
        pass = pass && (checkers.m_game[6][5] == BCELL);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testBecomingKingBlack(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", BCELL, "", "", "", "", "", "",
        "", "", BDISK, "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[1][2] == BDISK);
        pass = pass && (checkers.m_game[0][1] == BCELL);
        pass = pass && (checkers.play(pair<int,int>(1,2), pair<int,int>(0,1)));
        pass = pass && (checkers.m_game[0][1] == BKING);
        pass = pass && (checkers.m_game[1][2] == BCELL);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCorrectBackwardMovement(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BKING, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[4][3] == BKING);
        pass = pass && (checkers.play(pair<int,int>(4,3),pair<int,int>(5,2)));
        pass = pass && (checkers.m_game[5][2] == BKING);
        pass = pass && (checkers.m_game[4][3] == BCELL);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testCorrectBackwardMovementLeap(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        BKING, "", "", "", WDISK, "", WDISK, "",
        "", WKING, "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[3][0] == BKING);
        pass = pass && (checkers.m_game[4][1] == WKING);
        pass = pass && (checkers.play(pair<int,int>(3,0), pair<int,int>(5,2)));
        pass = pass && (checkers.m_game[5][2] == BKING);
        pass = pass && (checkers.m_game[4][1] == BCELL);
        pass = pass && (checkers.m_game[3][0] == BCELL);
    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testMovingToOccupiedSpce(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        BKING, "", "", "", WDISK, "", WDISK, "",
        "", WKING, "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[3][0] == BKING);
        pass = pass && (checkers.m_game[4][1] == WKING);
        pass = pass && !(checkers.play(pair<int,int>(3,0), pair<int,int>(4,1)));
        pass = pass && (checkers.m_game[3][0] == BKING);
        pass = pass && (checkers.m_game[4][1] == WKING);
    } catch(exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testMovingOutOfBounds(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        BKING, "", "", "", WDISK, "", WDISK, "",
        "", WKING, "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[3][0] == BKING);
        pass = pass && !(checkers.play(pair<int,int>(3,0), pair<int,int>(20,5)));
        pass = pass && (checkers.m_game[3][0] == BKING);
    } catch(exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testChoosingNonExistantSpace(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        BKING, "", "", "", WDISK, "", WDISK, "",
        "", WKING, "", "", "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[3][2] == BCELL);
        pass = pass && !(checkers.play(pair<int,int>(25,12), pair<int,int>(3, 2)));
        pass = pass && (checkers.m_game[3][2] == BCELL);

    } catch (exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testChoosingEmptySpace(Checkers &checkers) {
    bool pass = true;
    try {
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
        checkers.setGameState(game, size, WPLAYER);
        pass = pass && (checkers.m_game[2][1] == BCELL);
        pass = pass && (checkers.m_game[3][2] == BCELL);
        pass = pass && !(checkers.play(pair<int,int>(2,1), pair<int,int>(3,2)));
        pass = pass && (checkers.m_game[2][1] == BCELL);
        pass = pass && (checkers.m_game[3][2] == BCELL);
        
    } catch(exception &e) {
        cout << "Exception thrown" << endl;
        pass = false;
    }
    return pass;
}

bool Tester::testFailingToGoBackwards(Checkers &checkers) {
    bool pass = true;
    try {
    const int size = DEFBOARDSIZE*DEFBOARDSIZE;
    CELL game[size] = 
        {"", "", "", "", "", "", "", "",
        "", WDISK, "", "", "", "", "", "",
        "", BCELL, BCELL, BDISK, "", BCELL, "", BCELL,
        BKING, "", "", "", WDISK, "", WDISK, "",
        "", BDISK, "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", WDISK, "", "",
        "", "", "", "", "", "", BCELL, "",};
        checkers.setGameState(game, size, BPLAYER);
        pass = pass && (checkers.m_game[4][1] == BDISK);
        pass = pass && (checkers.m_game[5][2] == BCELL);
        pass = pass && !(checkers.play(pair<int,int>(4,1), pair<int,int>(5,2)));
        pass = pass && (checkers.m_game[4][1] == BDISK);
        pass = pass && (checkers.m_game[5][2] == BCELL);
    } catch(exception &e) {
        cout << "Exception thrown" << endl;
    }
    return pass;
}