#ifndef PROGAMINTERFACE_H
#define PROGAMINTERFACE_H
#include "IndexHandler.h"
#include "DocumentProcessor.h"

class ProgramInterface{
private:
    DocumentProcessor process;
    IndexHandler indexHandler;

public:

    int mainMenu();
    void maintenanceMenu(char *argv[]);
    void interactiveMenu(char *argv[]);

};

#endif // PROGAMINTERFACE_H
