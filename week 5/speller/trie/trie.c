// Implements trie's functionality

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "trie.h"

// Trie structure
struct tnode
{
    bool is_word;
    struct tnode *children[CHILDREN_LENGTH];
};

// Create new trie node; if failed - returns NULL
trie create_trie(void)
{
    trie root = malloc(sizeof(struct tnode));
    if (!root)
        return NULL;

    // Initialize all elements to NULL
    for (int i = 0; i < CHILDREN_LENGTH; i++)
        root->children[i] = NULL;
    return root;
}

// Insert the key into the node;
// if successful - returns true, otherwise - false
bool insert_trie(trie node, char *key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        int hash = gethash(key[i]);
        if (!node->children[hash])
        {
            trie temp = create_trie();
            if (!temp)
                return false;

            node->children[hash] = temp;
            node = temp;
        }
        else
            node = node->children[hash];
    }
    node->is_word = true;
    return true;
}

// Calculate the hash of the letter
int gethash(char letter)
{
    return (letter == '\'') ? CHILDREN_LENGTH - 1 : letter - 'a';
}

// Unload the trie
void unload_trie(trie node)
{
    for (int i = 0; i < CHILDREN_LENGTH; i++)
        if (node->children[i])
            unload_trie(node->children[i]);
    free(node);
}

// Check if the word is in dictionary
bool check_trie(trie node, const char *key)
{
    trie temp = node;
    for (int i = 0; key[i] != '\0'; i++)
    {
        int hash = gethash(tolower(key[i]));
        if (!temp->children[hash])
            return false;
        temp = temp->children[hash];
    }
    return temp->is_word;
}