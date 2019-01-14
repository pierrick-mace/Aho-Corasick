#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct _trie *Trie;

Trie createTrie(int maxNode);
size_t sizeTrie(Trie trie);
int nextTrie(Trie trie, int node, unsigned char letter);
size_t getOccurencesTrie(Trie trie, int node);
void addOccurencesTrie(Trie trie, int node, size_t occurences);
void initializeTrie(Trie trie);
void insertInTrie(Trie trie, unsigned char *w);
bool isInTrie(Trie trie, unsigned char *w);
void freeTrie(Trie trie);
#endif //TRIE_H
