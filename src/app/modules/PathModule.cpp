#include "app/modules/PathModule.h"
#include "app/utility/Console.h"

PathModule::PathModule() : Module("WYZNACZANIE NAJKROTSZEJ SCIEZKI:"){

    graph = nullptr;

    menu->addOption(PATH_EXIT, "Powrot do menu glownego");
    menu->addOption(PATH_LOAD, "Wczytaj graf z pliku");
    menu->addOption(PATH_PRINT, "Wyswietl graf");
    menu->addOption(PATH_DIJKSTRA, "Algorytm Dijkstry");
    menu->addOption(PATH_BELLMAN_FORD, "Algorytm Bellmana-Forda");

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

            // Algorytm Dijkstry
            case PATH_DIJKSTRA: algorithmDijkstra(); break;

            // Algorytm Bellmana-Forda
            case PATH_BELLMAN_FORD: algorithmBellmanFord(); break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;
        
        }

    }
    

}

#include "data-structures/AlgorithmResults.h"
void PathModule::algorithmBellmanFord(){

    // Sprawdzamy, czy moduł ma dane niezbędne do wczytania grafu, jeżeli nie, to każemy użytkownikowi je wczytac
    if(!loaded_graph_data){
        cout << "Brak danych! Wczytaj graf, przed wykonaniem na nim algorytmu." << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wczytujemy graf
    graph = chooseRepresentation(PATH_MODULE);
    if(graph == nullptr){
        Console::waitForUserResponse();
        return;
    }
    

    // Wykonuję algorytm Belmanna-Forda dla wczytanego aktualnie grafu oraz 
    // wierzchołka początkowego
    PathfindingResult result = graph->algorithmBellmanFord(begin);
    if(result.isEmpty()) cout << "Graf zawiera ujemny cykl!" << endl;
    else result.print();
    Console::waitForUserResponse();

    // Zwolnienie instancji grafu
    delete graph;
    graph = nullptr;

}

void PathModule::algorithmDijkstra(){

    // Sprawdzamy, czy moduł ma dane niezbędne do wczytania grafu, jeżeli nie, to każemy użytkownikowi je wczytac
    if(!loaded_graph_data){
        cout << "Brak danych! Wczytaj graf, przed wykonaniem na nim algorytmu." << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wczytujemy graf
    graph = chooseRepresentation(PATH_MODULE);
    if(graph == nullptr){
        Console::waitForUserResponse();
        return;
    }
    
    // Jeżeli graf zawiera ujemne krawędzie, to nie wykonuję algorytmu
    if(graph->containNegativeEdges()){
        cout << "Graf zawiera ujemne krawedzie!" << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wykonuję algorytm Dijkstry dla wczytanego aktualnie grafu oraz 
    // wierzchołka początkowego
    PathfindingResult result = graph->algorithmDijkstra(this->begin);
    result.print();
    Console::waitForUserResponse();

    // Zwolnienie instancji grafu
    delete graph;
    graph = nullptr;

}