/*
 * Linked List Header
 * Create template for linked list implementation
 * use to store ship data in battleship game
 */

/* 
 * File:   LinkedList.h
 * Author: Drew
 *
 * Created on October 23, 2017, 9:13 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<class T>
class LinkedList 
{
private:
	struct Link 
        {
		T data;
		Link *next, *prev;  //next and previous references which when utilized forms a linked list
	};
	Link *front, *temp, *iterate, *end, *found;//Permanent and Temp pointers
	void endLst();          //Find the end of the list
        void frontLst();        //Find the front of the list
	void fndLst(const T&);  //Determine address of link that contains the data
public:
        LinkedList();
	LinkedList(const T&);
	~LinkedList();
	void prntLst();           //Print each data element in the list
	void  addEnd(const T&); //Add data at the end of the list
	void addBegn(const T&); //Add data at the beginning of the list
	void addBefr(const T&, const T&); //Add data before an element in the list
	void addAftr(const T&, const T&); //Add data after an element in the list
	void dltList(const T&); //Delete data from the list
	int  findLst(const T&); //Determine what link contains the data
	int   cntLst();           //How many elements are in the list
        T  getData(int);        //Return the data
};

#endif /* LINKEDLIST_H */

template<class T>
LinkedList<T>::LinkedList()
{
    front = new Link;
    front->next = NULL; //At the moment not pointing it to anything
    front->prev = NULL;
}

template<class T>
LinkedList<T>::LinkedList(const T &data) 
{
	front = new Link;      //Allocate a link at the front of the list
	front->data = data;    //Initialize with data
	front->next = NULL; //At the moment not pointing it to anything
        front->prev = NULL;
}

template<class T>
LinkedList<T>::~LinkedList()
{
//    endLst();
//    do
//    {
//       temp=end->prev;   //Point to the next link in the list
//       delete end;          //Delete the front of the list
//       end=temp;            //Swap the front
//    }while(end!=NULL);
}

template<class T>
void LinkedList<T>::endLst()
{
    temp=front; //Declare pointers used to step through the list
    do
    {
        end=temp;          //Point to the current link with a swap
        temp=temp->next; //Point to the next link
    }while(temp!=NULL);     //Your done when you hit the end
}

template<class T>
void LinkedList<T>::frontLst() 
{
    endLst();
    temp = end;
    do 
    {
        front = temp;
        temp = temp->prev;
    }while(temp != NULL);
}

template<class T>
void LinkedList<T>::fndLst(const T& value)
{
    int n=0;                //Initialize the counter
    temp=front;             //Prepare to traverse the Link<Object>ed list
    do
    {
        n++;                //Increment the counter
        if(temp->data==value)
        {
           return;//Return where the data is found 
        }
        temp=temp->next; //Move to the next link
    }while(temp!=NULL);     //End when reaching the end of the linked list
    return;
}

template<class T>
void LinkedList<T>::prntLst()
{
    iterate=front;           //Create a pointer to the list
    cout<<endl<<"The Beginning of the List"<<endl;
    do
    {
        cout<<iterate->data<<endl; //Print the contents of the link
        iterate=iterate->next;     //Go to the next link in the list
    }while(iterate != NULL);         //Loop until reaching the end
    cout<<"The End of the List"<<endl<<endl;
}

template<class T>
void LinkedList<T>::addEnd(const T& data)
{
    endLst();  //Find the last link
    Link *add=new Link;        //Create the new link
    add->data=data;            //Add the data
    add->next=NULL;            //Set the pointer to NULL
    add->prev = end;
    end->next = add;          //Point to the new end of the list
}

template<class T>
void LinkedList<T>::addBegn(const T& data)
{
    Link *add = new Link; //create new link
    add->data = data; //add data
    add->next = front; //set next as the current front
    add->prev = NULL; //set previous pointer as null
    front->prev = add; //change previous pointer of the current front
    front = add; //set front to the new link
}

template<class T>
void LinkedList<T>::addBefr(const T& data, const T& id)
{
    //check list for correct id
    if (findLst(id) != 0) 
    {
        fndLst(id); //set temp to link with correct id
        Link *add = new Link; //create new link
        add->data = data; //add data
        //position new link before the temp
        add->next = temp;
        //check if temp is the front
        if (temp->prev != NULL)
        {
            //if not front then set the new link in between the temp and its previous link
            add->prev = temp->prev;
            temp->prev->next = add;
        }
        else 
        {
            //if front then set new link with null previous link
            add->prev = NULL;
        }
        //set new link as previous link for temp
        temp->prev = add;
        //set the new front link in the list
        frontLst();
    }
}

template<class T>
void LinkedList<T>::addAftr(const T& data, const T& id)
{
    //check list for correct id
    if (findLst(id) != 0) 
    {
        fndLst(id); //set temp as the id
        Link *add = new Link; //create new link
        add->data = data; //add data
        add->prev = temp; //set new link's previous link as the temp
        //check if end of list
        if (temp->next != NULL)
        {
            //if not end of list then place the new link correctly
            add->next = temp->next;
            temp->next->prev = add;
        }
        else 
        {
            //if end of list then set next link as null for new link
            add->next = NULL;
        }
        //set next link for temp as the new link
        temp->next = add;
        //find the new end of list
        endLst();
    }
}

template<class T>
void LinkedList<T>::dltList(const T& id)
{
    //search for correct id in list
    if (findLst(id) != 0)
    {
        //set temp to be placed at the id
        fndLst(id);
        Link *del = new Link;//create new link
        del = temp; //set new link equal to temp
        //check if link is at end of list
        if (temp->next != NULL)
        {
            //if not at end of list then pull temp out of list
            temp->next->prev = temp->prev;
        }
        else if (temp->prev != NULL)
        {
            //if at end of list then pull temp out of list
            temp->prev->next = NULL;
        }
        //check if temp is at beginning of list
        if (temp->prev != NULL) 
        {
            //if not at the beginning then pull out of list
            temp->prev->next = temp->next;
        }
        else if(temp->next != NULL)
        {
            //if at beginning then pull out in different way
            temp->next->prev = NULL;
        }
        endLst(); //find new end of list
        frontLst(); //find new front of list
        delete del; //delete the chosen link
    }
}

template<class T>
int  LinkedList<T>::findLst(const T& value)
{
    int n=0;                //Initialize the counter
    temp=front;             //Prepare to traverse the Link<Object>ed list
    do
    {
        n++;                //Increment the counter
        if(temp->data==value)
        {
            return n;//Return where the data is found
        }
        temp=temp->next; //Move to the next link
    }while(temp!=NULL);     //End when reaching the end of the linked list
    return 0;               //Not found then return a 0;
}

template<class T>
int  LinkedList<T>::cntLst()
{
    int n=0;            //Initialize the counter
    temp=front;   //Set the cursor to the front
    while(temp!=NULL) //Loop until the end is reached
    {
        n++;            //Increment the counter
        temp=temp->next;//Move to the next link
    }
    return n;           //Return the counter value
}

template<class T>
T LinkedList<T>::getData(int id) 
{
    int n=0;                      //Initialize the counter
    temp=front;                   //Set the cursor to the front
    do
    {
        if(n==id)return temp->data;
        n++;                      //Increment the counter
        temp=temp->next;       //Move to the next link
    }while(temp!=NULL);           //Loop until the end is reached
    return front->data;           //Return the counter value
}