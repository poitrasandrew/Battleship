/*
 * GameBoard source file
 * creates and uses game board in command line
 * stores hits and misses and shows players what has happened in game
 */

#include "GameBoard.h"

using namespace std;

//constructor for gameboard sets all valid spaces as blank
GameBoard::GameBoard()
{
    //loop through making every space blank
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            positions[i][j] = '_';
        }
    }
}

//prints board with all hits misses and blank spaces
void GameBoard::printBoard() 
{
    //print top line of board
    cout << "   _______________________________________ \n";
    //print y axis 10 because it takes two spaces instead of one
    cout << "10|";
    //loop through top row printing the board and hits, misses, and blanks
    for (int i = 0; i < 10; i++) 
    {
        cout << "_" << positions [i][9] << "_|";
    }
    cout << endl;
    //loop through to print rest of the rows
    for (int i = 8; i >= 0; i--) 
    {
        //prints the left edge of board and y axis positions
        cout << i + 1 << " |";
        for (int j = 0; j < 10; j++) 
        {
            //prints the row with correct markers in spaces
            cout << "_" << positions[j][i] << "_|";
        }
        cout << endl;
    }
    //print bottom of board with x axis positions
    cout << "    1   2   3   4   5   6   7   8   9  10  \n\n";
}

//marks the board with hits or misses
void GameBoard::markBoard(int x, int y, Ship& ship) 
{
    //checks if the space has been shot at before
    if (checkShot(x, y)) 
    {
        //checks if the space is part of a ship
        if (ship.checkShot(x, y)) 
        {
            //if part of a ship then mark a hit
            positions[x - 1][y - 1] = 'H';
            cout << "Hit!\n";
        }
        else 
        {
            //if not part of a ship then mark a miss
            positions[x - 1][y - 1] = 'M';
            cout << "Miss.\n";
        }
    }
}

//checks if spot on board has been shot already
bool GameBoard::checkShot(int x, int y) 
{
    //checks for the blank space
    if (positions[x - 1][y - 1] == '_') 
    {
        //return true if there is a blank space
        return true;
    }
    else 
    {
        //return false if not a blank space
        return false;
    }
}