#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "gen_mots.h"
#include "gen_texte.h"

#define FPC ' '

int main(int argc, char *argv[]) {

  if (argc < 4) {
    fprintf(stderr, "Error: Missing parameters\n[USAGE]: ./gen_mots words length alphabet_size\n");
    return EXIT_FAILURE;
  }

  // FILE *file = fopen(argv[1], "w");

  // if (file == NULL) {
  //   fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
  //   return EXIT_FAILURE;
  // }

  int words = atoi(argv[1]);

  if (words < 0) {
    fprintf(stderr, "Error: invalid words value (%d)\n", words);
    // fclose(file);
    return EXIT_FAILURE;
  }

  int length = atoi(argv[2]);

  if (length < 0) {
    fprintf(stderr, "Error: invalid length value (%d)\n", length);
    // fclose(file);
    return EXIT_FAILURE;
  }

  int alphabet_size = atoi(argv[3]);

  if (alphabet_size < 0) {
    fprintf(stderr, "Error: invalid alphabet size value (%d)\n", alphabet_size);
    // fclose(file);
    return EXIT_FAILURE;
  }

  // char generated_string[length * words];

  srand((unsigned int) time(NULL));

  // for (int i = 0; i < words; i++) {
  //   memset(generated_string, 0, sizeof(generated_string));
  //   generate_text(generated_string, length, alphabet_size);
  //   fprintf(stdout, "%s ", generated_string);
  // }

  int firstChar = (alphabet_size < UCHAR_MAX - FPC) ? FPC : '\0';
  for (int j = 0; j < words; ++j) {
      for (int k = 0; k < length; ++k) {
          printf("%c", rand() % alphabet_size + firstChar);
      }
      printf("\n");
  }

  // fclose(file);

  return EXIT_SUCCESS;
}

void generate_text(char string[], int len, int alphabet_size) {
  for (int i = 0; i < len; i++) {
    char c = generate_random_character(alphabet_size);
    string[i] = c;
  }
}

char generate_random_character(int alphabet_size) {
  return (char) ('A' + (char) (rand() % alphabet_size));
}
