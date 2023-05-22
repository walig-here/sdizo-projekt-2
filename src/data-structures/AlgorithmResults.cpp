#include "data-structures/AlgorithmResults.h"

MSTResult::MSTResult(DynamicArray<VertexData>& prim_array){

    // Inicjalizuje mst
    mst = 0;

    // Sczytuję dane nt kolejnych wierzchołków, budując w ten sposób krawędzie, które sortuje kolejno: wierzchołka początkowego, wagi 
    for(int i = 0; i < prim_array.getLength(); i++){
        // wierzchołek, startowy pomijam
        if(prim_array[i]->predecessor == NULL_VERTEX) continue;

        // wczytuję krawędź
        mst += prim_array[i]->weight;
        edges.push_back(EdgeData(
            min(prim_array[i]->predecessor, i),
            max(prim_array[i]->predecessor, i),
            prim_array[i]->weight
        ));

    }

}

MSTResult::MSTResult(DynamicArray<EdgeData>& kruskal_array){

    // Inicjalizuje mst
    mst = 0;

    // Sczytuję kolejne krawędzie wyznaczone przez algorytm Kruskala
    for(int i = 0; i < kruskal_array.getLength(); i++){
        edges.push_back(EdgeData(
            min(kruskal_array[i]->begin, kruskal_array[i]->end),
            max(kruskal_array[i]->end, kruskal_array[i]->begin),
            kruskal_array[i]->weigth
        ));
        mst += kruskal_array[i]->weigth;
    }

}

Path::Path(DynamicArray<VertexData>& dijkstra_array, unsigned start, unsigned end){

    // Z pomocą tablicy z algorytmu buduję ścieżkę od wierzchołka startowego do końcowego
    // Biorę wierzchołki od końca do początku ścieżki. Jeżeli dotrzemy do NULL_VERTEX, to oznacza,
    // że udało się przejść całą ścieżkę.
    int vertex = end;
    distance = dijkstra_array[vertex]->weight;
    if(distance == INFINITY_W) return;
    while (vertex != NULL_VERTEX){
        path.insert(path.begin(), vertex);
        vertex = dijkstra_array[vertex]->predecessor;
    }  

    // Jeżeli ścieżka nie zawiera wierzchołka startowego na swoim początku, to nie
    // jest ona uznawana za poprawną
    if(path[0] == start) return;
    path.clear();

}

void MSTResult::print(){

    // Nagłówek
    printf("\n%-12s\t\t%-s\n", "Edge", "Weight");

    // Wyświetlam listę krawędzi
    for(auto edge : edges)
        printf("(%4d, %4d)\t\t%d\n", edge.begin, edge.end, edge.weigth);
    
    // Wyświetlam MST
    printf("MST = %d\n", mst);

}

void Path::print(){

    // Jeżeli ścieżka nie istnieje to nie ma co wyświetlać
    if(path.size() == 0) return;

    // Koniec ścieżki oraz jej długość
    printf("%4u | %4d | ", path[path.size()-1], distance);

    // Wierzchołki ścieżki
    for(auto vertex : path)
        printf("%4u ", vertex);
    printf("\n");

}

void PathfindingResult::print(){

    // Wierzchołek startowy
    printf("\nStart = %u\n", start);

    // Nagłówek
    printf("%-5s  %-4s  %-s\n", "End", "Dist", "Path");

    // Ścieżki
    for(int i = 0; i < paths.size(); i++)
        if(i != start)
            paths[i].print();

}

PathfindingResult::PathfindingResult(DynamicArray<VertexData>& dijkstra_array, unsigned start){
        
    // Zapisuję wierzchołek startowy
    this->start = start;

    // Tworzymy ścieżki dla kolejnych wierzchołków
    for(int i = 0; i < dijkstra_array.getLength(); i++)
            paths.push_back(Path(dijkstra_array, this->start, i));

}

bool PathfindingResult::isEmpty(){

    for(auto path : paths)
        if(path.getVerticies().size() > 0)
            return false;
    return true;

}