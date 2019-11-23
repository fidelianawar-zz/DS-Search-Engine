#ifndef DOCUMENTPROCESSOR_H
#define DOCUMENTPROCESSOR_H

#include <unordered_set>
#include <unordered_map>
#include "dsavltree.h"

using namespace std;

class DocumentProcessor
{
public:
    DocumentProcessor();
    void readInputData();
    string& stripHTML(string& text) const;
    string parseWords(const string& base) const;
    void stemString(string& text) const;
    string& lowerCase(string& text) const;

private:
    unordered_set<string> stopWordsSet;
    mutable unordered_map<string, string> stemCache;
    DSAVLTree<string> parsedWords;
};

#endif // DOCUMENTPROCESSOR_H
