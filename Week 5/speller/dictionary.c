// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//record wordCount
int wordCount = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 27;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //gets hash
    int index = hash(word);

    // allocates new memory for cursor node
    node *cursor = malloc(sizeof(node));
    if (cursor == NULL)
    {
        return false;
    }

    //start at beginning of hashtable array
    cursor = table[index];

    //iterate until the end of the linked list
    while (cursor != NULL)
    {
        //check if word in cursor matches word
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        //jump to next node in linked list
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //Give different hashes depending if uppercase or lowercase
    if (isupper(word[0]) != 0)
    {
        return (int) word[0] - 'A';
    }

    else
    {
        return (int) word[0] - 'a';
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //Open dictionary file and check if empty
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    //initialise word array to 50 to suit longest word in English
    char word[LENGTH + 1];

    //read string from file one at a  until end of file
    while (fscanf(inptr, "%s", word) != EOF)
    {
        //allocate memory for new node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }

        //copy word found into note and set next node to NULL
        strcpy(newNode->word, word);
        newNode->next = NULL;

        //get index of hashtable to put word into
        int index = hash(newNode->word);

        //if first in index from hashtable
        if (table[index] == NULL)
        {
            //insert node as first node in index of hashtable
            table[index] = newNode;
        }

        else
        {
            //swap new node to be first node in index of hashtable
            newNode->next = table[index]->next;
            table[index]->next = newNode;
        }

        //+1 to word count
        wordCount++;
    }

    //close current input file
    fclose(inptr);

    if (wordCount > 0)
    {
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //iterate over hash table
    for (int index = 0; index < N; index++)
    {
        //allocate memory for cursor
        node *cursorUnload = malloc(sizeof(node));
        if (cursorUnload == NULL)
        {
            return false;
        }

        //set cursor to start of linked list
        cursorUnload = table[index];

        //iterate over linked list
        while (cursorUnload != NULL)
        {
            //allocate memory for temp
            node *temp = malloc(sizeof(node));
            if (temp == NULL)
            {
                return false;
            }

            //set temp to point to same point as cursor
            temp = cursorUnload;

            //get cursor to point at next link in linked list
            cursorUnload = cursorUnload->next;

            //free previous point and decrease word count
            free(temp);
            wordCount--;
        }

        //free memory
        free(cursorUnload);
    }

    if (wordCount == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}