#include "IndexAVL.h"

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

DSAVLTree<Word> indexAVL::getStructure(){
    return words;
}
void indexAVL::parseWords(){
    words.parseInOrder();
}
vector<Word> indexAVL::getWordVec(){
    return words.getAllNodes();
}
