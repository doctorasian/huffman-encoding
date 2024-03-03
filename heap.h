/**
        @file
        @author Mark Boady <mwb33@drexel.edu>
        @date 2023
        @section DESCRIPTION

        This file contains the interface for a heap data structure.

        It also includes heapSort which uses the heap to
        sort an array.
 */
/*
        You MAY NOT add or remove from this file.
        You MUST code to the interface provided.
 */

#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/**
Node which contains a left node that is conventionally smaller than the right
node.
Stores the frequency (what's being compared) and the ASCII representation of the
char
*/
typedef struct Node {
  double frequency;
  int asciiValue;
  struct Node *leftChild;
  struct Node *rightChild;
} node;
/**
        A structure to represent a heap (Priority Queue / Min Heap) Data
   Structure.
 */

typedef struct Heap {
  node **data;     /**< A pointer to your array of nodes. */
  int maxSize;     /**< The maximum size of the heap before it needs to be
                      resized.*/
  int currentSize; /**< The current number of items in the array. */
} heap;

/**
 Create a new empty Heap
 @return A pointer to the new heap
 */
heap *makenull(int capacity);

/**
 Free all memory used by the heap
 @param myHeap is the heap to free
 */
void deleteHeap(heap *myHeap);

/**
 Ask if the heap is currently empty
 @param myHeap is a pointer to the heap
 @return true if empty and false otherwise
 */
bool empty(heap *myHeap);

/**
 What is the smallest value in the heap?
 @param myHeap is the heap to find min of
 @return The smallest value in the heap
 */
node *min(heap *myHeap);

node *extractMin(heap *myHeap);

/**
 Delete the minimum from the heap
 @param myHeap is the heap to delete from
 */
void deletemin(heap *myHeap);

/**
 Downheap starting at the node at index i
 @param myHeap is the heap to modify
 @param i is the index to start from
 */
void downheap(heap *myHeap, int i);

node *createNode(double frequency, int asciiValue);

void insertNode(node *newNode, heap *myHeap);

node *combineNodes(node *node01, node *node02);

/**
 Insert value x into the Heap
 @param x is the value to insert
 @param myHeap is the heap to insert into
 */
void insert(double frequency, int asciiValue, heap *myHeap);

/**
 Upheap starting at node indexed to i
 @param myHeap is the heap to fix
 @param i is the index of the node to start upheaping at
 */
void upheap(heap *myHeap, int i);

/**
 What is the index of node n's parent?
 @param n is the child node's index
 @return n's parent's index
 */
int parent(int n);

/**
 What index contains the left child of n?
 @param n is the index of the parent
 @return the index of the left child of n
 */
int leftChild(int n);

/**
 What index contains the right child of n?
 @param n is the index of the parent
 @return the index of the right child of n
 */
int rightChild(int n);

/**
 Swap the values at indexes i and j in the heap.
 @param myHeap is the heap to modify
 @param i is the first index to swap
 @param j is the second index to swap with
 */
void swap(heap *myHeap, int i, int j);

node *searchForAscii(int target, char *huffmanCode, int count, node *nodePtr);

/**
 This function prints the heap and will help you debug.
 @param myHeap is the heap to print
 */
void printHuffman(heap *myHeap);

#endif
