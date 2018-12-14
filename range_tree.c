////////////////////////////////////////////////////////////////////////////////
// Main File:        testcases
// This File:        range_tree.c
// Other Files:      537malloc.c 537malloc.h range_tree.h
//                   linkedlist.c linkedlist.h
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
// Online sources:  Red Black Tree Algorithms
//                  https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
//                  https://towardsdatascience.com/red-black-binary-tree-maintaining-balance-e342f5aa6f5
//                  https://github.com/amitbansal7/Data-Structures-and-Algorithms/edit/master/9.Red-Black-tree/RedBlackTrees.c
//                  https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
//                  https://www.cs.auckland.ac.nz/software/AlgAnim/red_black.html
//
//
//////////////////////////// 80 columns wide ///////////////////////////////////

#include "range_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include "linkedlist.h"
#define LEFT 0
#define RIGHT 1

/*
 * Add the node to tree
 *
 * @param root: the root of the tree
 *        inputaddr: the starting addr
 *        data: the size of memory added
 */
void addnode(struct treenode** root,void* inputaddr, size_t data)
{
  if(!(*root)) {
      (*root) = (struct treenode*)malloc(sizeof(struct treenode));
      (*root)->red = 0;
      (*root)->addr = inputaddr;
      (*root)->len = data;
      (*root)->free = 0;

  }else{
    struct treenode* newnode = (struct treenode*)malloc(sizeof(struct treenode));
    newnode->len = data;
    newnode->addr = inputaddr;
    newnode->children[LEFT] = NULL;
    newnode->children[RIGHT] = NULL;
    newnode->parent = NULL;
    newnode->red = 1;

    struct treenode* temp = NULL;
    struct treenode* temproot = *root;//root

    while(temproot!=NULL)
    {
        temp = temproot;
        if(newnode->addr < temproot->addr)
            temproot = temproot->children[LEFT];

        else
            temproot = temproot->children[RIGHT];
    }
    newnode->parent = temp;

    if(temp==NULL){
        *root = newnode;
    }
    else if(newnode->addr < temp->addr){
      temp->children[LEFT] = newnode;
    }
    else{
      temp->children[RIGHT] = newnode;
    }
    RB_insert_fixup(root,&newnode);
  }
}

/*
 * After adding the node, restructure the tree
 *
 * @param root: the root of the tree
 *        fixnode: the node that added
 */
void RB_insert_fixup(struct treenode** root, struct treenode** fixnode)
{
    struct treenode* grandparent = NULL;
    struct treenode* parentpt = NULL;

    while(((*fixnode)!=*root) && ((*fixnode)->red == 1) && ((*fixnode)->parent->red == 1))
    {
        parentpt = (*fixnode)->parent;
        grandparent = (*fixnode)->parent->parent;

        if(parentpt == grandparent->children[LEFT])
        {
            struct treenode* uncle = grandparent->children[RIGHT];

            if(uncle!=NULL && uncle->red == 1)
            {
                grandparent->red = 1;
                parentpt->red = 0;
                uncle->red = 0;
                *fixnode = grandparent;
            }

            else
            {
                if((*fixnode) == parentpt->children[RIGHT])
                {
                    LeftRotate(root,&parentpt);
                    (*fixnode) = parentpt;
                    parentpt = (*fixnode)->parent;
                }

                RightRotate(root,&grandparent);
                parentpt->red = 0;
                grandparent->red = 1;
                (*fixnode) = parentpt;
            }
        }

        else
        {
            struct treenode* uncle = grandparent->children[LEFT];

            if(uncle!=NULL && uncle->red == 1)
            {
                grandparent->red = 1;
                parentpt->red = 0;
                uncle->red = 0;
                (*fixnode) = grandparent;
            }

            else
            {
                if((*fixnode) == parentpt->children[LEFT])
                {
                    RightRotate(root,&parentpt);
                    (*fixnode) = parentpt;
                    parentpt = (*fixnode)->parent;
                }
                LeftRotate(root,&grandparent);
                parentpt->red = 0;
                grandparent->red = 1;
                (*fixnode) = parentpt;
            }
        }
    }
    (*root)->red = 0;

}

/*
 * one case of restructure
 *
 * @param root: the root of the tree
 *        leftnode: the added node
 */
void LeftRotate(struct treenode** root,struct treenode** leftnode)
{
    struct treenode* temp = (*leftnode)->children[RIGHT];
    (*leftnode)->children[RIGHT] = temp->children[LEFT];

    if(temp->children[LEFT]!=NULL)
        temp->children[LEFT]->parent = *leftnode;

    temp->parent = (*leftnode)->parent;

    if((*leftnode)->parent == NULL)
        *root = temp;

    else if(*leftnode == (*leftnode)->parent->children[LEFT])
        (*leftnode)->parent->children[LEFT] = temp;

    else
        (*leftnode)->parent->children[RIGHT] = temp;

    temp->children[LEFT] = *leftnode;

    (*leftnode)->parent = temp;

}

