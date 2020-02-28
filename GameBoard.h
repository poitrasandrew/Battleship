/*
 * GameBoard header file
 * creates and uses game board in command line
 * stores hits and misses and shows players what has happened in game
 */

/* 
 * File:   GameBoard.h
 * Author: Drew
 *
 * Created on October 24, 2017, 12:28 AM
 */

#include "Ship.h"

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

class GameBoard
{
private:
    char positions[10][10]; //holds the hit miss or empty spaces for the board
    
public:
    GameBoard(); //creates game board and sets every position to a blank space
    void printBoard(); //prints out the board with all hits, mises, and empty spaces
    void markBoard(int, int, Ship&); //takes a position and marks the spot on the board as a hit or miss
    bool checkShot(int, int); //checks if spot has been shot at already
    
};

#endif /* GAMEBOARD_H */