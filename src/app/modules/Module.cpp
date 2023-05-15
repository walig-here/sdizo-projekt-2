#include "app/modules/Module.h"
#include "app/modules/TreeModule.h"
#include "app/modules/PathModule.h"
#include "app/utility/Console.h"

#include "graphs/MatrixGraph.h"
#include "graphs/ListGraph.h"

void Module::start(ModuleTypes module_type){

    Module* module;
    switch (module_type){
        
        // Moduł wyznaczanie MST
        case TREE_MODULE: module = new TreeModule(); break;

        // Moduł wyznaczania najkrótszej ścieżki
        case PATH_MODULE: module = new PathModule(); break;

    }
    
    module->loop();
    delete module;

}

Module::Module(const string menu_header){

    menu = new Menu(menu_header);
    graph = nullptr;
    verticies_amount = 0;
    loaded_graph_data= false;

}

Module::~Module(){

    delete menu;

}

Graph* Module::chooseRepresentation(ModuleTypes module_type){

    // Pytam użytkownika o formę wyświetlenia grafu
    Menu print_menu("WYBOR REPREZENTACJI GRAFU:");

    #define MATRIX 0
    #define LIST 1

    print_menu.addOption(MATRIX, "Macierzowa");
    print_menu.addOption(LIST, "Listowa");

    // Ustalam czy krawędzie mają być skierowane
    bool directed = false;
    if(module_type == PATH_MODULE) directed = true;

    switch (print_menu.getUserChoice())
    {
        // Macierzowe
        case MATRIX: return new MatrixGraph(verticies_amount, edges, directed);

        // Listowe
        case LIST: return new ListGraph(verticies_amount, edges, directed);
    
        // Niepoprawna opcja
        default: return nullptr; break;
    }

}

#include "app/utility/FileReader.h"
void Module::loadGraph(){

    // Pobranie nazwy pliku od użytkownika
    loaded_graph_data = false;
    edges = FileReader::readGraphData(Console::getInput("Wprowadz nazwe pliku:"), verticies_amount, begin, end);

    // Sprawdzenie, czy wczytywanie odbyło się poprawnie
    if(edges.size() == 0 && begin == 0 && end == 0 && verticies_amount == 0){
        cout << "Wystapil blad wczytywania danych! Sprobouj ponownie." << endl; 
        Console::waitForUserResponse();
        return;
    }

    // Jeżeli tak, to dane grafu znajdują się już w module
    loaded_graph_data = true;

}

void Module::printGraph(ModuleTypes module_type){

    // Sprawdzamy, czy moduł ma dane niezbędne do wczytania grafu, jeżeli nie, to każemy użytkownikowi je wczytac
    if(!loaded_graph_data){
        cout << "Brak danych do wyswietlenia! Wczytaj graf, przed jego wysweitleniem." << endl;
        Console::waitForUserResponse();
        return;
    }

    // Wczytujemy graf
    graph = chooseRepresentation(module_type);
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