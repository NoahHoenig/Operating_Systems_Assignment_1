/*
 *  Program # 1
 *  Header file containing dictionary tree methods
 *  CS480-1001
 *  1-26-2023
 *  @author  Noah Hoenig
 */
#ifndef DICTIONARY_H
#define DICTIONARY_H
#define NCHILD 30 /* a-z, ', -, _, terminator of word */ 

class dictNode  
{  
    public:
        dictNode* next[NCHILD];  
};
// method to add word read in from file to dictionary
bool add(char* wordBeingInserted,dictNode*root); 

// method to find last node of prefix, returns last node(not the /0 node)
dictNode* findEndingNodeOfAStr(char* strBeingSearched,dictNode*root);  

// method to count words in dict file starting from a node
void countWordsStartingFromANode(dictNode* start, int &count);  
 
// helper function that converts the character of a 
// word to an index of a child node
// Creates a mapping of index values to character values
int getIndex(char c);

#endif