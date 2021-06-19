#include "hash_table.h"

#define ALPHABET_TOTALNUMBER 24

// a = 97, b = 98, ... z = 122 in ASCII
// letterA = int('a') = ASCII 97, letterZ = int('z') = ASCII 122
// even if OS uses different table, as long as the alphabet is sequentially stored, int('a') will
//  yield the first letter of the alphabet and every other letter will be int('a') + i, where i is the letter's position in the alphabet

/*******************************************************************************************************************
class hash_table(): Implementation of the hash table data structure. A helping table is used to
                    store starting/finish positions. The implementation divides the hash table
                    to subtables, with every subtable storing words starting with a given letter.
                    Therefore, each alphabet letter has it's own slots in the hash table -
                    collisions will be absent because the hash function doesn't have to hash
                    the word and store it in the next empty slot. On the contrary, if the
                    corresponding subtable doesn't have empty slots, we create new empty slots
                    to that subtable. While, we gain a huge advantage during the searching of a
                    word, we have degrading disadvantages due to the sorting algorithm and the
                    addition of new slots every time we run out of empty slots in a given subtable.
    public:
        -hash_table():          instatiate the hash table to store every word(Open addressing hasing:
                                    every word is stored in this hash table)
                                instatiate a helping table to store the starting/finishing positions of
                                    a subtable
        -~hash_table():         delete the table
        -addWord(std::string):  Add the given word in the hash table
        -findWord(std::string): Search for the given word in the hash table. Return the position in
                                    the table
        -printTable():          Print the non-empty slots of the hash table
        -getDesc():             Return the description of the structure

    protected:
        -hashFunc(int):         Hashing function - arguments: the first letter of the word, as an int
                                    returns the corresponding position in the helping table
        -reconstruct():         Called when there are no empty slots left in a subtable - adds 10 new
                                    slots in every subtable which has 1 or less empty slot.
                                    returns the new hash table
        -sortSlots(dataHM):     Sorting algorithm to sort every word in their subtable.
                                    returns the sorted hash table

    private:
        -dataHM *table:         The hash table storing the words
        -int *hashFuncTable:    The helping table storing the starting/finish positions of every letter
        -int totalSize:         The total size of the hash table

    Helping data structure:
        struct dataHM:          A data structure storing the word and how many times it's found in the text
*******************************************************************************************************************/


/*  ============================================================ *
 *                      PUBLIC CLASSES                           *
 *  ============================================================ */

hash_table::hash_table()
{
    // instatiating hash table to a multiple of the total number of the letters in the alphabet
    // this way, each letter will have X free space before reconstructing the table
    // used to limit the number of times we copy the table to a new one
    //std::cout << "Hash Table constructor." << std::endl;
    description = "hash-table";
    hashFuncTable = new int[ALPHABET_TOTALNUMBER];
    totalSize = ALPHABET_TOTALNUMBER * 5;
    table = new dataHM[totalSize];
    for(int i = 0; i<totalSize; i++)
        table[i].word = "";
    for(int i = 0; i<ALPHABET_TOTALNUMBER; i++)
        hashFuncTable[i] = i * (totalSize / ALPHABET_TOTALNUMBER);
}

std::string hash_table::getDesc()
{
    return description;
}


