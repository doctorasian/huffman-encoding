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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 Implement Heap Sort using the heap data structure.
 
 @param array is the array to sort
 @param size is the number of elements in the array
 */
void heapSort(int* array, int size);

/**
	A structure to represent a heap (Priority Queue / Min Heap) Data Structure.
 */
typedef struct Heap Heap;
struct Heap{
	int* data;/**< A pointer to your array of numbers. */
	int maxSize;/**< The maximum size of the heap before it needs to be resized.*/
	int currentSize;/**< The current number of items in the array. */
};

/**
 Create a new empty Heap
 @return A pointer to the new heap
 */
Heap* makenull(int capacity);

/**
 Free all memory used by the heap
 @param myHeap is the heap to free
 */
void deleteHeap(Heap* myHeap);

/**
 Ask if the heap is currently empty
 @param myHeap is a pointer to the heap
 @return true if empty and false otherwise
 */
bool empty(Heap* myHeap);

/**
 What is the smallest value in the heap?
 @param myHeap is the heap to find min of
 @return The smallest value in the heap
 */
int min(Heap* myHeap);

/**
 Delete the minimum from the heap
 @param myHeap is the heap to delete from
 */
void deletemin(Heap* myHeap);

/**
 Downheap starting at the node at index i
 @param myHeap is the heap to modify
 @param i is the index to start from
 */
void downheap(Heap* myHeap, int i);

/**
 Insert value x into the Heap
 @param x is the value to insert
 @param myHeap is the heap to insert into
 */
void insert(int x, Heap* myHeap);

/**
 Upheap starting at node indexed to i
 @param myHeap is the heap to fix
 @param i is the index of the node to start upheaping at
 */
void upheap(struct Heap* myHeap,int i);

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
void swap(Heap* myHeap, int i, int j);

/**
 This function prints the heap and will help you debug.
 @param myHeap is the heap to print
 */
void printHeap(Heap* myHeap);


#endif
