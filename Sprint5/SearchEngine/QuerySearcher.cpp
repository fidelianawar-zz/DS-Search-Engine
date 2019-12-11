#include "QuerySearcher.h"
#include "QueryProcessor.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

QuerySearcher::QuerySearcher()
{

}

QuerySearcher::QuerySearcher(IndexInterface* handler, int numDocs,char *argv[])
{
    indexObj = handler;
    amountDocs = numDocs;
    path_ = argv[1];
}

//recieves query from user
void QuerySearcher::receiveQuery(){
    QueryProcessor query;
    inputQuery = query.requestUserInput();
    if(inputQuery.size()==1){
        vector<pair<string, int>> vectorPair;
        if (checkWordExists(inputQuery.front())) {
            vectorPair = getRequest(inputQuery.front());//equals a vector
        }
        inputQuery.pop();
        print(vectorPair);
    }
    else if(inputQuery.front()=="and")
    {
        andQ();
    }
    else if(inputQuery.front()=="or")
    {
        orQ();
    }
    else {
        notQ();
    }
}

//traces back to file
vector<pair<string, int>> QuerySearcher::getRequest(string request){
    Word wordFile = indexObj->find(request);
    return wordFile.getFiles();
}

//prints results including court case title, date, etc.
void QuerySearcher::print(vector<pair<string, int>> d){
    cout <<"\nDocument Results:" << endl;
    cout << endl << "The number of documents found: " << d.size() << endl<<endl;

    std::sort(d.begin(), d.end(),sort());

    if(!d.empty()){

        for(unsigned int i = 0; i < d.size(); i++){

            stringstream ss(d[i].first);

            vector<string> result;

            while( ss.good() )
            {
                string substr;
                getline( ss, substr, ',' );
                result.push_back(substr);
            }
            cout << "#" << i+1 << " - ";

            cout << "Number of Appearances: " << d[i].second << "\t\n";

            for (size_t i = 0; i < result.size(); i++)
                cout<<"\t" << result[i] << endl;

            if(i == 14){
                break;
            }
        }
    }
    char answer = 'N';
    cout << "Would you like to choose one of the opinions from the result set above and have the first ~300 words of the opinion printed? [Y]/[N]"<< endl;

    cin >> answer;

    if (answer == 'Y'){
        string answer = "";
        string resultPath = "";
        cout << "Type the desired opinion: " ;
        cin >> answer;

        resultPath = path_ + answer;
        process.parseInputData(resultPath,"",'X');

    }

    /*
        year, parties to the case, which justice wrote the majority opinion, etc
    */

    cout << endl;
}

//checking if the word exists in corpus
bool QuerySearcher::checkWordExists(string word){
    cout << endl;
    if (indexObj->contains(word)) {
        cout << word << " exists in corpus" << endl;
        return true;
    }
    else {
        cout << word << " doesn't exist in the corpus" << endl;
        return false;
    }
}

//'not' keyword query functionality
void QuerySearcher::notQ() {
    vector<pair<string, int>> temp;
    vector<pair<string, int>> results;


    while(!inputQuery.empty()){
        if(inputQuery.front() == "not"){

            inputQuery.pop();
            if (checkWordExists(inputQuery.front())) {
                temp=getRequest(inputQuery.front());
                if(!results.empty()){
                    results=notVec(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(inputQuery.front())) {
                temp=getRequest(inputQuery.front());
                if(results.empty()){
                    results=temp;
                }
            }
        }
        inputQuery.pop();
    }
    print(results);
}

//'and' keyword query functionality
void QuerySearcher::andQ() {
    vector<pair<string, int>> temp;
    vector<pair<string, int>> results;

    bool wordExists = true;

    inputQuery.pop();

    while(!inputQuery.empty()){
        if(inputQuery.front()=="not"){
            inputQuery.pop();
            if (checkWordExists(inputQuery.front())) {
                temp=getRequest(inputQuery.front());
                if(!results.empty()){
                    results=notVec(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(inputQuery.front())) {
                temp=getRequest(inputQuery.front());
                if(results.empty()){
                    results=temp;
                }
                else {
                    results=andVec(results, temp);
                }
            }
            else {
                wordExists = false;
            }
        }

        inputQuery.pop();
        if (wordExists == false) {
            int resultsSize = results.size();
            for (int i = 0; i < resultsSize; i++) {
                results.pop_back();
            }
            break;
        }
    }

    print(results);
}

vector<pair<string, int>> QuerySearcher:: orVec(vector<pair<string, int>>& a, vector<pair<string, int>>& b){

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

vector<pair<string, int>> QuerySearcher:: notVec(vector<pair<string, int>>& a, vector<pair<string, int>>& b)
{
    for(unsigned int i=0; i<a.size(); i++){
        for(unsigned int j=0; j<b.size(); j++){
            if(a[i].first==b[j].first){
                a.erase(a.begin()+i);
                b.erase(b.begin()+j);
            }
        }
    }
    return a;
}


vector<pair<string, int>> QuerySearcher:: andVec(vector<pair<string, int>>& a, vector<pair<string, int>>& b){
    vector<pair<string, int>> finalAndVector;
    for(unsigned int i=0; i<a.size(); i++){
        for(unsigned int j=0; j<b.size(); j++){
            if(a[i].first==b[j].first){
                a[i].second+=b[j].second;
                finalAndVector.push_back( make_pair(a[i].first,a[i].second));
            }
        }
    }

    return finalAndVector;
}

//'or' keyword query functionality
void QuerySearcher::orQ(){
    vector<pair<string, int>> results;
    vector<pair<string, int>> temp;

    //we remove the first element
    inputQuery.pop();

    //search words implementd
    while(!inputQuery.empty()) {

        if(inputQuery.front()=="not") {
            inputQuery.pop();
            if (checkWordExists(inputQuery.front())) {
                temp=getRequest(inputQuery.front());
                if(!results.empty()){
                    results=notVec(results, temp);
                }
            }
        }
        else {
            if (checkWordExists(inputQuery.front())) {
                temp=getRequest(inputQuery.front());
                if(results.empty()) {
                    results=temp;
                }
                else {
                    results=orVec(results, temp);
                }
            }
        }
        inputQuery.pop();
    }

    print(results);
}