/*
 * one case of restructure
 *
 * @param root: the root of the tree
 *        rotatenode: the added node
 */
void RightRotate(struct treenode** root,struct treenode** rotatenode)
{
    struct treenode* temp = (*rotatenode)->children[LEFT];
    (*rotatenode)->children[LEFT] = temp->children[RIGHT];

    if(temp->children[RIGHT]!=NULL)
        temp->children[RIGHT]->parent = *rotatenode;

    temp->parent = (*rotatenode)->parent;

    if((*rotatenode)->parent==NULL)
        *root = temp;

    else if((*rotatenode)== (*rotatenode)->parent->children[LEFT])
        (*rotatenode)->parent->children[LEFT] = temp;

    else
        (*rotatenode)->parent->children[RIGHT] = temp;

    temp->children[RIGHT] = *rotatenode;
    (*rotatenode)->parent = temp;

}

/*
 * delete a node from the tree
 *
 * @param root: the root of the tree
 *        dnode: the node to be deleted
 */
void deletenode(struct treenode** root,struct treenode* dnode)
{
    struct treenode *temp = dnode;
    int color;
    color = dnode->red; // y's original color

    struct treenode* temp1;

    if(dnode->children[LEFT]==NULL )
    {
        temp1 = dnode->children[RIGHT];
        RB_transplat(root,&dnode,&(dnode->children[RIGHT]));
    }

    else if(dnode->children[RIGHT]==NULL )
    {
        temp1 = dnode->children[LEFT];
        RB_transplat(root,&dnode,&(dnode->children[LEFT]));
    }

    else
    {
        temp = Tree_minimum(dnode->children[RIGHT]);
        color = temp->red;
        temp1 = temp->children[RIGHT];

        if(temp->parent==dnode) {
            if(temp1)
            temp1->parent = temp;
        }
        else
        {
            RB_transplat(root,&temp,&(temp->children[RIGHT]));
            temp->children[RIGHT] = dnode->children[RIGHT];
            temp->children[RIGHT]->parent = temp;
        }

        RB_transplat(root,&dnode,&temp);
        temp->children[LEFT] = dnode->children[LEFT];
        temp->children[LEFT]->parent = temp;
        temp->red = dnode->red;

    }

    if(color==0) {
        if(temp1)
        RB_delete_fixup(root,&temp1);
    }
}

/*
 * reconnect after deletion
 *
 * @param root: the root of the tree
 *        uncle: the uncle of the node to be deleted
 *        sibling: the sibling of the node to be deleted
 */
void RB_transplat(struct treenode** root, struct treenode** uncle,struct treenode** sibling)
{
    if((*uncle)->parent == NULL)
        *root = *sibling;

    else if((*uncle)==(*uncle)->parent->children[LEFT])
        (*uncle)->parent->children[LEFT] = *sibling;
    else if((*uncle)==(*uncle)->parent->children[RIGHT])
        (*uncle)->parent->children[RIGHT] = *sibling;

    if((*sibling)!=NULL)
        (*sibling)->parent = (*uncle)->parent;
}

/*
 * get the leftmost node under root, used to get successor
 *
 * @param node: the root of the tree
 *
 */
struct treenode* Tree_minimum(struct treenode* node)
{
    while(node->children[LEFT]!=NULL)
        node = node->children[LEFT];

    return node;
}

/*
 * restructure the tree after deletion
 *
 * @param root: the root of the tree
 *        node: the deleted node
 */
