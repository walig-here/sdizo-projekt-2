#include "app/modules/PathModule.h"
#include "app/utility/Console.h"

PathModule::PathModule() : Module("WYZNACZANIE NAJKROTSZEJ SCIEZKI:"){

    graph = nullptr;

    menu->addOption(PATH_EXIT, "Powrot do menu glownego");
    menu->addOption(PATH_LOAD, "Wczytaj graf z pliku");
    menu->addOption(PATH_PRINT, "Wyswietl graf");

}

PathModule::~PathModule(){

    if(graph != nullptr)
        delete graph;

}

void PathModule::loop(){

    bool is_running = true;
    while (is_running){
        
        Console::clearScreen();

        switch (menu->getUserChoice()){

            // Wyjście do menu
            case PATH_EXIT: is_running = false; break;

            // Wczytanie grafu z pliku
            case PATH_LOAD: loadGraph(); break;

            // Wyśweitlenie grafu
            case PATH_PRINT: printGraph(PATH_MODULE); break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;
        
        }

    }
    

}