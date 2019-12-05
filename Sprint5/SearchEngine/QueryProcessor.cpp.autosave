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

using namespace std;

QueryProcessor::QueryProcessor()
{
    StopWords stops;
    stopTree=stops.getStopTree();
}

queue<string>& QueryProcessor::requestUserInput(){
    while(!userInput.empty()){
        userInput.pop();
    }

    cout<<"Enter search query"<<endl;
    string query;
    string bufferQuery;
    getline(cin, bufferQuery);
    cout << "Search results for: " << bufferQuery << endl;
    istringstream ss(bufferQuery);

    while(getline( ss, bufferQuery, ' '))
    {
        Word w(bufferQuery);
        query=w.getText();

        //check for stop words
        if(stopTree.contains(query)){
            if(query == "and" || query == "or" || query == "not"){
                userInput.push(query);
                continue;
            }
            else
            {
                cout<<"The stop word: "<<query<<" was detected please try again."<<endl;

                //if stop word detected, clear queue
                while(!userInput.empty()){
                    userInput.pop();
                }
                bufferQuery.clear();
                requestUserInput();
                break;
            }
        }
        else
        {
            userInput.push(query);
        }
    }
    return userInput;
}
