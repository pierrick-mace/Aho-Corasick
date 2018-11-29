#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define FPC ' '    // first printable character : SPACE
#define USAGE() fprintf(stderr, "Usage: %s <text length> <alphabet size>\n",\
                    argv[0])

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "This program needs exactly 2 arguments\n");
        USAGE();
        return EXIT_FAILURE;
    }

    // arguments checking
    int textLength = atoi(argv[1]);
    int alphabetSize = atoi(argv[2]);
    if (textLength < 1) {
        fprintf(stderr, "The <text length> must be a"
            " strictly positive integer\n");
        USAGE();
        return EXIT_FAILURE;
    }
    if (alphabetSize < 1 || alphabetSize > UCHAR_MAX + 1) {
        fprintf(stderr, "The <alphabet size> must be an integer"
            " between 1 and %d included\n", UCHAR_MAX + 1);
        USAGE();
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));
    int firstChar = (alphabetSize < UCHAR_MAX - FPC) ? FPC : '\0';
    for (int k = 0; k < textLength; ++k) {
        printf("%c", rand() % alphabetSize + firstChar);
    }

    return EXIT_SUCCESS;
}
