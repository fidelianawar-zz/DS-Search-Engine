#ifndef QUERYSEARCHER_H
#define QUERYSEARCHER_H

#include "QueryProcessor.h"
#include "DSAVLTree.h"
#include "DSHashTable.h"
#include "IndexInterface.h"
#include "DocumentProcessor.h"

class QuerySearcher
{
    struct sort {
        bool operator()(const std::pair<string,int> &left, const std::pair<string,int> &right) {
            return left.second > right.second;
        }
    };

private:
    IndexInterface* index;
    queue<string> input;
    int amountDocs;
    DocumentProcessor process;
    string path_;

public:
    QuerySearcher();
    QuerySearcher(IndexInterface*, int,char *argv[]);
    bool sortbysec(const pair<string,int> &a,
                   const pair<string,int> &b);
    void getQuery();
    bool checkWordExists(string);
    void printResults(vector<pair<string, int>>);
    vector<pair<string, int>> receiveStringRequest(string);
    void notQuery();
    void andQuery();
    void orQuery();
    void simpleQuery(string);

    vector<pair<string, int>> differentVector(vector<pair<string, int>>&, vector<pair<string, int>>&);
    vector<pair<string, int>> intersectVector(vector<pair<string, int>>&, vector<pair<string, int>>&);
    vector<pair<string, int>> unionVector(vector<pair<string, int>>&, vector<pair<string, int>>&);

};

#endif // QUERYSEARCHER_H
