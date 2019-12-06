#include <iostream>
#include "DSAVLTree.h"
#include "IndexHandler.h"
#include "DocumentProcessor.h"
#include "queryProcessor.h"
#include <fstream>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

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
            "[3] - Populate Corous with New Index\n" <<
            ">> ";

    cin >> answer;

    if(answer > 3){
        cout << "\nInvalid Choice. Please Try again.\n\n";
        maintenanceMenu();
    }

}

void interactiveMenu(){
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
            ">> ";

    cin >> answer;

    if(answer > 3){
        cout << "\nInvalid Choice. Please Try again.\n\n";
        interactiveMenu();
    }

    switch(answer){
    case 1:
        queryProcessor q;
        q.requestInput();
        break;
   // default:
       // break;
    }
}

int main(int argc, char *argv[])
{
    if(argc > 2){
        char type;
        cout << "Which Structure" <<endl;
        cin >> type;
        string jsonPath = argv[1];
        DocumentProcessor process;
        process.readInputData(argv[1],type);
        //process.search(argv[2]);


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
