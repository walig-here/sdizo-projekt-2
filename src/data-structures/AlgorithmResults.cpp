#include "data-structures/AlgorithmResults.h"

MSTResult::MSTResult(DynamicArray<VertexData>& prim_array){

    // Inicjalizuje mst
    mst = 0;

    // Sczytuję dane nt kolejnych wierzchołków, budując w ten sposób krawędzie, które sortuje kolejno: wierzchołka początkowego, wagi 
    EdgeData edge(0,0,0);
    int j;
    for(int i = 0; i < prim_array.getLength(); i++){
        // wierzchołek, startowy pomijam
        if(prim_array[i]->predecessor == NULL_VERTEX) continue;

        // wczytuję krawędź
        edge = EdgeData(
            min(prim_array[i]->predecessor, i),
            max(prim_array[i]->predecessor, i),
            prim_array[i]->weight
        );
        mst += prim_array[i]->weight;

        // sortowanie wyników
        j = edges.size();
        for(; j-1 >= 0; j--){
            // względem początku krawędzia
            if(edges[j-1].begin < edge.begin)
                break;
            // względem wagi krawędzi
            if(edges[j-1].begin == edge.begin && edges[j-1].weigth < edge.weigth)
                break;
        }
        edges.insert(edges.begin() + j, {edge});
    }

}

Path::Path(DynamicArray<VertexData>& dijkstra_array, unsigned end){

    // Z pomocą tablicy z algorytmu buduję ścieżkę od wierzchołka startowego do końcowego
    // Biorę wierzchołki od końca do początku ścieżki. Jeżeli dotrzemy do NULL_VERTEX, to oznacza,
    // że udało się przejść całą ścieżkę.
    int vertex = end;
    distance = dijkstra_array[vertex]->weight;
    while (vertex != NULL_VERTEX){
        path.insert(path.begin(), vertex);
        vertex = dijkstra_array[vertex]->predecessor;
    }  

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
        paths[i].print();

}

PathfindingResult::PathfindingResult(DynamicArray<VertexData>& dijkstra_array, unsigned start){

    // Zapisuję wierzchołek startowyu
    this->start = start;

    // Tworzymy ścieżki dla kolejnych wierzchołków
    for(int i = 0; i < dijkstra_array.getLength(); i++)
            paths.push_back(Path(dijkstra_array, i));

}