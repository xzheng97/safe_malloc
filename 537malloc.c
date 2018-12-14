////////////////////////////////////////////////////////////////////////////////
// Main File:        testcases
// This File:        537malloc.c
// Other Files:      537malloc.h range_tree.c range_tree.h
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
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include "range_tree.h"
#include "linkedlist.h"
#define LEFT 0
#define RIGHT 1

static struct treenode* root;
/*
 * In addition to actually allocating the memory by calling malloc(), this
 * function will record a tuple (addri, leni), for the memory that you
 * allocate in the heap.
 *
 * @param size: memory size that user want to allocate
 * @return: address of that memory
 */
void *malloc537(size_t size){
   void *returnaddr = NULL;
   struct treenode* tempnode = NULL;
   struct treenode* tempnode1 = NULL;
   struct treenode* samenode = NULL;
   struct treenode* successor = NULL;
   if(size == 0) {
		printf("Your allocating size is 0 byte!!!\n");
	 }

  // store the address returned from malloc
  returnaddr = malloc(size);
  // get the blk of memory that overlaps with the starting address
  tempnode = lookupboundnode(&root, returnaddr);
  // get the blk of memory that overlaps with the end address
  tempnode1 = lookupboundnode(&root, (void *)(((char*)returnaddr) + size));
  // modify two blks of memory's size and address
  if(tempnode && tempnode->free){
    if(tempnode->addr != returnaddr)
    tempnode->len = (size_t)returnaddr - (size_t)tempnode->addr;
  }
  else if (tempnode && !tempnode->free){
    fprintf(stderr, "Allocated memory at %p has not been freed.\n", (void *)returnaddr);
    exit(EXIT_FAILURE);
  }
  if(tempnode1){
    if(!tempnode1->free){
      if(tempnode1->addr != (void *)(((char*)returnaddr) + size)){
        fprintf(stderr, "Allocated memory at %p has not been freed.\n", (void *)returnaddr);
        exit(EXIT_FAILURE);
      }
    }
}

  // delete all blks of memory that lie inside of the range
  struct LinklistNode* trashlist = NULL;
  lookuptrash(&root, returnaddr, size, &trashlist);
  for(int i = 0; i < getsize(&trashlist); i++){
    deletenode(&root, (struct treenode*)getnodedata(&trashlist, i));
    free((struct treenode*)getnodedata(&trashlist, i));
  }
  // check to see if there's any node in the tree that has the same addr
  samenode = lookupnode(&root, returnaddr);
  if(samenode){
    // if there is and the node completely include the memory range wanted
    if(samenode->len >= size){
      // if it is freed, modify that blk
      if(samenode->free == 1){
          samenode->len = size;
          samenode->free = 0;
      }
      else{
        fprintf(stderr, "Allocated memory at %p has not been freed.\n", (void *)returnaddr);
        exit(EXIT_FAILURE);
      }
    }
    // if there is and the memory range wanted is larger than the node size
    else{
      // get the successor
      if(samenode->children[RIGHT]){
        if(Tree_minimum(samenode->children[RIGHT])){
          successor = Tree_minimum(samenode->children[RIGHT]);
          // if the memory range does not affect the successor
          if((size_t)returnaddr + size <= (size_t)successor->addr){
            if(samenode->free == 1){
              samenode->len = size;
              samenode->free = 0;
            }
            else{
              fprintf(stderr, "Allocated memory at %p has not been freed.\n", (void *)returnaddr);
              exit(EXIT_FAILURE);
            }
          }
        }
      }
      // case when there is no successor
      else{
        if(samenode->free == 1){
          samenode->len = size;
          samenode->free = 0;
        }
        else{
          fprintf(stderr, "Allocated memory at %p has not been freed.\n", (void *)returnaddr);
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  // other wise, add the node to the tree
  else{
    addnode(&root, returnaddr,size);
  }
return(returnaddr);
}

/*
 * This function checks to see the address range specified by address ptr
 * and length size are fully within a range allocated by malloc537() and
 * memory not yet freed by free537().
 *
 * @param ptr: input starting address
 *        size: memory size
 *
 */
void memcheck537(void *ptr, size_t size){

  //Look up to see if the ptr is valid in the tree
  struct treenode* temp = lookupnode(&root, ptr);
  // case when there's no node in the tree such that has the same addr as ptr
  if(temp == NULL){
    struct treenode* temp1 = lookupboundnode(&root,ptr);
      // case when there input addr is not in the tree range
      if (temp1 == NULL) {
        fprintf(stderr, "Your input pointer %p of size %d bytes is never allocated\n",ptr, (int)size);
        exit(EXIT_FAILURE);
      }
      else{
        if(temp1->free) {
          fprintf(stderr,"Your input pointer %p of size %d bytes is inside pointer %p of size %d, but already freed\n",ptr, (int)size,temp1->addr, (int)temp1->len);
          exit(EXIT_FAILURE);
        }
        else if ( ((size_t)temp1->addr + temp1->len) < ((size_t)ptr + size)){
          fprintf(stderr, "Your input pointer %p of size %d bytes is inside pointer %p of size %d. But there does not have enough room for your pointer.\n", ptr, (int)size, temp1->addr, (int)temp1->len );
        }
      }
  }

  // when addr is same as ptr, check the valid size
  else if(size > temp->len){
      fprintf(stderr, "Cannot validate your input pointer %p of size %d bytes. It only has size %d allocated.\n", ptr, (int)size, (int)temp->len);
      exit(EXIT_FAILURE);
  }
  // check if memory has already been freed
  else if(temp->free){
    fprintf(stderr,"Your input pointer %p of size %d bytes was allocated before, but already freed\n",ptr, (int)size);
    exit(EXIT_FAILURE);
  }
}


/*
 * This function will first check to make sure that freeing the memory
 * specified by ptr makes sense, then will call free() to do the actual free.
 *
 * @param ptr: input starting address
 *
 */
void free537(void *ptr){
    // case if ptr is NULL
    if(!ptr) {
        printf("Freeing Null!\n");
    }
    // check if the starting address is valid
    struct treenode* temp = lookupnode(&root, ptr);
    // case when there's no node in the tree such that has the same addr as ptr
    if(temp == NULL){
      struct treenode* temp1 = lookupboundnode(&root,ptr);
        if (temp1 == NULL) {
          fprintf(stderr, "Cannot free memory that has not be allocated with malloc537().\n");
          exit(EXIT_FAILURE);
        }
        else if(temp1->free) {
            fprintf(stderr,"Cannot free memory that was previously freed\nNote: memory is not the first byte of the range of memory that was allocated.\n");
            exit(EXIT_FAILURE);
          }
          else{
            fprintf(stderr,"Cannot Free memory that is not the first byte of the range of memory that was allocated.\n");
            exit(EXIT_FAILURE);
          }
    }

    // check if memory has already been freed
    else if(temp->free){
      fprintf(stderr,"Cannot free memory that was previously freed\n");
      exit(EXIT_FAILURE);
    }
    // regular case, free ptr
    else{
      free(ptr);
      temp->free = 1;
    }

}


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
void *realloc537(void *ptr, size_t size){
  // if there's no pointer, do the same operation as malloc537
  if(ptr == NULL){
    return malloc537(size);
  }
  // if size is zero, do the same operation as free537
  else if( size == 0 && ptr != NULL){
    printf("Your reallocating size is 0 byte!!! Pointer is now freed.\n");
    free537(ptr);
    return NULL;
  }
  // otherwise, do realloc
  else{
    struct treenode* temp = lookupnode(&root, ptr);
    void* result = NULL;
    // case when input addr is valid
    if(temp != NULL){
      temp->free = 1;
      result = realloc(ptr, size);
      struct treenode* successor = NULL;
      // create a list to store all nodes that need to be deleted
      struct LinklistNode* trashlist1 = NULL;
      // look up all trash nodes within the range
      lookuptrash(&root, result, size, &trashlist1);
      // delete nodes from the tree
      for(int i = 0; i < getsize(&trashlist1); i++){
        deletenode(&root, (struct treenode*)getnodedata(&trashlist1, i));
        free((struct treenode*)getnodedata(&trashlist1, i));
      }
      // check to see if there's any node in the tree that has the same addr
      struct treenode*  samenode = lookupnode(&root, result);
        if(samenode){
          // if there is and the node completely include the memory range wanted
          if(samenode->len >= size){
            // if it is freed, modify that blk
            if(samenode->free == 1){
              samenode->len = size;
              samenode->free = 0;
            }
            else{
              printf("memory not freed\n");
              exit(EXIT_FAILURE);
            }
          }
          // if there is and the memory range wanted is larger than the node size
          else{
            // get the successor
            if(samenode->children[RIGHT]){
              if(Tree_minimum(samenode->children[RIGHT])){
                successor = Tree_minimum(samenode->children[RIGHT]);
                // if the memory range does not affect the successor
                if((size_t)result + size <= (size_t)successor->addr){
                  if(samenode->free == 1){
                    samenode->len = size;
                    samenode->free = 0;
                  }
                  else{
                    printf("memory not freed\n");
                    exit(EXIT_FAILURE);
                  }
                }
                else{
                  printf("Cannot malloc\n");
                  exit(EXIT_FAILURE);
                }
              }
            }
            // case when there is no successor
            else{
              if(samenode->free == 1){
                samenode->len = size;
                samenode->free = 0;
              }
              else{
                printf("memory not freed\n");
                exit(EXIT_FAILURE);
              }
            }
          }
        }
          // other wise, add the node to the tree
        else{
            addnode(&root, result,size);
        }
        return result;
      }
      else{
        fprintf(stderr, "Cannot realloc memory that is not the first byte of the range of memory that was allocated.\n");
        exit(EXIT_FAILURE);
    }
  }
}
