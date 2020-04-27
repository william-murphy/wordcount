#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "bst.h"

int main(int argc, char* argv[]) {

  //Open the output file and check for errors
  int output = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
  if (output < 0) { //Check for errors opening the file
    printf("\nError creating file.\n");
    return 1;
  }

  //Populate bstArray with NULL bst's
  struct Node* bstArray[26];
  for (int i=0; i<26; i++) {
    bstArray[i] = NULL;
  }

  //Declaring variables that will be used a few times for the different methods of input
  char buffer[1024];
  int filedesc;
  int bytes;
  char word[100];
  int count;
  int size = 0; //Hold size of word being parsed
  int max = 0; //Holds the length of the largest word

  //This is the files given in argv method
  if (argc >= 2) {
    int argCount = 1;
    while (argCount < argc) {
      filedesc = open(argv[argCount], O_RDONLY);
      if (filedesc > 0) {
        //Parsing starts here
        count = 0;
        while (bytes = read(filedesc, buffer, 1024)) { //This loop parses the buffer and puts the individual words into the BSTs
          if (bytes > 0) {
            for (int i=0; i<bytes; i++) {
              if ((bytes < 1024) && (i == bytes)) {
                word[count] = '\0';
                count = 0;
                if (word[0] != '\0') {
                  insertIntoArray(bstArray, getFirstLetter(word) - 97, word);
                }
                break;
              }
              if ((buffer[i] >= 'A') && (buffer[i] <= 'Z')) {
                word[count] = buffer[i] + 32;
                size++;
                count++;
              }else if ((buffer[i] >= 'a') && (buffer[i] <= 'z')) {
                word[count] = buffer[i];
                size++;
                count++;
              }else {
                word[count] = '\0';
                count = 0;
                if (word[0] != '\0') {
                  insertIntoArray(bstArray, getFirstLetter(word) - 97, word);
                }
                if (size > max) {
                  max = size; //set new maximum size
                }
                size = 0; //reset size
              }
            }
          }
        }
      }
      argCount++;
      if (close(filedesc) == -1) {
        printf("\nError closing file.\n");
      }
    }
  }

  //This is the file given as environment variable method
  char* env = getenv("WORD_FREAK");
  if (env != NULL) {
    filedesc = open(env, O_RDONLY);
    if (filedesc > 0) {
      //Parsing starts here
      count = 0;
      while (bytes = read(filedesc, buffer, 1024)) { //This loop parses the buffer and puts the individual words into the BSTs
        if (bytes > 0) {
          for (int i=0; i<bytes; i++) {
            if ((bytes < 1024) && (i == bytes)) {
              word[count] = '\0';
              count = 0;
              if (word[0] != '\0') {
                insertIntoArray(bstArray, getFirstLetter(word) - 97, word);
              }
              break;
            }
            if ((buffer[i] >= 'A') && (buffer[i] <= 'Z')) {
              word[count] = buffer[i] + 32;
              size++;
              count++;
            }else if ((buffer[i] >= 'a') && (buffer[i] <= 'z')) {
              word[count] = buffer[i];
              size++;
              count++;
            }else {
              word[count] = '\0';
              count = 0;
              if (word[0] != '\0') {
                insertIntoArray(bstArray, getFirstLetter(word) - 97, word);
              }
              if (size > max) {
                max = size; //set new maximum size
              }
              size = 0; //reset size
            }
          }
        }
      }
    }
    if (close(filedesc) == -1) {
      printf("\nError closing file.\n");
    }
  }

  //This is the standard input method
  //Parsing starts here
  count = 0;
  while (bytes = read(0, buffer, 1024)) { //This loop parses the buffer and puts the individual words into the BSTs
    if (bytes > 0) {
      for (int i=0; i<bytes; i++) {
        if ((bytes < 1024) && (i == bytes)) {
          word[count] = '\0';
          count = 0;
          if (word[0] != '\0') {
            insertIntoArray(bstArray, getFirstLetter(word) - 97, word);
          }
          break;
        }
        if ((buffer[i] >= 'A') && (buffer[i] <= 'Z')) {
          word[count] = buffer[i] + 32;
          size++;
          count++;
        }else if ((buffer[i] >= 'a') && (buffer[i] <= 'z')) {
          word[count] = buffer[i];
          size++;
          count++;
        }else {
          word[count] = '\0';
          count = 0;
          if (word[0] != '\0') {
            insertIntoArray(bstArray, getFirstLetter(word) - 97, word);
          }
          if (size > max) {
            max = size; //set new maximum size
          }
          size = 0; //reset size
        }
      }
    }
  }
  close(0);

  //Iterate through the array of BSTs and write the contents onto the ouput file, also frees the BSTs
  for (int i=0; i<26; i++) {
    traverse(bstArray[i], output, max);
    free(bstArray[i]);
  }

  //After writing to the ouput file, close the output file and check for errors
  if (close(output) == -1) {
    printf("\nError closing file.\n");
    return 1;
  }

  return 0;
}
