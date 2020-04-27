#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Node {
  char word[100];
  int wordcount;
  struct Node* left;
  struct Node* right;
};

struct Node* createNode(char* word, int wordcount, struct Node* left, struct Node* right);
int getFirstLetter(char* word);
struct Node* insertWord(char* word, struct Node* bst);
void insertIntoArray(struct Node* bstArray[26], int index, char* word);
void writeLine(struct Node* bst, int filedesc, int max);
void traverse(struct Node* bst, int max, int filedesc);
