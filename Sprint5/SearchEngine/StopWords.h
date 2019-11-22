#ifndef STOPWORDS_H
#define STOPWORDS_H
#include "dsavltree.h"
#include <fstream>


class StopWords
{
private:
    DSAVLTree<string> stopWordsTree;
public:
    StopWords();
    DSAVLTree<string>&getStopTree();
};

#endif // STOPWORDS_H
