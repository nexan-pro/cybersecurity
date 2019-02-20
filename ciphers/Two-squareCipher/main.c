/**************************************************
 * The letter "q" is removed in the alphabet
 * If we can't create bigram, we put 'x' at the EOS
**************************************************/

#include "Two_square.h"

int main(int argc, char** argv) {
  if (argc == 4) {
    char *first_key = argv[1], *second_key = argv[2];
    first_key = format_key(first_key);
    second_key = format_key(second_key);
    char *msg = argv[3];
    msg = remove_char(msg, 'q');
    msg = check_bigrams(msg);
    printf("encrypted msg: %s", execute(first_key, second_key, msg));
  }
  else
    printf("usage: ./Two-square <first key> <second key> <message>");
  return 0;
}