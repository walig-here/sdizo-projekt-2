#pragma once
#include "app/modules/Module.h"

using namespace std;

// Moduł obsługujący algorytmy wyznaczania minimalnego drzewa spinającego
class TreeModule : virtual public Module{

    /* POLA */

    /* METODY */

    // Konstruktor
    public: TreeModule();

    // Destruktor
    public: virtual ~TreeModule();

    public: virtual void loop();

    private: void loadGraph();

    private: void printGraph();

};

enum TreeOptions{
    TREE_EXIT,
    TREE_LOAD,
    TREE_PRINT
};