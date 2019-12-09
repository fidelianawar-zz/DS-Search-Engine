#ifndef QUERYSEARCHER_H
#define QUERYSEARCHER_H

#include "QueryProcessor.h"
#include "DSAVLTree.h"
#include "DSHashTable.h"
#include "IndexInterface.h"
#include "DocumentProcessor.h"

class QuerySearcher
{
    //sort two pairs based upon which has higher ranking
    struct sort {
        bool operator()(const std::pair<string,int> &left, const std::pair<string,int> &right) {
            return left.second > right.second;
        }
    };

private:
    IndexInterface* indexObj;
    queue<string> inputQuery;
    int amountDocs;
    DocumentProcessor process;
    string path_;

public:

    vector<pair<string, int>> notVec(vector<pair<string, int>>&, vector<pair<string, int>>&);
    vector<pair<string, int>> andVec(vector<pair<string, int>>&, vector<pair<string, int>>&);
    vector<pair<string, int>> orVec(vector<pair<string, int>>&, vector<pair<string, int>>&);

    QuerySearcher();
    QuerySearcher(IndexInterface*, int,char *argv[]);
    bool sortbysec(const pair<string,int> &a,
                   const pair<string,int> &b);
    void receiveQuery();
    bool checkWordExists(string);
    void print(vector<pair<string, int>>);
    vector<pair<string, int>> getRequest(string);

    void simple(string);

    void notQ();
    void andQ();
    void orQ();

};

#endif // QUERYSEARCHER_H
