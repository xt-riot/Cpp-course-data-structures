#include "unordered_table.h"

unordered_table::unordered_table()
{
    std::cout << "Constructor." << std::endl;
    table = new data[0];
    totalSize = 0;
}

void unordered_table::addWord(std::string word)
{
    if(word.empty()) return;
    std::cout << "Adding \"" << word << "\"."<<std::endl;
    int pos;
    if(totalSize == 0) {
        std::cout << "Total size = 0" << std::endl;
        totalSize++;
        delete []table;
        table = new data[1];
        table[0].word = word;
        table[0].occurencies = 1;
        return;
    }
    else pos = findWord(word, 0);
    if(pos != -1) {
        std::cout << word << " exists and was found at position" << pos << " another " << table[pos].occurencies << " times." << std::endl;
        table[pos].occurencies++;
        return;
    }
    totalSize++;
    data *temp = new data[totalSize];
    for(int i = 0; i < totalSize - 1; i++) {
        temp[i] = table[i];
    }
    temp[totalSize-1].word = word;
    temp[totalSize-1].occurencies = 1;
    delete []table;
    table = new data[totalSize];
    for(int i = 0; i < totalSize; i++) {
        table[i] = temp[i];
    }
    delete []temp;
    std::cout << word << " was added." << std::endl;
}

bool unordered_table::deleteWord(std::string word)
{
    int pos = findWord(word, 0);
    int currPos = 0;
    if(pos != -1) {
        data *temp = new data[totalSize-1];
        for(int i = 0; i < totalSize; i++) {
            if(i == pos)
                continue;
            temp[currPos] = table[i];
            std::cout << "Adding " << table[i].word << " to temp at position " << currPos << " from table's position" << i << " : " << temp[currPos].word << " // " << temp[currPos].occurencies << std::endl;
            currPos++;
        }
        delete []table;
        table = new data[--totalSize];
        for(int i = 0; i < totalSize; i++) {
            table[i] = temp[i];
        }
        delete []temp;
        std::cout << word << " was found with " << table[pos].occurencies << " occurencies and was deleted." << std::endl;
        return true;
    }
    std::cout << word << " was not found." << std::endl;
    return false;
}

int unordered_table::findWord(std::string word, int start)
{
    for(int i = start; i<totalSize; i++) {
        if(table[i].word.compare(0, word.length(), word) == 0) {
            std::cout << "\t\t\t\t" << word << " was found in the table at position" << i << std::endl;
            return i;
        }
    }
    return -1;
}

void unordered_table::printTable()
{
    std::cout << "Printing unordered table..." << totalSize << std::endl;
    for(int i=0; i<totalSize; i++) {
            std::cout << table[i].word << " at position: " << i << " with " << table[i].occurencies << " occurencies." << std::endl;
    }
}

unordered_table::~unordered_table()
{
    delete []table;
}
