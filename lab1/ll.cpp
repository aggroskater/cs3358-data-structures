/* Doubly Linked List */

#include "ll.h"
#include <iostream>
#include <string>
#include <cstdlib>

#ifndef NULL
#define NULL 0
#endif

using namespace std;

ll::ll()
{
  head = NULL;
//  tail = NULL;
}

ll::~ll()
{
  deleteListContents();
  delete head;
//  delete tail;

}

void ll::insertTail(Student* stu)
{

  /* Test if empty list */
  if (head == NULL)
  {
    node *temp = new node;
    temp->student = stu;
    temp->next = NULL;
    temp->prev = NULL;
    head = temp;
    //tail = temp;
    return;
  }

  /* add (first) to tail */
  else  
  if (head->next == NULL)
  {
    node *temp = new node;
    temp->student = stu;
    temp->next = NULL;
    temp->prev = head;
    head->next = temp;
    //tail = temp;
    return; 
  }  

  /* add to tail */
  node *temp;
  temp = head;
  while(temp->next != NULL)
  {
    temp = temp->next;
  }

  node *temp2 = new node;
  temp2->student = stu;
  temp2->prev = temp;
  temp2->next = NULL;
  temp->next = temp2;
  //tail = temp2;

  return;

}

void ll::insertHead(Student *stu)
{

  /* Test for empty list */  
  if (head == NULL)
  {
    node *temp = new node;
    temp->student = stu;
    temp->next = NULL;
    temp->prev = NULL;
    head = temp;
    //tail = temp;
    return;
  }

  /* If list isn't empty, do this */
  else
  {
    node *temp = new node;
    temp->student = stu;
    head->prev = temp;
    temp->next = head;
    temp->prev = NULL;
    head = temp;
  }

}

void ll::insert(Student* stu,int slot)
{

  /* Test if empty list */
  if (head == NULL)
  {
    node *temp = new node;
    temp->student = stu;
    temp->next = NULL;
    temp->prev = NULL;
    head = temp;
    //tail = temp;
    return;
  }

  if (slot == 1)
  {
    insertHead(stu);
    return;
  }

  /* Cycle through 'til we get to the slot */
  int i = 1;
  node *temp;
  temp = head;

  while(temp != NULL && i < slot)
  {
    i++;
    temp = temp->next;
  }

  /* temp is now pointing at the slot we wish to insert at ideally*/

  /* Test if the slot the user asked for exists */
  if( i < slot)
  {
    insertTail(stu);
    return;
  }

  node *add = new node;
  add->student = stu;
  add->next = temp;
  add->prev = temp->prev; 

  /* Now update other elements */ 

  temp->prev->next = add;
  temp->prev = add; 

}

void ll::deleteListContents()
{
  
 
  if(head == NULL)
  {
    return;
    /* What if head get's set to NULL inappropriately? Then
     * memory still isn't free'd and we can't get to it!
     * Gotta make sure that doesn't happen.
     */
  }
 
  node *temp;

  while(head->next != NULL) 
  {
   
    temp = head->next;
    head->next = temp->next;
    delete temp;
    
  }


  delete head;
  head = NULL;
 
 
  /* Don't need to delete tail. We deleted its contents in the while loop
   * above
   */

//  tail = NULL;

}

void ll::sortByName()
{


}

void ll::sortById()
{

  if(head == NULL)
  {
    return;
  }
  else
  if(head->next == NULL)
  {
    return;
  }

  node* i;
  node* l;
  node* p;

  i = head;
  l = i;
  p = i->next;  

  short flag = 0; 

  while(p != NULL)
  {
   
    string temp1 = i->student->getId();
    int temp1i = atoi(temp1.c_str());


    while(p != NULL)
    {
      string temp2 = p->student->getId(); 
      int temp2i = atoi(temp2.c_str());
      string temp3 = l->student->getId();
      int temp3i = atoi(temp3.c_str());

      if(temp2i < temp1i && temp2i < temp3i)
      {
        l = p;
      }

      p = p->next;
    }


    if(flag == 0)
    {
      head = l;
      flag++;
    }

    /* If l and i are right next to each other, then l->prev->next breaks.
     * Heck, if i and l are equal, this breaks.
     */

    /* i IS l ; this iteration is already sorted. Carry on.*/
    if(l == i)
    {
      i = i->next;
      l = i;
      p = i->next;
      continue;
    }

    /* l and i right next to each other */
    if(l->prev == i && ( l->student->getId() < l->prev->student->getId() ))
    {
      
      if(l->next != NULL)
      {
        l->next->prev = i;
      }

      if(i->prev != NULL)
      {
        i->prev->next = l;
      }

      /* Forgot about adding iteration code */
      node* nextIndex;
      nextIndex = i->next;

      i->next = l->next;
      l->next = i;

      node* iprev;
      iprev = i->prev;

      i->prev = l;
      l->prev = iprev;

      /* Forgot to include iteration in this case */

      i = nextIndex;
      l = i;
      p = i->next;

      continue;
    }

    /* l and i are separated by at least one node */
    
    l->prev->next = i;
    
    if(l->next != NULL)
    {
      l->next->prev = i;
    }
    
    if(i->prev != NULL)
    {
      i->prev->next = l;
    }
    i->next->prev = l;

    node* t1;
    node* t2;

    t1 = l->next;
    t2 = l->prev;

    l->next = i->next;
    l->prev = i->prev;

    node* nextIndex;
    nextIndex = i->next;

    i->next = t1;
    i->prev = t2;

    i = nextIndex;
    l = i;
    p = i->next;


  }

}

void ll::displayContents()
{

  node *temp;
  temp = head;
  
 
  while(temp != NULL)
  {
    temp->student->display();
    temp = temp->next;
  }


}

