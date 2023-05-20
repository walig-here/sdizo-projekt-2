#pragma once
#include "data-structures/DynamicArray.h"

class MSTResult;
class PathfindingResult;


#define NO_CONNECTION -2147483648   // oznaczenie braku połączenia między wierzchołkami

/**
 * @brief 
 * Struktura zawierająca dane na temat pojedynczej krawedzi
 */
struct EdgeData{

    /* POLA */
    unsigned begin = -1;                // wierzchołek początkowy
    unsigned end = -1;                  // wierzchołek końcowy
    int weigth = NO_CONNECTION;         // waga krawędzi

    /* KONSTRUKTOR */
    EdgeData(unsigned begin, unsigned end, int weigth);

    /* KONSTRUKTOR DOMYŚLNY */
    EdgeData(){
        begin = end = -1;
        weigth = NO_CONNECTION;
    }

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
     */
    public: virtual void algorithmKruskal() = 0;


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

};