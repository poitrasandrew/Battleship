/*
 * Ship source file
 * used for ship objects, can be used as template for new ship types if needed
 * holds size of ship and linked list of its positions
 */

#include "Ship.h"
#include <cstdlib>

using namespace std;

Ship::Ship()//default constructor does nothing
{
    Position position;
    list = new LinkedList<Position>(position);
}

//constructor takes the type of ship and creates it with the correct size
Ship::Ship (string type) 
{
    Position position;
    list = new LinkedList<Position>(position);
    this->type = type;
    if (type == "carrier") 
    {
        size = 5;
    }
    if (type == "battleship")
    {
        size = 4;
    }
    if (type == "cruiser")
    {
        size = 3;
    }
    if (type == "submarine")
    {
        size = 3;
    }
    if (type == "destroyer")
    {
        size = 2;
    }
}

// checks if a shot is on the ship or not
bool Ship::checkFirst(int xPos, int yPos) 
{
    //create a temporary position
    Position* temp = new Position();
    //set positions for temp
    temp->setXPos(xPos);
    temp->setYPos(yPos);
    //check if position is part of the ship and return true if it is and delete the link
    if (this->list->findLst(*temp) != 0) 
    {
        return true;
    }
    //return false if the position is not apart of the ship
    else 
    {
        return false;
    }
}

//function checks the position that the player wants to shoot at to see if its part of the ship and changes data if it is
bool Ship::checkShot(int xPos, int yPos) 
{
    //create a temporary position
    Position* temp = new Position();
    //set positions for temp
    temp->setXPos(xPos);
    temp->setYPos(yPos);
    //check if position is part of the ship and return true if it is and delete the link
    if (this->list->findLst(*temp) != 0) 
    {
        this->list->dltList(*temp);
        size--;
        return true;
    }
    //return false if the position is not apart of the ship
    else 
    {
        return false;
    }
}

//sets the coordinates for the ship list and checks that they are valid coordinates
bool Ship::placeShip(int xPos, int yPos, char direction, Ship ships[5]) 
{
    //create temp and counter variables
    int counter = 1;
    Position* temp = new Position();
    Position* temp2 = new Position();
    LinkedList<Position> *tempList = new LinkedList<Position>(*temp);
    
    //set up x and y for the temp position
    temp->setXPos(xPos);
    temp->setYPos(yPos);
    //check that front of ship is within the bounds of the game board
    if (xPos <= 10 && xPos >= 1 && yPos <=10 &&yPos >= 1) 
    {
        //if player chose north, check that the ships positions will be valid when the rest of the ship is placed
        if (tolower(direction) == 'n' && yPos <= 10 - size) 
        {
            //check that spaces aren't occupied by other ships
            for (int i = 0; i < 5; i++)
            {
                *tempList = ships[i].getList();
                for (int j = 0; j < size; j++)
                {
                    temp2->setXPos(xPos);
                    temp2->setYPos(yPos + j);
                    if (tempList->findLst(*temp2) != 0)
                    {
                        return false;
                    }
                }
            }
            //create ship list with front in the chosen spot
            list = new LinkedList<Position>(*temp);
            //fill ship list with the trailing positions of the ship
            while (counter < size)
            {
                temp->setXPos(xPos);
                temp->setYPos(yPos + counter);
                list->addEnd(*temp);
                counter++;
            }
            //exit true
            return true;
        }
        //check for southern placement and valid positions
        else if (tolower(direction) == 's' && yPos >= size) 
        {
            //check that spaces aren't occupied by other ships
            for (int i = 0; i < 5; i++)
            {
                *tempList = ships[i].getList();
                for (int j = 0; j < size; j++)
                {
                    temp2->setXPos(xPos);
                    temp2->setYPos(yPos - j);
                    if (tempList->findLst(*temp2) != 0)
                    {
                        return false;
                    }
                }
            }
            //create ship list with front position
            list = new LinkedList<Position>(*temp);
            //fill ship list with trailing spots in south direction
            while (counter < size)
            {
                temp->setXPos(xPos);
                temp->setYPos(yPos - counter);
                list->addEnd(*temp);
                counter++;
            }
            //exit true
            return true;
        }
        //check for easter placement and valid positions
        else if (tolower(direction) == 'e' && xPos <= 10 - size) 
        {
            //check that spaces aren't occupied by other ships
            for (int i = 0; i < 5; i++)
            {
                *tempList = ships[i].getList();
                for (int j = 0; j < size; j++)
                {
                    temp2->setXPos(xPos + j);
                    temp2->setYPos(yPos);
                    if (tempList->findLst(*temp2) != 0)
                    {
                        return false;
                    }
                }
            }
            //create ship list with front position
            list = new LinkedList<Position>(*temp);
            //fill ship list with trailing positions in east direction
            while (counter < size)
            {
                temp->setXPos(xPos + counter);
                temp->setYPos(yPos);
                list->addEnd(*temp);
                counter++;
            }
            //exit true
            return true;
        }
        //check for western placement and valid positions
        else if (tolower(direction) == 'w' && xPos >= size) 
        {
            //check that spaces aren't occupied by other ships
            for (int i = 0; i < 5; i++)
            {
                *tempList = ships[i].getList();
                for (int j = 0; j < size; j++)
                {
                    temp2->setXPos(xPos - j);
                    temp2->setYPos(yPos);
                    if (tempList->findLst(*temp2) != 0)
                    {
                        return false;
                    }
                }
            }
            //create ship list with front position
            list = new LinkedList<Position>(*temp);
            //fill ship list with trailing positions in west direction
            while (counter < size)
            {
                temp->setXPos(xPos - counter);
                temp->setYPos(yPos);
                list->addEnd(*temp);
                counter++;
            }
            //exit true
            return true;
        }
    }
    //exit false if not a valid placement
    return false;
}

//check if the ship has been destroyed or not
bool Ship::shipDestroyed()
{
    //check if list has anymore links
    if (size == 0)
    {
        //return true if no more links
        return true;
    }
    else 
    {
        //return false if links exist still
        return false;
    }
}