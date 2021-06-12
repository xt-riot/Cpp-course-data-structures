#ifndef ORDERED_TABLE_H
#define ORDERED_TABLE_H

#include <string>
#include <iostream>

class ordered_table
{
    public:
        ordered_table();
        virtual ~ordered_table();

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

#endif // ORDERED_TABLE_H
