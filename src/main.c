#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"

int main() {
  init_curses();
  print_menu();
  int ch;
  while ((ch = getch()) != '\n')
    continue;
  start_game();
  clear();
  endwin();
  return 0;
}

