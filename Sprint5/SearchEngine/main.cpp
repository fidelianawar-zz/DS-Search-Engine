#include <iostream>
#include "dsavltree.h"
#include <fstream>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

int main()
{

    DSAVLTree<int>* newTree = new DSAVLTree<int>;
    newTree->insert(2);
    newTree->insert(5);
    newTree->insert(1);
    newTree->insert(1);
    newTree->insert(9);
    newTree->printInOrder();

    bool result = newTree->isEmpty()? true: false;
    result == false? cout << "Tree contains members" << endl : cout << "Tree is empty"<< endl;


    ifstream file("101310.json");

    if(!file.is_open()){
        cout << "File did not open";
    }

    json j;
    file >> j;

   // cout << j;
    cout << j["plain"] << endl;
     cout << j["html"];

}
