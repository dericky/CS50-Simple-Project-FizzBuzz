/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include <cs50.h>

typedef struct node{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int words;
node *hashTable[26];
int hasher(char input[]){
    char letter = tolower(input[0]);
    return (letter - 97);
}
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    char tempWord[strlen(word)+1];
    for(int i = 0; i < strlen(word); i++){
        tempWord[i] = tolower(word[i]);
    }
    tempWord[strlen(word)] = '\0';
    if(strlen(word) > 0 && strlen(word) <= LENGTH)
    {
        int index = hasher(tempWord);
        node *temp = hashTable[index];
        while(temp!=NULL){
            string compare = temp->word;
            for(int j = 0; j < strlen(compare); j++){
                compare[j] = tolower(compare[j]);
            }
            if(strcmp(compare, tempWord) == 0){
                return true;
            }
            temp=temp->next;
        }
    }
    return false;
}


void append(node *hashTable[], node *newNode, int index){
    node *temp = NULL;
    if(hashTable[index] != NULL){
        temp = hashTable[index];
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
    else
    {
        hashTable[index] = newNode;
    }
    words++;
}
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open input file 
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    for(int i = 0; i < 26; i++){
        hashTable[i] = NULL;
    }
    char word[LENGTH+1];
    while(fscanf(input, "%45s", word) == 1){
        int hashIndex = hasher(word);
        node *newNode = malloc(sizeof(node));
        if(newNode == NULL){
            return false;
        }
        for(int i = 0; i < strlen(word); i++){
            newNode->word[i] = word[i];
        }
        append(hashTable, newNode, hashIndex);
    }
    fclose(input);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    int i = 0;
    for(i = 0; i < 26; i++){
        node *temp = hashTable[i];
        while(temp != NULL){
            node *temp2 = temp;
            temp = temp->next;
            free(temp2);
        }
    }
    return true;
}
