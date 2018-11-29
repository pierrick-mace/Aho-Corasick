#include <stdlib.h>
#include <stdio.h>
#include "search.h"

#define TEST(algo) printf(#algo ": x1=\"%s\",x2=\"%s\" y=\"%s\" : %lu %lu \n",\
            x1, x2, y,\
            algo((const unsigned char*)x1, (const unsigned char*)y),\
            algo((const unsigned char*)x2, (const unsigned char*)y));


int main(void) {
    char x1[] = "baba";
    char x2[] = "ab";
    char y[] = "abababababaabababab";

    TEST(naivesearch);
    TEST(naivesearch_ql);
    TEST(naivesearch_ql_sent);
    TEST(strnaivesearch);
    TEST(strnaivesearch_ql);
    TEST(strnaivesearch_ql_sent);
    TEST(mpsearch);
    TEST(kmpsearch);
    return EXIT_SUCCESS;
}