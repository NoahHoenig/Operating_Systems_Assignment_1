/*
 *  Program # 1
 *  This files runs the application
 *  Inserts the contents of a vocabulary file into a dictionary tree data
 *      structure.  Each word is stored along a path of the tree. Starting from 
 *      the child nodes of the root node, each tree node represents a single 
 *      character of the word.
 *  Read words from test text file, and for each word read in: search, count, 
 *      and print the number of words in the dictionary tree that start with it. 
 *  Compile using the Makefile command 'make' in command prompt
 *  Run program using './countprefix vocabulary.txt testfile1.txt' in command prompt
 *  CS480-1001
 *  1-26-2023
 *  @author  Noah Hoenig
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include "dictionary.h"


using namespace std;

int main(int argc, char **argv) {

    // Check if user gives 3 inputs
    if(argc != 3){
        cout << "Error: wrong number of arguments" << endl;
        cout << "Usage: " << argv[0] << " <vocabulary.txt> <testfile.txt>" << endl;
        return 1;
    }

    string vocab_file = argv[1]; 
    string test_file = argv[2];

    dictNode* root = new(dictNode);

    
    // characters by which to seperate words by
    const char* delimiters = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";

    // DICTIONARY FILE
    ifstream dictstream(vocab_file); // open vocab file for parsing 
    string line; 
    if(dictstream.is_open()){
        // iterate over dictionary file line by line 
        while (getline(dictstream, line)) {
            // convert string to array of characters
            char* line_c = new char[line.length()+1];
            strcpy(line_c,line.c_str());
        
            // seperate line into words while eliminating unwanted characters
            char* word = strtok(line_c,delimiters);
            while (word != nullptr) {
                
                // call add method to insert word to build the dictionary tree 
                add(word,root);
                // read next word
                word = strtok(NULL, delimiters);  
            } 
        }
        dictstream.close();
    }else{
        cout << "Error: vocab file not found" << endl;
        return 1;
    }

    int count = 0;

    // PREFIX FILE
    ifstream teststream(test_file); // open test file for parsing
    if(teststream.is_open()){
        // iterate over prefix file line by line 
        while (getline(teststream, line)) {
            // convert string to array of characters
            char* line_c = new char[line.length()+1];
            strcpy(line_c,line.c_str());
        
            // seperate line into words while eliminating unwanted characters
            char* word = strtok(line_c,delimiters);
            while (word != nullptr) {

                // Count all the words that start with the prefix
                countWordsStartingFromANode(findEndingNodeOfAStr(word,root),count);
                
                cout << word << " " << count << endl;
                
                // read next word, reset count
                count = 0;
                word = strtok(NULL, delimiters);  
            } 
        }
        teststream.close();
    }else{
        cout << "Error: test file not found" << endl;
        return 1;
    }
    return 0;
}
