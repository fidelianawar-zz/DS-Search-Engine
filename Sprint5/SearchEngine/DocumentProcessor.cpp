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
#include <cstring>
#include <ctime>
#include <dirent.h>
#include "Word.h"
#include "IndexAVL.h"
#include "IndexInterface.h"
#include "IndexHash.h"

bool print = true;

using namespace std;
using nlohmann::json;

//copy constructor for stop words set
DocumentProcessor::DocumentProcessor(){
    ifstream input("stopWords.txt");
    string stopWord;

    while (input >> stopWord){
        stopWord.erase(std::remove_if(stopWord.begin(), stopWord.end(), [] (char c){
            return !(c == '\'' || (c >= 'a' && c <= 'z'));
        }), stopWord.end());

        if (stopWord.size() == 0){
            continue;
        }

        stopWordsSet.emplace(stopWord);

        stopWord.erase(std::remove_if(stopWord.begin(), stopWord.end(), [] (char c){
            return c == '\'';
        }), stopWord.end());

        stopWordsSet.emplace(stopWord);
    }
}
void DocumentProcessor::setIndex(IndexInterface*index){
    this->index = index;
}

//strips HTML tags from input corpus documents
string& DocumentProcessor::stripHTML(string& text) const {
    for (unsigned int i = 0; i < text.size(); i++){
        if (text[i] == '<'){
            unsigned int j = i;
            while (text[j] != '>' && j < text.size()){
                j++;
            }
            text.erase(i, j - i + 1);
            i--;
        }
    }

    return text;
}

//parses word from document (changes to lowercase, stems, and removes stop words)
string DocumentProcessor::parseWords(const string& base) const{
    string processed = base;
    if (processed.size() == 0){
        return processed;
    }

    lowerCase(processed);

    processed.erase(std::remove_if(processed.begin(), processed.end(), [] (char c){
        return !(c == '\'' || (c >= 'a' && c <= 'z'));
    }), processed.end());

    if (processed.size() == 0){
        return processed;
    }

    if (stopWordsSet.count(processed) > 0){
        return "";
    }

    stemString(processed);
    return processed;
}

//stemming of words using Porter2_Stemmer
inline void DocumentProcessor::stemString(string& text) const{
    string key = text;

    if (stemCache.find(key) != stemCache.end()){
        text = stemCache.at(text);
        return;
    }

    Porter2Stemmer::stem(text);
    stemCache.emplace(key, text);
}

//changes word to lower case
string& DocumentProcessor::lowerCase(string& text) const{
    for (unsigned int i = 0; i < text.size(); i++){
        text[i] = tolower(text[i]);
    }

    return text;
}

//parses title of document
inline string parseCaseTitle(string& absoluteURL){
    istringstream sections(absoluteURL);
    string title;

    string r1;

    for (int i = 0; i < 4; i++){
        getline(sections, r1, '/');
    }

    istringstream split(r1);

    string r2;

    while (getline(split, r2, '-')){
        if (r2 == "v"){
            r2 = "v.";
        }
        else if (r2.size() > 0){
            r2[0] = toupper(r2[0]);

            if (r2[r2.size() - 1] == '/'){
                r2 = r2.substr(0, r2.size() - 1);
            }
        }

        title += (r2 + ' ');
    }

    return title.substr(0, title.size() - 1);
}

//parses and returns the date
inline time_t parseDate(string& date){
    std::tm parsed;
    memset(&parsed, 0, sizeof(parsed));
    strptime(date.c_str(), "%Y-%m-%dT%T%H:%M:%SZ", &parsed);
    return mktime(&parsed);
}

//reads input data using file path directory
void DocumentProcessor::readInputData(const string& directory, char type){
    numDocs = 0;

    string path = directory;

    if (directory[directory.size() - 1] != '/'){
        path += '/';
    }

    DIR* corpus;
    struct dirent* dir;

    char filePath[5000];

    numWordsTotal = 0;
    numWordsIndexed = 0;

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
                strncpy(filePath, path.c_str(), 5000);
                strncat(filePath, "/", 5000);
                strncat(filePath, dir->d_name, 5000);
                /// if(numDocs <= 1000){
                parseInputData(filePath,path,type);

            }
        }
        // cout << numDocs << endl;
    }

    if(print == true){
        if(type == 'A'){
            //wordTree.printInOrder();
            index->printWords();
            index->parseWords();
           // index->getWordVec();
           vector<Word> temp;
           temp= index->getWordVec();
           //temp = wordTree.getAllNodes();
           cout << temp.at(0);
            //index->parseWords();
            //index->printWords();

            //parsedWords.printInOrder();
        }else{
            index->printWords();
            parsedHash.print();
            //wordHashTable.print();
        }
    }
}

/*
 * parses json elements of document
 * chooses processing technique for HTML vs plaintext
 */
