#ifndef INDEXAVL_H
#define INDEXAVL_H
#include "IndexInterface.h"
#include "DSAVLTree.h"

class indexAVL: public IndexInterface {
    private:

    public:
    DSAVLTree<Word> words;
        indexAVL();
        void addWord(Word);
        Word& find(string);
        bool contains(string);
        void printWords();
        void parseWords();
        void createPersistent();
        ~indexAVL() = default;
         DSAVLTree<Word> getStructure();
        vector<Word> getWordVec();
};

#endif // INDEXAVL_H
