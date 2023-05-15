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

    public: virtual void loop();

};

enum PathOptions{
    PATH_EXIT,
    PATH_LOAD,
    PATH_PRINT
};