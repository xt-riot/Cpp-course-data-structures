#ifndef UNORDERED_TABLE_H
#define UNORDERED_TABLE_H

#include <string>
#include <iostream>

class unordered_table
{
    public:
        unordered_table();
        virtual ~unordered_table();

        void addWord(std::string word);
        bool deleteWord(std::string word);
        int findWord(std::string word, int start);

        void printTable();

    protected:

    private:
        int totalSize;
        struct data {
            std::string word;
            int occurencies;
        };
        data *table;
};

#endif // UNORDERED_TABLE_H
