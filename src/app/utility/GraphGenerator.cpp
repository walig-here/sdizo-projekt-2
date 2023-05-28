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

    // Zapewniam spójność
    vector<EdgeData> required_edges = ensureConnectivity(possible_edges, verticies);
    if(chosen_edges.size() < verticies-1) chosen_edges.resize(verticies-1);
    for(int i = 0; i < verticies-1; i++)
        chosen_edges[i] = required_edges[i];

    // Rozdzielam zbiór wszystkich możliwych krawędzi na 2 podzbiory: odrzucony i nieodrzucony.
    // Z metody zawsze zwracany jest zbiór nieodrzucony. Jest to ten zbiór, którego liczebność 
    // wynosi edges_count (docelowa liczbę krawędzi generowanego grafu). Zbiory buduję przenosząc 
    // losowo krawędzie ze zbioru possible_edges do chosen_edges, który ma zawsze najmniejszą możliwą
    // liczebność równą edges_count lub (max_egdes_count- edge_count). W ten sposób zawsze
    // muszę wykonać minimalną ilość losowań i przeniesień. Z metody zwracam ten zbiór, który
    // ma liczebność edge_count (jest to zbiór krawędzi nieodrzuconych).
    long long chosen_edge_index;
    for(long long i = verticies-1; i < chosen_edges.size(); i++){
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

vector<EdgeData> GraphGenerator::ensureConnectivity(vector<EdgeData>& all_edges, unsigned size){

    // Inicjalizuje tablicę informującą o tym, czy dany wierzchołek znajduje się już w grafie
    vector<bool> tree_includement(size, false);

    // Inicjalizuje tablicę zawierającą wybrane krawędzie
    vector<EdgeData> chosen_edges(size-1);
    int chosen_edge;                            // indeks wybranej krawędzie
    unsigned already_chosen_edges = 0;          // liczba już wybranych krawędzi

    // Wybieram pierwszą krawędź
    chosen_edge = RandomNumberGenerator::getIntegers(1, 0, all_edges.size()-1)[0];
    chosen_edges[already_chosen_edges] = all_edges[chosen_edge];
    all_edges.erase(all_edges.begin() + chosen_edge);
    tree_includement[chosen_edges[already_chosen_edges].end] = true;
    tree_includement[chosen_edges[already_chosen_edges].begin] = true;
    already_chosen_edges++;

    // Losuję krawędź. Jeżeli zawiera ona oba wierzchołki już obecne w grafie lub oba wierzchołki nieobecne w grafie, to
    // ją odrzucam. Jeżeli zawiera ona jeden wierzchołek spoza grafu, a drugi należący do grafu, to ją przyjmuję.
    // Losowanie kończy się po uzyskaniu minimalnej liczby krawędzi zapewniającej spójność (|V|-1).
    bool is_running = true;
    do {
        chosen_edge = RandomNumberGenerator::getIntegers(1, 0, all_edges.size()-1)[0];

        if(!(tree_includement[all_edges[chosen_edge].end] ^ tree_includement[all_edges[chosen_edge].begin]))
            continue;
        
        chosen_edges[already_chosen_edges] = all_edges[chosen_edge];
        all_edges.erase(all_edges.begin() + chosen_edge);
        tree_includement[chosen_edges[already_chosen_edges].end] = true;
        tree_includement[chosen_edges[already_chosen_edges].begin] = true;
        already_chosen_edges++;

    } while (already_chosen_edges < size-1);

    return chosen_edges;

}