void hash_table::addWord(std::string word)
{
    if (word.empty() || int(word[0]) < 97) return;
    //std::cout << "Adding \"" << word << "\"."<<std::endl;
    int found = findWordProt(word); // search the word before doing anything
    if(found != -1) { // if we find it, just increase the occurencies and return
        //std::cout << "Increasing the total times we've seen the word." << std::endl;
        table[found].occurencies++;
        return;
    }
    // getting the result of the hash function
    int letter = int(word[0]);
    int start = hashFunc(letter);
    int finish = hashFunc(letter + 1);
    int pos = hashFuncTable[start];
    // iterating through the table, starting at the hash result position and stoping when either we encounter another starting letter(therefore the word is not in the table) or we go to end of table
    // linear probing
    while(pos < hashFuncTable[finish] && start < totalSize) {
        if( table[pos].word.empty() ) {
            //std::cout << "Adding the word " << word << std::endl;
            // we found an empty slot
            table[pos].word = word;
            table[pos].occurencies = 1;
            table = sortSlots(table); // sort the new word
            return;
        }
        // we did not find an empty spot
        pos++;
    }
    // in case we jumped out of the while, we did not add the word

    // if the next position is empty, we jumped out of the while because the letter's slots are full
    // add the word and reconfigure the hasfunctable so the next letter starts after this word
    if(pos < totalSize && table[pos].word.empty() ) {
        table[pos].word = word;
        table[pos].occurencies = 1;
        //std::cout << "\tAdding the word " << word << " but, first, we have to move next letter's start." << std::endl;
        hashFuncTable[finish] = ++pos;
        //std::cout << hashFuncTable[finish] << std::endl;
        table = sortSlots(table); // sort the new word
        return;
    }
    // if the next position is occupied, reconstruct the hash table and add the word afterwards
    table = reconstruct();
    addWord(word);
}

int hash_table::findWord(std::string word)
{
    int temp = findWordProt(word);
    if(temp == -1) std::cout << "Requested word " << word << " was not found in the table." << std::endl;
    else std::cout << "Requested word " << table[temp].word << " was found " << table[temp].occurencies << " time(s) in the text." << std::endl;
    return temp;
}

void hash_table::printTable()
{
    std::streambuf *psbuf, *backup; // used to interchange between console output and file output
    std::ofstream filestr; // the handle to file output
    filestr.open ("./out/hash-table.txt", std::ios::out);
    backup = std::cout.rdbuf(); // take a backup of the cout buffer
    psbuf = filestr.rdbuf();   // get the file's buffer
    std::cout.rdbuf(psbuf);    // assign the file's buffer to cout - from now on, if we want to write something to the console,
                               // it will be re-directed to the output file

    // BEGIN WRITING EVERY WORD IN THE TABLE
    std::cout << std::endl << "Printing the hash table:" << std::endl;
    for(int i = 0; i < ALPHABET_TOTALNUMBER-1; i++) {
        for(int j = hashFuncTable[i]; j < hashFuncTable[i+1]; j++)
            if(table[j].word.empty()) continue;
            else std::cout << "\t" << table[j].word << std::endl;
    }
    filestr.close(); // close the output file
    std::cout.rdbuf(backup); // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console
}

hash_table::~hash_table()
{
    delete []table;
}


/*  ============================================================ *
 *                  PROTECTED CLASSES                            *
 *  ============================================================ */


int hash_table::hashFunc(int letter)
{
    // the hash function is trivial: it returns the position of the first letter in a table
    // the helping table stores the starting position of every sub-hashtable according to the corresponding letter of the alphabet
    return ((letter - int('a')) % ALPHABET_TOTALNUMBER);
}

dataHM* hash_table::sortSlots(dataHM *tab)
{
    // trivial sorting algorithm
    // sorting the hash table minimizes the time used to search for a given word

    //std::cout << "Starting sort" << std::endl;
    dataHM *temp = new dataHM[totalSize];
    // for every subtable
    for(int i = 0; i < ALPHABET_TOTALNUMBER-1; i++) {
        int start = hashFuncTable[i];
        temp[start] = tab[start];
        // start sorting every slot that has non-empty word
        for(int j = start+1; j < hashFuncTable[i+1]; j++) {
            if(!tab[j].word.empty()) {
                int pos = j-1;
                // while the new word to sort, check if it's position should be before the words in the table
                // if it is, swap the current word in the table with the one we got and continue -
                //  - till the new word has been placed correctly in the table
                while(pos >= start && temp[pos].word.compare(tab[j].word) > 0) {
                    temp[pos+1] = temp[pos];
                    temp[pos] = tab[j];
                    pos--;
                }
                // if the current word is bigger than every other already-sorted word, just add it at the end
                if(pos == j-1) temp[j] = tab[j];
            }
            // if the unsorted table has an empty word at the current position, just copy it to the sorted table
            // there will be junk in the new table, otherwise
            else temp[j].word = "";
        }
    }
    return temp;
}

