////////////////////////////////////////////////////////////////////////////////
// Main File:        testcases
// This File:        537malloc.h
// Other Files:      537malloc.c range_tree.c range_tree.h
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
// Online sources:   NULL
//
//////////////////////////// 80 columns wide ///////////////////////////////////
#ifndef _537malloc_h
#define _537malloc_h
#include <sys/types.h>
#include "range_tree.h"
#include "linkedlist.h"

/*
 * In addition to actually allocating the memory by calling malloc(), this
 * function will record a tuple (addri, leni), for the memory that you
 * allocate in the heap.
 *
 * @param size: memory size that user want to allocate
 * @return: address of that memory
 */
void *malloc537(size_t size);
/*
 * This function checks to see the address range specified by address ptr
 * and length size are fully within a range allocated by malloc537() and
 * memory not yet freed by free537().
 *
 * @param ptr: input starting address
 *        size: memory size
 *
 */
void memcheck537(void *ptr, size_t size);

/*
 * This function will first check to make sure that freeing the memory
 * specified by ptr makes sense, then will call free() to do the actual free.
 *
 * @param ptr: input starting address
 *
 */
void free537(void *ptr);

/*
 * If ptr is NULL,then this follows the specification of malloc537() above.
 * If size is zero and ptr is not NULL,then this follows the specification of
 * free537() above. Otherwise, in addition to changing the memory allocation by
 * calling realloc(), this function will first check to see if there was a tuple.
 *
 * @param ptr: input starting address
 *        size: input size
 * @return realloc address
 */
void *realloc537(void *ptr, size_t size);
#endif
