#include "Word.h"

Word::Word() {
    totalFrequency = 0;
    text = "";
}

Word::Word(string wrd) {
    totalFrequency = 0;
    text = wrd;
    formatString();
    clearPunctuation();
    stemWord();
}

Word::Word(string wrd, string file) {
    totalFrequency = 0;
    text = wrd;
    formatString();
    clearPunctuation();
    stemWord();
    addFile(file);
}

Word::Word(string str, pair<string, int> p) {
    totalFrequency = p.second;
    text = str;
    files.push_back(p);
}

string Word::getText() {
    return text;
}

int Word::getTotalFrequency() {
    return totalFrequency;
}

void Word::addFile(string file) {
    totalFrequency += 1;
    int index = findFile(file);
    if (index != -1) {
        files[index].second += 1;
    }
    else {
        files.push_back(pair<string, int>(file, 1));
    }
}

void Word::addFileFromIndex(pair<string, int> file) {
    totalFrequency += file.second;
    files.push_back(file);
}

vector<pair<string, int>>& Word::getFiles() {
    return files;
}

int Word::findFile(string file) {

    for (unsigned int i = 0; i < files.size(); i++) {

    for (int i = 0; i < files.size(); i++) {
        if (files[i].first == file) {
            return i;
        }
    }
    return -1;
}
}

bool Word::operator>(const Word& wrd) {
    return text > wrd.text;
}

bool Word::operator<(const Word& wrd) {
    return text < wrd.text;
}

bool Word::operator==(const Word& wrd) {
    return text == wrd.text;
}

void Word::formatString() {
    locale loc;
    for (string::size_type i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i], loc);
    }
}

void Word::clearPunctuation() {
    for (unsigned int i = 0, len = text.size(); i < len; i++) {
        if (text[i] < 97 || text[i] > 122 || ispunct(text[i])) {
            text.erase(i--, 1);
            len = text.size();
        }
    }
}

void Word::stemWord() {
   // Porter2Stemmer::trim(text);
    //Porter2Stemmer::stem(text);
}


ostream& operator<<(ostream& output, const Word& wrd) {
    output << wrd.text << endl << wrd.files.size() << endl;
    for (pair<string, int> p: wrd.files) {
        output << p.second << " " << p.first << endl;
    }
    return output;
}
