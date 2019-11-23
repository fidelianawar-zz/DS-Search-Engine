#include "DocumentProcessor.h"
#include "Porter2_Stemmer.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>


using namespace std;
using nlohmann::json;

DocumentProcessor::DocumentProcessor(){
    ifstream input("stopwords.txt");
    string stopWord;

    while (input >> stopWord)
    {
        stopWord.erase(std::remove_if(stopWord.begin(), stopWord.end(), [] (char c)
        {
            return !(c == '\'' || (c >= 'a' && c <= 'z'));
        }), stopWord.end());

        if (stopWord.size() == 0)
        {
            continue;
        }

        stopWordsSet.emplace(stopWord);

        stopWord.erase(std::remove_if(stopWord.begin(), stopWord.end(), [] (char c)
        {
            return c == '\'';
        }), stopWord.end());

        stopWordsSet.emplace(stopWord);
    }
}

string& DocumentProcessor::stripHTML(string& text) const
{
    for (unsigned int i = 0; i < text.size(); i++)
    {
        if (text[i] == '<')
        {
            unsigned int j = i;

            while (text[j] != '>' && j < text.size())
            {
                j++;
            }

            text.erase(i, j - i + 1);
            i--;
        }
    }

    return text;
}


string DocumentProcessor::parseWords(const string& base) const
{
    string processed = base;

    if (processed.size() == 0)
    {
        return processed;
    }

    lowerCase(processed);

    processed.erase(std::remove_if(processed.begin(), processed.end(), [] (char c)
    {
        return !(c == '\'' || (c >= 'a' && c <= 'z'));
    }), processed.end());

    if (processed.size() == 0)
    {
        return processed;
    }

    if (stopWordsSet.count(processed) > 0)
    {
        return "";
    }

    stemString(processed);

    return processed;
}

inline void DocumentProcessor::stemString(string& text) const
{
    string key = text;

    if (stemCache.find(key) != stemCache.end())
    {
        text = stemCache.at(text);
        return;
    }

    Porter2Stemmer::stem(text);
    stemCache.emplace(key, text);
}

string& DocumentProcessor::lowerCase(string& text) const
{
    for (unsigned int i = 0; i < text.size(); i++)
    {
        text[i] = tolower(text[i]);
    }

    return text;
}

void DocumentProcessor::readInputData(){
    ifstream opinion("101310.json");
    if(!opinion){
        cerr << "Cannot open input data file" << endl;
        exit(EXIT_FAILURE);
    }

    json j;
    opinion >> j;
    string contents;
    string a = "";
    contents = j["html"];
    regex numbers("[0-9]");
    char buffer[256];

    for(int i = 0; i < contents.size(); i++){
        if(ispunct(contents[i])){
            contents[i] = NULL;
        }
    }

    //    contents = regex_replace(contents, regex(R"(/div|div|/p|class=|num id|san|num|href|footnote)"), a);
    //    contents = regex_replace(contents, numbers, a);

    //cout << contents;

    istringstream ss(contents);
    do {
        string word;
        ss >> word;
        //cout << word << " ";
        parsed.insert(parseWords(word));
    } while (ss);

    parsed.printInOrder();

}
