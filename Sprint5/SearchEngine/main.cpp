#include <iostream>
#include "dsavltree.h"
#include <fstream>
#include <json.hpp>
#include "readIndexFile.h"

using namespace std;
using json = nlohmann::json;

int main()
{
    readIndexFile indexFile;
    indexFile.readInputData();
}
