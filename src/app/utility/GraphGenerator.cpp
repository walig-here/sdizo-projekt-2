#include "app/utility/GraphGenerator.h"

Graph* GraphGenerator::generateGraph(GraphRepresentations representation, int size, bool directed, float density, bool not_negative){

    // Normalizacja parametrów
    if(density < 0) density = 0.0f;
    else if (density > 1) density = 1.0f;
    if(size < 0) size = 0;

    // Maksymalna ilość krawędzi w grafie nieskierowanym -> |V| po 2
    // W grafie skierowanym -> V^2
    unsigned long long max_edge_count;
    if(directed) max_edge_count = size*size;
    else max_edge_count = (size*size - size)/2;

    // Generowanie krawędzi
    vector<EdgeData> edges = getRandomEdges(size, max_edge_count * density , max_edge_count, directed, not_negative);

    // Tworzony jest graf w odpowiedniej reprezentacji
    Graph* graph = nullptr;
    if(representation == LIST) graph = new ListGraph(size, edges, directed);  
    else if (representation == MATRIX) graph = new MatrixGraph(size, edges, directed);
    return graph;

}

vector<EdgeData> GraphGenerator::getRandomEdges(int verticies, long long edges_count, long long max_egdes_count, bool directed, bool not_negative){

    // Generuję zbiór wszystkich możliwych krawędzi
    vector<EdgeData> possible_edges = getAllPossibleEdges(verticies, directed, max_egdes_count, not_negative);
    vector<EdgeData> chosen_edges(min(edges_count, max_egdes_count - edges_count));

    // Rozdzielam zbiór wszystkich możliwych krawędzi na 2 podzbiory: odrzucony i nieodrzucony.
    // Z metody zawsze zwracany jest zbiór nieodrzucony. Jest to ten zbiór, którego liczebność 
    // wynosi edges_count (docelowa liczbę krawędzi generowanego grafu). Zbiory buduję przenosząc 
    // losowo krawędzie ze zbioru possible_edges do chosen_edges, który ma zawsze najmniejszą możliwą
    // liczebność równą edges_count lub (max_egdes_count- edge_count). W ten sposób zawsze
    // muszę wykonać minimalną ilość losowań i przeniesień. Z metody zwracam ten zbiór, który
    // ma liczebność edge_count (jest to zbiór krawędzi nieodrzuconych).
    long long chosen_edge_index;
    for(long long i = 0; i < chosen_edges.size(); i++){
        chosen_edge_index = RandomNumberGenerator::getIntegers(1, 0, possible_edges.size()-1)[0];
        chosen_edges[i] = possible_edges[chosen_edge_index];
        possible_edges.erase(possible_edges.begin() + chosen_edge_index);
    }
    
    if(possible_edges.size() == edges_count) return possible_edges;
    return chosen_edges;

}

vector<EdgeData> GraphGenerator::getAllPossibleEdges(int verticies, bool directed, int max_egde_count, bool not_negative){

    vector<EdgeData> combinations(max_egde_count);
    vector<int> weights = RandomNumberGenerator::getIntegers(max_egde_count, ( not_negative ? 0 : 2*CHAR_MIN ), 2*CHAR_MAX);
    long long combination_index = 0;
    for(int i = 0; i < verticies; i++){
        for(int j = 0; j < verticies; j++){
            if(!directed && j <= i) continue;
            combinations[combination_index] = EdgeData(i, j, weights[combination_index]);
            combination_index++;
        }
    }
    return combinations;

}