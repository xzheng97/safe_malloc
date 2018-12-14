////////////////////////////////////////////////////////////////////////////////
// Main File:        testcases
// This File:        linkedlist.c
// Other Files:      537malloc.c 537malloc.h range_tree.c range_tree.h
//                   linkedlist.h
// Semester:         CS 537 Fall 2018
//
// Author:           Youmin Han
// Email:            youmin.han@wisc.edu
// CS Login:         youmin
//
// Author:           Xianjie Zheng
// Email:            xzheng97@wisc.edu
// CS Login:         xianjie
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          NULL
//
// Online sources:   NULL
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * Function that adds a new node at the end of a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * newdata: new data that will be saved into the linked list
 */
void append(struct LinklistNode** headref, void* newdata)
{
    struct LinklistNode* newnode = (struct LinklistNode*) malloc(sizeof(struct LinklistNode));

    struct LinklistNode* last = *headref;

    newnode->data = newdata;
    newnode->next = NULL;

    // case when there is no node in the linked list yet
    if (*headref == NULL)
    {
        *headref = newnode;
        return;
    }
    // otherwise, append a new node to the end of the linked list
    while (last->next != NULL){
        last = last->next;
    }
    last->next = newnode;
    return;
}


/*
 * Function that removes the last node in a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * newdata: new data that will be saved into the linked list
 */
void removelastnode (struct LinklistNode** headref)
{

    struct LinklistNode* temp = *headref;
    struct LinklistNode* t = NULL;

    // case when there is no node in the linked list yet
    if (temp == NULL)
    {
        return;
    }
    else if(temp->next == NULL) {
        free(temp);
        temp = NULL;
    }
    // otherwise, append a new node to the end of the linked list
    else {
        while (temp->next != NULL){
            t = temp;
            temp = temp->next;
        }
        free(t->next);
        t->next = NULL;
    }
}

/*
 * Function that counts the size of a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 */
int getsize(struct LinklistNode** headref)
{
    struct LinklistNode* cursor = *headref;
    int counter = 0;
    // traverse the linked list and count the size
    while(cursor != NULL)
    {
        counter++;
        cursor = cursor->next;
    }
    return counter;
}

/*
 * Function that grab the data stored in a linked list with specific location
 *
 * @param
 * headref: a reference to the head of the linked likst
 * index: the location of the data in the linked list
 */
void* getnodedata(struct LinklistNode** headref,int index)
{
    if(*headref == NULL)
    return NULL;
    struct LinklistNode *cursor = *headref;
    for(int i=0; i<index; i++)
    {
        if(cursor->next == NULL){
            return NULL;
        }
        cursor = cursor->next;
    }
    return (void *)cursor->data;
}

/*
 * Function that grab a node with specific location in a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * index: the location of the node in the linked list
 */
struct LinklistNode* getnode(struct LinklistNode** headref,int index)
{
    if(*headref == NULL)
    return NULL;
    struct LinklistNode *cursor = *headref;
    for(int i=0; i<index; i++)
    {
        if(cursor->next == NULL){
            return NULL;
        }
        cursor = cursor->next;
    }
    return cursor;
}
