#include "graphs/Graph.h"
#include "data-structures/Matrix.h"

#define NO_CONNECTION -2147483648   // oznaczenie braku połączenia między wierzchołkami

/**
 * @brief 
 * Reprezentuje graf zaimplementowany w formie macierzy sąsiedztwa.
 */
class MatrixGraph : public Graph{

    /* POLA */
    private: Matrix* adjacency_matrix;   // macierz sąsiedztwa grafu, gdzie wartości elementów oznaczają wagę krawędzi a wartość NO_CONNECTION wskazuje na nieistnienie krawędzi

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Tworzy graf na podstawie danych wczytanych z pliku.
     * 
     * @param verticies_count liczba wierzchołków
     * @param edges_data wektor zawierający dane nt poszczególnych krawedzi
     */
    public: MatrixGraph(unsigned verticies_count, vector<EdgeData> edges_data);


    /**
     * @brief 
     * Destruktor. Zwalnia pamięć po grafie.
     */
    public: ~MatrixGraph();


    /**
     * @brief 
     * Pobranie macierzy sąsiedztwa grafu
     */
    public: Matrix* getAdjentancyMatrix() { return adjacency_matrix; }


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