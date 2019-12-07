#ifndef STOPWORDS_H
#define STOPWORDS_H
#include "DSAVLTree.h"
#include <fstream>

class StopWords
{
private:

public:
    DSAVLTree<string> stopWordsTree;
    StopWords();
    DSAVLTree<string>& getStopTree();
    void populateStopWords();
};

#endif // STOPWORDS_H
