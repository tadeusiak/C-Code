/** \file dictionary.h
 *  This file contains the  prototypes for functions in dictionary.c that are
 *  visible to the rest of the code.
 * 
 */


/** A node in the list. Contains one word and references an adjacent
 *  node containing another word. */
typedef struct node
{
   char *word; //!< A pointer to allocated memory storing the word.
   struct node *next_node; //!< A pointer referencing an adjacent node in the list
}  Node;

/** The dictionary. Contains pointers to the heads of 26 lists, each containing
 *  words starting with the same letter. */
typedef struct dictionary
{
   Node *wordlists[26]; //!< An array of pointers to 26 lists
}  Dictionary;                 


Dictionary *create_dictionary(void);
void free_dictionary(Dictionary *dict);
int add_word(Dictionary *dict, char *word);
int find_word(Dictionary *dict, char *word);
void print_dictionary(Dictionary *dict);




