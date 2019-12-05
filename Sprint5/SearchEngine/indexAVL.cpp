#include "indexAVL.h"

indexAVL::indexAVL() {

}

void indexAVL::addWord(Word wrd) {
    words.insert(wrd);
}

Word& indexAVL::find(string str) {
    Word wrd(str);
    return words.find(wrd);
}

bool indexAVL::contains(string str) {
    Word temp(str);
    return words.contains(temp);
}

void indexAVL::printWords() {
    words.printInOrder();
}
