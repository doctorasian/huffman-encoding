/**
        @file
        @author Francis Nguyen <fn87@drexel.edu>
        @date 24 Feb 2024
        @section DESCRIPTION

        This file implements the heap data structure.
        I used a lot of ternary operators. Enjoy!

 */
#include "heap.h"
#include <stdbool.h>
#include <string.h>

/**
 Create a new empty heap
 @return A pointer to the new heap
 */
heap *makenull(int capacity) {
  heap *newHeap = malloc(sizeof(heap));
  newHeap->maxSize = capacity;
  newHeap->currentSize = 0;
  node **data = malloc(sizeof(node *) * capacity);
  newHeap->data = data;
  return newHeap;
}

/**
Helper function that recursively deletes nodes in tree
@param myNode is the current node to delete
*/
void deleteHuffmanHelper(node *myNode) {
  if (myNode == NULL) {
    return;
  }
  deleteHuffmanHelper(myNode->leftChild);
  deleteHuffmanHelper(myNode->rightChild);
  free(myNode);
}

/**
This function deletes all the data used by the huffman tree.
@param myHeap is the heap to delete
*/
void deleteHuffman(heap *myHeap) {
  for (int i = 0; i < myHeap->currentSize; i++) {
    deleteHuffmanHelper(myHeap->data[i]);
  }
  free(myHeap->data);
  free(myHeap);
}

/**
 Ask if the heap is currently empty
 @param myHeap is a pointer to the heap
 @return true if empty and false otherwise
 */
bool empty(heap *myHeap) { return myHeap->data == NULL ? true : false; }

/**
 What is the smallest value in the heap?
 @param myHeap is the heap to find min of
 @return The node containing the smallest frequency in the heap, NULL if heap is
 empty
 */
node *min(heap *myHeap) { return !(empty(myHeap)) ? myHeap->data[0] : NULL; }

/**
This function combines min() and deletemin() into one function to avoid
repetition
@param myHeap is the heap to grab the min value from
@return node with the most minimum frequency value
*/
node *extractMin(heap *myHeap) {
  node *minNode = min(myHeap);
  deletemin(myHeap);
  return minNode;
}

/**
 Delete the minimum from the heap
 @param myHeap is the heap to delete fronode *min(heap *myHeap) { return
 !(empty(myHeap)) ? myHeap->data[0] : NULL; }m
 */
void deletemin(heap *myHeap) {
  if (empty(myHeap))
    return;
  int tailIndex = myHeap->currentSize - 1;
  /* swap the min and the tail */
  swap(myHeap, 0, tailIndex);
  myHeap->currentSize--;
  downheap(myHeap, 0);
}

/**
 Downheap starting at the node at index i
 @param myHeap is the heap to modify
 @param i is the index to start from
 */
void downheap(heap *myHeap, int i) {
  int leftIndex = leftChild(i);
  int rightIndex = rightChild(i);
  if (leftIndex >= myHeap->currentSize) // No Children
    return;
  /* Get child with minimum value */
  int minIndex =
      myHeap->data[leftIndex]->frequency <= myHeap->data[rightIndex]->frequency
          ? leftIndex
          : rightIndex;
  /* Edge case: Right Child is smaller but out of bounds */
  if (rightIndex >= myHeap->currentSize) {
    minIndex = leftIndex;
  }
  if (myHeap->data[i]->frequency > myHeap->data[minIndex]->frequency) {
    /* Swap the value of parent with minIndex child */
    swap(myHeap, i, minIndex);
    downheap(myHeap, minIndex);
  }
}
/**
Wrapper function that initializes a new node
@param frequency is the probability of an ASCII character appearing in textfile
@param asciiValue is the ASCII value in question
*/
node *createNode(double frequency, int asciiValue) {
  node *newNode = malloc(sizeof(node));
  newNode->frequency = frequency;
  newNode->asciiValue = asciiValue;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  return newNode;
}

/**
Alternate function to insert() but inserts node to heap
@param newNode to insert to heap
@param heap to insert node into
*/
void insertNode(node *newNode, heap *myHeap) {
  int size = myHeap->currentSize;
  /* size == capacity */
  if (size == myHeap->maxSize) {
    return;
  }
  myHeap->data[size] = newNode;
  myHeap->currentSize++;
  /* Note: size also refers to index inserted */
  upheap(myHeap, size);
}

