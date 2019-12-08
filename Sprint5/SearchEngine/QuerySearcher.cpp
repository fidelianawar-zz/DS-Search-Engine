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
    cout << "got into getQuery" << endl;
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
        andQuery();
    }
    else if(input.front()=="or")
    {
        orQuery();
    }
    else {
        notQuery();
    }
}

bool QuerySearcher::checkWordExists(string word){
    index->printWords();
    cout << endl;
    if (index->contains(word)) {
        cout << word << " exists in corpus" << endl;
        return true;
    }
    else {
        cout << word << " does not exist in the corpus" << endl;
        return false;
    }
}

void QuerySearcher::printResults(vector<pair<string, int>> d){
cout << "Print results"<< endl;
}

vector<pair<string, int>> QuerySearcher::receiveStringRequest(string request){
    Word wordFile = index->find(request);
    return wordFile.getFiles();
}

void QuerySearcher::notQuery() {
    vector<pair<string, int>> temp;
    vector<pair<string, int>> results;


    while(!input.empty()){
        cout << "query is not empty" << endl;
        if(input.front() == "not"){

            input.pop();
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(!results.empty()){
                 //   results=differentVector(results, temp);
                }
            }
        }
        else {
            cout << "the front of queue is: " << input.front() << endl;
            if (checkWordExists(input.front())) {
                cout << "front word exists" << endl;
                temp=receiveStringRequest(input.front());
                if(results.empty()){
                    results=temp;
                }
            }
        }
        input.pop();
    }
    printResults(results);
}

void QuerySearcher::andQuery() {
    vector<pair<string, int>> temp;
    vector<pair<string, int>> results;

    bool wordExists = true;

    //we remove  first element "and" from  queue
    input.pop();

    //while queue not empty, search words implementd
    while(!input.empty()){
        if(input.front()=="not"){
            input.pop();
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(!results.empty()){
                  //  results=differentVector(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(results.empty()){
                    results=temp;
                }
                else {
                 //   results=intersectVector(results, temp);
                }
            }
            else {
                wordExists = false;
            }
        }

        input.pop();
        if (wordExists == false) {
            int resultsSize = results.size();
            for (int i = 0; i < resultsSize; i++) {
                results.pop_back();
            }
            break;
        }
    }

    printResults(results);
}/*
vector<pair<string, int>> QuerySearcher:: unionVector(vector<pair<string, int>>& a, vector<pair<string, int>>& b){
vector<pair<string, int>> temp;
return temp;

}
vector<pair<string, int>> QuerySearcher:: differentVector(vector<pair<string, int>>& a, vector<pair<string, int>>& b){
    vector<pair<string, int>> temp;
    return temp;
}
vector<pair<string, int>> QuerySearcher:: intersectVector(vector<pair<string, int>>& a, vector<pair<string, int>>& b){
    vector<pair<string, int>> temp;
    return temp;
}*/
void QuerySearcher::orQuery(){
    vector<pair<string, int>> results;
    vector<pair<string, int>> temp;

    //we remove the first element "and" from the queue
    input.pop();

    //while the queue is not empty, search words are implementd
    while(!input.empty()) {

        if(input.front()=="not") {
            input.pop();
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(!results.empty()){
                    //results=differentVector(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(results.empty()) {
                    results=temp;
                }
                else {
                  //  results=unionVector(results, temp);
                }
            }
        }
        input.pop();
    }

    printResults(results);
}
