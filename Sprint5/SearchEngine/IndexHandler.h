#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <iostream>
#include "Word.h"

class IndexInterface {
    public:
        virtual void addWord(Word)=0;
        virtual Word& find(std::string)=0;
        virtual bool contains(std::string)=0;
        virtual void printWords()=0;
        virtual ~IndexInterface() = default;
};

#endif // INDEXHANDLER_H
