#include "IndexHandler.h"


IndexHandler::IndexHandler() {
    numDocuments = numWordsIndexed = numWordsTotal = 0;
}

IndexInterface* IndexHandler::returnIndex() {
    return index;
}
void IndexHandler::addToIndex(DocumentProcessor process,string argv){
    index = new indexAVL;
    process.setIndex(index);

    process.readInputData(argv,'A');

    numDocuments = process.getNumDocs();
    numWordsTotal = process.getNumWordsTotal();
    numWordsIndexed = process.getNumWordsIndexed();

    avgPerOpinion = process.getAvgWords();
    allWords = process.getWordTree();

    writeToIndex();
    cout << "\nPersistent Index Created.\n" << endl;
}

void IndexHandler::chooseIndex(DocumentProcessor process,string argv) {
    char choice;

    cout << "\t[A] AVL tree" << endl;
    cout << "\t[H] Hash table" << endl;
    cout << "\t[X] Return to query menu" << endl;
    cout << ">> ";
    cin >> choice;

    if (choice == 'A') {
        index = new indexAVL;
        process.setIndex(index);

        /*  process.readInputData(argv,choice);

        numDocuments = process.getNumDocs();
        numWordsTotal = process.getNumWordsTotal();
        numWordsIndexed = process.getNumWordsIndexed();

        avgPerOpinion = process.getAvgWords();
        allWords = process.getWordTree();
*/
        readFromIndex(index);


        // writeToIndex();
    }
    else if (choice == 'H') {
        index = new indexHash;
        process.setIndex(index);
        //  process.readInputData(argv[1],choice);

        readFromIndex(index);

    }/*else if(choice == 'P'){
        index->createPersistent();
    }*/
    else {
        cout << "That is not a valid index option. Please choose AVL or hash." << endl;
    }
    cout << endl;
}
void IndexHandler::readFromIndex(IndexInterface*index){
    f.open("indexCorpus.txt",ios::in);
    string word;

    if(!f.is_open()){
        cout << "Corpus did not open." << endl;
    }
    int numFiles;

    cout << "here!" << endl;

    f >> numDocuments;
    f >> numWordsIndexed;
    f >> numWordsTotal;

    f >> word;

    while (!f.eof()) {
        //while(numDocuments <=5000){
        Word entry(word);
        f >> numFiles;
        int frequency;
        string json;
        for (int i = 0; i < numFiles; i++) {
            f >> frequency;
            getline(f, json);
            json = json.substr(1, json.length());
            entry.addIndexFile(pair<string, int>(json, frequency));
        }

        index->addWord(entry);

        allWords.push_back(entry);
        f >> word;
    }
}
int IndexHandler::getNumDocuments() {
    return numDocuments;
}
void IndexHandler::writeToIndex(DSAVLTree<Word> &words){


    f.open("indexCorpus.txt",ios::out);

    if(!f.is_open()){
        cout << "Corpus did not open." << endl;
    }

    f<< numDocuments << endl;
    f << numWordsIndexed << endl;
    f << numWordsTotal << endl;

    words.printInOrder(f);
}
void IndexHandler::writeToIndex(){


    f.open("indexCorpus.txt",ios::out);

    if(!f.is_open()){
        cout << "Corpus did not open." << endl;
    }

    f<< numDocuments << endl;
    f << numWordsIndexed << endl;
    f << numWordsTotal << endl;

    index->getStructure().printInOrder(f);
}

void IndexHandler::printStatistics() {
    cout << "Total number of opinions indexed: " << numDocuments << endl;
    cout << "Average number of words indexed per opinion (after removal of stop words): " << numWordsIndexed << endl;
    cout << "Number of words total: " << numWordsTotal << endl;
    cout<<   "Top 50 most frequent words (after removal of stop words): ";
    getTopWords();
    cout << endl << endl;
}

void IndexHandler::getTopWords() {
    DocumentProcessor p;
    vector<pair<string,int>> sortedFreq;
    // allWords = indexT->getWordVec();



    if(allWords.size()!= 0){
        for(unsigned int i = 0; i < allWords.size(); i++){
            if(p.parseWords(allWords[i].getText()).size() > 3 && p.parseWords(allWords[i].getText()) != "brbr" )
                sortedFreq.push_back(std::make_pair(p.parseWords(allWords[i].getText()),allWords[i].getFreq()));
        }

        std::sort(sortedFreq.begin(),sortedFreq.end(),sort());

        cout << "Word\tFrequency" << endl;
        for(int i = 0; i < 50; i++){
            cout << sortedFreq[i].first << "\t" << sortedFreq[i].second << endl;
        }
    }else{
        cout << "Word Vector empty\n";
    }
}
void IndexHandler::clearIndex(){
    f.open("indexCorpus.txt", ios::in);

    if (!f) {
        cerr << "Persistent index does not exist" << endl;
    }
    else {
        f.close();
        if (remove("indexCorpus.txt") != 0) {
            perror("Error deleting file");
        }
        else {
            puts("File successfully deleted");
        }
    }
}
