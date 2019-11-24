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
#include <ctime>
#include<dirent.h>


using namespace std;
using nlohmann::json;

DocumentProcessor::DocumentProcessor(){
    ifstream input("stopWordFile.txt");
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

inline string parseCaseTitle(string& absoluteURL)
{
    istringstream sections(absoluteURL);
    string title;

    string r1;

    for (int i = 0; i < 4; i++)
    {
        getline(sections, r1, '/');
    }

    istringstream split(r1);

    string r2;

    while (getline(split, r2, '-'))
    {
        if (r2 == "v")
        {
            r2 = "v.";
        }
        else if (r2.size() > 0)
        {
            r2[0] = toupper(r2[0]);

            if (r2[r2.size() - 1] == '/')
            {
                r2 = r2.substr(0, r2.size() - 1);
            }
        }

        title += (r2 + ' ');
    }

    return title.substr(0, title.size() - 1);
}

inline time_t parseDate(string& date)
{
    std::tm parsed;
    memset(&parsed, 0, sizeof(parsed));
    strptime(date.c_str(), "%Y-%m-%dT%H:%M:%SZ", &parsed);

    return mktime(&parsed);
}

void DocumentProcessor::readInputData(const string& directory){

    string path = directory;

    if (directory[directory.size() - 1] != '/')
    {
        path += '/';
    }

    cout << path << endl;

    DIR* corpus;
    struct dirent* dir;

    char filePath[4096];

    while ((corpus = opendir(path.c_str())) == nullptr) {
        fprintf(stderr, "Could not open directory: %s\n", path.c_str());
    }
    while ((dir = readdir(corpus)) != nullptr) {
        if (strncmp(dir->d_name, "..", 2) != 0 && strncmp(dir->d_name, ".", 1) != 0) {
            string fileName = dir->d_name;
            string onlyFile = fileName.substr(0, fileName.length()-5);
            string fileType = fileName.substr(fileName.length()-5, fileName.length());

            if (fileType == ".json") {
                numDocs++;
                strncpy(filePath, path.c_str(), 4095);
                strncat(filePath, "/", 4095);
                string dirPath = filePath;
                strncat(filePath, dir->d_name, 4095);

                string newFileName = "\"" + fileName + "\"";
                string textFile = onlyFile + ".txt";
                parseInputData(filePath,path);

            }
        }
    }

    cout << numDocs <<endl;
    parsedWords.printInOrder();

}

void DocumentProcessor::parseInputData(const string& fileDirectory, const string& path){

    ifstream opinion(fileDirectory);
    if(!opinion){
        cerr << "Cannot open input data file" << endl;
        exit(EXIT_FAILURE);
    }

    DocumentInfo info;
    json j;
    opinion >> j;
    string contents;
    string a = "";

    if (!j["id"].empty())
    {
        j["id"].get_to(info.id);
    }

    info.path = path;
    string extracted;

    if (!j["absolute_url"].empty())
    {
        extracted.clear();
        j["absolute_url"].get_to(extracted);
        info.title = parseCaseTitle(extracted);
    }

    if (!j["date_created"].empty())
    {
        extracted.clear();
        j["date_created"].get_to(extracted);
        info.date = parseDate(extracted);
    }


    if(!j["plain"].empty()){
        contents = j["plain"];

        for(unsigned int i = 0; i < contents.size(); i++){
            if(ispunct(contents[i])){
                contents[i] = '\0';
            }
        }
        istringstream ss(contents);
        do {
            string word;
            ss >> word;
            parsedWords.insert(parseWords(word));
        } while (ss);
    }

    if(!j["html"].empty()){
        contents = j["html"];

        for(unsigned int i = 0; i < contents.size(); i++){
            if(ispunct(contents[i])){
                contents[i] = '\0';
            }
        }
        istringstream ss(contents);
        do {
            string word;
            ss >> word;
            parsedWords.insert(parseWords(word));
        } while (ss);
    }

}
