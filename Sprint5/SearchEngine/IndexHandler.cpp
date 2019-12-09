#include "IndexHandler.h"


IndexHandler::IndexHandler() {
    numDocuments = numWordsIndexed = numWordsTotal = 0;
}

IndexInterface* IndexHandler::returnIndex() {
    return index;
}

void IndexHandler::chooseIndex(DocumentProcessor process,char *argv[]) {
    char choice;

    cout << "\t[A] AVL tree" << endl;
    cout << "\t[H] Hash table" << endl;
    cout << "\t[X] Return to query menu" << endl;
    cout << ">> ";
    cin >> choice;

    if (choice == 'A') {
        index = new indexAVL;
        process.setIndex(index);
        process.readInputData(argv[1],choice);

        numDocuments = process.getNumDocs();
        numWordsTotal = process.getNumWordsTotal();
        numWordsIndexed = process.getNumWordsIndexed();

        writeToIndex(process.getWordAVL());
        avgPerOpinion = process.getAvgWords();
        allWords = process.getWordTree();
    }
    else if (choice == 'H') {
        index = new indexHash;
        process.setIndex(index);
        process.readInputData(argv[1],choice);
    }
    else {
        cout << "That is not a valid index option. Please choose AVL or hash." << endl;
    }
    cout << endl;
}
int IndexHandler::getNumDocuments() {
    return numDocuments;
}
void IndexHandler::writeToIndex(DSAVLTree<Word> &words){
    f.open("indexCorpus.txt",ios::out);

    f<< numDocuments << endl;
    f << numWordsIndexed << endl;
    f << numWordsTotal << endl;

    words.outputInOrder(f);

}

void IndexHandler::printStatistics() {
    cout << "Total number of opinions indexed: " << numDocuments << endl;
    cout << "Average number of words indexed per opinion (after removal of stop words): " << avgPerOpinion << endl;
    cout << "Number of words total: " << numWordsTotal << endl;
    cout<<   "Top 50 most frequent words (after removal of stop words): ";
    getTopWords();
    cout << endl << endl;
}

void IndexHandler::getTopWords() {
    vector<pair<string,int>> sortedFreq;
    for(int i = 0; i < allWords.size(); i++){
        sortedFreq.push_back(std::make_pair(allWords[i].getText(),allWords[i].getTotalFrequency()));
    }

    std::sort(sortedFreq.begin(),sortedFreq.end(),sort());

    cout << "Word\tFreequency" << endl;
    for(int i = 0; i < 50; i++){
       cout << sortedFreq[i].first << "\t" << sortedFreq[i].second << endl;
    }
}
