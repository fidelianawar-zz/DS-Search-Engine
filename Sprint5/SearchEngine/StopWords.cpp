#include "StopWords.h"

StopWords::StopWords() {

}
DSAVLTree<string>& StopWords::getStopTree()
{
    return stopWordsTree;
}
void StopWords::populateStopWords(){
    ifstream inFile;
    inFile.open("stopWords.txt");

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

   // stopWordsTree.isEmpty() == true? cout <<"is empty":cout<< "full";
    //cout << endl;

}
