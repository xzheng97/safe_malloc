////////////////////////////////////////////////////////////////////////////////
// Main File:        testcases
// This File:        linkedlist.h
// Other Files:      537malloc.c 537malloc.h range_tree.c range_tree.h
//                   linkedlist.c
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

#ifndef linkedlist_h
#define linkedlist_h

#include <stdio.h>

struct LinklistNode {
    void* data;
    struct LinklistNode* next;
};

/*
 * Function that adds a new node at the end of a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * newdata: new data that will be saved into the linked list
 */
void append(struct LinklistNode** headref, void* newdata);
/*
 * Function that removes the last node in a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * newdata: new data that will be saved into the linked list
 */
void removelastnode (struct LinklistNode** headref);
/*
 * Function that counts the size of a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 */
int getsize(struct LinklistNode** headref);
/*
 * Function that grab the data stored in a linked list with specific location
 *
 * @param
 * headref: a reference to the head of the linked likst
 * index: the location of the data in the linked list
 */
void* getnodedata(struct LinklistNode** headref,int index);
/*
 * Function that grab a node with specific location in a linked list
 *
 * @param
 * headref: a reference to the head of the linked likst
 * index: the location of the node in the linked list
 */
struct LinklistNode* getnode(struct LinklistNode** headref,int index);


#endif /* linkedlist_h */
