#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <iostream>

struct dataHM {
    std::string word;
    int occurencies;
};

class hash_table
{
    public:
        hash_table();
        virtual ~hash_table();

        void addWord(std::string word);
        int findWord(std::string word);
        void printTable();

    protected:
        int hashFunc(int letter);
        dataHM* reconstruct();
        dataHM* sortSlots(dataHM *tab);

    private:
        dataHM *table;
        int *hashFuncTable;
        int totalSize;
};

#endif // HASH_TABLE_H
