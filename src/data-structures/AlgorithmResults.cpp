#include "data-structures/AlgorithmResults.h"

MSTResult::MSTResult(DynamicArray<PrimVertex>& prim_array){

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

void MSTResult::print(){

    // Nagłówek
    printf("\n%-12s\t\t%-s\n", "Edge", "Weight");

    // Wyświetlam listę krawędzi
    for(auto edge : edges)
        printf("(%4d, %4d)\t\t%d\n", edge.begin, edge.end, edge.weigth);
    
    // Wyświetlam MST
    printf("MST = %d\n", mst);

}