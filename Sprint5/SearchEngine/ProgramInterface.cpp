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

int main(int argc, char *argv[])
{
    if(argc > 2){
        string jsonPath = argv[1];
        DocumentProcessor process;
        process.readInputData(argv[1]);
        process.search(argv[2]);

    }else{
        IndexHandler indexHandler;

        int mode;
        cout << "Welcome to Fidelia and Annalise's Search Engine!" << endl;
        cout << "Let's Search!" << endl << endl;
        cout << "There are 2 Modes: Maintenance and Interactive.\n>>Choose [1] for Maintenance or [2] for Interactive: " ;
        cin >> mode;
        cout << endl;

        mode == 1? maintenanceMenu(): interactiveMenu();
    }
}
