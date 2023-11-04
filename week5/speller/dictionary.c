// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <cs50.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = (26 * 26) + 26;
unsigned int numofword = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table [index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;

    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[1] == '\0')
    {
        return toupper(word[0]) - 'A';
    }
    else
    {
        return (((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A') + 26);
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict_file = fopen(dictionary, "r");
    char dict_word[LENGTH + 1];
    node *n;
    if (dict_file == NULL)
    {
        return false;
    }
    while (fscanf(dict_file, "%s", dict_word) != EOF)
    {
        //fscanf(dict_file, "%s", dict_word);
        n  = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            fclose(dict_file);
            return false;
        }
        strcpy(n->word, dict_word);
        n->next = NULL;
        int index = hash(n->word);
        n->next = table[index];
        table[index] = n;
        numofword++;
    }
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return numofword;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *temp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
