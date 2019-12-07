#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <queue>
#include <string>
#include "DSAVLTree.h"
#include "StopWords.h"

using namespace std;

class QueryProcessor
{
private:
    DSAVLTree<string> stopTree;
    queue<string> userInput;
    StopWords sW;


public:
    QueryProcessor();
    queue<string>& requestUserInput();
    void populateStopTree();
};

#endif // QUERYPROCESSOR_H