/**
This function combines two trees/nodes together by creating a new node and
setting nodes passed to the function as its children
@param node01 first node
@param node02 second node
@return parent node or root of tree
*/
node *combineNodes(node *node01, node *node02) {
  double frequency01 = node01->frequency;
  double frequency02 = node02->frequency;
  double totalFrequency = frequency01 + frequency02;
  node *newNode = createNode(totalFrequency, -1);
  if (frequency01 == frequency02) {
    newNode->leftChild =
        (node01->asciiValue < node02->asciiValue) ? node01 : node02;
    newNode->rightChild =
        (node01->asciiValue > node02->asciiValue) ? node01 : node02;
  } else {
    newNode->leftChild = (frequency01 < frequency02) ? node01 : node02;
    newNode->rightChild = (frequency01 > frequency02) ? node01 : node02;
  }
  return newNode;
}

/**
 Insert value x into the heap
 @param x is the value to insert
 @param myHeap is the heap to insert into
 */
void insert(double frequency, int asciiValue, heap *myHeap) {
  int size = myHeap->currentSize;
  /* size == capacity */
  if (size == myHeap->maxSize) {
    return;
  }
  node *newNode = createNode(frequency, asciiValue);
  myHeap->data[size] = newNode;
  myHeap->currentSize++;
  /* Note: size also refers to index inserted */
  upheap(myHeap, size);
}

/**
 Upheap starting at node indexed to i
 @param myHeap is the heap to fix
 @param i is the index of the node to start upheaping at
 */
void upheap(heap *myHeap, int i) {
  int parentIndex = parent(i);
  if (parentIndex < 0)
    return; /* If root, then return */
  if (myHeap->data[parentIndex]->frequency > myHeap->data[i]->frequency) {
    swap(myHeap, parentIndex, i);
    upheap(myHeap, parentIndex);
  }
}

/**
 What is the index of node n's parent?
 @param n is the child node's index
 @return n's parent's index
 */
int parent(int n) { return ((n - 1) / 2); }

/**
 What index contains the left child of n?
 @param n is the index of the parent
 @return the index of the left child of n
 */
int leftChild(int n) { return (n + 1) * 2 - 1; }

/**
 What index contains the right child of n?
 @param n is the index of the parent
 @return the index of the right child of n
 */
int rightChild(int n) { return (n + 1) * 2; }

/**
 Swap the values at indexes i and j in the heap.
 @param myHeap is the heap to modify
 @param i is the first index to swap
 @param j is the second index to swap with
 */
void swap(heap *myHeap, int i, int j) {
  /* Assuming valid indices */
  node *temp = myHeap->data[i];
  myHeap->data[i] = myHeap->data[j];
  myHeap->data[j] = temp;
}

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
node *searchForAscii(int target, char *huffmanCode, int count, node *nodePtr) {
  if (nodePtr == NULL)
    return NULL;
  if (target == nodePtr->asciiValue) {
    huffmanCode[count] = '\0';
    return nodePtr;
  }
  if (nodePtr->leftChild != NULL) {
    huffmanCode[count] = '0';
    node *result =
        searchForAscii(target, huffmanCode, count + 1, nodePtr->leftChild);
    if (result != NULL)
      return result;
  }
  if (nodePtr->rightChild != NULL) {
    huffmanCode[count] = '1';
    node *result =
        searchForAscii(target, huffmanCode, count + 1, nodePtr->rightChild);
    if (result != NULL)
      return result;
  }

  return NULL;
}

/**
 This function prints the Huffman tree
 @param myHeap is the heap to print
 */
void printHuffman(heap *myHeap) {
  printf("| %5s | %s | %s |\n", "ASCII", "Percent", "Code");
  printf("| ----- | ------- | ---- |\n");
  // int totalBits = 0;
  for (int value = 0; value < 128; value++) {
    char *huffmanCode = malloc(sizeof(char) * 127);
    node *nodePtr = searchForAscii(value, huffmanCode, 0, myHeap->data[0]);
    if (nodePtr == NULL) {
      free(huffmanCode);
      continue;
    }
    printf("| %5d | %1.5f | %s |\n", nodePtr->asciiValue, nodePtr->frequency,
           huffmanCode);
    // totalBits += (nodePtr->frequency * 100 * strlen(huffmanCode));
    free(huffmanCode);
  }
  // printf("Total Bits: %d\n", totalBits);
}
