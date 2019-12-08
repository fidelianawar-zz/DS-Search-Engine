#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include "DocumentProcessor.h"
#include "QueryProcessor.h"
#include "StopWords.h"
#include "DSAVLTree.h"
#include "Word.h"
#include <queue>
#include <string>

using namespace std;

QueryProcessor::QueryProcessor()
{

}

queue<string>& QueryProcessor::requestUserInput(){
    sW.populateStopWords();
    while(!userInput.empty()){
        userInput.pop();
    }

    cout<<"Enter search query: ";
    string query;
    string bufferQuery;

    cin.ignore();
    getline(cin, bufferQuery);
    //cin.ignore();

    cout << "Search results for: '" << bufferQuery <<"' "<< endl;

    istringstream ss(bufferQuery);

    while(getline(ss, bufferQuery, ' '))
    {
        Word w(bufferQuery);
        query=w.getText();
        cout << endl << "the query is: " << query << endl << endl;
        //check for stop words
        if(sW.stopWordsTree.contains(query)){
            if(query == "and" || query == "or" || query == "not"){
                cout << "query included and/or/not" << endl;
                userInput.push(query);
                continue;
            }
            else
            {
                //if stop word detected, clear queue
                while(!userInput.empty()){
                    userInput.pop();
                }
                bufferQuery.clear();

                cout << "Invalid Form. Please try again."<< endl;
                requestUserInput();
                break;
            }
        }
        else
        {
            cout << query << " is not a stop word\n";
            userInput.push(query);
        }
    }
    cout << "size of queue is: " << userInput.size() << endl;
    return userInput;
}
