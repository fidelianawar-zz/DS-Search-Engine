#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include "IndexInterface.h"
#include "IndexAVL.h"
#include "IndexHash.h"
#include "DSAVLTree.h"
#include "DSHashTable.h"
#include "DocumentProcessor.h"
#include "Word.h"

class IndexHandler {
    struct sort {
        bool operator()(const std::pair<string,int> &left, const std::pair<string,int> &right) {
            return left.second > right.second;
        }
    };
    private:
        fstream f;
        IndexInterface * index;
        DSAVLTree<Word> wordTree;
        int numDocuments;
        int numWordsIndexed;
        int numWordsTotal;
        int avgPerOpinion;
        vector<string> txtFiles;
        vector<Word> allWords;
    public:
        IndexHandler();
        IndexInterface* returnIndex();
        vector<string> getTextFiles();
        void chooseIndex(DocumentProcessor,string);
        void getIndex();
        void addToIndex(DocumentProcessor,string);


        bool doesIndexExist();
        void writeToIndex(DSAVLTree<Word>&);
        void writeToIndex();
        void readFromIndex();
        void clearIndex();

        int getNumDocuments();
        void printStatistics();
        void getTopWords();

};

#endif  // INDEXHANDLER_H
