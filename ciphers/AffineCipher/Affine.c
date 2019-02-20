#include <malloc.h>
#include <stdlib.h>
#include "Affine.h"

#define MOD(___x, ___n) \
  (___x % ___n + ___n) % ___n;

struct FileHandle {
  int size;
};

struct FileHandle pointer;

void writeToFileAndPrint(FILE* out, char* alphabet, int* id) {
  for (size_t i = 0; i < pointer.size; ++i) {
    printf("%c", alphabet[id[i]]);
    fputc(alphabet[id[i]], out);
  }
}

bool isEmpty(FILE *in) {
  if (fgetc(in) == EOF)
    return true;
  rewind(in); // restore pointer at begin in file
  return false;
}

char* readFile(FILE *in) {
  int tmp = 0;
  long length = ftell(in);
  char c, *msg = malloc(length);
  while ((c = fgetc(in)) != EOF) {
    if (c != ' ')
      msg[tmp] += c;
    else
      continue;
    tmp++;
  }
  pointer.size = tmp;
  return msg;
}

bool encrypt(FILE *in, FILE *out, int _a, int _b, int _m) {
  if (!in) {
    printf("error, can't open file!");
    return 0;
  }

  if (isEmpty(in)) {
    printf("msg is empty!");
    return 0;
  }

  int a = _a, b = _b, m = _m;
  char *msg = readFile(in);
  int ecx = pointer.size;
  char *mod_alphabet = malloc(m);
  int *id = malloc(ecx * sizeof(int));

  for (unsigned short i = 0; i < m; ++i)
    mod_alphabet[i] += 'A' + MOD((a * i + b), m);
  for (unsigned short i = 0; i < ecx; ++i)
    for (unsigned short j = 0; j < m; ++j)
      if ('A' + j == msg[i])
        id[i] = j;
  printf("msg: %s", msg);
  printf("\nkeys in clear text alphabet: ");
  for (unsigned short i = 0; i < ecx; ++i)
    printf("%d ", id[i]);
  printf("\nmodified alphabet: %s", mod_alphabet);
  printf("\nencrypted msg: ");
  writeToFileAndPrint(out, mod_alphabet, id);
  free(id);
  free(mod_alphabet);
  free(msg);
  fclose(in);
  fclose(out);
  return 1;
}

bool decrypt(FILE *in , FILE *out, int _a, int _b, int _m) {
    if (!in) {
      printf("error, can't open file!");
      return 0;
    }

    if (isEmpty(in)) {
      printf("msg is empty!");
      return 0;
    }

    int a = _a, b = _b, m = _m;
    char *msg = readFile(in);
    int ecx = pointer.size;
    printf("a = %d, b = %d\n", a, b);
    char *alphabet = malloc(m);
    int *mod_id = malloc(ecx * sizeof(int));
    int *id = malloc(ecx * sizeof(int));

    for (unsigned short i = 0; i < m; ++i)
      alphabet[i] += 'A' + i;
    for (unsigned short i = 0; i < ecx; ++i)
      for (unsigned short j = 0; j < m; ++j)
        if ('A' + j == msg[i])
          mod_id[i] = j;
    printf("msg: %s", msg);
    printf("\nkeys in clear text alphabet: ");
    for (unsigned short i = 0; i < ecx; ++i) {
      printf("%d ", mod_id[i]);
      id[i] = a * (mod_id[i] - b);
      id[i] = MOD(id[i], m);
    }
    printf("\ndecrypted keys: ");
    for (unsigned short i = 0; i < ecx; ++i) {
      printf("%d ", id[i]);
    }
    printf("\nmodified alphabet: %s", alphabet);
    printf("\ndecrypted msg: ");
    writeToFileAndPrint(out, alphabet, id);
    free(id);
    free(mod_id);
    free(alphabet);
    free(msg);
    fclose(in);
    fclose(out);
    return 1;
}