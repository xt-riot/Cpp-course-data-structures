#include "ordered_table.h"

/*******************************************************************************************************************
class ordered_table():  Implementation of the ordered table data structure. With each new
                        word, we create a bigger table. The words are stored in increasing
                        order(i.e that < this).
    public:
        -ordered_table():           Initialize the table and the description
        -~ordered_table():          Delete the table
        -addWord(std::string):      Add a new word to the table
        -deleteWord(std::string):   Delete a word(if it exists) from the table. Returns true if it exists and was deleted, false otherwise
        -findWord(std::string):     Find a word(if it exists) in the table. Returns the position.
        -printTable():              Print the whole table
        -getDesc():                 Return the description of the structure
    protected:
        -findWord(std::string, int, int, bool): Helping function to search the table. It splits the table into 2
                                                if the word is in the middle, then return the position, otherwise
                                                check in which half of the table the word is(remember, the table is ordered)
                                                and recursively find the word. The boolean is used to write to the console -
                                                in order to omit writing while adding a word(addWord() uses findWord()).
    private:
        -totalSize:                             The table's current size
        -table:                                 The table(1-D array of struct data)
        -description:                           A string that holds the name of the current class.
    Helping data structure:
        struct data:        A data structure storing the word and how many times it's found in the text.
*******************************************************************************************************************/

/*  ============================================================ *
 *                      PUBLIC CLASSES                           *
 *  ============================================================ */

ordered_table::ordered_table()
{
    //std::cout << "Ordered table constructor." << std::endl;
    description = "ordered-table";
    table = new data[0];
    totalSize = 0;
}

std::string ordered_table::getDesc()
{
    return description;
}


void ordered_table::addWord(std::string word)
{
    // if the word is empty, do nothing
    if(word.empty() || int(word[0] < 97)) return;
    //std::cout << "Adding \"" << word << "\"."<<std::endl;
    int pos;
    // if the total size of the table is 0, it means it holds no words
    if(totalSize == 0) {
        //std::cout << "Total size = 0" << std::endl;
        // therefore, increment the size
        totalSize++;
        // make a new table and add the word
        delete []table;
        table = new data[1];
        table[0].word = word;
        table[0].occurencies = 1;
        return;
    }
    else pos = findWordProt(word, 0, totalSize); // if the size is > 0, search for the word

    // in case it is found, just add the occurencies and return
    if(pos != -1) {
        //std::cout << word << " exists and was found at position" << pos << " another " << table[pos].occurencies << " times." << std::endl;
        table[pos].occurencies++;
        return;
    } // otherwise
    //std::cout << "Adding \"" << word << "\"."<<std::endl;
    totalSize++; // we gotta make a new table with 1 more slot
    data *temp = new data[totalSize]; // create the helping table
    int currPos = 0;
    // start iterating through the table
    while (currPos < totalSize-1) {
        // if we find a word that is smaller than the given word
        if(table[currPos].word.compare(word) > 0) {
            break;
        }
        //std::cout << "\t\tAdding " << table[currPos].word << " because its smaller than " << word << std::endl;
        // as long as the given word is smaller than the current position
        // add the words to the helping table and increment the position
        temp[currPos] = table[currPos];
        currPos++;
    }
    // by now we have split the table into two:
    // temp has every word that is smaller than the word we are given
    // but we did not add the whole table yet
    //std::cout << "\tAdding " << word << std::endl;
    temp[currPos].word = word; // this is the position we must add the word
    temp[currPos++].occurencies = 1;
    //std::cout << "\t\tAdding the rest" << std::endl;
    // for the remaining words in the main table
    for(int i = currPos; i < totalSize; i++) {
        // just copy the words
        temp[i] = table[i-1];
    }
    delete []table; // re-create the table with the new size
    table = new data[totalSize];
    for(int i = 0; i < totalSize; i++) {
        // just copy every word in the helping table
        table[i] = temp[i];
    }
    delete []temp;
    //std::cout << word << " was added." << std::endl;
}

bool ordered_table::deleteWord(std::string word)
{
    int pos = findWordProt(word, 0, totalSize); // search for the word
    int currPos = 0;
    // if the word is found
    if(pos != -1) {
        // decrease the total size
        data *temp = new data[totalSize-1];
        // for every word in the table
        for(int i = 0; i < totalSize; i++) {
            // that is not the same as the word we are about to delete
            if(i == pos)
                continue;
            temp[currPos] = table[i]; // copy it in the helping table
            //std::cout << "Adding " << table[i].word << " to temp at position " << currPos << " from table's position" << i << " : " << temp[currPos].word << " // " << temp[currPos].occurencies << std::endl;
            currPos++;
        }
        delete []table; // delete the table and re-create it with 1 less slot
        table = new data[--totalSize];
        for(int i = 0; i < totalSize; i++) {
            // add all the words from the helping table
            table[i] = temp[i];
        }
        delete []temp;
        //std::cout << word << " was found with " << table[pos].occurencies << " occurencies and was deleted." << std::endl;
        return true; // we successfully deleted the word
    }
    //std::cout << word << " was not found." << std::endl;
    return false; // the word was not found in the table, therefore return false
}

int ordered_table::findWord(std::string word)
{
    int temp = findWordProt(word, 0, totalSize);// find the word

    // this function is called by main, therefore output to the console
    //std::cout << temp << std:: endl;
    if(temp == -1) std::cout << "Requested word " << word << " was not found in the table." << std::endl;
    else std::cout << "Requested word " << table[temp].word << " was found " << table[temp].occurencies << " time(s) in the text." << std::endl;
    return temp;
}

void ordered_table::printTable()
{
    std::streambuf *psbuf, *backup; // used to interchange between console output and file output
    std::ofstream filestr; // the handle to file output
    filestr.open ("./out/ordered-table.txt", std::ios::out);
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

ordered_table::~ordered_table()
{
    delete []table;
}

/*  ============================================================ *
 *                  PROTECTED CLASSES                            *
 *  ============================================================ */

// A helping function that finds the position of the given word - no output to the console
// it splits the table into two and checks in which of the two tables it must continue searching
// until the word is found. Reminding, the table is ordered, therefore each word that is bigger than
// some other word can only be on the right of the latter.
int ordered_table::findWordProt(std::string word, int start, int finish)
{
    int middle = (start + finish) / 2; // get the middle of the table
    //std::cout << middle << " // " << word << " // " << start << " // " << finish << " // " << table[middle].word.compare(word) << std::endl;
    if (middle == start && table[middle].word.compare(word) != 0)
            return -1;

    // if the middle is well defined within the size of the table
    if(table[middle].word.compare(word) == 0 && middle >= start && middle < finish) { // if the current slot holds the given word
        return middle; // return the position
    }
    else if(table[middle].word.compare(word) > 0 && middle >= start && middle < finish) { // if the given word is smaller than the current word
        return findWordProt(word, start, middle); // search in the first half of the table
    }
    else if(table[middle].word.compare(word) < 0 && middle >= start && middle < finish) { // if the given word is bigger than the current word
        return findWordProt(word, middle, finish); // search in the second half of the table
    }

    return -1; // we did not find the word and we can't divide the table anymore - return -1
}
