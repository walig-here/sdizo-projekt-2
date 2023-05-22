#include "data-structures/DynamicArray.h"
#include "graphs/Graph.h"

/**
 * @brief 
 * Klasa zapewniająca mechanizmy sortujące.
 */
class SortingMachine{

    /* METODY */

    /**
     * @brief 
     * Sortuje tablicę krawędzi, używając rekurencyjnej metody quick-sort. Sortowanie odbywa się na obszarze tablicy
     * ograniczonym przez indeksy left oraz right. W wypadku zadania wartości left i right spoza zakresu tablicy zostanie
     * dokonany podział na całości tablicy.
     * 
     * @param array tablica dynamiczna zawierająca krawędzie
     * @param left indeks lewego krańca tablicy
     * @param right indek prawego krańca tablicy
     * 
     * @return posortowaną tablicę
     */
    public: static void sort(DynamicArray<EdgeData>& array, unsigned left, unsigned right);


    /**
     * @brief 
     * Wydziela punkt podziału na podtablice do algorytmu quick-sort sortującego tablicę krawędzi.
     * Ten podział może odbyć się na całej tablicy, jak i wyłącznie na jej fragmencie ograniczanym
     * przez zadane indeksy left oraz right. W wypadku zadania tablicy pustej lub 1-elementowej 
     * zwróci wartość -1. W wypadku zadania wartości left i right spoza zakresu tablicy zostanie
     * dokonany podział na całości tablicy.
     * 
     * @param array tablica, na której chcemy dokonać podziału
     * @param left indeks lewego krańca tablicy
     * @param right indeks prawego krańca tablicy
     * 
     * @return Indeks, pod którym znajduje się ostatni element pierwszej z wydzielonych podtablic.
     * Wartość -1 zostanie zwrócona przy zadaniu tablicy mniejszej niż 2-elementowa.
     */
    private: static int quickSortPartition(DynamicArray<EdgeData>& array, unsigned left, unsigned right);

};