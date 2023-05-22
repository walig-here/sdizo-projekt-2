#include "app/modules/TreeModule.h"
#include "app/utility/Console.h"

#include "graphs/MatrixGraph.h"
#include "graphs/ListGraph.h"

TreeModule::TreeModule() : Module("WYZNACZANIE MINIMALNEGO DRZEWA ROZPINAJACEGO:"){

    graph = nullptr;

    menu->addOption(TREE_EXIT, "Powrot do menu glownego");
    menu->addOption(TREE_LOAD, "Wczytaj graf z pliku");
    menu->addOption(TREE_PRINT, "Wyswietl graf");
    menu->addOption(TREE_PRIM, "Algorytm Prima");
    menu->addOption(TREE_KRUSKAL, "Algorytm Kruskala");

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
            case TREE_PRINT: printGraph(TREE_MODULE); break;

            // Algorytm Prima
            case TREE_PRIM: algorithmPrim(); break;

            // Algorytm Kruskala
            case TREE_KRUSKAL: algorithmKruskal(); break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;
        
        }

    }
    

}

void TreeModule::algorithmKruskal(){

    // Sprawdzamy, czy moduł ma dane niezbędne do wczytania grafu, jeżeli nie, to każemy użytkownikowi je wczytac
    if(!loaded_graph_data){
        cout << "Brak danych! Wczytaj graf, przed wykonaniem na nim algorytmu." << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wczytujemy graf
    graph = chooseRepresentation(TREE_MODULE);
    if(graph == nullptr){
        Console::waitForUserResponse();
        return;
    }

    // Wykonuję algorytm Kruskala dla wczytanego aktualnie grafu oraz 
    // wierzchołka początkowego begin (chociaż może być to dowolny inny wierzchołek)
    MSTResult result = graph->algorithmKruskal();
    if(result.isEmpty()) cout << "Blad wykonywania algorytmu! Graf jest pusty lub niespojny!" << endl;
    else result.print();
    Console::waitForUserResponse();

    // Zwolnienie instancji grafu
    delete graph;
    graph = nullptr;

}

void TreeModule::algorithmPrim(){

    // Sprawdzamy, czy moduł ma dane niezbędne do wczytania grafu, jeżeli nie, to każemy użytkownikowi je wczytac
    if(!loaded_graph_data){
        cout << "Brak danych! Wczytaj graf, przed wykonaniem na nim algorytmu." << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wczytujemy graf
    graph = chooseRepresentation(TREE_MODULE);
    if(graph == nullptr){
        Console::waitForUserResponse();
        return;
    }

    // Wykonuję algorytm Prima dla wczytanego aktualnie grafu oraz 
    // wierzchołka początkowego begin (chociaż może być to dowolny inny wierzchołek)
    MSTResult result = graph->alogrithmPrim(begin);
    if(result.isEmpty()) cout << "Blad wykonywania algorytmu! Graf jest pusty lub niespojny!" << endl;
    else result.print();
    Console::waitForUserResponse();

    // Zwolnienie instancji grafu
    delete graph;
    graph = nullptr;

}