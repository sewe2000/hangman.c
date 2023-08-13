#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"


/*
  Name: pick_word
  Args:
  word* word_ptr - a pointer to word struct
  Return value: void
  Purpose: Gets a random word from FILENAME file and writes it to a word
  pointed by word_ptr
 */
void pick_word(word* word_ptr) {
  srand(time(NULL));
  char buffer[MAX_WORDS][MAX_WORD_LENGTH] = {};
  FILE* fp = fopen("words.txt", "r");
  int i = 0;
  while (i < MAX_WORDS && fgets(buffer[i], MAX_WORD_LENGTH, fp)) {
    char* ch;
    if ((ch = strchr(buffer[i], '\n')))
      *ch = '\0';
    i++;
  }
  int random_index = rand() % i;
  strcpy(word_ptr->text, buffer[random_index]);
  fclose(fp);
}

void init_word(word* word_ptr) {
  int i = 0;
  while(word_ptr->text[i]) {
    if (word_ptr->text[i] != ' ')
      word_ptr->current_state[i] = '_';
    else 
      word_ptr->current_state[i] = ' ';
    i++;
  }
  word_ptr->current_state[i] = '\0';
}

bool guess_letter(word* word_ptr, char guessed_char) {
  char needle[2] = {guessed_char, '\0'};
  if (!strcasestr(word_ptr->text, needle))
    return false;
  char *ptr = word_ptr->text;
  while ((ptr = strcasestr(ptr, needle))) {
    int pos = ptr - word_ptr->text;
    word_ptr->current_state[pos] = word_ptr->text[pos];
    ptr++;
  }
  return true;
}
