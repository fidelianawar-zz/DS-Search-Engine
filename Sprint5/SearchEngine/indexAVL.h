#ifndef INDEXAVL_H
#define INDEXAVL_H
#include "IndexInterface.h"
#include "dsavltree.h"

class indexAVL: public IndexInterface {
    private:
        DSAVLTree<Word> words;
    public:
        indexAVL();
        void addWord(Word);
        Word& find(string);
        bool contains(string);
        void printWords();
        ~indexAVL() = default;
};

#endif // INDEXAVL_H
