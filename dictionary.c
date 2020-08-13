// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // This line included in CS50 problem set files, not written but S Hunerwadel
#include <string.h>
#include <strings.h>
#include "dictionary.h" // This line included in CS50 problem set files, not written but S Hunerwadel

// Represents a node in a hash table
typedef struct node // This line included in CS50 problem set files, not written but S Hunerwadel
{
    char word[LENGTH + 1];// This line included in CS50 problem set files, not written but S Hunerwadel
    struct node *next; // This line included in CS50 problem set files, not written but S Hunerwadel
}
node; // This line included in CS50 problem set files, not written but S Hunerwadel

// Number of buckets in hash table
const unsigned int N = 65536; // This line included in CS50 problem set files, not written but S Hunerwadel

// Hash table
node *table[N]; // This line included in CS50 problem set files, not written but S Hunerwadel

// Declare variable for counting words in dictionary
int count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word) // This line included in CS50 problem set files, not written but S Hunerwadel
{
    // Hash word
    int i = hash(word);

    // Access linked list at hash index
    node *cursor = table[i];

    // Compare word to those in list
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false; // This line included in CS50 problem set files, not written but S Hunerwadel
}

// Hashes word to a number(credit to https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function)
unsigned int hash(const char *word) // This line included in CS50 problem set files, not written but S Hunerwadel
{
    unsigned int hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Handle capital and lower case letter the same
        if (word[i] > 90)
        {
            hash_value = (hash_value << 2) ^ word[i];
        }
        else
        {
            hash_value = (hash_value << 2) ^ (word[i] + 32);
        }
    }
    return hash_value % N; //N is size of hashtable
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary) // This line included in CS50 problem set files, not written but S Hunerwadel
{
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");

    // Check for successful load
    if (inptr == NULL)
    {
        printf("Could not open file \n");
        return false;
    }

    // Declare variables
    char *temp_word = malloc(LENGTH + 1);

    // Read words from dictionary
    while (fscanf(inptr, "%s", temp_word) != EOF)
    {
        // Allocate memory for new node in proper linked list
        node *n = malloc(sizeof(node));

        // Check for memory error
        if (n == NULL)
        {
            printf("Memory location returned NULL. Could not store %s from dictionary. \n", temp_word);
            return false;
        }

        // Store word in node
        strcpy(n->word, temp_word);

        // Hash word
        int i = hash(temp_word);

        // Check if first entry at array location
        if (table[i] == NULL)
        {
            // Point head at new node
            table[i] = n;
            // Point new node at NULL
            n->next = NULL;
        }
        // Put new node at beginning of linked list
        else
        {
            // Point new node at old list head
            n->next = table[i];
            // Point actual head at new node
            table[i] = n;
        }
        // Count number loaded from dictionary
        count += 1;
    }
    // Free memory
    free(temp_word);
    // Close dictionary
    fclose(inptr);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void) // This line included in CS50 problem set files, not written but S Hunerwadel
{
    // Return number of words loaded from dictionary
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void) // This line included in CS50 problem set files, not written but S Hunerwadel
{
    // Declare counter variable
    int counter = 0;

    for (int i = 0; i < N; i++)
    {
        // Access linked list at hash index
        node *cursor = table[i];
        node *tmp = cursor;

        // Free each node
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        // Set counter equal to number of array indexes freed
        counter = i;
    }
    // Check that all indexes were freed successfully
    if (counter == N - 1)
    {
        return true;
    }
    else
    {
        return false;
    }

}
