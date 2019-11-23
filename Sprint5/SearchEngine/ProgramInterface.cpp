#include <iostream>
#include "dsavltree.h"
#include "IndexHandler.h"
#include "DocumentProcessor.h"
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
    IndexHandler indexHandler;

    int mode;
    cout << "Welcome to Fidelia and Annalise's Search Engine!" << endl;
    cout << "Let's Search!" << endl << endl;
    cout << "There are 2 Modes: Maintenance and Interactive.\n>>Choose [1] for Maintenance or [2] for Interactive: " ;
    cin >> mode;
    cout << endl;

    mode == 1? maintenanceMenu(): interactiveMenu();

    DocumentProcessor process;

    process.readInputData();

    //Okay so don't use your branch bc it's all very confusing, but I think this branch {master} is all caught up!

}
