/*
 * Position source file
 * Create position class that will be used as links for linked list
 * holds positions of ship and whether they've been hit or not
 */

#include "Position.h"

//constructor sets values to defaults
Position::Position() 
{
    xPos = 0;
    yPos = 0;
    hit = false;
}

//overloaded constructor sets specified values
Position::Position(int x, int y, bool hit)
{
    xPos = x;
    yPos = y;
    this->hit = hit;
}

//overloads compare operator in order to work properly in the linked list find functions
bool Position::operator==(const Position & pos) 
{
    //checks each variable as comparison to the data in the linked list
    if (pos.xPos == this->xPos && pos.yPos == this->yPos && pos.hit == this->hit) 
    {
        //return true if data matches
        return true;
    }
    else 
    {
        //return false if data doesn't match
        return false;
    }
}

//getter for yPos variable
int Position::getYPos() 
{
    return yPos;
} 

//setter for yPos
void Position::setYPos(int y) 
{
    yPos = y;
}

//getter for xPos
int Position::getXPos() 
{
    return xPos;
}

//setter for xPos
void Position::setXPos(int x) 
{
    xPos = x;
}

//getter for hit
bool Position::getHit() 
{
    return hit;
}

//setter for hit
void Position::setHit(bool hit) 
{
    this->hit = hit;
}
   
//changes hit to true when a position gets hit
void Position::spotHit() 
{
    hit = true;
}