#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct _trie *Trie;

Trie createTrie(int maxNode);
void insertInTrie(Trie trie, unsigned char *w);
bool isInTrie(Trie trie, unsigned char *w);
void disposeTrie(Trie *trie);

#endif //TRIE_H
