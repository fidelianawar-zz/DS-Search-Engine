#include <iostream>
#include "DSAVLTree.h"
#include "IndexHandler.h"
#include "DocumentProcessor.h"
#include "QueryProcessor.h"
#include "QuerySearcher.h"
#include <fstream>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;
IndexHandler indexHandler;

int mainMenu(){
    int mode;
    cout << "Welcome to Fidelia and Annalise's Search Engine!" << endl;
    cout << "Let's Search!" << endl << endl;
    cout << "There are 2 Modes: Maintenance and Interactive.\n>>Choose [1] for Maintenance or [2] for Interactive: " ;
    cin >> mode;
    cout << endl;

    return mode;
}

void maintenanceMenu(){
    cout << "Maintenace Mode:\n";

    /*
        allows the user to add opinions to the index by supplying the path to a folder containing new opinions
        allows the user to clear the index completely
        allows the user to parse the corpus and populate index

     */

    int answer;

    cout << "[1] - Add opinions to index\n" <<
            "[2] - Clear Index\n" <<
            "[3] - Populate Corpus with New Index\n" <<
            ">> ";

    cin >> answer;

    if(answer > 3){
        cout << "\nInvalid Choice. Please Try again.\n\n";
        maintenanceMenu();
    }
}

void interactiveMenu(char *argv[]){
    cout << "Interactive Mode:\n";

    /*
        allow the user to indicate if they want the index loaded into an AVL structure or a hash table structure (if a persisted index exists).
        allow the user to enter a properly formatted Boolean query (as described above).
            The results should display the opinion’s identifying/important information such as year, parties to the case, which justice wrote the majority opinion, etc.  The result set shown to the user need not contain any more than the top 15 opinions.  If you’d like to show more, you may wish to paginate.
            The user should be allowed to choose one of the opinions from the result set above and have the first ~300 words of the opinion printed.
            Helpful Hint:  that the query terms should have stop words removed and stemmed before querying the index.
        Upon request, print basic statistics of the search engine including:
            Total number of opinions indexed
            Average number of words indexed per opinion (after removal of stop words)
            Top 50 most frequent words (after removal of stop words)
    */

    int answer;

    cout << "[1] - Load Index into AVL structure or Hash table\n" <<
            "[2] - Enter a query\n" <<
            "[3] - Print Statistics (# of opinions, avg # of indexed per opinion, and Top 50 most frequent words)\n" <<
            "[4] - Go back to Main Menu\n" <<
            "[5] - Exit Search Engine\n"
         << ">> ";

    cin >> answer;

    if(answer > 5){
        cout << "\nInvalid Choice. Please Try again.\n\n";
        interactiveMenu(argv);
    }
    else if(answer == 4){
        mainMenu();
    }
    else if(answer == 5){
        cout << "Shutting Down.\n";
        exit(EXIT_SUCCESS);
    }

    DocumentProcessor process;

    while(answer != 4){
        if(answer == 1){
            cout << "Choose a data structure?\n";
            string jsonPath = argv[1];
            indexHandler.chooseIndex(process,argv);
        }
        else if(answer == 2){
            QuerySearcher s(indexHandler.returnIndex(),process.getNumDocs());
            s.getQuery();
        }
        else if(answer == 3){
            process.printParsingStats();
        }
        interactiveMenu(argv);
    }
}

int main(int argc, char *argv[])
{
    if(argc > 1){
        int choice = 0;
        mainMenu();
        choice == 1? maintenanceMenu(): interactiveMenu(argv);
    }
}
