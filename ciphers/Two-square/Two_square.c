#include "Two_square.h"

const char* ALPHABET = "abcdefghijklmnoprstuvwxyz";

__uint8_t strlen(const char* str) {
  __uint8_t len = 0;
  for (__uint8_t i = 0; str[i] != '\0'; i++)
    len = i;
  return ++len;
}

bool _strcmp(const char* lhs, const char* rhs) {
  if (strlen(lhs) != strlen(rhs)) return false;
  for (size_t i = 0; lhs[i] != '\0'; i++)
      if (lhs[i] != rhs[i])
        return false;
  return true;
}

char* _strcat(const char* lhs, const char* rhs) {
  size_t total_length = strlen(lhs) + strlen(rhs) + 1;
  char* tmp = malloc(total_length * sizeof(char));
  int ecx = 0;
  for (int i = 0; lhs[i] != '\0'; i++) {
    tmp[ecx] = lhs[i];
    ecx++;
  }
  for (int i = 0; rhs[i] != '\0'; i++) {
    tmp[ecx] = rhs[i];
    ecx++;
  }
  return tmp;
}

char* _chrcat(const char lhs, const char rhs) {
  char* tmp = malloc(2 * sizeof(char));
  tmp[0] = lhs;
  tmp[1] = rhs;
  return tmp;
}

void print(char** arr) {
  for (int i = 0; i < STRINGS; i++) {
    for (int j = 0; j < COLUMNS; j++)
      printf("%c ", arr[i][j]);
    printf("\n");
  }
}

char* remove_char(char* sequence, char c) {
  char* tmp = malloc(strlen(sequence) * sizeof(char));
  int ecx = 0;
  for (int i = 0; i < strlen(sequence); i++)
    if (sequence[i] != c) {
      tmp[ecx] = sequence[i];
      ecx++;
    }
  return tmp;
}

char* check_bigrams(const char *msg) {
  if (strlen(msg) % 2 != 0) {
    char *formatted_msg = malloc(strlen(msg) + 1 * sizeof(char));
    for (int i = 0; i < strlen(msg); i++)
      formatted_msg[i] = msg[i];

    formatted_msg[strlen(msg)] = 'x';
    return formatted_msg;
  }
  return msg;
}

char* remove_duplicate(char* key) {
  char* tmp_alp = ALPHABET, *clear = malloc(strlen(key) * sizeof(char));
  int ecx = 0;
  for (size_t i = 0; i < strlen(key); i++)
    for (size_t j = 0; j < strlen(ALPHABET); j++)
      if (key[i] == tmp_alp[j]) {
        clear[ecx] = tmp_alp[j];
        ecx++;
        tmp_alp = remove_char(tmp_alp, tmp_alp[j]);
      }
  return clear;
}

char* format_key(const char* key) {
  char* formatted_key = key;
  formatted_key = remove_char(key, 'q');
  formatted_key = remove_duplicate(formatted_key);
  return formatted_key;
}

char* encrypt(const char* msg, const char** first_block, const char** second_block) {
  char* encrypted_msg = malloc(strlen(msg) * sizeof(char));
  struct letter first_block_ltr, second_block_ltr;

  int ecx = 0;
  char* bigram = malloc(2 * sizeof(char));
  printf("bigrams: ");
  for (int c = 0; c < strlen(msg) / 2; c++) {
    for (int i = 0; i < 2; i++) {
      bigram[i] = msg[ecx];
      ecx++;
    }
    printf("%s ", bigram);
    for (size_t i = 0; i < STRINGS; i++)
      for (size_t j = 0; j < COLUMNS; j++) {
        if (first_block[i][j] == bigram[0]) {
          first_block_ltr.i = i;
          first_block_ltr.j = j;
        }
        if (second_block[i][j] == bigram[1]) {
          second_block_ltr.i = i;
          second_block_ltr.j = j;
        }
      }

    if (first_block_ltr.i == second_block_ltr.i)
      encrypted_msg = _strcat(encrypted_msg, _chrcat(second_block[first_block_ltr.i][first_block_ltr.j], first_block[second_block_ltr.i][second_block_ltr.j]));
    else
      encrypted_msg = _strcat(encrypted_msg, _chrcat(second_block[first_block_ltr.i][second_block_ltr.j], first_block[second_block_ltr.i][first_block_ltr.j]));
  }
  printf("\n");

  return  encrypted_msg;
}

char* execute(const char* first_key, const char* second_key, const char* msg) {
  char** first_block = malloc(STRINGS * sizeof(char *));
  char** second_block = malloc(STRINGS * sizeof(char*));

  for (int i = 0; i < COLUMNS; i++) {
    first_block[i] = malloc(COLUMNS * sizeof(char));
    second_block[i] = malloc(COLUMNS * sizeof(char));
  }

  char* first_key_tmp, *second_key_tmp, *tmp_alp = ALPHABET;

  for (int i = 0; i < strlen(first_key); i++)
    tmp_alp = remove_char(tmp_alp, first_key[i]);

  first_key_tmp = _strcat(first_key, tmp_alp);
  tmp_alp = ALPHABET;

  for (int c = 0; c < strlen(second_key); c++)
    tmp_alp = remove_char(tmp_alp, second_key[c]);

  second_key_tmp = _strcat(second_key, tmp_alp);

  printf("first sequence is: %s \n", first_key_tmp);
  printf("second sequence is: %s \n", second_key_tmp);
  int ecx = 0; // counter
  for (int i = 0; i < STRINGS; i++)
    for (int j = 0; j < COLUMNS; j++) {
      first_block[i][j] = first_key_tmp[ecx];
      second_block[i][j] = second_key_tmp[ecx];
      ecx++;
    }

  free(first_key_tmp);
  free(second_key_tmp);

  printf("first block content is: \n");
  print(first_block);
  printf("second block content is: \n");
  print(second_block);

  char* encrypted_msg = encrypt(msg, first_block, second_block);
  return encrypted_msg;
}
