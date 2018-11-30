#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Affine.h"

int main(int argc, char **argv) {
  if (argc == 4 && isdigit(*argv[1]) && isdigit(*argv[2]) && *argv[3] == 'e') {
    FILE *in_msg = fopen("../exmpl/msg.txt", "rt"), *out_encrypt_msg = fopen("../exmpl/ecnyptedMsg.txt", "w");
    char *p;
    if(encrypt(in_msg, out_encrypt_msg, strtol(argv[1], &p, 10), strtol(argv[2], &p, 10), 26))
      puts("\nSuccess, encrypted!\n");
    else
      puts("\nError to encrypt!\n");
  } else if (argc == 4 && isdigit(*argv[1]) && isdigit(*argv[2]) && *argv[3] == 'd') {
    char *p;
    FILE *in_msg = fopen("../exmpl/msg.txt", "rt"), *out_encrypt_msg = fopen("../exmpl/decryptedMsg.txt", "w");
    if(decrypt(in_msg, out_encrypt_msg, strtol(argv[1], &p, 10), strtol(argv[2], &p, 10), 26))
      puts("\nSuccess, decrypted!\n");
    else
      puts("\nError to decrypt!\n");
  } else
      printf("Error, arguments example: AffineCipher [a] [b] [cfg]\ncfg may be:\ne - encrypt message\nd - decrypt message\n");
  return 0;
}