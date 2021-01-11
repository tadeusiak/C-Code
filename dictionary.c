/** \file dictionary.c
 * This file contains functions relating to manipulating a dictionary, 
 * represented by an array pointing to 26 linked lists, each list containing
 * linked lists of nodes containing words which start with the same letter.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include headers for functions and stack type */
#include "dictionary.h"

/* Function prototype process_word, not visible outside this file */
char *process_word(char *word);

/**Function definition create_dictionary. Creates a new dictionary structure
 * and allocates memory.
 *
 * \param void.
 * \return A pointer to the new Dictionary.
 */
Dictionary *create_dictionary(void)
{
    // allocate memory for a new Dictionary structure
    Dictionary *new_dictionary;
    new_dictionary = (Dictionary*)calloc(1, sizeof(Dictionary));
    //test if memory allocated correctly
    if(new_dictionary == NULL)
    {
        printf("Unable to allocate memory for dictionary.\n");
        exit(1);
    }
    
    //return the pointer to the new Dictionary
    return new_dictionary;
}

/**Function definition free_dictionary. Releases the memory used by a dictionary
 * and any internal storage it may have associated with it. This should be
 * called at the end of the program.
 *
 * \param dict A pointer to the dictionary.
 * \return void.
 */
void free_dictionary(Dictionary *dict)
{
    int list_number;
    //temporary pointers
    Node *ptr;
    Node *ptr2;
    for(list_number=0; list_number<26; list_number++)
    {
        ptr = dict->wordlists[list_number];
        while(ptr != NULL)
        {                    
            //free memory allocated for each word
            
            //free memory allocated for each node
            
            //CODE DOES NOT WORK!!
            ptr2 = ptr;
            ptr = ptr->next_node;
            free(ptr2);
        }        
    }
    //free memory allocated for dictionary
    free(dict);
}

/**Function definition add_word. Adds the provided word to the dictionary,
 * provided that the word does not already exist in the dictionary. Returns
 * false if invalid word entry attempted or word already exists, and true if
 * word added successfully.
 *
 * \param dict A pointer to the dictionary.
 * \param word A pointer to the word to add.
 * \return int Returns boolean.
 */
int add_word(Dictionary *dict, char *word)
{
    //if non-alphabetical word entered, exit function - word not added
    if(process_word(word)==NULL)
    {
        return 0;
    }
    
    //check whether the word pointed to by 'word' already exists in 'dict'
    //if it does, the word is not added and false is returned
    int result = find_word(dict, word);
    if(result==1)
    {
        return 0;
    }
    
    //if it does not, the word is added to the storage inside dict...
    
	//=================== Add an item to the list =============================
        
	//allocate a new node structure
	Node *new_node;
	//allocate space for a new node and initialise to NULL
	new_node = (Node*)calloc(1, sizeof(Node));
	//test if memory allocated correctly
	if(new_node == NULL)
    {
        printf("Unable to allocate memory for new node.\n");
        exit(1);
    }
        
    //allocate space for new word
    new_node->word = (char*)calloc(strlen(word), sizeof(char));
    //test if memory allocated correctly
	if(new_node->word == NULL)
    {
        printf("Unable to allocate memory for new word.\n");
        exit(1);
    }
    
    //copy the word pointer over into the newly created node
	strcpy(new_node->word, word);
    
    //assign word to correct list number
    int listnum = word[0] - 'a';
    
    //store the pointer to the new word in the newly created node
    //EITHER start a new alphabetical list
    if(dict->wordlists[listnum] == NULL)
    {
        dict->wordlists[listnum] = new_node;
    }
    //OR add to existing alphabetical list
    else
    {
        new_node->next_node = dict->wordlists[listnum];
        dict->wordlists[listnum] = new_node;
    } 
	
	//word has been added to 'dict', therefore return true
	return 1;
}

/**Function definition find_word. Attempts to find the word pointed to by
 * 'word' in 'dict'. Returns true (1) if the word is found, false (0) if it is not,
 * and true (-1) if an invalid word search attempted.
 *
 * \param dict A pointer to the dictionary.
 * \param word A pointer to the word to find.
 * \return int Returns true or false.
 */
int find_word(Dictionary *dict, char *word)
{
    //if non-alphabetical word entered, exit function - invalid string
    if(process_word(word)==NULL)
    {
        return -1;
    }
    
    //determine which alphabetical list to search
    int listnum = word[0] - 'a';
    
    //assign temporary pointer to head of alphabetical list
    Node *ptr;
    ptr = dict->wordlists[listnum];
    
    //work through each node in wordlist ie each word searching for word
    while(ptr!=NULL)
    {
        //if word to find is same as word in node currently being pointed
        //at in wordlist of dictionary, return true i.e. word found
        if(strcmp(word, ptr->word) == 0)
        {
            return 1;
        }
        //move pointer to next node in list
        ptr = ptr->next_node;
    }
    
    //return false ie word not found
    return 0;
}

/**Function definition print_dictionary. APrints the contents of the dictionary
 * with one word on each line.
 *
 * \param dict A pointer to the dictionary.
 * \return void
 */
void print_dictionary(Dictionary *dict)
{
    int list_number;
    //a temporary pointer
    Node *node;
    //work through each of 26 linked lists
    for(list_number=0; list_number<26; list_number++)
    {
        node = dict->wordlists[list_number];
        //work through each node in list until a null pointer is reached
        while(node != NULL)
        {
            //print word in node
            printf("%s\n", node->word);
            node = node->next_node;
        }        
    }
}

//------------------------------------------------------------------------------

/**Function definition process_word. Check that all characters are alphabetical
 * & if so convert to lower case.
 *
 * \param word The word to process.
 * \return A pointer to the word, or NULL if not a word.
 */
char *process_word(char *word)
{
    int number_of_letters = strlen(word);
    int letter;
    for(letter = 0; letter < number_of_letters; letter ++)
    {
        if(isalpha(word[letter]) == 0)
        {
            if(word[letter] != '\'' && word[letter] != '.')
            {
                return NULL;
            }
        }
        word[letter] = tolower(word[letter]);
    }
    return word;
}


