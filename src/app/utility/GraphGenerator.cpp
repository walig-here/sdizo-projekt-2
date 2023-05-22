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
    cout << "Ilosc wierzcholkow: " << size << endl;
    cout << "Ilosc krawedzi: " << max_edge_count << endl;
    vector<EdgeData> edges = getRandomEdges(size, max_edge_count * density , max_edge_count, directed, not_negative);

    // Tworzony jest graf w odpowiedniej reprezentacji
    if(representation == LIST) return new ListGraph(size, edges, directed);  
    else if (representation == MATRIX) return new MatrixGraph(size, edges, directed);
    return nullptr;

}

vector<EdgeData> GraphGenerator::getRandomEdges(int verticies, long long edges_count, long long max_egdes_count, bool directed, bool not_negative){

    // Jeżeli mamy wykluczyć wszystkie krawędzie, to optymalniej jest zwrócić pusty zbiór krawędzi
    if(edges_count == 0) return vector<EdgeData>();

    // Z puli wszystkich dostępnych krawędzi wykluczam losowo część.
    // Wielkość tej części to różnica między wszystkimi krawędziami, a ilością krawędzi, która ma znaleźć
    // się docelowo w grafie. W ten sposób uzyskuję losowy zbiór krawędzi dla generowanego grafu.
    vector<EdgeData> possible_edges = getAllPossibleEdges(verticies, directed, max_egdes_count, not_negative);
    long long chosen_edge_data;
    for(long long i = 0; i < max_egdes_count-edges_count; i++){
        chosen_edge_data = RandomNumberGenerator::getIntegers(1, 0, possible_edges.size()-1)[0];
        possible_edges.erase(possible_edges.begin() + chosen_edge_data);
    }
    
    return possible_edges;

}

vector<EdgeData> GraphGenerator::getAllPossibleEdges(int verticies, bool directed, int max_egde_count, bool not_negative){

    vector<EdgeData> combinations(max_egde_count);
    int weight;
    long long combination_index = 0;
    for(int i = 0; i < verticies; i++){
        for(int j = 0; j < verticies; j++){
            if(!directed && j <= i) continue;
        
            weight = RandomNumberGenerator::getIntegers(1, ( not_negative ? 0 : 2*CHAR_MIN ), 2*CHAR_MAX)[0];
            combinations[combination_index] = EdgeData(i, j, weight);
            combination_index++;
        }
    }
    return combinations;

}