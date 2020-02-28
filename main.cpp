/*
 * Main file for battleship game
 * execute the game and create dialog for players to follow
 * include the gameboard and tree headers and all others will follow
 */

/* 
 * File:   main.cpp
 * Author: Drew
 *
 * Created on October 23, 2017, 9:10 PM
 */

#include <cstdlib>
#include <ctime>

#include "GameBoard.h"
#include "Tree.h"

using namespace std;

int hashed(int); //simple hashing function
void sortShips(Ship[], int); //recursively sorts the ship array from largest
                             //to smallest

/*
 * 
 */
int main(int argc, char** argv) 
{
    //Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    //create temp variables
    int xPos;
    int yPos;
    int shipNum;
    
    //variables used for direction of random ship placement
    char direction[4] = {'n','s','e','w'};
    char dir;
    
    Position tempPos;//used to hash ship positions into array of linked lists
    
    int turnNum = 0;//holds number of turns until game over to save score
    
    LinkedList<Position> positions[20];//hashing table used to make searching
                                       //faster
    
    //variables used to control game looping
    bool gameOver = false;
    bool endTurn = false;
    
    //create ships
    Ship ships[5];//holds each ship in the game
    ships[0] = Ship("carrier");
    ships[1] = Ship("battleship");
    ships[2] = Ship("cruiser");
    ships[3] = Ship("submarine");
    ships[4] = Ship("destroyer");
    
    GameBoard *board = new GameBoard();//holds the game board with each
                                       //hit and miss
    
    //set ships in random positions and hash positions into array
    for (int i = 0; i < 5; i++)
    {
        do
        {
            xPos = (rand() % 10) + 1;
            yPos = (rand() % 10) + 1;
            dir = rand() % 4;
            //ships[i].placeShip(xPos, yPos, direction[0], ships);
        } while(!ships[i].placeShip(xPos, yPos, direction[dir], ships));
        cout << xPos << " " << yPos << " " << direction[dir] << endl;//TEST
        for (int j = 0; j < ships[i].getSize(); j++)//hash new positions into position array
        {
            if (direction[dir] == 'n')//for north placement
            {
                positions[hashed(xPos*(yPos + j))].addEnd(Position(xPos, yPos + j, false));
            }
            if (direction[dir] == 's')//for south placement
            {
                positions[hashed(xPos*(yPos - j))].addEnd(Position(xPos, yPos - j, false));
            }
            if (direction[dir] == 'e')//for east placement
            {
                positions[hashed((xPos + j)*yPos)].addEnd(Position(xPos + j, yPos, false));
            }
            if (direction[dir] == 'w')//for west placement
            {
                positions[hashed((xPos - j)*yPos)].addEnd(Position(xPos - j, yPos, false));
            }
        }
    }
    
    
    board->printBoard();//prints board for player to see
    //have player make turns until all ships are destroyed
    while (!gameOver) 
    {
        turnNum++;//increment to hold number of turns
        endTurn = false;
        cout << "Make a turn.\n";
        while (!endTurn)
        {
            cout << "Enter the x coordinate you would like to attack: ";
            cin >> xPos;
            tempPos.setXPos(xPos);
            cout << "Enter the y coordinate you would like to attack: ";
            cin >> yPos;
            tempPos.setYPos(yPos);//sets tempPos to search through hash table
            if (board->checkShot(xPos, yPos))//checks if shot was valid on the board
            {
                endTurn = true;
                if (positions[hashed(xPos*yPos)].findLst(tempPos) != 0)//quickly check if shot is on a ship using hash table
                {
                    for (int i = 0; i < 5; i++)
                    {
                        if (ships[i].checkFirst(xPos, yPos))//goes through ships and positions and adjusts which position was hit
                        {
                            shipNum = i;//holds position of ship that was hit to mark the board later
                        }
                    }
                }
            }
        }
        board->markBoard(xPos, yPos, ships[shipNum]);//marks the board and displays if shot was a hit or miss
        board->printBoard();
        sortShips(ships, 5);//uses the recursive sort to sort the ships by size to make the shot checks faster
        //check if ships are destroyed
        for (int i = 0; i < 5; i++)
        {
            cout << "The " ;
            if (ships[i].shipDestroyed())
            {
                cout << ships[i].getType() << " is sunk.\n";
            }
            else if (!ships[i].shipDestroyed())
            {
                cout << ships[i].getType() << " is afloat.\n";
            }
        }
        //check if the first ship in the array is destroyed
        //first ship should be the largest ship after each sort
        if (ships[0].shipDestroyed())
        {
           gameOver = true;
        }
    }
    
    //print out winner
    cout << "YOU WIN!!\n\nGAME OVER\n\n";
    cout << "It took you " << turnNum << " turns to finish the game!\n\n";
    Tree scores(turnNum);
    
    return 0;
}

//simple hashing function to use for ship array
int hashed(int x)
{
    return x % 20;
}

//simple recursive sort to sort ship array from largest to smallest
void sortShips(Ship ships[], int size)
{
    Ship temp;
    if (size == 1)
    {
        return;
    }
    for (int i = 0; i < size - 1; i++)
    {
        if (ships[i].getSize() < ships[i+1].getSize())//checks for swap
        {
            temp = ships[i];
            ships[i] = ships[i + 1];
            ships[i + 1] = temp;
        }
    }
    sortShips(ships, size - 1);//recursive function call
}