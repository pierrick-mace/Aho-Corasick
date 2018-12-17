#ifndef __GEN_TEXTE__
#define __GEN_TEXTE__

#include <stdio.h>

#define FILE_ERR -1
#define FILE_SUCCESS 1

void generate_text(char string[], int len, int alphabet_size);
char generate_random_character(int alphabet_size);

#endif
