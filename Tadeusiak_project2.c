/** \file Tadeusiak_project2.c
 * Submission for Project 2.
 * This file opens a text file containing the words of a dictionary, reads them
 * and stores them. It then checks words entered in the command line against the
 * newly created dictionary, and outputs if they exist.
 * 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include headers for functions and stack type */
#include "dictionary.h"

/* Function prototype chomp. Returns a pointer to a string after removing a
 * trailing CR or LF from input string*/
char *chomp(char *string);

int main(int argc, char *argv[])
{
    //open text file containing words
    FILE *infile;
    infile = fopen("words.txt", "r");
    //check that file has been opened ok
    if (infile == NULL)
    {
       printf("error opening 'words.txt'\n");
       system("PAUSE");
       exit(1);
    }
    
    //create Dictionary
    Dictionary *dict = create_dictionary();
    
    // read each line from the file words.txt, add each word to dict
    int word_added;
    char string[80];
    while (fgets(string, 80, infile))
    {
        //attempt to add word to dictionary
        word_added = add_word(dict, chomp(string));

        //print a message if invalid word entry not added
        if(word_added == 0)
        {
            printf("%s not added.\n", chomp(string));
        }
    }
    
    //==========================================================================
    //go through each entry in argv[]
    int i;
    char *word;
    
    for(i = 1; i < argc; ++i)
    {
        word = argv[i];
        
        // work out the length of the word
        int length = strlen(chomp(word));
        
        //use find_word to determine whether it is in the dictionary
        if( find_word(dict, word))
        {
            //if the word is in the dictionary, print a success message
            printf("\'%s\' is OK\n", word);
        }
        //if the word is not in the dictionary, but it ends in 's'
        else if(word[length-1]=='s')
        {
            //set the 's' to '\0'
            word[length-1] = '\0';
            //use find_word to determine whether it is in the dictionary
            if( find_word(dict, word))
            {
                //if it is, print singular success
                printf("Singular of \'%ss\' is OK\n", word);
            }
            else
            {
                //otherwise print an error
                printf("\'%ss\' is not OK\n", word);
            }  
        }
        else
        {
            //otherwise print an error
            printf("\'%s\' is not OK\n", word);
        }        
    }
    
    //close the data file
    fclose(infile);
    
    //free memory associated with dictionary and contents
    free_dictionary(dict);
    
    system("PAUSE");	
    return 0;
}

//------------------------------------------------------------------------------

/** Function definition chomp. Remove the trailing newline from the specified
 *  string, if it has one. If the string does not end in a newline then this
 *  will not modify the string.
 *
 * \param string The string to remove the newline from.
 * \return A pointer to the string.
 */
char *chomp(char *string)
{
    int size = strlen(string); 
    int pos;

    // move back down the string from the end, as there may be a CR, CR+LF or LF there...    
    for(pos = (size - 1); pos >= 0; --pos)
    {
        // If the character is a CR or LF, replace it with null
        if(string[pos] == 0xD || string[pos] == 0xA)
        {
            string[pos] = 0;
        }
        else
        {
            return string;
        }
    }    
    return string;
}
