/**
    @mainpage
    @section Description

    Huffman Encoding Implementation
 */
/**
        @file
        @author Francis Nguyen <fn87@drexel.edu>
        @date Feb 29 2023
        @section DESCRIPTION

        This program uses the properties of min_heap to implement
        a Huffman data compression algorithm. Takes a file as input and
        calculates the frequencies for each ASCII character [0,127],
        then encodes it into mod 2 form.
 */

#include "heap.h"
#include <stdio.h>
#define MAX_SIZE 128

/**
Huffman algorithm which constructs a huffman tree and prints it
@param fileName is the file to open and construct a huffman tree off of
*/
void huffman(char *fileName) {
  FILE *file;

  file = fopen(fileName, "r");
  /* We'll use an array, which acts sort of like a dictionary
   * The index is the ASCII character, and the value is the number of times it
   * appears in the text file. We know that ASCII chars range from 0-127, so the
   * max size is 128
   */
  int frequencyArray[MAX_SIZE] = {0};
  /* Implicit conversion from char to ASCII code */
  int index;
  /* Use total chars to calculate number of bits later */
  int totalChars = 0;
  while ((index = fgetc(file)) != EOF) {
    totalChars += index >= 0 && index <= 127 ? frequencyArray[index]++ : 0;
  }
  fclose(file);
  heap *heap = makenull(MAX_SIZE);
  for (int asciiValue = 0; asciiValue < MAX_SIZE; asciiValue++) {
    if (frequencyArray[asciiValue] == 0) {
      continue;
    }
    insert((double)frequencyArray[asciiValue] / 100, asciiValue, heap);
  }
  while (heap->currentSize != 1) {
    node *node01 = extractMin(heap);
    node *node02 = extractMin(heap);
    node *newNode = combineNodes(node01, node02);
    insertNode(newNode, heap);
  }
  printHuffman(heap);
  deleteHuffman(heap);
}

int main() {
  char fileName[100];
  printf("Enter File Name to read:\n");
  /* Assume file names are always correct */
  fscanf(stdin, "%s", fileName);
  huffman(fileName);
}
