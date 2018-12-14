////////////////////////////////////////////////////////////////////////////////
// Main File:        testcases
// This File:        range_tree.h
// Other Files:      537malloc.c 537malloc.h range_tree.c
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

#ifndef range_tree_h
#define range_tree_h
#include <sys/types.h>
#include "linkedlist.h"

struct treenode {
    struct treenode *parent;
    struct treenode *children[2];
    int red;
    int free;
    void* addr;
    size_t len;
};

/*
 * Add the node to tree
 *
 * @param root: the root of the tree
 *        inputaddr: the starting addr
 *        data: the size of memory added
 */
void addnode(struct treenode** T,void* inputaddr, size_t data);
/*
 * After adding the node, restructure the tree
 *
 * @param root: the root of the tree
 *        fixnode: the node that added
 */
void RB_insert_fixup(struct treenode** T, struct treenode** z);
/*
 * one case of restructure
 *
 * @param root: the root of the tree
 *        leftnode: the added node
 */
void LeftRotate(struct treenode** T,struct treenode** x);
/*
 * one case of restructure
 *
 * @param root: the root of the tree
 *        rotatenode: the added node
 */
void RightRotate(struct treenode** T,struct treenode** x);
/*
 * delete a node from the tree
 *
 * @param root: the root of the tree
 *        dnode: the node to be deleted
 */
void deletenode(struct treenode** T,struct treenode* z);
/*
 * reconnect after deletion
 *
 * @param root: the root of the tree
 *        uncle: the uncle of the node to be deleted
 *        sibling: the sibling of the node to be deleted
 */
void RB_transplat(struct treenode** T, struct treenode** u,struct treenode** v);
/*
 * get the leftmost node under root, used to get successor
 *
 * @param node: the root of the tree
 *
 */
struct treenode* Tree_minimum(struct treenode* node);
/*
 * restructure the tree after deletion
 *
 * @param root: the root of the tree
 *        node: the deleted node
 */
void RB_delete_fixup(struct treenode** T, struct treenode** x);
/*
 * look up in the tree to find a node that has the same starting addr
 *
 * @param root: the root of the tree
 *        inputaddr: given starting addr
 *
 */
struct treenode* lookupnode(struct treenode** root, void* inputaddr);
/*
 * look up in the tree to find a node that contains the starting addr
 *
 * @param root: the root of the tree
 *        inputaddr: given starting addr
 *
 */
struct treenode* lookupboundnode(struct treenode** root, void* inputaddr);
/*
 * look up in the tree to find all nodes within a range
 *
 * @param root: the root of the tree
 *        returnaddr: given starting addr
 *        size: size of range_tree
 *        trashlist: store all nodes within that range
 *
 */
void lookuptrash(struct treenode** root, void* returnaddr, size_t size, struct LinklistNode** trashlist);
#endif /* tree_h */
