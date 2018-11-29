#ifndef PREF_SUFF_FACT_H
#define PREF_SUFF_FACT_H

#include "trie.h"

Trie prefixes(unsigned char *w);
Trie suffixes(unsigned char *w);
Trie factors(unsigned char *w);

#endif //PREF_SUFF_FACT_H
