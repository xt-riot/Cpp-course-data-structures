#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <iostream>
#include <fstream>

struct dataHM {
    std::string word;
    int occurencies;
};

class hash_table
{
    public:
        hash_table();
        virtual ~hash_table();

        void addWord(std::string);
        int findWord(std::string);
        void printTable();
        std::string getDesc();

    protected:
        int hashFunc(int letter);
        dataHM* reconstruct();
        dataHM* sortSlots(dataHM *tab);
        int findWordProt(std::string);

    private:
        dataHM *table;
        int *hashFuncTable;
        int totalSize;
        std::string description;
};

#endif // HASH_TABLE_H
