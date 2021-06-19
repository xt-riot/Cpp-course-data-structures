#include "unordered_table.h"

/*******************************************************************************************************************
class unordered_table():    Implementation of the unordered table data structure. Each new word
                            is searched in the whole table and if it doesn't exist, add it to the end.
    public:
        -unordered_table():         Initialize the table and the description
        -~unordered_table():        Delete the table
        -addWord(std::string):      Add a new word to the table
        -deleteWord(std::string):   Delete a word(if it exists) from the table. Returns true if it exists and was deleted, false otherwise
        -findWord(std::string):     Find a word(if it exists) in the table. Returns the position.
                                    Writes to the console.
        -printTable():              Print the whole table
        -getDesc():                 Return the description of the structure

    protected:
        -findWord(std::string):     Helping function to search for the word. Search every
                                    position in the table, and if the word is found return the position.
                                    It doesn't write to the console.
    private:
        -totalSize:                 The table's current size
        -table:                     The table(1-D array of struct data)
        -description:               A string that holds the name of the current class.

    Helping data structure:
        struct data:        A data structure storing the word and how many times it's found in the text.
*******************************************************************************************************************/

/*  ============================================================ *
 *                      PUBLIC CLASSES                           *
 *  ============================================================ */

unordered_table::unordered_table()
{
    //std::cout << "Unordered table constructor." << std::endl;
    description = "unordered-table";
    table = new data[0];
    totalSize = 0;
}

std::string unordered_table::getDesc()
{
    return description;
}


void unordered_table::addWord(std::string word)
{
    if(word.empty()) return; // if the word is empty, do nothing
    //std::cout << "Adding \"" << word << "\"."<<std::endl;
    int pos;
    if(totalSize == 0) { // if the total size of the table is 0, it means it holds no words
        //std::cout << "Total size = 0" << std::endl;
        totalSize++; // therefore, increment the size
        delete []table; // make a new table and add the word
        table = new data[1];
        table[0].word = word;
        table[0].occurencies = 1;
        return;
    }
    else pos = findWord(word); // if the size is > 0, search for the word
    if(pos != -1) { // in case it is found, just add the occurencies and return
        //std::cout << word << " exists and was found at position" << pos << " another " << table[pos].occurencies << " times." << std::endl;
        table[pos].occurencies++;
        return;
    } // otherwise
    totalSize++; // we gotta make a new table with 1 more slot
    data *temp = new data[totalSize]; // create the helping table
    for(int i = 0; i < totalSize - 1; i++) {
        temp[i] = table[i]; // copy all the words the table has to the new one
    }
    temp[totalSize-1].word = word; // add the new word to the end of the table
    temp[totalSize-1].occurencies = 1;
    delete []table; // delete the main table
    table = new data[totalSize]; // re-create it with the new size
    for(int i = 0; i < totalSize; i++) {
        table[i] = temp[i]; // and copy all the words in the main table
    }
    delete []temp;
    //std::cout << word << " was added." << std::endl;
}

bool unordered_table::deleteWord(std::string word)
{
    int pos = findWord(word); // search for the word
    int currPos = 0;
    if(pos != -1) { // if the word is found
        data *temp = new data[totalSize-1]; // decrease the total size
        for(int i = 0; i < totalSize; i++) { // for every word in the table
            if(i == pos) // that is not the same as the word we are about to delete
                continue;
            temp[currPos] = table[i]; // copy it in the helping table
            //std::cout << "Adding " << table[i].word << " to temp at position " << currPos << " from table's position" << i << " : " << temp[currPos].word << " // " << temp[currPos].occurencies << std::endl;
            currPos++;
        }
        delete []table; // delete the table and re-create it with 1 less slot
        table = new data[--totalSize];
        for(int i = 0; i < totalSize; i++) {
            table[i] = temp[i]; // add all the words from the helping table
        }
        delete []temp;
        //std::cout << word << " was found with " << table[pos].occurencies << " occurencies and was deleted." << std::endl;
        return true; // we successfully deleted the word
    }
    //std::cout << word << " was not found." << std::endl;
    return false; // the word was not found in the table, therefore return false
}

int unordered_table::findWord(std::string word) {
    int temp = findWord(word); // find the word

    // this function is called by main, therefore output to the console
    if(temp == -1) std::cout << "Requested word " << word << " was not found in the table." << std::endl;
    else std::cout << "Requested word " << table[temp].word << " was found " << table[temp].occurencies << " time(s) in the text." << std::endl;
    return temp; // return the position
}

void unordered_table::printTable()
{
    std::streambuf *psbuf, *backup; // used to interchange between console output and file output
    std::ofstream filestr; // the handle to file output
    filestr.open ("./out/unordered-table.txt", std::ios::out);
    backup = std::cout.rdbuf(); // take a backup of the cout buffer
    psbuf = filestr.rdbuf();   // get the file's buffer
    std::cout.rdbuf(psbuf);    // assign the file's buffer to cout - from now on, if we want to write something to the console,
                               // it will be re-directed to the output file

    // BEGIN WRITING EVERY WORD IN THE TABLE
    std::cout << "Printing unordered table..." << totalSize << std::endl;
    for(int i=0; i<totalSize; i++) {
            std::cout << table[i].word << " at position: " << i << " with " << table[i].occurencies << " occurencies." << std::endl;
    }
    std::cout << "Total table size: " << totalSize << std::endl;
    filestr.close(); // close the output file
    std::cout.rdbuf(backup); // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console
}

unordered_table::~unordered_table()
{
    delete []table;
}

/*  ============================================================ *
 *                  PROTECTED CLASSES                            *
 *  ============================================================ */

// A helping function that finds the position of the given word - no output to the console
int unordered_table::findWordProt(std::string word)
{
    for(int i = 0; i<totalSize; i++) { // for every slot in the table
        if(table[i].word.compare(word) == 0) // if the current slot holds the word we are searching for
            return i; // return the position
    }
    return -1; // if got here, it means we didn't find the word - return -1
}
