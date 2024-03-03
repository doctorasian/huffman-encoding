/**
        @file
        @author Francis Nguyen <fn87drexel.edu>
        @date 2023
        @section DESCRIPTION

        This file contains the interface for a min heap data structure,
        using an array of node pointers to organize a huffman tree.

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
  double frequency;        /**< Probability of ASCII value */
  int asciiValue;          /**< Character stored as ASCII value */
  struct Node *leftChild;  /**< Left child pointer */
  struct Node *rightChild; /**< Right child pointer */
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
Helper function that recursively deletes nodes in tree
@param myNode is the current node to delete
*/
void deleteHuffmanHelper(node *myNode);

/**
This function deletes all the data used by the huffman tree.
@param myHeap is the heap to delete
*/
void deleteHuffman(heap *myHeap);

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
/**
This function combines min() and deletemin() into one function to avoid
repetition
@param myHeap is the heap to grab the min value from
@return node with the most minimum frequency value
*/
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
/**
Wrapper function that initializes a new node
@param frequency is the probability of an ASCII character appearing in textfile
@param asciiValue is the ASCII value in question
*/
node *createNode(double frequency, int asciiValue);
/**
Alternate function to insert() but inserts node to heap
@param newNode to insert to heap
@param heap to insert node into
*/

void insertNode(node *newNode, heap *myHeap);

/**
This function combines two trees/nodes together by creating a new node and
setting nodes passed to the function as its children
@param node01 first node
@param node02 second node
@return parent node or root of tree
*/
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
/**
This recursive function searches for an ASCII value in the huffman tree.
For efficiency reasons, it will also build a huffman code as a string
as it traverses the tree.
@param target is the ASCII value to find
@param huffmanCode is the string passed to each recursive call
@param count keeps track of current index of huffmanCode string
@param nodePtr as the root node
@return node containing ASCII value, or NULL if it doesn't exist
*/
node *searchForAscii(int target, char *huffmanCode, int count, node *nodePtr);
/**
 This function prints the Huffman tree
 @param myHeap is the heap to print
 */
void printHuffman(heap *myHeap);

#endif
