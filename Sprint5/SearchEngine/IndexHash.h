#ifndef INDEXHASH_H
#define INDEXHASH_H
#include "IndexInterface.h"
#include "DSHashTable.h"
#include "DSAVLTree.h"

class indexHash : public IndexInterface {
    private:
        DSHashtable<string, Word> words;
    public:
        indexHash();
        void addWord(Word);
        Word& find(string);
        bool contains(string);
        void printWords();
        void parseWords();
        ~indexHash() = default;
        DSAVLTree<Word> getStructure();
        vector<Word> getWordVec();
};

#endif // INDEXHASH_H
