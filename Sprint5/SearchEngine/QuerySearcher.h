#ifndef QUERYSEARCHER_H
#define QUERYSEARCHER_H

#include "QueryProcessor.h"
#include "DSAVLTree.h"
#include "DSHashTable.h"
#include "IndexInterface.h"

class QuerySearcher
{

private:
    IndexInterface* index;
    queue<string> input;
    int amountDocs;

public:
    QuerySearcher();
    QuerySearcher(IndexInterface*, int);
    void getQuery();
    bool checkWordExists(string);
    void printResults(vector<pair<string, int>>);
    vector<pair<string, int>> receiveStringRequest(string);
};

#endif // QUERYSEARCHER_H
