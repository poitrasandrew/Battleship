/*
 * Position header file
 * Create position class that will be used as links for linked list
 * holds positions of ship and whether they've been hit or not
 */

/* 
 * File:   Position.h
 * Author: Drew
 *
 * Created on October 23, 2017, 9:58 PM
 */

#ifndef POSITION_H
#define POSITION_H

class Position 
{
private:
    int yPos; //holds y value of position as integer
    int xPos; //holds x value of position as character
    bool hit; //holds whether or not position has been hit or not
    
public:
    Position(); //creates position with x and y and begins with hit as false
    Position(int, int, bool); //creates position with chosen x, y, and hit values
    bool operator==(const Position&); //overload comparative operator to work with linked list implementation
    //getters and setters
    int getYPos();
    void setYPos(int);
    int getXPos();
    void setXPos(int);
    bool getHit();
    void setHit(bool hit);
    void spotHit(); //sets hit to true, used for when a shot lands
};

#endif /* POSITION_H */