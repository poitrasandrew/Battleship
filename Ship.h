/*
 * Ship header file
 * used for ship objects, can be used as template for new ship types if needed
 * holds size of ship and linked list of its positions
 */

/* 
 * File:   Ship.h
 * Author: Drew
 *
 * Created on October 23, 2017, 9:14 PM
 */

#include "Position.h"
#include "LinkedList.h"

#ifndef SHIP_H
#define SHIP_H

class Ship 
{
private:
    LinkedList<Position> *list; //holds positions of ship as linked list
    int size; //holds size of the ship
    string type; //holds the type of ship ex:battleship, cruiser,...
    
public:
    Ship(string); //creates ship with specified size
    Ship();
    bool checkFirst(int, int); //checks if shot was a hit or not
    bool checkShot(int, int); //checks if shot hit the ship in a valid spot or not and changes data accordingly
    bool placeShip(int, int, char, Ship[5]); //places front of ship on position and sets rest of ship in specified direction ex: 1, 5, n. returns true if valid
    bool shipDestroyed(); //check if the ship is destroyed or not
    bool checkPlace();
    LinkedList<Position> getList() {return *list;}
    int getSize() {return size;}
    string getType() {return type;}
};

#endif /* SHIP_H */