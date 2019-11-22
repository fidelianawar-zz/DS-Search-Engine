#include "readIndexFile.h"
#include <fstream>
#include <iostream>
#include "json.hpp"
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <regex>

using namespace std;
using nlohmann::json;

void readIndexFile::readInputData(){
    ifstream opinion("101310.json");
    if(!opinion){
        cerr << "Cannot open input data file" << endl;
        exit(EXIT_FAILURE);
    }

    json j;
    opinion >> j;
    string contents;
    string a = "";
    contents = j["html"];
    regex numbers("[0-9]");
    char buffer[256];

    for(int i = 0; i < contents.size(); i++){
        if(ispunct(contents[i])){
            contents[i] = NULL;
        }
    }

    contents = regex_replace(contents, regex(R"(/div|div|/p|class=|num id|san|num|href|footnote)"), a);
    contents = regex_replace(contents, numbers, a);

    cout << contents;
<<<<<<< HEAD

=======
>>>>>>> origin/FideliaBranch
}
