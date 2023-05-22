#include "app/utility/GraphGenerator.h"

Graph* GraphGenerator::generateGraph(GraphRepresentations representation, int size, bool directed, float density, bool not_negative){

    // Normalizacja parametrów
    if(density < 0) density = 0.0f;
    else if (density > 1) density = 1.0f;
    if(size < 0) size = 0;

    // Maksymalna ilość krawędzi w grafie nieskierowanym -> |V| po 2
    // W grafie skierowanym -> V^2
    long long max_edge_count;
    if(directed) max_edge_count = size*size;
    else if(size < 2) max_edge_count = 0;
    else max_edge_count = factorial(size)/(factorial(size - 2) * 2);

    // Generowanie krawędzi
    vector<EdgeData> edges = getRandomEdges(size, max_edge_count * density , max_edge_count, directed, not_negative);

    // Tworzony jest graf w odpowiedniej reprezentacji
    if(representation == LIST) return new ListGraph(size, edges, directed);  
    else if (representation == MATRIX) return new MatrixGraph(size, edges, directed);
    return nullptr;

}

vector<EdgeData> GraphGenerator::getRandomEdges(int verticies, long long edges_count, long long max_egdes_count, bool directed, bool not_negative){

    // Inicjowanie miejsca na krawędzie
    vector<EdgeData> edges(edges_count);

    // Losujemy kolejno wagę krawędzi oraz jej wierzchołki składowe
    // Dla skierowanego losowanie odbywa się z pełnej puli
    // Dla nieskierowanego losowanie odbywa się z puli pomniejszonej o wierzołek początkowy
    vector<EdgeData> possible_edges = getAllPossibleEdges(verticies, directed, max_egdes_count);
    long long chosen_edge_data;
    for(long long i = 0; i < edges_count; i++){
        chosen_edge_data = RandomNumberGenerator::getIntegers(1, 0, possible_edges.size()-1)[0];
        edges[i].begin = possible_edges[chosen_edge_data].begin;
        edges[i].end = possible_edges[chosen_edge_data].end;
        edges[i].weigth = ( not_negative ? abs(possible_edges[chosen_edge_data].weigth) : possible_edges[chosen_edge_data].weigth );
        possible_edges.erase(possible_edges.begin() + chosen_edge_data);
    }
    
    return edges;

}

long long GraphGenerator::factorial(int n){

    if(n < 2) return 1;
    long long factorial = 1;
    for(int i = 2; i <= n; i++)
        factorial *= i;
    return factorial;

}

vector<EdgeData> GraphGenerator::getAllPossibleEdges(int verticies, bool directed, int max_egde_count){

    vector<EdgeData> combinations(max_egde_count);
    int weight;
    long long combination_index = 0;
    for(int i = 0; i < verticies; i++){
        for(int j = 0; j < verticies; j++){
            if(!directed && j <= i) continue;
            
            weight = RandomNumberGenerator::getIntegers(1, 2*CHAR_MIN, 2*CHAR_MAX)[0];
            combinations[combination_index] = EdgeData(i, j, weight);
            combination_index++;
        }
    }
    return combinations;

}