#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include "Word.h"

class IndexInterface {
    public:
        virtual void addWord(Word)=0;
        virtual Word& find(string)=0;
        virtual bool contains(string)=0;
        virtual void printWords()=0;
        virtual void parseWords()=0;
        virtual DSAVLTree<Word> getStructure()=0;
        virtual vector<Word> getWordVec()=0;
        virtual ~IndexInterface() = default;
};

#endif // INDEXINTERFACE_H
