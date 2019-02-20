#ifndef TWO_SQUARE_TWO_SQUARE_H
#define TWO_SQUARE_TWO_SQUARE_H

#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>

#define STRINGS 5
#define COLUMNS 5

struct letter {
  size_t i;
  size_t j;
};

__uint8_t strlen(const char* str);
char* _strcat(const char* lhs, const char* rhs);
char* _chrcat(const char lhs, const char rhs);
char* remove_char(char* sequence, char c);
char* remove_duplicate(char* key);
char* check_bigrams(const char* msg);
char* format_key(const char* key);

char* encrypt(const char* msg, const char** first_block, const char** second_block);
char* execute(const char* key, const char* second_key, const char* msg);

void print(char** arr);

#endif //TWO_SQUARE_TWO_SQUARE_H
