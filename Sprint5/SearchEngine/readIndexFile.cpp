#include "readIndexFile.h"
#include <fstream>
#include <iostream>
#include "json.hpp"

using namespace std;
using nlohmann::json;

void readIndexFile::readInputData(){
    ifstream opinion("101310.json");
    if(!opinion){
        cerr << "Cannot open input data file" << endl;
        exit(EXIT_FAILURE);
    }
    json k;
    opinion >> k;
    cout << k << endl;


}
