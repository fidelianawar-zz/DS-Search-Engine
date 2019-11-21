#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <locale>
#include "word.h"
#include "stopwords.h"
#include "dsavltree.h"
#include <algorithm>
#include "searcher.h"

using namespace std;

class queryProcessor
{
private:
    DSAVLTree<string>stopTree;
    queue<string> input;

public:
    queryProcessor();
    queue<string>& requestInput();

};

#endif // QUERYPROCESSOR_H
