#ifndef DOCUMENTPROCESSOR_H
#define DOCUMENTPROCESSOR_H

#include <unordered_set>
#include <unordered_map>

using namespace std;

class DocumentProcessor
{
public:
    DocumentProcessor();
private:
    unordered_set<string> stopWordsSet;
};

#endif // DOCUMENTPROCESSOR_H
