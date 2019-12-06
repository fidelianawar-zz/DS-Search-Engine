#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include "IndexInterface.h"
#include "IndexAVL.h"
#include "IndexHash.h"
#include "DSAVLTree.h"

class IndexHandler {
    private:
        fstream f;
        IndexInterface* index;
       // DSAVLTree<Word> index1;
        int numDocuments;
        int numWordsIndexed;
        int numWordsTotal;
        vector<string> txtFiles;
    public:
        IndexHandler();
        IndexInterface* returnIndex();
        vector<string> getTextFiles();
        void chooseIndex();
        void getIndex();

        bool doesIndexExist();
        void writeToIndex(DSAVLTree<Word>&);
        void readFromIndex();
        void clearIndex();

        int getNumDocuments();
        void printStatistics();
        void getTopWords();

};

#endif  // INDEXHANDLER_H
