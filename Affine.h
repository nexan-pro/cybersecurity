#ifndef AFFINECIPHER_AFFINE_H
#define AFFINECIPHER_AFFINE_H

#include <stdio.h>
#include <stdbool.h>
/*----------------------------------------------------------
 *                     File handle
 ---------------------------------------------------------*/
void writeToFileAndPrint(FILE* out, char* alphabet, int* id);
bool isEmpty(FILE *in);
char* readFile(FILE *in);

/*----------------------------------------------------------
 *                     Content handle
 ---------------------------------------------------------*/
bool encrypt(FILE *in, FILE *out, int _a, int _b, int _m);
bool decrypt(FILE *in , FILE *out, int _a, int _b, int _m);

#endif //AFFINECIPHER_AFFINE_H
