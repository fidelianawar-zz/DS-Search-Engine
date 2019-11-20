#include <iostream>
#include "dsavltree.h"
#include <fstream>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

void maintenanceMenu(){
    cout << "Maintenace\n";
}

void interactiveMenu(){
    cout << "Interactive\n";
}

int main()
{

    int mode;
    DSAVLTree<string>* newTree = new DSAVLTree<string>;
    newTree->insert("Dallas");
    newTree->insert("Austin");
    newTree->insert("Houston");
    newTree->insert("NYC");
    newTree->insert("Dallas");
   // newTree->printInOrder();

    bool result = newTree->isEmpty()? true: false;
  //  result == false? cout << "Tree contains members" << endl : cout << "Tree is empty"<< endl;


    ifstream file("101310.json");

    if(!file.is_open()){
        cout << "File did not open";
    }

    json j;
    file >> j;

   // cout << j;
//    cout << j["plain"] << endl;
//    cout << j["html"];

    cout << "Welcome to Fidelia and Annalise's Search Engine!" << endl;
    cout << "Let's Search!" << endl << endl;
    cout << "There are 2 Modes: Maintenance and Interactive.\n>>Choose [1] for Maintenance or [2] for Interactive: " ;
    cin >> mode;
    cout << endl;

    mode == 1? maintenanceMenu(): interactiveMenu();

}
