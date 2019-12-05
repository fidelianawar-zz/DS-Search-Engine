#ifndef INDEXHASH_H
#define INDEXHASH_H
#include "IndexInterface.h"
#include "DSHashTable.h"

class indexHash : public IndexInterface {
    private:
        DSHashtable<string, Word> words;
    public:
        indexHash();
        void addWord(Word);
        Word& find(string);
        bool contains(string);
        void printWords();
        ~indexHash() = default;
};

#endif // INDEXHASH_H
