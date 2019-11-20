#include "stopwords.h"
#include <fstream>
#include <iostream>
using namespace std;
stopWords::stopWords()
{

}
void stopWords::openStopFile(){
    fstream stopF;

    stopF.open("stopWordFile.txt");



}
