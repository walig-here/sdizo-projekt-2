#include "app/utility/GraphGenerator.h"

Graph* GraphGenerator::generateGraph(GraphRepresentations representation, int size, bool directed, float density){

    // Normalizacja parametrów
    if(density < 0) density = 0.0f;
    else if (density > 1) density = 1.0f;
    if(size < 0) size = 0;

    // Maksymalna ilość krawędzi w grafie nieskierowanym -> V*(V-1), bo do każdego innego wierzchołka
    // W grafie skierowanym -> V^2, bo do samego siebie oraz do innych wierzchołków 
    long long edge_count;
    if(directed) edge_count = size*size;
    else edge_count = size*(size-1);

    // Gęstość definiuje ostateczną ilość krawędzi
    edge_count *= density;

    // Generowanie krawędzi
    vector<EdgeData> edges = getRandomEdges(size, edge_count, directed);

    // Tworzony jest graf w odpowiedniej reprezentacji
    if(representation == LIST) return new ListGraph(size, edges, directed);  
    else if (representation == MATRIX) return new MatrixGraph(size, edges, directed);
    return nullptr;

}

bool GraphGenerator::edgeExistIn(vector<EdgeData> edges_set, int start, int end, bool directed){

    for(auto edge : edges_set){
        if(!directed && ((edge.begin == start && edge.end == end) || (edge.begin == end && edge.end == start)))
            return true;
        else if(edge.begin == start && edge.end == end)
            return true;
    }
    return false;

}

vector<EdgeData> GraphGenerator::getRandomEdges(int verticies, long long edges_count, bool directed){

    // Inicjowanie miejsca na krawędzie
    vector<EdgeData> edges(edges_count);

    // Losujemy kolejno wagę krawędzi oraz jej wierzchołki składowe
    // Dla skierowanego losowanie odbywa się z pełnej puli
    // Dla nieskierowanego losowanie odbywa się z puli pomniejszonej o wierzołek początkowy
    vector<int> edge_data;
    int weight;
    for(long long i = 0; i < edges_count; i++){

        weight = RandomNumberGenerator::getIntegers(1, INT_MIN+1, INT_MAX-1)[0];
        while(true){
            
            edge_data = RandomNumberGenerator::getIntegers(2, 0, verticies);

            if(!directed && edge_data[0] == edge_data[1]) continue;
            if(edgeExistIn(edges, edge_data[0], edge_data[1], directed)) continue;
            break;

        }
        edges.push_back(EdgeData(edge_data[0], edge_data[1], weight));
        edge_data.clear();

    }
    
    return edges;

}