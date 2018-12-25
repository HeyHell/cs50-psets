// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "trie.h"
#include "dictionary.h"

trie root = NULL;

// Number of the found words
unsigned long words_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool res = check_trie(root, word);
    return res;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Create a new trie
    root = create_trie();
    if (!root)
        return false;

    // Load dictionary
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
        return false;

    // Temporary storage a word
    char buf[LENGTH + 1];
    int i = 0;
    for (char c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // Found the end of the word
        if (c == '\n')
        {
            buf[i] = '\0';
            if (!insert_trie(root, buf))
                return false;

            words_count++;
            i = 0;
        }
        else
        {
            buf[i] = c;
            i++;
        }
    }

    // Close dictionary
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    unload_trie(root);
    return true;
}
