#include <iostream>
#include "app/utility/Menu.h"
#include "app/utility/Console.h"
#include "app/modules/Module.h"

using namespace std;


// testowanie funkcji, które nie przeszły testu jednostkowego
#include "graphs/MatrixGraph.h"
void test(){

    // Tworzenie grafu
    vector<EdgeData> edges = {
        EdgeData(0,2,2),
        EdgeData(2,0,-1),
        EdgeData(0,1,10),
        EdgeData(1,3,-1),
        EdgeData(3,2,11)
    };
    unsigned v = 4;
    MatrixGraph graph(v, edges, true);
    unsigned start = 2;

    // Wykonanie algorytmu
    PathfindingResult result = graph.algorithmBellmanFord(start);

    result.print();

}

/**
 * @brief Zbiór opcji dostępnych w głównym menu aplikacji.
 */
enum mainMenuOptions{
    MENU_EXIT,
    MENU_TREE_MODULE,
    MENU_PATH_MODULE
};


/**
 * @brief Główna pętla aplikacji.
 */
int main(int argc, char const *argv[]){

    // Ustalenie opcji w menu głównym
    Menu main_menu("MENU GLOWNE:");
    main_menu.addOption(MENU_EXIT, "Zamknij program");
    main_menu.addOption(MENU_TREE_MODULE, "Wyszukiwanie minimalnego drzewa rozpinajacego");
    main_menu.addOption(MENU_PATH_MODULE, "Wyszukiwanie najkrotszej sciezki w grafie");

    // Główna pętla aplikacji
    bool is_running = true;
    while(is_running){

        Console::clearScreen();
        switch (main_menu.getUserChoice()){
        
            // Wyjście z aplikacji
            case MENU_EXIT: is_running = false; break;

            // Wejście do modułu wyszukiwania MST
            case MENU_TREE_MODULE: Module::start(TREE_MODULE); break;

            // Wejście do modułu wyszukiwania najkrótszej ścieżki
            case MENU_PATH_MODULE: Module::start(PATH_MODULE); break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;

        }

    }

    // Wyjście z aplikacji
    return 0;
}

