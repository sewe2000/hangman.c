#include <curses.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"

#define NUM_OF_HANGMAN_STAGES 7

const char* logo = "\n \
\n \
$$\\   $$\\                                                                              \n \
$$ |  $$ |                                                                             \n \
$$ |  $$ | $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\  $$$$$$$\\      $$$$$$$\\ \n \
$$$$$$$$ | \\____$$\\ $$  __$$\\ $$  __$$\\ $$  _$$  _$$\\  \\____$$\\ $$  __$$\\    $$  _____|\n \
$$  __$$ | $$$$$$$ |$$ |  $$ |$$ /  $$ |$$ / $$ / $$ | $$$$$$$ |$$ |  $$ |   $$ /      \n \
$$ |  $$ |$$  __$$ |$$ |  $$ |$$ |  $$ |$$ | $$ | $$ |$$  __$$ |$$ |  $$ |   $$ |      \n \
$$ |  $$ |\\$$$$$$$ |$$ |  $$ |\\$$$$$$$ |$$ | $$ | $$ |\\$$$$$$$ |$$ |  $$ |$$\\\\$$$$$$$\\ \n \
\\__|  \\__| \\_______|\\__|  \\__| \\____$$ |\\__| \\__| \\__| \\_______|\\__|  \\__|\\__|\\_______|\n \
                              $$\\   $$ |                                               \n \
                              \\$$$$$$  |                                               \n \
                               \\______/                                                \n \
\n \
";

const char *stages_of_hangman[NUM_OF_HANGMAN_STAGES] = {
"\n \
  +---+\n \
  |   |\n \
      |\n \
      |\n \
      |\n \
      |\n \
=========\n",

"\n \
  +---+\n \
  |   |\n \
  0   |\n \
      |\n \
      |\n \
      |\n \
=========\n",

"\n \
  +---+\n \
  |   |\n \
  0   |\n \
  |   |\n \
      |\n \
      |\n \
=========\n",

"\n \
  +---+\n \
  |   |\n \
  0   |\n \
 /|   |\n \
      |\n \
      |\n \
=========\n",

"\n \
  +---+\n \
  |   |\n \
  0   |\n \
 /|\\  |\n \
      |\n \
      |\n \
=========\n",

"\n \
  +---+\n \
  |   |\n \
  0   |\n \
 /|\\  |\n \
 /    |\n \
      |\n \
=========\n",

"\n \
  +---+\n \
  |   |\n \
  0   |\n \
 /|\\  |\n \
 / \\  |\n \
      |\n \
=========\n",
};

inline void init_curses() {
  initscr();
  cbreak();
  noecho();
}

void print_menu() {
  addstr(logo);
  attron(A_STANDOUT);
  addstr("Play\n");
  attroff(A_STANDOUT);
}

void game_won() {
  clear();
  addstr("You've won the game!!!\n");
  addstr("Press ENTER to exit...\n");
  getch();
}

void game_lost(const char* correct_word) {
  clear();
  addstr("You've lost the game ;(\n");
  printw("The correct word was: \'%s\'\n", correct_word);
  addstr(stages_of_hangman[NUM_OF_HANGMAN_STAGES - 1]);
  addstr("Press ENTER to exit...\n");
  getch();
}

void start_game() {
  clear();

  int stage_of_hangman = -1;

  addstr("Press Enter to exit...\n");
  int ch = 0;
  word game_word;
  pick_word(&game_word);
  init_word(&game_word);
  do {
    if (stage_of_hangman == NUM_OF_HANGMAN_STAGES - 1) {
      game_lost(game_word.text);
      return;
    }
    if (!strcasecmp(game_word.current_state, game_word.text)) {
      game_won();
      return;
    }
    clear();
    addstr("Press Enter to exit...\n");
    printw("%s\n", game_word.current_state);
    addstr("! - guess the word\n");
    printw("Stages of hangman left: %d\n", NUM_OF_HANGMAN_STAGES - (stage_of_hangman + 1));
    if (stage_of_hangman != -1) {
      addstr(stages_of_hangman[stage_of_hangman]);
    }
    ch = getch();
    if (isalnum(ch)) {
      if (!guess_letter(&game_word, ch))
	stage_of_hangman++;
    }
    if (ch == '!') {
      printw("Type a word: ");
      char answer[MAX_WORD_LENGTH];
      char format[5] = ""; // gonna be %MAX_WORD_LENGTHs
      sprintf(format, "%%%ds", MAX_WORD_LENGTH);
      echo();
      scanw(format, answer);
      noecho();
      if (!strcasecmp(answer, game_word.text)) {
	game_won();
	return;
      } else
	stage_of_hangman++;
    }
  } while (ch != '\n');
}
