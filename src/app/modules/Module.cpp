#include "app/modules/Module.h"
#include "app/modules/TreeModule.h"
#include "app/utility/Console.h"

#include "graphs/MatrixGraph.h"
#include "graphs/ListGraph.h"

void Module::start(ModuleTypes module_type){

    Module* module;
    switch (module_type){
        
        case TREE_MODULE: module = new TreeModule(); break;

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

Graph* Module::chooseRepresentation(){

    // Pytam użytkownika o formę wyświetlenia grafu
    Menu print_menu("WYBOR REPREZENTACJI GRAFU:");

    #define MATRIX 0
    #define LIST 1

    print_menu.addOption(MATRIX, "Macierzowa");
    print_menu.addOption(LIST, "Listowa");

    switch (print_menu.getUserChoice())
    {
        // Macierzowe
        case MATRIX: return new MatrixGraph(verticies_amount, edges, false);

        // Listowe
        case LIST: return new ListGraph(verticies_amount, edges, false);
    
        // Niepoprawna opcja
        default: return nullptr; break;
    }

}