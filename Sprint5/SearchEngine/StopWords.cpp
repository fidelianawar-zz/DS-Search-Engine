#include "StopWords.h"

StopWords::StopWords() {
    ifstream inFile;
    inFile.open("StopWords", ios::in);

    if (!inFile) {
        cerr << "Stop words file could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    string word;
    inFile >> word;

    while (!inFile.eof()) {
        stopWordsTree.insert(word);
        inFile >> word;
    }

    inFile.close();
}

DSAVLTree<string>& StopWords::getStopTree()
{
    return stopWordsTree;
}
