/*
 *  Program # 1
 *  Contains the implementation of the dicitionary tree
 *  CS480-1001
 *  1-26-2023
 *  @author  Noah Hoenig
 */
#define APOSTROPHE 26
#define HYPHEN 27
#define UNDERSCORE 28
#define NULL_TERMINATOR 29 /* \0 signifies end of string*/
#define NCHILD 30
#include "dictionary.h"


// Map appropiate characters to index values

int getIndex(char c) {
    int index = 0;
    // If uppercase subtract appropiate ascii vaue
    if(c >='A' && c <= 'Z'){
        index = c - 'A';
    }
    // If lowercase subtract appropiate ascii vaue
    else {
        index = c - 'a';
    }
    // Handle  a-z, ', -, _  characters
    // Magic numbers occuring from subtraction in the else condition
    switch(index){
            case -58:
                index = APOSTROPHE;
                break;
            case -52:
                index = HYPHEN;
                break;
            case -2:
                index = UNDERSCORE;
                break;
    }
    return index;
}


bool add(char* wordBeingInserted,dictNode*root) {
    dictNode* current = root;
    
    // initalizes a pointer to the first char of the word
    // then increments pointer
    // allows character by character iteration using pointer
    // *p is a char
    for(char* p = wordBeingInserted; *p; ++p){
        
        int index = getIndex(*p);

        // Don't add if character isn't valid
        if (index < 0 && index > NULL_TERMINATOR){
            return false;
        }
        // Add node to path if doesn't exist along that path already
        if(current->next[index] == nullptr) {
            current->next[index] = new(dictNode);
        }
        // Update node
        current = current->next[index];
    }
    // Create node signifying end of word
    current->next[NULL_TERMINATOR] = new(dictNode);
    return true;
    
}

// Search for node path representing the prefix that is read in
dictNode* findEndingNodeOfAStr(char* strBeingSearched,dictNode*root){
    dictNode* traverse = root;
    
    // initalizes a pointer to the first char of the word
    // then increments pointer
    for(char* p = strBeingSearched; *p; ++p) {
        int index = getIndex(*p);
        // If node exists in path
        if(traverse->next[index] != nullptr){
            // Update node
            traverse = traverse->next[index];
        }
        else{
            // Prefix not found in dictionary
            return nullptr;
        }
    }
    // Returns last character of prefix
    return traverse;
}

// Increments count variable if prefix is in dictionary word
void countWordsStartingFromANode(dictNode* start,int &count){
    // prefix not found or word doesn't exist in dictionary
    if(start == nullptr){
        return;
    }
    // word found if end of word (\0) exists
    if(start->next[NULL_TERMINATOR] != nullptr){
        count++;
    }
    // recursive call on all characters
    for (int i = 0; i < NULL_TERMINATOR; i++) {
            countWordsStartingFromANode(start->next[i], count);
        }
}