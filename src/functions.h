
#define MAX_WORD_LENGTH 20
#define MAX_WORDS 200
#define FILENAME "words.txt"

typedef struct {
  char text[MAX_WORD_LENGTH];
  char current_state[MAX_WORD_LENGTH];
} word;

/* question.c */
void pick_word(word* word_ptr);
void init_word(word* word_ptr);
bool guess_letter(word* word_ptr, char guessed_char);
/* display.c */
void game_won();
void game_lost(const char* correct_word);
void init_curses();
void print_menu();
void start_game();
