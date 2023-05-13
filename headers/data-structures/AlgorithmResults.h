
/**
 * @brief 
 * Zbiór struktur danych zawierających w sobie wyniki działania implementowanych algorytmów grafowych:
 * - Prima i Kruskala
 * - Dijkstry i Bellmana-Forda
 */

#pragma once
#include "graphs/Graph.h"
#include "data-structures/DynamicArray.h"
#include <vector>

#define NULL_VERTEX -2147483648     // oznacza wierchołek NULL
#define INFINITY 2147483647         // waga krawędzi równa nieskończoność

/**
 * @brief 
 * Element tablicy obrazującej stan wierzchołka wewnątrz algorytmu prima.
 */
struct PrimVertex{

    /* POLA */
    bool processed = false;             // stan rozważenia wierzchołka
    int predecessor = NULL_VERTEX;      // wierzchołek poprzedni
    int weight = INFINITY;              // waga krawędzi łączącej wierzchołek z poprzenikiem

};

/**
 * @brief 
 * Wynik algorytmów Kruskala i Prima.
 */
class MSTResult{

    /* POLA */
    private: std::vector<EdgeData> edges;    // zbiór krawędzi drzewa rozpinającego
    private: long long mst;                  // suma krawędzi drzewa rozpinającego

    /* METODY */

    /**
     * @brief 
     * Służy do sprawdzenia czy wynik algorytmu nie jest pusty.
     */
    public: bool isEmpty() { return edges.size() == 0 && mst == 0; }

    /**
     * @brief 
     * Kontruktor. Tworzy pustą strukturę przechowującą wynik algorytmu Prima.
     * 
     * @param prim_array tablica zawierająca stan wierzchołków na koniec algorytmu
     */
    public: MSTResult(DynamicArray<PrimVertex>& prim_array);


    /**
     * @brief 
     * Destruktor. Zwalnia pamięć po wyniku algorytmu Kruskala i Prima.
     */
    public: ~MSTResult() {};


    /**
     * @brief 
     * Wyświetla wynik aglorytmu Prima lub Kruskala.
     */
    public: void print();


    /**
     * @brief 
     * Pobranie mst.
     */
    public: long long getMST() { return mst; }

    /**
     * @brief 
     * Pobranie zbioru krawędzi.
     */
    public: vector<EdgeData> getEdges() { return edges; }

};

