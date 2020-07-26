// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * (26 + 1) * LENGTH;

// Hash table
node *table[N];

// Counter of elements in table
int count = 0;

// Recursive function to delete hash table
void destroy(node *current);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if (table[hash(word)] != NULL)
    {
        for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
        {
            if ((strcasecmp(tmp->word, word) == 0))
            {
                //printf("match: '%s' with '%s'\n", tmp->word, word);
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Check first letter of word and assign to table with 26 backets works fine, but relatively slow
    //int idx;
    //if (isalpha(tolower(word[0])))
    //{
    //    //ASCII value of a is 97
    //    idx = tolower(word[0]) - 97;
    //    //printf("to be returned: %i\n", x);
    //    return idx;
    //}

    //Check first letter and length, and assign to table with 26 * length buckets is faster
    int idx;
    idx = tolower(word[0]) - 97 + strlen(word);
    return idx;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(dictFile, "%s", word) != EOF)
    {
        //Create new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        //Hash word and insert
        if (table[hash(word)] != NULL)
        {
            n->next = table[hash(word)];
            table[hash(word)] = n;
            count++;
        }
        else
        {
            table[hash(word)] = n;
            count++;
        }
    }
    //for (node *tmp = table[0]; tmp != NULL; tmp = tmp->next)
    //{
    //    printf("goes to table[0]: %s\n", tmp->word);
    //}
    fclose(dictFile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //printf("count: %i\n", count);
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate through the hash table array
    for (int i = 0; i < N - 1; i++)
    {
        destroy(table[i]);
    }
    return true;
}

void destroy(node *current)
{
    if (current == NULL)
    {
        return;
    }
    destroy(current->next);
    free(current);
    return;
}
