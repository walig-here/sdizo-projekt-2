#include <iostream>
#include "app/utility/Menu.h"
#include "app/utility/Console.h"
#include "app/modules/Module.h"

using namespace std;


// testowanie funkcji, które nie przeszły testu jednostkowego
#include "graphs/MatrixGraph.h"
void test(){

    // Inicjalizacja grafu
    vector<EdgeData> edges = {
        EdgeData(0,1,10),
        EdgeData(0,3,1),
        EdgeData(1,3,4),
        EdgeData(1,4,8),
        EdgeData(4,3,13),
        EdgeData(3,2,1)
    };
    unsigned verticies = 5;
    unsigned start = 1;
    MatrixGraph graph(verticies, edges, false);

    graph.print();

    // Wykonanie algorytmu
    MSTResult result = graph.alogrithmPrim(start);
    result.print();

}

/**
 * @brief Zbiór opcji dostępnych w głównym menu aplikacji.
 */
enum mainMenuOptions{
    MENU_EXIT,
    MENU_TREE_MODULE
};


/**
 * @brief Główna pętla aplikacji.
 */
int main(int argc, char const *argv[]){

    test();
    return 0;

    // Ustalenie opcji w menu głównym
    Menu main_menu("MENU GLOWNE:");
    main_menu.addOption(MENU_EXIT, "Zamknij program");
    main_menu.addOption(MENU_TREE_MODULE, "Wyszukiwanie minimalnego drzewa rozpinajacego");

    // Główna pętla aplikacji
    bool is_running = true;
    while(is_running){

        Console::clearScreen();
        switch (main_menu.getUserChoice()){
        
            // Wyjście z aplikacji
            case MENU_EXIT: is_running = false; break;

            // Wejście do modułu wyszukiwania MST
            case MENU_TREE_MODULE: Module::start(TREE_MODULE); break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;

        }

    }

    // Wyjście z aplikacji
    return 0;
}

