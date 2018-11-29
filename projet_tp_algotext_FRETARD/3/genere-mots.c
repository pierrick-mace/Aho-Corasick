#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

#define FPC ' '    // first printable character : SPACE
#define USAGE() fprintf(stderr, "Usage: %s <nb of words> <word length min>"\
                    " <word length max> <alphabet size>\n", argv[0])

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "This program needs exactly 4 arguments\n");
        USAGE();
        return EXIT_FAILURE;
    }

    // arguments checking
    int nbWords = atoi(argv[1]);
    int minLength = atoi(argv[2]);
    int maxLength = atoi(argv[3]);
    int alphabetSize = atoi(argv[4]);
    if (nbWords < 1) {
        fprintf(stderr, "The <nb of words> must be a"
            " strictly positive integer\n");
        USAGE();
        return EXIT_FAILURE;
    }
    if (minLength < 1) {
        fprintf(stderr, "The <word length min> must be a"
            " strictly positive integer\n");
        USAGE();
        return EXIT_FAILURE;
    }
    if (maxLength < 1) {
        fprintf(stderr, "The <word length max> must be a"
            " strictly positive integer\n");
        USAGE();
        return EXIT_FAILURE;
    }
    if (maxLength < minLength) {
        fprintf(stderr, "The <word length max> must be superior to"
            " <word length max>\n");
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
    for (int j = 0; j < nbWords; ++j) {
        int wordLength = rand() % (maxLength - minLength + 1) + minLength;
        for (int k = 0; k < wordLength; ++k) {
            printf("%c", rand() % alphabetSize + firstChar);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
