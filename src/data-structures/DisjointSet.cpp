#include "data-structures/DisjointSet.h"

DisjointSets::DisjointSets(int amount_of_sets){

    sets = new DisjointSet[amount_of_sets];
    size =  amount_of_sets;
    for(int i = 0; i < size; i++)
        sets[i].representant = i;

}

DisjointSets::~DisjointSets(){

    delete[] sets;

}

int DisjointSets::getSet(int vertex){

    if(sets[vertex].representant != vertex) 
        sets[vertex].representant = getSet(sets[vertex].representant);
    return sets[vertex].representant;

}

void DisjointSets::unionSets(int representant_1, int representant_2){

    // Jeżeli obaj reprezentanci są równi, to nie ma czego łączyć
    if(representant_1 == representant_2)
        return;

    // Do zbioru o większej randze dołączam zbiór o mniejszej randze
    if(sets[representant_1].rank > sets[representant_2].rank)
        sets[representant_2].representant = representant_1;
    else 
        sets[representant_1].representant = representant_2;
    if(sets[representant_1].rank == sets[representant_2].rank)
        sets[representant_1].rank++;

}