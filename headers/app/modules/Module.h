#pragma once
#include "app/utility/Menu.h"
#include "graphs/Graph.h"
#include <vector>

using namespace std;

// Typy modułów
enum ModuleTypes{
    TREE_MODULE
};

// Klasa służąca do obługi modułów aplikacji
class Module{

    /* POLA */
    protected: Menu* menu;                    // menu modułu
    protected: Graph* graph;                  // graf, na którym zostaną wywołane algorytmy
    protected: vector<EdgeData> edges;        // zbiór krawędzi wczytanego grafu
    protected: unsigned verticies_amount;     // liczba wierzchołków wczytanego grafu
    protected: bool loaded_graph_data;        // czy zostały wczytane jakiekolwiek dane niezbędne do stworzenia grafu

    /* METODY */

    // Otwiera wskazany moduł
    public: static void start(ModuleTypes type);

    // Konstruktor
    protected: Module(const string menu_header);

    // Destruktor
    protected: virtual ~Module();

    // Obsługa pętli
    private: virtual void loop() = 0;

    // Wybór reprezentacji grafu
    protected: Graph* chooseRepresentation();

};