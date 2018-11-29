#ifndef SEARCH_H
#define SEARCH_H

// algorithmes de recherche du nombre d'occurences de x dans y
// pour les algorithmes ..._sent y ddoit pointer sur une zone mémoire
// pouvant contenir le mot yx

size_t naivesearch(const unsigned char *x, const unsigned char *y);
size_t naivesearch_ql(const unsigned char *x, const unsigned char *y);
size_t naivesearch_ql_sent(const unsigned char *x, const unsigned char *y);
size_t strnaivesearch(const unsigned char *x, const unsigned char *y);
size_t strnaivesearch_ql(const unsigned char *x, const unsigned char *y);
size_t strnaivesearch_ql_sent(const unsigned char *x, const unsigned char *y);
size_t mpsearch(const unsigned char *x, const unsigned char *y);
size_t kmpsearch(const unsigned char *x, const unsigned char *y);
size_t bmsearch(const unsigned char *x, const unsigned char *y);
size_t horspoolsearch(const unsigned char *x, const unsigned char *y);
size_t quicksearch(const unsigned char *x, const unsigned char *y);

#endif //SEARCH_H