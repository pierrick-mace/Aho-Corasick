#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct _trie *Trie;

Trie createTrie(int maxNode);
size_t sizeTrie(Trie trie);
int nextTrie(Trie trie, int node, unsigned char letter);
size_t nbOccTrie(Trie trie, int node);
void addOccTrie(Trie trie, int node, size_t nbOcc);
void createInitialLoopTrie(Trie trie);
void insertInTrie(Trie trie, unsigned char *w);
bool isInTrie(Trie trie, unsigned char *w);
void disposeTrie(Trie *trie);

#endif //TRIE_H
