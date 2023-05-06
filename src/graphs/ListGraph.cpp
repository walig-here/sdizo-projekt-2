#include "graphs/ListGraph.h"

ListGraph::ListGraph(unsigned verticies_count, vector<EdgeData> edges_data){

    // Inicjalizacja zbioru list sąsiadów
    adjentency_lists = new List[verticies_count];

}

ListGraph::~ListGraph(){

}