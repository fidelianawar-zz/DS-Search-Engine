#include "QuerySearcher.h"
#include "QueryProcessor.h"
#include <iostream>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

QuerySearcher::QuerySearcher()
{

}


QuerySearcher::QuerySearcher(IndexInterface* handler, int numDocs,DocumentProcessor process)
{
    index = handler;
    amountDocs = numDocs;
    process = process;
}

void QuerySearcher::getQuery(){
    QueryProcessor query;
    input = query.requestUserInput();
    if(input.size()==1){
        vector<pair<string, int>> data;
        if (checkWordExists(input.front())) {
            data = receiveStringRequest(input.front());//equals a vector
        }
        input.pop();
        printResults(data);
    }
    else if(input.front() == "and")
    {
        andQuery();
    }
    else if(input.front() == "or")
    {
        orQuery();
    }
    else {
        notQuery();
    }
}

bool QuerySearcher::checkWordExists(string word){
    cout << endl;
    if (index->contains(word)) {
        // cout << word << " exists in corpus" << endl;
        return true;
    }
    else {
        // cout << word << " does not exist in the corpus" << endl;
        return false;
    }
}

void QuerySearcher::printResults(vector<pair<string, int>> d){
    cout << endl << "The number of documents found: " << d.size() << endl<<endl;

    if(!d.empty()){
        for(int i = 0; i < d.size(); i++){
            cout << "# of Appearances: " << d[i].second << "\t\n";

            stringstream ss(d[i].first);

            vector<string> result;

            while( ss.good() )
            {
                string substr;
                getline( ss, substr, ',' );
                result.push_back( substr );
            }
            for (std::size_t i = 0; i < result.size(); i++)
                std::cout<<"\t" << result[i] << std::endl;


        }
    }

    /*
        year, parties to the case, which justice wrote the majority opinion, etc
    */
    cout << endl;
}

vector<pair<string, int>> QuerySearcher::receiveStringRequest(string request){
    Word wordFile = index->find(request);
    return wordFile.getFiles();
}

void QuerySearcher::notQuery() {
    vector<pair<string, int>> temp;
    vector<pair<string, int>> results;


    while(!input.empty()){
        if(input.front() == "not"){

            input.pop();
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(!results.empty()){
                    results = differentVector(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(results.empty()){
                    results = temp;
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
        if(input.front() == "not"){
            input.pop();
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(!results.empty()){
                    results = differentVector(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(input.front())) {
                temp=receiveStringRequest(input.front());
                if(results.empty()){
                    results = temp;
                }
                else {
                    results = intersectVector(results, temp);
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
}


vector<pair<string, int>> QuerySearcher:: unionVector(vector<pair<string, int>>& a, vector<pair<string, int>>& b){

    for(unsigned int i = 0; i < a.size(); i++){
        for(unsigned int j = 0; j < b.size(); j++){
            if(a[i].first == b[j].first){
                a[i].second += b[j].second;
                b.erase(b.begin() + j);
            }
        }
    }

    for (pair<string, int> p: b) {
        a.push_back(p);
    }

    return a;
}

vector<pair<string, int>> QuerySearcher:: differentVector(vector<pair<string, int>>& a, vector<pair<string, int>>& b)
{
    for(unsigned int i = 0; i < a.size(); i++){
        for(unsigned int j = 0; j < b.size(); j++){
            if(a[i].first == b[j].first){
                a.erase(a.begin() + i);
                b.erase(b.begin() + j);
            }
        }
    }
    return a;
}

vector<pair<string, int>> QuerySearcher:: intersectVector(vector<pair<string, int>>& a, vector<pair<string, int>>& b){
    vector<pair<string, int>> finalAndVector;
    vector<pair<string, int>>::iterator it;

    for(unsigned int i = 0; i < a.size(); i++){
        for(unsigned int j = 0; j < b.size(); j++){
            if(a[i].first == b[j].first){
                a[i].second += b[j].second;
                finalAndVector.push_back( make_pair(a[i].first,a[i].second));
            }
        }
    }
    return finalAndVector;
}

void QuerySearcher::orQuery(){
    vector<pair<string, int>> results;
    vector<pair<string, int>> temp;

    //we remove the first element "and" from the queue
    input.pop();

    //while the queue is not empty, search words are implementd
    while(!input.empty()) {

        if(input.front() == "not") {
            input.pop();
            if (checkWordExists(input.front())) {
                temp = receiveStringRequest(input.front());
                if(!results.empty()){
                    results = differentVector(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(input.front())) {
                temp = receiveStringRequest(input.front());
                if(results.empty()) {
                    results = temp;
                }
                else {
                    results = unionVector(results, temp);
                }
            }
        }
        input.pop();
    }

    printResults(results);
}
