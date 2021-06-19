#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <ctype.h>
#include "unordered_table.h"
#include "ordered_table.h"
#include "binary_tree.h"
#include "AVL_tree.h"
#include "hash_table.h"

using namespace std;

// The path to the text file
string path = "small-file.txt";

/********************************************************************************
    preProcess(string): Removes every non alphabetical character for a string
 ********************************************************************************/
string preProcess(string str) {
    string temp = "\0"; // the string to return
    for(int i = 0; i<str.size(); i++) // for every character in the given string
        if(isalpha((int(str[i])))) // if the integer representation of the character is a letter of the alphabet
            temp.append(1, tolower(char(str[i]))); // change it to the lowercase letter and append it in the string
    return temp; // return the string with only alphabetical characters
}

/********************************************************************************
    chooseRandomStrings(string): Record the number of the total words in the
                                 given text and choose a random number in the
                                 range [0, totalNumber/1000). After that, re-visit
                                 the text and store every kth word in the array
                                 of strings(k is the generated random number).
 ********************************************************************************/
void chooseRandomStrings(string *randomStrings)
{
    ifstream file;
    streambuf *psbuf, *backup; // used to interchange between console output and file output
    ofstream filestr; // the handle to file output
    int totalWords = 0;

    file.open(path, ios::in); // open the text so we can record the total words
    if(!file.is_open())
        cout << "Please copy the text file in the directory with name \"gutenberg\" and restart." << endl;
    else {
        string word;
        while(file >> word) totalWords++; // for every word till EOF, count the words
        file.close(); // close the file
    }
    srand(static_cast<unsigned int>(time(0))); // generate a seed so rand() returns a different number each time
    int randomNumbers = rand() % (totalWords / 1000); // generate the random number in the range of [0, totalWords/1000)
                                                      // the /1000 is because we need 1000 words, so generating a number close to the last words
                                                      // will not give us enough room to fill the array of strings


    file.open(path, ios::in); // re-open the text file so we can save the random words
    if(!file.is_open())
        cout << "Please copy the text file in the directory with name \"gutenberg\" and restart." << endl;
    else {
        string word;
        int j = 0, k = 0;
        while( file >> word ) {
            j++; // for every word we iterate, assign a number
            if(j % randomNumbers == 0) { // if that number doesn't return a remainder, add it to the list
                string temp = preProcess(word); // preProcess the string, so we only get alphabetical strings
                if(temp.empty()) // if the word is empty, namely a '\0' or ' ' string
                    j--; // don't count that word - that means we will choose the next eligible word
                else {
                    randomStrings[k++] = temp; // if it's eligible, add it to the array of strings
                }
                if(k == 1000) break; // if we filled the array of strings, stop iterating
            }
        }
        file.close(); // and close the file
    }

    // WE CAN OMIT THIS - JUST FOR DEBUG REASONS
    filestr.open("./out/random-words.txt", ios::out); // open the file to write the random words that we chose
    if(!filestr.is_open())
        cout << "Could not open random-words.txt to write the words" << endl;
    else {
        backup = cout.rdbuf();     // take a backup of the cout buffer
        psbuf = filestr.rdbuf();   // get the file's buffer
        cout.rdbuf(psbuf);         // assign the file's buffer to cout - from now on, if we want to write something to the console,
                                   // it will be re-directed to the output file
        for(int i = 0; i < 1000; i++)
            cout << "Random word(" << i << "): " << randomStrings[i] << endl; // write every word we randomnly chose(mainly debug reasons)
        filestr.close(); // close the output file
        cout.rdbuf(backup);        // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console
    }
}


/********************************************************************************
    loadWords(auto): The function to add every word in the text to the given
                     structure. We use auto, because the data structures are
                     not the same class(or derived from the same class).
                     Therefore, the program will assign the correct class
                     each time.
 ********************************************************************************/
void loadWords(auto &structure)
{
    ifstream file;
    file.open(path, ios::in); // open the text file
    if(!file.is_open())
        cout << "Please rename the file as \"" << path << "\", add it to the main directory and restart." << endl;
    else {
        string word;
        while( file >> word ) { // for every word in the text file
            string temp = preProcess(word); // preProcess the word
            structure.addWord(temp); // and add it to the structure
        }
        file.close(); // when we reach EOF, close the file
    }
}


/********************************************************************************
    findWords(auto, string): Record the time as well as the word and times found
                             in the text file for every randomly chosen word.
                             Write those data into ./out/ folder, with each
                             data structure having it's own .txt file
 ********************************************************************************/
void findWords(auto &structure, string *stringsToSearch)
{
    streambuf *psbuf, *backup; // used to interchange between console output and file output
    ofstream filestr; // the handle to file output
    string path = "./out/" + structure.getDesc() + "-search.txt"; // each structure will output their corresponding searches in their own file
    filestr.open (path , ios::out); // open the corresponding file
    backup = cout.rdbuf();     // take a backup of the cout buffer
    psbuf = filestr.rdbuf();   // get the file's buffer
    cout.rdbuf(psbuf);         // assign the file's buffer to cout - from now on, if we want to write something to the console,
                               // it will be re-directed to the output file

    auto time = chrono::high_resolution_clock::now(); // get the current time
    for(int i = 0; i < 1000; i++)
        structure.findWord(stringsToSearch[i]); // find the word in the structure
    auto timeNow = chrono::high_resolution_clock::now(); // get the current time
    auto duration = chrono::duration_cast<chrono::seconds>(timeNow - time); // take the difference between the times
    cout << structure.getDesc() << " - Total time elapsed: " << duration.count() << " seconds" << endl; // write the total elapsed time into the output file


    filestr.close(); // close the output file
    cout.rdbuf(backup); // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console

    // write the total time difference in the console, too
    cout << "\tTotal time elapsed: " << duration.count() << " seconds" << endl;
}


int main()
{
    // initialize the randomStrings array
    cout << "We start by choosing 1000 random words from the text file." << endl;
    string *randomStrings = new string[1000];
    // fill it with random strings from the text file
    chooseRandomStrings(randomStrings);

    // initialize every data structure
    cout << "We initialize the data structures to be used." << endl;
    unordered_table untab = unordered_table();
    ordered_table ortab   = ordered_table();
    binary_tree btree     = binary_tree();
    AVL_tree atree        = AVL_tree();
    hash_table htab = hash_table();

    // load the text file in every data structure
    cout << "Loading the words into the binary tree." << endl;
    loadWords(btree);
    cout << "Loading the words into the AVL tree." << endl;
    loadWords(atree);
    cout << "Loading the words into the ordered table." << endl;
    loadWords(ortab);
    cout << "Loading the words into the unordered table." << endl;
    loadWords(untab);
    cout << "Loading the words into the hash table." << endl;
    //loadWords(htab);

    // find every word in the randomStrings array - use every structure
    cout << "Start searching for the random words in the binary tree." << endl;
    findWords(btree, randomStrings);
    cout << "Start searching for the random words in the AVL tree." << endl;
    findWords(atree, randomStrings);
    cout << "Start searching for the random words in the ordered table." << endl;
    findWords(ortab, randomStrings);
    cout << "Start searching for the random words in the unordered table." << endl;
    findWords(untab, randomStrings);
    cout << "Start searching for the random words in the hash table." << endl;
    //findWords(htab, randomStrings);

    return 0;
}
