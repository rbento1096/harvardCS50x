// Implements a dictionary's functionality
// https://cs50.harvard.edu/x/2021/psets/5/speller/
// USING LARGE DICTIONARY AND TOLSTOY.TXT: ME VS HARVARD STAFF
// TIME IN LOAD: 0.02 VS 0.02
// TIME IN CHECK: 2.31 VS 0.46
// TIME IN SIZE: 0.00 VS 0.00
// TIME IN UNLOAD: 0.00 VS 0.01
// TOTAL TIME: 2.33 VS 0.49

// This was the first iteration.
// Code was done only to attain the 100% grade
// however, as soon as possible, I'll perfect it until I get closer to Harvard's values

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
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
// 26 alphabetic charcters times the possible word lengths (1-45)
const unsigned int N = 26 * LENGTH;
// Hash table
node *table[N];

// word count for dictionary
int dic_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash key (index) is obtained by hashing current word
    int index = hash(word);
    // creates a temporary node that will act as cursor
    node *temp = malloc(sizeof(node));
    // if memory allocation fails
    if (temp == NULL)
    {
        printf("Not enough memory in system.\n");
        return false;
    }

    //points to the first value of the list
    temp->next = table[index];
    // if there are no nodes
    if (temp->next == NULL)
    {
        // free temp node
        free(temp);
        // return false, word is not on dictionary
        return false;
    }

    // else check if current node has the same word
    // if it doesnt, iterate through the list until you find it or the list ends
    while (strcasecmp(word, temp->next->word) != 0)
    {
        // if current node doesn't match and is the last node
        if (temp->next->next == NULL)
        {
            // free temp node
            free(temp);
            // word is not on dictionary
            return false;
        }
        // else check the next node
        temp->next = temp->next->next;
    }

    // free temp node
    free(temp);
    // if the function reaches this stage, return true: match has been found!
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // I used the first letter of the word and the word's size to create this hash table
    // this gets the size
    int size = strlen(word);
    // gets the first letter and converts it to lower case
    char first_letter = tolower(word[0]);
    // subtracting the first character from a, gives us a relative position in the table
    char a = 'a';
    // the hash key is equal to the max word length times the distance from the first letter + word size minus 1 due to zero indexing
    int length = LENGTH * (first_letter - a) + size - 1;
    return length;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    // allocates space for a word of maximum size (45)
    char str[LENGTH];

    // checks every string in file until the end (End Of File)
    while (fscanf(file, "%s", str) != EOF)
    {
        // creates a node to store the word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Not enough memory in system.\n");
            return false;
        }

        // copies the current word from the dictionary into the node
        strcpy(n->word, str);
        // generates the hash key for this word
        int index = hash(str);
        // links the current node to the beginning of the list
        n->next = table[index];
        // links the table to the current node
        table[index] = n;
        // counts the number of words on the dictionary for the size() function
        dic_words++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // merely returns the number of words in dictionary
    return dic_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // creates two nodes to iterate over every list
    node *cursor = malloc(sizeof(node));
    node *temp = malloc(sizeof(node));

    if (cursor == NULL || temp == NULL)\
    {
        printf("Not enough memory in system.\n");
        return false;
    }

    // loops through the whole table
    for (int i = 0; i < N; i++)
    {
        // sets both cursors to point at the first element
        cursor->next = table[i];
        temp->next = table[i];

        // if the first element doesn't exist, no memory allocated: proceed
        if (cursor->next == NULL)
        {
            continue;
        }

        // else, point the cursor node to the next node in the list
        cursor->next = cursor->next->next;
        // free the node temp is still pointing at
        free(temp->next);
        // change free to point at the node cursor is now pointing at
        temp-> next = cursor->next;

    }

    free(cursor);
    free(temp);
    return true;
}
