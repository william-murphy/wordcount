#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "bst.h"

struct Node* createNode(char* word, int wordcount, struct Node* left, struct Node* right) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  strcpy(newNode->word, word);
  newNode->wordcount = wordcount;
  newNode->left = left;
  newNode->right = right;
  return newNode;
}

//Returns the first letter of a given word, so it can be put in the correct bst
int getFirstLetter(char* word) {
  return (int)word[0];
}

//Inserts the given word into the corresponding bst
struct Node* insertWord(char* word, struct Node* bst) {
  int num;
  if (bst == NULL) {
    bst = createNode(word, 1, NULL, NULL);
  }else {
    num = strcmp(word, bst->word);
    if (num > 0) {
      bst->right = insertWord(word, bst->right);
    }else if (num < 0) {
      bst->left = insertWord(word, bst->left);
    }else {
      bst->wordcount++;
    }
  }
  return bst;
}

void insertIntoArray(struct Node* bstArray[26], int index, char* word) {
  bstArray[index] = insertWord(word, bstArray[index]);
}


void writeLine(struct Node* bst, int filedesc, int max) {
  char word[100];
  char buffer[100];
  int size = 0;
  int count = 0;
  while (isalpha((bst->word)[count])) {
    word[count] = (bst->word)[count];
    count++;
  }
  word[count] = '\0';
  sprintf(buffer, "%-*s : %i\n", max, word, bst->wordcount); //format the line with sprintf
  for (int i=0; i<100; i++) {
    if (buffer[i] == '\0') {
      break;
    }else {
      size++;
    }
  }
  write(filedesc, buffer, size);
  count = 0;
  size = 0;
}

//Traverses the given bst and writes its contents to the buffer
void traverse(struct Node* bst, int filedesc, int max) {
  if (bst != NULL) {
    traverse(bst->left, filedesc, max); //Traverse the left subtree
    writeLine(bst, filedesc, max);
    traverse(bst->right, filedesc, max); //Traverse the right subtree
  }
}
