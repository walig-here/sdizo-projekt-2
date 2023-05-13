#include "app/modules/TreeModule.h"
#include "app/utility/Console.h"

#include "graphs/MatrixGraph.h"
#include "graphs/ListGraph.h"

TreeModule::TreeModule() : Module("WYZNACZANIE MINIMALNEGO DRZEWA ROZPINAJACEGO:"){

    graph = nullptr;

    menu->addOption(TREE_EXIT, "Powrot do menu glownego");
    menu->addOption(TREE_LOAD, "Wczytaj graf z pliku");
    menu->addOption(TREE_PRINT, "Wyswietl graf");

}

TreeModule::~TreeModule(){

    if(graph != nullptr)
        delete graph;

}

void TreeModule::loop(){

    bool is_running = true;
    while (is_running){
        
        Console::clearScreen();

        switch (menu->getUserChoice()){

            // Wyjście do menu
            case TREE_EXIT: is_running = false; break;

            // Wczytanie grafu z pliku
            case TREE_LOAD: loadGraph(); break;

            // Wyśweitlenie grafu
            case TREE_PRINT: printGraph(); break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;
        
        }

    }
    

}

#include "app/utility/FileReader.h"
void TreeModule::loadGraph(){

    // Pobranie nazwy pliku od użytkownika
    loaded_graph_data = false;
    unsigned placeholder;
    edges = FileReader::readGraphData(Console::getInput("Wprowadz nazwe pliku:"), verticies_amount, placeholder, placeholder);

    // Sprawdzenie, czy wczytywanie odbyło się poprawnie
    if(edges.size() == 0 && placeholder == 0 && verticies_amount == 0){
        cout << "Wystapil blad wczytywania danych! Sprobouj ponownie." << endl; 
        Console::waitForUserResponse();
        return;
    }

    // Jeżeli tak, to dane grafu znajdują się już w module
    loaded_graph_data = true;

}

void TreeModule::printGraph(){

    // Sprawdzamy, czy moduł ma dane niezbędne do wczytania grafu, jeżeli nie, to każemy użytkownikowi je wczytac
    if(!loaded_graph_data){
        cout << "Brak danych do wyswietlenia! Wczytaj graf, przed jego wysweitleniem." << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wczytujemy graf
    graph = chooseRepresentation();
    if(graph == nullptr){
        Console::waitForUserResponse();
        return;
    }

    // Wyświetlam graf
    graph->print();
    Console::waitForUserResponse();

    // Zwolnienie instancji grafu
    delete graph;
    graph = nullptr;

}