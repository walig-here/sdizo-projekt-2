#include "graphs/MatrixGraph.h"

MatrixGraph::MatrixGraph(unsigned verticies_count, vector<EdgeData> edges_data){

    // Inicjalizacja macierzy - domyślnie graf nie zawiera żadnych krawędzi
    adjacency_matrix = new Matrix(verticies_count, NO_CONNECTION);

    // Na podstawie danych wczytuje z pliku uzupełniam macierze
    // Jeżeli krawędź zawiera przynajmniej jeden wierzchołek, który nie istnieje w grafie, to zostaje pominięta
    int* control_element = nullptr;
    for(auto edge : edges_data){
        control_element = adjacency_matrix->get(edge.begin, edge.end);
        if(control_element == nullptr) continue;

        *adjacency_matrix->get(edge.end, edge.begin) = *control_element = edge.weigth;
    }

}

MatrixGraph::~MatrixGraph(){

    delete adjacency_matrix;

}