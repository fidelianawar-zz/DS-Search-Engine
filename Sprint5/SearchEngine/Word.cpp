#include "Word.h"

Word::Word() {
    freq = 0;
    text = "";
}

Word::Word(string wordd) {
    freq = 0;
    text = wordd;
}

Word::Word(string wordd, string file) {
    freq = 0;
    text = wordd;
    addFile(file);
}

Word::Word(string s_string, pair<string, int> pairElement) {
    freq = pairElement.second;
    text = s_string;
    files.push_back(pairElement);
}

int Word::getFreq() {
    return freq;
}

string Word::getText() {
    return text;
}

void Word::addFile(string file) {
    freq += 1;
    int index = find(file);
    if (index != -1) {
        files[index].second += 1;
    }
    else {
        files.push_back(pair<string, int>(file, 1));
    }
}

void Word::addIndexFile(pair<string, int> file) {
    freq += file.second;
    files.push_back(file);
}

int Word::find(string file) {

    for (unsigned int i = 0; i < files.size(); i++) {

        for (unsigned int i = 0; i < files.size(); i++) {
            if (files[i].first == file) {
                return i;
            }
        }
        return -1;
    }
    return -1;
}

vector<pair<string, int>>& Word::getFiles() {
    return files;
}


ostream& operator<<(ostream& out, const Word& wordd) {
    out << wordd.text << endl << wordd.files.size() << endl;
    for (pair<string, int> p: wordd.files) {
        out << p.second << " " << p.first << endl;
    }
    return out;
}

bool Word::operator<(const Word& wordd) {
    return text < wordd.text;
}
bool Word::operator>(const Word& wordd) {
    return text > wordd.text;
}

bool Word::operator==(const Word& wordd) {
    return text == wordd.text;
}

