#include "IndexHash.h"

indexHash::indexHash()
{

}
void indexHash::addWord(Word wrd) {
    words.insert(wrd.getText(), wrd);
}

Word& indexHash::find(string str) {
    return words.find(str);
}

bool indexHash::contains(string str) {
    return words.contains(str);
}

void indexHash::printWords() {
    words.print();
}
void indexHash::createPersistent(){
  //  words.createPersistent();
}
DSAVLTree<Word> indexHash::getStructure(){
   // return words;
}
void indexHash::parseWords(){
   // words.parseInOrder();
}
vector<Word> indexHash::getWordVec(){
  //  return words.getAllNodes();
}
