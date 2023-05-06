#include "graphs/Graph.h"
#include "data-structures/List.h"

/**
 * @brief 
 * Reprezentuje graf zaimplementowany w formie listy sąsiadów.
 */
class ListGraph{

    /* POLA */
    private: List* adjentency_lists;      // zbiór list sąsiadów kolejnych wierzchołów

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Tworzy graf na podstawie danych wczytanych z pliku. W wypadku zadania
     * ilości wierzchołków równej 0, zostanie stworzony graf pusty, który nie zawiera
     * żadnych wierzchołów oraz krawędzi.
     * 
     * @param verticies_count liczba wierzchołków
     * @param edges_data wektor zawierający dane nt poszczególnych krawedzi
     */
    public: ListGraph(unsigned verticies_count, vector<EdgeData> edges_data);


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
     * Wykonuje algorytm Kruskalla na grafie.
     */
    public: virtual void algorithmKruskal() {};


    /**
     * @brief 
     * Wykonuje algorytm Prima na grafie.
     */
    public: virtual void alogrithmPrim() {};


    /**
     * @brief 
     * Wykonuje algorytm Dijkstry na grafie.
     */
    public: virtual void algorithmDijkstra() {};


    /**
     * @brief 
     * Wynokuje algorytm Bellmana-Forda na grafie.
     */
    public: virtual void algorithmBellmanFord() {};


};