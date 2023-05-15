
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
 * Element tablicy obrazującej stan wierzchołka wewnątrz algorytmu Prima lub Dijkstry.
 */
struct VertexData{

    /* POLA */
    bool processed = false;             // stan rozważenia wierzchołka
    int predecessor = NULL_VERTEX;      // wierzchołek poprzedni
    int weight = INFINITY;              // waga krawędzi łączącej wierzchołek z poprzenikiem

};

/**
 * @brief 
 * Ścieżka wyznaczona za pomocą algorytmu Dijkstry lub Bellmana-Forda
 */
class Path{

    /* POLA */
    private: std::vector<unsigned> path;    // ciąg wierzchołków tworzoących ścieżkę
    private: int distance;                  // suma wag krawędzi składających się na ścieżkę

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Tworzy strukturę przechowującą ścieżkę z algorytmu Dijkstry.
     * 
     * @param dijkstra_array tablica zawierająca stan wierzchołków na koniec algorytmu
     * @param end wierzchołek końcowy
     */
    public: Path(DynamicArray<VertexData>& dijkstra_array, unsigned end);


    /**
     * @brief 
     * Destruktor. Zwalnia pamięć po ścieżce z algorytmu Dijkstry.
     */
    public: ~Path() {};


    /**
     * @brief 
     * Wyświetla ścieżkę z aglorytmu Dijkstry lub Bellmana-Forda.
     */
    public: void print();


    /**
     * @brief 
     * Pobiera ciąg wierzchołków tworzących ścieżkę.
     */
    public: vector<unsigned> getVerticies() { return path; }

    
    /**
     * @brief 
     * Pobiera długość ścieżki.
     */
    public: unsigned getDistance() { return distance; }

};


/**
 * @brief 
 * Wynik algorytmów Dijkstry oraz Bellmana-Forda
 */
class PathfindingResult{

    /* POLA */
    private: std::vector<Path> paths;       // zbiór ścieżek wyznaczonych z pomocą algorytmu
    private: unsigned start;                // wierzchołek startowy ścieżki

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Tworzy strukturę przechowującą wynik algorytmu Dijkstry.
     * 
     * @param dijkstra_array tablica zawierająca stan wierzchołków na koniec algorytmu 
     * @param start wierzchołek startowy
     */
    public: PathfindingResult(DynamicArray<VertexData>& dijkstra_array, unsigned start);


    /**
     * @brief 
     * Destruktor. Zwalnia pamięć po wyniku algorytmu Dijkstry lub Bellmana-Forda.
     */
    public: ~PathfindingResult() {};


    /**
     * @brief 
     * Służy do sprawdzenia czy wynik algorytmu nie jest pusty.
     */
    public: bool isEmpty();


    /**
     * @brief 
     * Pobiera ścieżkę do wskazanego wierzchołka.
     * 
     * @param vertex wierzchołek, do którego ścieżkę pobieramy
     */
    public: Path getPathTo(unsigned vertex) { return paths[vertex]; }


    /**
     * @brief 
     * Wyświetla wynik aglorytmu Dijkstry lub Bellmana-Forda.
     */
    public: void print();

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
    public: MSTResult(DynamicArray<VertexData>& prim_array);


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

