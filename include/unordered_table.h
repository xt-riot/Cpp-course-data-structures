#ifndef UNORDERED_TABLE_H
#define UNORDERED_TABLE_H

#include <string>
#include <iostream>
#include <fstream>

class unordered_table
{
    public:
        unordered_table();
        virtual ~unordered_table();

        void addWord(std::string);
        bool deleteWord(std::string);
        int findWord(std::string);

        std::string getDesc();
        void printTable();

    protected:
        int findWordProt(std::string);

    private:
        int totalSize;
        struct data {
            std::string word;
            int occurencies;
        };
        data *table;
        std::string description;
};

#endif // UNORDERED_TABLE_H
