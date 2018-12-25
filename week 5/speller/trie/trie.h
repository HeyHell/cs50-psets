#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

// Maximum length of the trie's children array
#define CHILDREN_LENGTH 27

typedef struct tnode *trie;

// Prototypes
trie create_trie(void);
void add_trie(trie, char *);
bool insert_trie(trie, char *);
int gethash(char letter);
void unload_trie(trie);
bool check_trie(trie, const char *);

#endif // TRIE_H