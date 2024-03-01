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
  printf("The frequency of a is: %.5f\n", (double)frequencyArray[97] / 100);
  // TODO: Huffman Node stores ASCII value and probability
  fclose(file);
  Heap *heap = makenull(MAX_SIZE);
  for (int value = 0; value < MAX_SIZE; value++) {
    if (frequencyArray[value] == 0) {
      continue;
    }
    //insert
  }
}

int main() {
  char fileName[100];
  printf("Enter File Name to read:\n");
  /* Assume file names are always correct */
  fscanf(stdin, "%s", fileName);
  huffman(fileName);
}
