
#ifndef WORD_H
#define WORD_H

#include <string>
#include <locale>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include "DSAVLTree.h"
#include "Porter2_Stemmer.h"

#include <vector>
#include "DSAVLTree.h"


using namespace std;
using namespace Porter2Stemmer;

class Word {

    friend ostream& operator<<(ostream&, const Word&);

    private:

        int freq;
        string text;
        vector<pair<string, int> > files;

    public:
        Word();
        Word(string);
        Word(string, string);

        Word(string, pair<string, int>);

        int getFreq();
        string getText();

        void format();
        void removePunc();
        void stemm();

        void addFile(string);
        void addIndexFile(pair<string, int>);
        vector<pair<string, int> >& getFiles();
        int find(string);

        bool operator>(const Word&);
        bool operator<(const Word&);
        bool operator==(const Word&);

};

#endif // WORD_H
