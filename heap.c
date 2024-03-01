/**
        @file
        @author Francis Nguyen <fn87@drexel.edu>
        @date 24 Feb 2024
        @section DESCRIPTION

        This file implements the heap data structure.
        I used a lot of ternary operators. Enjoy!

 */
#include "heap.h"
#include <assert.h>
#include <stdbool.h>

/**
 Implement Heap Sort using the heap data structure.

 @param array is the array to sort
 @param size is the number of elements in the array
 */
void heapSort(int *array, int size) {
  /* Initialize Heap */
  Heap *myHeap = makenull(size);
  for (int i = 0; i < size; i++) {
    insert(array[i], myHeap);
  }
  /* Put Min into Array */
  for (int j = 0; j < size; j++) {
    array[j] = min(myHeap);
    deletemin(myHeap);
  }
}

/**
        A structure to represent a heap (Priority Queue / Min Heap) Data
Structure. typedef struct Heap Heap; struct Heap{ int* data; < A pointer to your
array of numbers. int maxSize; < The maximum size of the heap before it needs to
be resized. int currentSize; < The current number of items in the array.
}; */

/**
 Create a new empty Heap
 @return A pointer to the new heap
 */
Heap *makenull(int capacity) {
  Heap *newHeap = malloc(sizeof(Heap));
  newHeap->maxSize = capacity;
  newHeap->currentSize = 0;
  int *data = malloc(sizeof(int) * capacity);
  newHeap->data = data;
  return newHeap;
}

/**
 Free all memory used by the heap
 @param myHeap is the heap to free
 */
void deleteHeap(Heap *myHeap) {
  free(myHeap->data);
  assert(myHeap->data == NULL);
  free(myHeap);
  assert(myHeap == NULL);
}

/**
 Ask if the heap is currently empty
 @param myHeap is a pointer to the heap
 @return true if empty and false otherwise
 */
bool empty(Heap *myHeap) { return myHeap->data == NULL ? true : false; }

/**
 What is the smallest value in the heap?
 @param myHeap is the heap to find min of
 @return The smallest value in the heap, -1 if Heap is empty
 */
int min(Heap *myHeap) { return !(empty(myHeap)) ? myHeap->data[0] : -1; }

/**
 Delete the minimum from the heap
 @param myHeap is the heap to delete from
 */
void deletemin(Heap *myHeap) {
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
void downheap(Heap *myHeap, int i) {
  int leftIndex = leftChild(i);
  int rightIndex = rightChild(i);
  if (leftIndex >= myHeap->currentSize) // No Children
    return;
  /* Get child with minimum value */
  int minIndex = myHeap->data[leftIndex] <= myHeap->data[rightIndex]
                     ? leftIndex
                     : rightIndex;
  /* Edge case: Right Child is smaller but out of bounds */
  if (rightIndex >= myHeap->currentSize) {
	minIndex = leftIndex;
  }
  if (myHeap->data[i] > myHeap->data[minIndex]) {
    /* Swap the value of parent with minIndex child */
    swap(myHeap, i, minIndex);
    downheap(myHeap, minIndex);
  }
}

/**
 Insert value x into the Heap
 @param x is the value to insert
 @param myHeap is the heap to insert into
 */
void insert(int x, Heap *myHeap) {
  int size = myHeap->currentSize;
  /* size == capacity */
  if (size == myHeap->maxSize) {
    return;
  }
  myHeap->data[size] = x;
  myHeap->currentSize++;
  /* Note: size also refers to index inserted */
  upheap(myHeap, size);
}

/**
 Upheap starting at node indexed to i
 @param myHeap is the heap to fix
 @param i is the index of the node to start upheaping at
 */
void upheap(struct Heap *myHeap, int i) {
  int parentIndex = parent(i);
  if (parentIndex < 0)
    return; /* If root, then return */
  if (myHeap->data[parentIndex] > myHeap->data[i]) {
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
void swap(Heap *myHeap, int i, int j) {
  /* Assuming valid indices */
  int temp = myHeap->data[i];
  myHeap->data[i] = myHeap->data[j];
  myHeap->data[j] = temp;
}

/**
 This function prints the heap and will help you debug.
 @param myHeap is the heap to print
 */
void printHeap(Heap *myHeap) {
  printf("Heap Current Size: %d\n", myHeap->currentSize);
  printf("Heap Max Size: %d\n", myHeap->maxSize);
  printf("Contents:\n");
  for (int i = 0; i < myHeap->currentSize; i++) {
    printf("%d ", myHeap->data[i]);
  }
  printf("\n");
}
