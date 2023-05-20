#pragma once
#include "app/modules/Module.h"

using namespace std;

// Moduł obsługujący algorytmy wyznaczania minimalnego drzewa spinającego
class PathModule : virtual public Module{

    /* POLA */

    /* METODY */

    // Konstruktor
    public: PathModule();

    // Destruktor
    public: virtual ~PathModule();

    // Główna pętla modułu
    public: virtual void loop();

    // Algorytm Dijkstry
    public: void algorithmDijkstra();

    // Algorytm Bellmana-Forda
    public: void algorithmBellmanFord();

};

enum PathOptions{
    PATH_EXIT,
    PATH_LOAD,
    PATH_PRINT,
    PATH_DIJKSTRA,
    PATH_BELLMAN_FORD
};