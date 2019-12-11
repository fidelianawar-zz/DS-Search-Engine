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

    DocumentProcessor process;
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

    cout << "\nSearch results for: '" << bufferQuery <<"' ";

    istringstream ss(bufferQuery);

    while(getline(ss, bufferQuery, ' '))
    {
        Word w(bufferQuery);
        query = w.getText();
        query = process.parseWords(query);

        if(sW.stopWordsTree.contains(query)){
            if(query == "or" || query == "and" || query == "not"){
                userInput.push(query);
                continue;
            }
            else
            {
                while(!userInput.empty()){
                    userInput.pop();
                }
                bufferQuery.clear();

                cout << "Invalid Form (stop word). Please try again."<< endl;
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
