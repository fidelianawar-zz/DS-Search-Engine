#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include <queue>
#include <string>
#include "DSAVLTree.h"

using namespace std;

class QueryProcessor
{
private:
    DSAVLTree<string>stopTree;
    queue<string> userInput;

public:
    QueryProcessor();
    queue<string>& requestUserInput();
};

#endif // QUERYPROCESSOR_H
