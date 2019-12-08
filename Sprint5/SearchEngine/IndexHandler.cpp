#include "IndexHandler.h"

IndexHandler::IndexHandler() {
    numDocuments = 0;
    numWordsIndexed = 0;
    numWordsTotal = 0;
}

IndexInterface* IndexHandler::returnIndex() {
    return index;
}

vector<string> IndexHandler::getTextFiles() {
    return txtFiles;
}

void IndexHandler::chooseIndex() {
    char choice;

    cout << "\t[A] AVL tree" << endl;
    cout << "\t[H] Hash table" << endl;
    cout << "\t[X] Return to query menu" << endl;
    cout << ">> ";
    cin >> choice;

    if (choice == 'A') {
        index = new indexAVL();
        if (doesIndexExist()) {
            readFromIndex();
        }
    }
    else if (choice == 'H') {
        index = new indexHash();
        if (doesIndexExist()) {
            readFromIndex();
        }
    }
    else {
        cout << "That is not a valid index option. Please choose AVL or hash." << endl;
    }
    cout << endl;
}
/*
void IndexHandler::getIndex() {
    parser.readDirectory();
    numDocuments = parser.getNumDocs();
    numWordsIndexed = parser.getNumWordsIndexed();
    numWordsTotal = parser.getNumWordsTotal();
    writeToIndex(parser.getWords());
}
*/
bool IndexHandler::doesIndexExist() {
    f.open("index.txt", ios::in);
    if (!f) {
        f.close();
        //cerr << "Persistent index could not be opened for reading" << endl;
        return false;
    }
    else {
        f.close();
        return true;
    }
}

void IndexHandler::writeToIndex(DSAVLTree<Word>& words) {

    bool persistenceExists = doesIndexExist();
    f.open("index.txt", ios::out);
    if (!persistenceExists) {
        //cerr << "Persistent index could not be opened for writing" << endl;
        f << numDocuments << endl;
        f << numWordsIndexed << endl;
        f << numWordsTotal << endl;

        words.outputInOrder(f);
    }
    else {
        words.outputInOrder(f);
    }

    f.close();
}

void IndexHandler::readFromIndex() {
    f.open("index.txt", ios::in);

    string word;
    int numFiles;

    cout << numDocuments;
    cout <<numWordsIndexed;
    cout <<numWordsTotal;

    cout <<word;

   // while (!f.eof()) {
        Word entry(word);
        cout <<numFiles;
        int frequency;
        string corpusDoc;
        for (int i = 0; i < numFiles; i++) {
            cout <<frequency;
            getline(f, corpusDoc);
            corpusDoc = corpusDoc.substr(1, corpusDoc.length());
            entry.addFileFromIndex(pair<string, int>(corpusDoc, frequency));
        }

        index->addWord(entry);
        cout <<word;
   // }

    //index->printWords();

    f.close();
}

void IndexHandler::clearIndex() {
    f.open("index.txt", ios::in);

    if (!f) {
        cerr << "Persistent index does not exist" << endl;
    }
    else {
        f.close();
        if (remove("index.txt") != 0) {
            perror("Error deleting file");
        }
        else {
            puts("File successfully deleted");
        }
    }
}

int IndexHandler::getNumDocuments() {
    return numDocuments;
}

void IndexHandler::printStatistics() {
    cout << "Number of documents parsed: " << numDocuments << endl;
    cout << "Number of words indexed: " << numWordsIndexed << endl;
    cout << "Number of pages indexed: " << numWordsTotal/400 << endl << endl;
}

void IndexHandler::getTopWords() {

}