void RB_delete_fixup(struct treenode** root, struct treenode** node)
{
    while((*node)!=(*root) && (*node) &&(*node)->red == 0)
    {
        if((*node)==(*node)->parent->children[LEFT])
        {
            struct treenode* sibling = (*node)->parent->children[RIGHT];
            // FIXED check w null
            if (!sibling)
              return;
            if(sibling->red==1)
            {
                sibling->red = 0;
                (*node)->parent->red = 0;
                LeftRotate(root,&((*node)->parent));
                sibling = (*node)->parent->children[RIGHT];
            }
            // FIXED check w, w->children null
            if (!sibling || !sibling->children[LEFT] || !sibling->children[RIGHT])
              return;
            if(sibling->children[LEFT]->red==0 && sibling->children[RIGHT]->red == 0)
            {
                sibling->red = 1;
                (*node) = (*node)->parent;
            }

            else
            {
                if(sibling->children[RIGHT]->red == 0)
                {
                    sibling->children[LEFT]->red = 0;
                    sibling->red = 1;
                    RightRotate(root,&sibling);
                    sibling = (*node)->parent->children[RIGHT];
                }

                sibling->red = (*node)->parent->red;
                (*node)->parent->red = 0;
                sibling->children[RIGHT]->red = 0;
                LeftRotate(root,&((*node)->parent));
                (*node) = *root;
            }
        }

        else
        {
            struct treenode* sibling = (*node)->parent->children[LEFT];
            // FIXED check w null
            if (!sibling)
              return;
            if(sibling->red==1)
            {
                sibling->red = 0;
                (*node)->parent->red = 0;
                RightRotate(root,&((*node)->parent));
                sibling = (*node)->parent->children[LEFT];
            }

            // FIXED check w, w->children null
            if (!sibling || !sibling->children[LEFT] || !sibling->children[RIGHT])
              return;
            if(sibling->children[RIGHT]->red==0 && sibling->children[LEFT]->red == 0)
            {
                sibling->red = 1;
                (*node) = (*node)->parent;
            }

            else
            {
                if(sibling->children[LEFT]->red == 0)
                {
                    sibling->children[RIGHT]->red = 0;
                    sibling->red = 1;
                    LeftRotate(root,&sibling);
                    sibling = (*node)->parent->children[LEFT];
                }

                sibling->red = (*node)->parent->red;
                (*node)->parent->red = 0;
                sibling->children[LEFT]->red = 0;
                RightRotate(root,&((*node)->parent));
                (*node) = *root;
            }
        }
    }
    if(*node){
      (*node)->red = 0;
    }
}

/*
 * look up in the tree to find a node that has the same starting addr
 *
 * @param root: the root of the tree
 *        inputaddr: given starting addr
 *
 */
struct treenode* lookupnode(struct treenode** root, void* inputaddr) {
    struct treenode* temp = *root;
    while (temp != NULL) {
        if (temp->addr == inputaddr) {
            return temp;
        } else if (temp->addr > inputaddr) {
            temp = temp->children[LEFT];
        } else {
            temp = temp->children[RIGHT];
        }
    }
    return temp;
}

/*
 * look up in the tree to find a node that contains the starting addr
 *
 * @param root: the root of the tree
 *        inputaddr: given starting addr
 *
 */
struct treenode* lookupboundnode(struct treenode** root, void* inputaddr) {
    struct treenode* temp = *root;
    while (temp != NULL) {
        if (temp->addr <= inputaddr &&  ((size_t)temp->addr + temp->len) >= (size_t)inputaddr) {  //TODO: CAST TO SIZE_t
            return temp;
        } else if (temp->addr > inputaddr) {
            temp = temp->children[LEFT];
        } else {
            temp = temp->children[RIGHT];
        }
    }
    return temp;
}


/*
 * look up in the tree to find all nodes within a range
 *
 * @param root: the root of the tree
 *        returnaddr: given starting addr
 *        size: size of range_tree
 *        trashlist: store all nodes within that range
 *
 */
void lookuptrash(struct treenode** root, void* returnaddr, size_t size, struct LinklistNode** trashlist){
    if(*root == NULL){
      return;
    }

    if( ((size_t)returnaddr + size) < (size_t)((*root)->addr)){
      lookuptrash(&((*root)->children[LEFT]), returnaddr, size, trashlist);
    }

    if(((size_t)returnaddr) > (size_t)((*root)->addr) + (*root)->len){
      lookuptrash(&((*root)->children[RIGHT]), returnaddr, size, trashlist);
    }

    if(((*root)->addr > returnaddr) && ((size_t)(*root)->addr + (*root)->len) <= ((size_t)returnaddr + size)) {
      if((*root)->free == 1){
            append(trashlist, (void*)(*root));

          if((*root)->children[LEFT] && (*root)->children[LEFT]->addr >= returnaddr) {
              lookuptrash(&((*root)->children[LEFT]), returnaddr, size, trashlist);
          }
          if((*root)->children[RIGHT] && ((size_t)(*root)->children[RIGHT]->addr + (*root)->children[RIGHT]->len <= (size_t)returnaddr + size)) {
              lookuptrash(&((*root)->children[RIGHT]), returnaddr, size, trashlist);
          }
      }
          else {
            fprintf(stderr, "Allocated memory at %p has not been freed.\n", (void *)returnaddr);
            exit(EXIT_FAILURE);
          }
    }

    else{
      return;
    }

    return;
}