dataHM* hash_table::reconstruct()
{
    // give another 10 slots to the letters that have no space or are left with 1 free space
    // initializing temporary helping tables
    int *newSlots = new int[ALPHABET_TOTALNUMBER];
    for(int i = 0; i<ALPHABET_TOTALNUMBER; i++)
        newSlots[i] = hashFuncTable[i];
    dataHM *temp = new dataHM[totalSize];
    for(int i = 0; i < totalSize; i++)
        temp[i] = table[i]; // copy current hash table so we can delete it and make a new one with more slots

    // if a subtable needs more slots, store that information to the new helping table
    for(int i = 1; i<ALPHABET_TOTALNUMBER; i++) {
        int finish = hashFunc(i + int('a'));
        int prevLetter = newSlots[finish] - 2;

        if ( prevLetter < totalSize && table[prevLetter].word.empty() )
            continue; // previous letter has empty spaces - we don't have to add new slots
        else {
            for(int j = i; j < ALPHABET_TOTALNUMBER; j++) {
                finish = hashFunc(j + int('a'));
                newSlots[finish] = newSlots[finish] + 10;
            }
        }
    }

    // delete the hash table and re-make/initialize it with the new total size
    delete []table;
    totalSize = newSlots[ALPHABET_TOTALNUMBER-1];
    table = new dataHM[totalSize];
    for(int i = 0; i<totalSize; i++)
        table[i].word = "";

    // start copying the helping table to the hash table
    for(int i = 0; i < ALPHABET_TOTALNUMBER-1; i++) {
        int start = hashFunc(i+int('a'));
        int oldDiff = hashFuncTable[start+1] - hashFuncTable[start]; // previous starting/finishing positions of the subtable
        // for every subtable, copy every previous word - empty slots don't need to be copied because we instatiated the table above
        for(int j = 0; j < oldDiff; j++) // for every word in the previous positions of the subtable
            table[hashFuncTable[start] + j] = temp[hashFuncTable[start] + j]; // copy the word to the new hash table
    }
    hashFuncTable = newSlots; // copy the new startin/finishing positions of the subtables
    return table;
}

int hash_table::findWordProt(std::string word)
{
    if(word.empty() || int(word[0]) < 97)
        return -1;
    int letter = int(word[0]); // get the integer value of the first letter of the word
    int start = hashFunc(letter); // get the starting position of the subtable
    int finish = hashFunc(letter + 1); // get the finish position of the subtable
    int middle = hashFuncTable[start] + ((hashFuncTable[finish] - hashFuncTable[start]) / 2); // where should we start searching the subtable
    int step = 0;

    // we must check if the table's middle position is an empty slot - if so, check the previous positions until we find the biggest word
    while(table[middle].word.empty() && middle >= hashFuncTable[start])
        middle--;

    // check if the current hashed word is the one we are searching for.
    if (table[middle].word.compare(word) == 0) {
        //std::cout << "We found the word " << word << " at position: " << middle << " of the table. It is found " << table[middle].occurencies << " times in the text." << std::endl;
        return middle;
    }
    else {
        // we did not find the word at the current position - check if the given word is less than the current and adjust the step accordingly
        //std::cout << "We did not find the word " << word << std::endl;
        if ( table[middle].word.compare(word) < 0 && !table[middle].word.empty())
            step = 1; // the word, we are looking for, is in the next positions
        else if (!table[middle].word.empty() && table[middle].word.compare(word) > 0)
            step = -1; // the word, we are looking for, is in the previous positions

        middle += step;
        // checking if the position to be search doesn't exceed the table's size or the starting/finishing position of the words starting with the same letter
        while(middle < totalSize && middle >= hashFuncTable[start] && middle < hashFuncTable[finish] && !table[middle].word.empty()) {
            // searching in the table
            if(table[middle].word.compare(word) == 0)
                return middle; // we found the word
            // we did not find the word - go to the next position
            middle += step;
        }
    }
    // the word is not in the subtable, therefore the word doesn't exist in our hash table.
    return -1;
}
