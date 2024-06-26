#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string>
#include <iostream>

struct dataHM {
    std::string word;
    int occurencies;
};

class hash_map
{
    public:
        hash_map();
        virtual ~hash_map();

        void addWord(std::string word);
        int findWord(std::string word);

    protected:
        int hashFunc(std::string key);

    private:
        dataHM *table;
        int *hashFuncTable;
        int totalSize;
        int letterA;
};

#endif // HASH_MAP_H
