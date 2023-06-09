#pragma once
#include "graphs/Graph.h"
#include "data-structures/List.h"
#include "data-structures/AlgorithmResults.h"

/**
 * @brief 
 * Reprezentuje graf zaimplementowany w formie listy sąsiadów.
 */
class ListGraph : public Graph{

    /* POLA */
    private: List* adjentency_lists;        // zbiór list sąsiadów kolejnych wierzchołów
    private: unsigned verticies_count;      // liczba wierzchołków

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Tworzy graf na podstawie danych wczytanych z pliku. W wypadku zadania
     * ilości wierzchołków równej 0, zostanie stworzony graf pusty, który nie zawiera
     * żadnych wierzchołów oraz krawędzi.
     * 
     * @param verticies_count liczba wierzchołków
     * @param edges_data wektor zawierający dane nt poszczególnych krawedzi
     * @param directed określa czy graf jest skierowany
     */
    public: ListGraph(unsigned verticies_count, vector<EdgeData> edges_data, bool directed);


    /**
     * @brief 
     * Destruktor. Zwalnia pamięć po grafie.
     */
    public: ~ListGraph();


    /**
     * @brief 
     * Zwraca informacje, czy graf jest pusty.
     */
    public: virtual bool isNull() { return adjentency_lists == nullptr; }


    /**
     * @brief 
     * Zwraca listę krawędzi grafu.
     * 
     * @param directional wskazuje czy krawędzie są skierowane
     */
    public: DynamicArray<EdgeData> getEdgesList(bool directional);


    /**
     * @brief 
     * Wyświetla graf.
     */
    public: virtual void print();


    /**
     * @brief 
     * Pobiera listę sąsiadów wierzchołka o wskazanym indeksie. Jeżeli taki wierzchołek nie
     * istnieje lub nie ma sąsiadów, to zostanie zwrócony nullptr.
     * 
     * @param vertex_index indeks wierzchołka
     */
    public: List* getAdjetencyList(unsigned vertex_index);


    /**
     * @brief
     * Zwraca ilość wierzchołków w grafie.
    */
   public: virtual unsigned verticiesCount() { return verticies_count; }


    /**
     * @brief 
     * Wykonuje algorytm Kruskalla na grafie.
     * 
     * @return Wynik alfgorytmu Kruskala w formie zbioru krawędzi oraz sumy wag krawędzi.
     * Wypadku, gdy algorytm zostanie wykonany na grafie pustym, to zwrócony zostanie pusty wynik.
     */
    public: virtual MSTResult algorithmKruskal();


    /**
     * @brief 
     * Wykonuje algorytm Prima na grafie.
     */
    public: virtual MSTResult alogrithmPrim(unsigned start);


    /**
     * @brief 
     * Wykonuje algorytm Dijkstry na grafie.
     */
    public: virtual PathfindingResult algorithmDijkstra(unsigned start);


    /**
     * @brief 
     * Wynokuje algorytm Bellmana-Forda na grafie.
     */
    public: virtual PathfindingResult algorithmBellmanFord(unsigned start);


    /**
     * @brief 
     * Zwraca prawdę, jeżeli w grafie znajduje się waga o ujemnej krawędzi.
     */
    public: virtual bool containNegativeEdges();


};