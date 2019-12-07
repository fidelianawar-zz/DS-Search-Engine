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

}

queue<string>& QueryProcessor::requestUserInput(){

    sW.populateStopWords();

    while(!userInput.empty()){
        userInput.pop();
    }

    cout<<"Enter search query"<<endl;
    string query;
    string bufferQuery;
    getline(cin, bufferQuery);
    cin.ignore();
    cout << "Search results for: '" << bufferQuery <<"' "<< endl;
    istringstream ss(bufferQuery);

    while(getline(ss, bufferQuery, ' '))
    {
        cout << "made it inside while loop " << endl;
        Word w(bufferQuery);
        query=w.getText();

        //check for stop words
        if(sW.stopWordsTree.contains(query)){
            if(query == "and" || query == "or" || query == "not"){
                cout << "query included and/or/not" << endl;
                userInput.push(query);
                continue;
            }
            else
            {
                cout<<"The stop word: '"<<query<<"' was detected please try again."<<endl;

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
            cout << "Query is not a stop word\n";
            userInput.push(query);
        }
    }
    return userInput;
}
