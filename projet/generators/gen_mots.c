#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "gen_mots.h"
#include "gen_texte.h"

int main(int argc, char *argv[]) {

  if (argc < 5) {
    fprintf(stderr, "Error: Missing parameters\n[USAGE]: ./gen_mots words min_length max_length alphabet_size\n");
    return EXIT_FAILURE;
  }

  int words = atoi(argv[1]);

  if (words < 0) {
    fprintf(stderr, "Error: invalid words value (%d)\n", words);
    return EXIT_FAILURE;
  }

  int minLength = atoi(argv[2]);

  if (minLength < 0) {
    fprintf(stderr, "Error: invalid minimum length value (%d)\n", minLength);
    return EXIT_FAILURE;
  }

  int maxLength = atoi(argv[3]);

  if (maxLength < 0 || maxLength < minLength) {
    fprintf(stderr, "Error: invalid maximum length value (%d)\n", maxLength);
    return EXIT_FAILURE;
  }

  int alphabet_size = atoi(argv[4]);

  if (alphabet_size < 0) {
    fprintf(stderr, "Error: invalid alphabet size value (%d)\n", alphabet_size);
    return EXIT_FAILURE;
  }

  srand((unsigned int) time(NULL));

  char firstPrintableChar = ' ';
  int firstChar = (alphabet_size < UCHAR_MAX - firstPrintableChar) ? firstPrintableChar : '\0';

  for (int i = 0; i < words; i++) {
      int length = rand() % (maxLength - minLength + 1) + minLength;
      for (int j = 0; j < length; j++) {
          printf("%c", rand() % alphabet_size + firstChar);
      }
      printf("\n");
  }

  return EXIT_SUCCESS;
}
