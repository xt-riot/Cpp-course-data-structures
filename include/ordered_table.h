#ifndef ORDERED_TABLE_H
#define ORDERED_TABLE_H

#include <string>
#include <iostream>
#include <fstream>

class ordered_table
{
    public:
        ordered_table();
        virtual ~ordered_table();

        void addWord(std::string);
        bool deleteWord(std::string);
        int findWord(std::string);

        void printTable();
        std::string getDesc();

    protected:
        int findWordProt(std::string, int, int);

    private:
        int totalSize;
        struct data {
            std::string word;
            int occurencies;
        };
        data *table;
        std::string description;
};

#endif // ORDERED_TABLE_H
