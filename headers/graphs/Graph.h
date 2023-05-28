#pragma once
#include "data-structures/DynamicArray.h"

class MSTResult;
class PathfindingResult;

#define NO_CONNECTION -2147483648           // oznaczenie braku połączenia między wierzchołkami
#define INFINITY_W 2147483647               // waga krawędzi równa nieskończoność
#define NULL_VERTEX -2147483648             // oznacza wierchołek NULL


/**
 * @brief 
 * Element tablicy obrazującej stan wierzchołka wewnątrz zaimplementowanych algorytmów.
 */
struct VertexData{

    /* POLA */
    int vertex;           // indeks wierzchołka reprezentowanego przez strukturę
    int weight;           // waga przypisana do wierzchołka             
    int predecessor;      // indeks wierzchołka poprzedzającego  

    /**
     * @brief 
     * Konstruktor.
     */
    VertexData(int vertex = NULL_VERTEX, int weight = INFINITY_W, int predecessor = NULL_VERTEX){
        this->vertex = vertex;
        this->weight = weight;
        this->predecessor = predecessor;
    }

};


/**
 * @brief 
 * Struktura zawierająca dane na temat pojedynczej krawedzi
 */
struct EdgeData{

    /* POLA */
    unsigned begin;     // wierzchołek początkowy
    unsigned end;       // wierzchołek końcowy
    int weigth;         // waga krawędzi

    /* KONSTRUKTOR */
    EdgeData(unsigned begin=NULL_VERTEX, unsigned end=NULL_VERTEX, int weigth=INFINITY_W);

};

/**
 * @brief 
 * Klasa reprezentująca graf o nieokreślonej reprezentacji.
 */
class Graph{

    /**
     * Wirtualny konstruktor domyślny.
     */
    protected: Graph() {};


    /**
     * Destruktor. 
     */
    public: ~Graph() {};

    /**
     * @brief 
     * Zwraca listę krawędzi grafu.
     * 
     * @param directional wskazuje czy krawędzie są skierowane
     */
    public: virtual DynamicArray<EdgeData> getEdgesList(bool directional) = 0;


    /**
     * @brief 
     * Zwraca informacje, czy graf jest pusty.
     */
    public: virtual bool isNull() = 0;

    /**
     * @brief 
     * Wyświetla graf.
     */
    public: virtual void print() = 0;

    /**
     * @brief
     * Zwraca ilość wierzchołków w grafie.
    */
   public: virtual unsigned verticiesCount() = 0;


    /**
     * @brief 
     * Wykonuje algorytm Kruskalla na grafie.
     * 
     * @return Wynik alfgorytmu Kruskala w formie zbioru krawędzi oraz sumy wag krawędzi.
     * Wypadku, gdy algorytm zostanie wykonany na grafie pustym, to zwrócony zostanie pusty wynik.
     */
    public: virtual MSTResult algorithmKruskal() = 0;


    /**
     * @brief 
     * Wykonuje algorytm Prima na grafie.
     * 
     * @param start wierzchołek startowy
     * 
     * @return Wynik alfgorytmu Prima w formie zbioru krawędzi oraz sumy wag krawędzi.
     * Wypadku, gdy algorytm zostanie wykonany na grafie pustym, to zwrócony zostanie pusty wynik.
     */
    public: virtual MSTResult alogrithmPrim(unsigned start) = 0;


    /**
     * @brief 
     * Wykonuje algorytm Dijkstry na grafie.
     */
    public: virtual PathfindingResult algorithmDijkstra(unsigned start) = 0;


    /**
     * @brief 
     * Wynokuje algorytm Bellmana-Forda na grafie.
     */
    public: virtual PathfindingResult algorithmBellmanFord(unsigned start) = 0;


    /**
     * @brief 
     * Zwraca prawdę, jeżeli w grafie znajduje się waga o ujemnej krawędzi.
     */
    public: virtual bool containNegativeEdges() = 0;

};