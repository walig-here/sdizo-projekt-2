#include "graphs/Graph.h"
#include "data-structures/Matrix.h"
#include "data-structures/AlgorithmResults.h"

#define NO_CONNECTION -2147483648   // oznaczenie braku połączenia między wierzchołkami

/**
 * @brief 
 * Reprezentuje graf zaimplementowany w formie macierzy sąsiedztwa.
 */
class MatrixGraph : public Graph{

    /* POLA */
    private: Matrix* matrix;   // macierz sąsiedztwa grafu, gdzie wartości elementów oznaczają wagę krawędzi a wartość NO_CONNECTION wskazuje na nieistnienie krawędzi

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
    public: MatrixGraph(unsigned verticies_count, vector<EdgeData> edges_data, bool directed);


    /**
     * @brief 
     * Destruktor. Zwalnia pamięć po grafie.
     */
    public: ~MatrixGraph();


    /**
     * @brief 
     * Wyświetla graf.
     */
    public: virtual void print();


    /**
     * @brief 
     * Zwraca informacje, czy graf jest pusty.
     */
    public: bool isNull() { return matrix->getDegree() == 0; }

    /**
     * @brief
     * Zwraca ilość wierzchołków w grafie.
    */
   public: virtual unsigned verticiesCount() { return matrix->getDegree(); }


    /**
     * @brief 
     * Pobranie macierzy sąsiedztwa grafu
     */
    public: Matrix* getAdjentancyMatrix() { return matrix; }


    /**
     * @brief 
     * Wykonuje algorytm Kruskalla na grafie.
     */
    public: virtual void algorithmKruskal() {};


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
    public: virtual void algorithmBellmanFord() {};

};