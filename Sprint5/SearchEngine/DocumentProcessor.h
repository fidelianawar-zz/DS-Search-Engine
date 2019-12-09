#ifndef DOCUMENTPROCESSOR_H
#define DOCUMENTPROCESSOR_H

#include <unordered_set>
#include <unordered_map>
#include "DSAVLTree.h"
#include "DSHashTable.h"
#include "Word.h"
#include "IndexAVL.h"
#include "IndexInterface.h"
#include "IndexHash.h"

using namespace std;

struct DocumentInfo
{
    unsigned int id;
    string path;
    string title;
    time_t date;
};

class DocumentProcessor
{
private:
      indexAVL indexer;
      IndexInterface*index;
public:
    DocumentProcessor();
    void setIndex(IndexInterface*);
    void readInputData(const string&, char);
    void readDirectory();
    void parseInputData(const string&, const string&, char);
    string& stripHTML(string& text) const;
    string parseWords(const string& base) const;
    void stemString(string& text) const;
    string& lowerCase(string& text) const;
    int getNumWordsIndexed();
    int getNumDocs();
    int getNumWordsTotal();
    void insertTree(string, string);
    void insertHash(string, string);
    void search(const string& search);
    void printParsingStats();
    void getCaption(string);
    void getStatistics();
    int getAvgWords();
    string getFilePath();
   // DSAVLTree<Word> getWordTree();
   // int getNumDocs();
    vector<Word> getWordTree();


    private:
    unordered_set<string> stopWordsSet;
    mutable unordered_map<string, string> stemCache;
    DSAVLTree<string> parsedWords;
    DSAVLTree<Word> wordTree;
    DSHashtable<Word, string> wordHashTable;
    DSHashtable<string,string>parsedHash;
    int numDocs;
    int numWordsIndexed;
    int numWordsTotal;
    string filePathtoUse;

    vector<int> wordsPerOpinion;
};

#endif // DOCUMENTPROCESSOR_H
