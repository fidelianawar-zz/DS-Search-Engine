<<<<<<< HEAD

=======
>>>>>>> f4484064109f08e06344542da1e21d6a676ab8b1
#ifndef WORD_H
#define WORD_H

#include <string>
#include <locale>
#include <ostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cctype>
<<<<<<< HEAD
#include "dsavltree.h"
#include "porter2_stemmer.h"
=======
#include <vector>
#include "dsavltree.h"
#include "Porter2_Stemmer.h"
>>>>>>> f4484064109f08e06344542da1e21d6a676ab8b1

using namespace std;
using namespace Porter2Stemmer;

class Word {

    friend ostream& operator<<(ostream&, const Word&);

    private:
        string text;
        vector<pair<string, int>> files;
        int totalFrequency;
    public:
        Word();
        Word(string);
        Word(string, string);
        Word(string, pair<string, int>);

        string getText();
        int getTotalFrequency();

        void addFile(string);
        void addFileFromIndex(pair<string, int>);
        vector<pair<string, int>>& getFiles();
        int findFile(string);
        bool operator>(const Word&);
        bool operator<(const Word&);
        bool operator==(const Word&);
        void formatString();
        void clearPunctuation();
        void stemWord();
};

<<<<<<< HEAD
#endif
=======
#endif // WORD_H
>>>>>>> f4484064109f08e06344542da1e21d6a676ab8b1
