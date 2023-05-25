#include <iostream>
#include "app/utility/Menu.h"
#include "app/utility/Console.h"
#include "app/modules/Module.h"
#include "app/utility/GraphGenerator.h"
#include "examinations/Examination.h"

using namespace std;

/**
 * @brief Zbiór opcji dostępnych w głównym menu aplikacji.
 */
enum mainMenuOptions{
    MENU_EXIT,
    MENU_TREE_MODULE,
    MENU_PATH_MODULE,
    MENU_GENERATE_GRAPH,
    MENU_EXAMINATION
};


/**
 * @brief 
 * Generuje losowy graf i zapisuje go do pliku
 */
void generateGraph();

/**
 * @brief Główna pętla aplikacji.
 */
int main(int argc, char const *argv[]){

    // Ustalenie opcji w menu głównym
    Menu main_menu("MENU GLOWNE:");
    main_menu.addOption(MENU_EXIT, "Zamknij program");
    main_menu.addOption(MENU_TREE_MODULE, "Wyszukiwanie minimalnego drzewa rozpinajacego");
    main_menu.addOption(MENU_PATH_MODULE, "Wyszukiwanie najkrotszej sciezki w grafie");
    main_menu.addOption(MENU_GENERATE_GRAPH, "Wygeneruj losowy graf");
    main_menu.addOption(MENU_EXAMINATION, "Przeprowadz badania algorytmow");

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

            // Wygenerowanie losowego grafu
            case MENU_GENERATE_GRAPH: generateGraph(); break;

            // Przeprowadzenie badań
            case MENU_EXAMINATION: {
                Examination examination;
                examination.examineAlgorithm();
            }break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;

        }

    }

    // Wyjście z aplikacji
    return 0;
}

#include "app/utility/FileWriter.h"
void generateGraph(){

    // Ustalenie parametrów grafu
    unsigned size;
    int density;
    bool directed;
    bool not_negative;

    Menu representation_menu("CZY GRAF MA BYC SKIEROWANY?");
    representation_menu.addOption(0, "Nie");
    representation_menu.addOption(1, "Tak");
    switch (representation_menu.getUserChoice())
    {
        case 0: directed = false; break;
        case 1: directed = true; break;
        default:
            cout << "Wybrano niepoprawna opcje!" << endl;
            Console::waitForUserResponse();
            return;
        break;
    }

    Menu negativeness_menu("CZY GRAF MA ZAWIERAC UJEMNE KRAWEDZIE?");
    negativeness_menu.addOption(0, "Nie");
    negativeness_menu.addOption(1, "Tak");
    switch (negativeness_menu.getUserChoice())
    {
        case 0: not_negative = true; break;
        case 1: not_negative = false; break;
        default:
            cout << "Wybrano niepoprawna opcje!" << endl;
            Console::waitForUserResponse();
            return;
        break;
    }

    try{
        size = Console::getIntInput("Wprowadz ilosc wierzcholkow:");
    } catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        Console::waitForUserResponse();
        return;
    }

    try{
        density = Console::getIntInput("Wprowadz gestosc grafu[0-100]:");
        if(density < 0 || density > 100){
            cout << "Wprowadzona wartosc jest niepoprawna!" << endl;
            Console::waitForUserResponse();
            return;
        }
    } catch(const std::exception& e){
        std::cerr << e.what() << '\n';
        Console::waitForUserResponse();
        return;
    }
    
    // Generowanie grafu
    Graph* graph = GraphGenerator::generateGraph(MATRIX, size, directed, density/100.0f, not_negative);

    // Zapisanie grafu
    string filename = Console::getInput("Wprowadz nazwe pliku, do ktorego zapisany ma zostac graf:");
    if(!FileWriter::saveGraph(filename, size, 0, size/2, graph->getEdgesList(directed))){
        cout << "Wsytapil blad zapisu!" << endl;
        Console::waitForUserResponse();
        return;
    }
    cout << "Zapisano graf do pliku " << filename << endl;
    Console::waitForUserResponse();

}