void DocumentProcessor::parseInputData(const string& fileDirectory, const string& path, char type){

    ifstream opinion(fileDirectory);
    if(!opinion){
        cerr << "Cannot open input data file" << endl;
        exit(EXIT_FAILURE);
    }

    int numWordsPerOpinion = 0;

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

            if(parseWords(word).length() > 2){
                if (type == 'A'){

                    char buff[20];
                    strftime(buff, 20, "%Y-%m-%d", localtime(&info.date));

                    string date(buff);
                    string titledate = to_string(info.id)+ ".json," + " Opinion Id: " + to_string(info.id)+ ", Court Case Title: " + info.title +", Date Created: "+ date;

                    insertTree(parseWords(word),titledate);
                }
                else{
                    insertHash(parseWords(word),info.title);
                }

            }
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
            if (type == 'A'){
                char buff[20];
                strftime(buff, 20, "%Y-%m-%d", localtime(&info.date));

                string date(buff);
                string titledate = to_string(info.id)+ ".json," + " Opinion Id: " + to_string(info.id)+ ", Court Case Title: " + info.title +", Date Created: "+ date;

                insertTree(parseWords(word),titledate);
                numWordsPerOpinion++;
            }
            else{
                char buff[20];
                strftime(buff, 20, "%Y-%m-%d", localtime(&info.date));

                string date(buff);
                string titledate = to_string(info.id)+ ".json," + " Opinion Id: " + to_string(info.id)+ ", Court Case Title: " + info.title +", Date Created: "+ date;

                insertHash(parseWords(word),titledate);
                numWordsPerOpinion++;
            }
        } while (ss);
    }
   // cout << numWordsPerOpinion<<endl;
    wordsPerOpinion.push_back(numWordsPerOpinion);
}

//displays "loading" information when parsing large amounts of data sets
void DocumentProcessor::printParsingStats(){
    numWordsTotal++;

    if(numWordsTotal == 1)
        cout << "\nNumber of Words Parsed: \n";
    if(numWordsTotal % 100000 == 0)
        cout <<"\t"<<numWordsTotal <<endl;
    // cout << "In Printingparsingstats"<<numWordsTotal << endl;
}

/*
 * inserts word AVL tree of parsed words (parsedWords)
 * inserts word/respective document information into AVL tree of word objects (word tree)
 */
void DocumentProcessor::insertTree(string parsedWord, string doc) {

    printParsingStats();

    parsedWords.insert(parsedWord);

    Word newWord(parsedWord, doc);

    if (newWord.getText() != "") {

        if (!index->contains(newWord.getText())) {
            numWordsIndexed++;
            //indexer.addWord(newWord);
            index->addWord(newWord);
           // wordTree.insert(newWord);
        }
        else {
            // indexer.words.find(newWord).addFile(doc);
            index->find(newWord.getText()).addFile(doc);

        }
    }
}

void DocumentProcessor::insertHash(string parsedWord, string document) {
    Word newWord(parsedWord);
    if(newWord.getText() != ""){
        //     if (!wordHashTable.contains(newWord)){
        numWordsIndexed++;
        //wordHashTable.insert(newWord, document);
        parsedHash.insert(parsedWord,document);
        index->addWord(newWord);
        //   }
        //       else{
        //            int keyindex = wordHashTable.getKeyIndex(newWord);
        //            int index = wordHashTable.getIndex(newWord);
        //            wordHashTable

        //        }
    }
}

int DocumentProcessor::getNumWordsIndexed() {
    return numWordsIndexed;
}

int DocumentProcessor::getNumDocs() {
    return numDocs;
}

int DocumentProcessor::getNumWordsTotal() {
    return numWordsTotal;
}

//search output for demo
void DocumentProcessor::search(const string& search){
    cout << "Searching the Word: '" << search << "'\n";

    Word wordToSearch = parseWords(search);

    cout << "After stemming/removing stop words, your word is '" << wordToSearch.getText() << "'\n";

    cout << "Results: " << endl;

    //  wordTree.countTotalNodes();
    //        cout << "Total # of Nodes '" << wordToSearch.getText()
    //             << "' has: "<<wordTree.find(wordToSearch).getFiles().size()*wordTree.find(wordToSearch).getTotalFrequency()<< endl;        //check if this is correct
    cout << "Total # of Nodes in tree: "// << wordToSearch.getText()
            //<< "' has: "
         <<wordTree.getTotalNodes() << endl;

    if(wordTree.contains(wordToSearch) == true){

        cout << "Total # of Docs '" << wordToSearch.getText()
             << "' Appears in: " << wordTree.find(wordToSearch).getFiles().size() << endl;
        cout << "Total # of Appearances of '" << wordToSearch.getText()<< "': "
             <<wordTree.find(wordToSearch).getTotalFrequency() << endl;

        cout << endl;

    }else{
        cout << "Word is not Found" << endl;
    }
}

int DocumentProcessor:: getAvgWords(){

    int n = 0;
    double mean = 0.0;
    for (auto x : wordsPerOpinion) {
        double delta = x - mean;
        mean += delta/++n;
    }
    return mean;
}
vector<Word> DocumentProcessor:: getWordTree(){
    index->parseWords();
   // index->getWordVec();
   vector<Word> temp;
   vector<Word> parsed;
   temp= index->getWordVec();

   for(int i = 0; i < temp.size();i++){

       if(stopWordsSet.count(temp[i].getText()) > -1 || temp[i].getText().size() < 4 ||temp[i].getText() == "that" || temp[i].getText() == "classfootnot"){

       }else{
           parsed.push_back((temp[i]));
       }
   }
    return parsed;
}
