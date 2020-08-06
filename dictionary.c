// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = (LENGTH +1)* 'z';

// Hash table
node *table[N];

int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word); //obtener index de palabra
    
    node *cursor = table[index]; //sets cursor to the index value
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0) //check if word is in dict
        {
            return true; //word in dictionary
        }
        cursor = cursor->next; //passes to next word in dict
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file) //if file damaged
    {
        return false;
    }
    //Read each word
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (!new_node)
        {
            return false;
        }
        
        strcpy(new_node->word, word); //copies word to new location(node)
        new_node->next = NULL; //empty node after the word
        
        int index = hash(word); //where the new word is located
        if(table[index] == NULL)
        {
            table[index] = new_node; // if no pointer set, sets one
        }
        else //if pointer has alredy a pointer
        {
            new_node->next = table[index]; //sets index for location of pointer
            table[index] = new_node; //new pointer for index
        }
        word_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //free linked list
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
