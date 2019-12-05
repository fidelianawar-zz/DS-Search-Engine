#include "QuerySearcher.h"
#include "QueryProcessor.h"
#include <iostream>
#include <vector>

using namespace std;

QuerySearcher::QuerySearcher()
{

}

QuerySearcher::QuerySearcher(IndexInterface* handler, int numDocs)
{
    index = handler;
    amountDocs = numDocs;
}

void QuerySearcher::getQuery(){
    QueryProcessor query;
    input = query.requestUserInput();
    if(input.size()==1){
        vector<pair<string, int>> data;
        if (checkWordExists(input.front())) {
            data=receiveStringRequest(input.front());//equals a vector
        }

        input.pop();
        printResults(data);
    }
    else if(input.front()=="and")
    {

        // andQuery();

    }
    else if(input.front()=="or")
    {
        // orQuery();
    }
    else {
        //notQuery();
    }
}


bool QuerySearcher::checkWordExists(string word){
    if (index->contains(word)) {
        return true;
    }
    else {
        cout << word << " does not exist in the corpus" << endl;
        return false;
    }
}

void QuerySearcher::printResults(vector<pair<string, int>> d){

}

vector<pair<string, int>> QuerySearcher::receiveStringRequest(string request){
    Word wordFile = index->find(request);
    return wordFile.getFiles();
}
