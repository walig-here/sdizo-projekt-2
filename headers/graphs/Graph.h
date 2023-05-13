#pragma once

class MSTResult;

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
    public: virtual void algorithmDijkstra() = 0;


    /**
     * @brief 
     * Wynokuje algorytm Bellmana-Forda na grafie.
     */
    public: virtual void algorithmBellmanFord() = 0;

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
    EdgeData(unsigned begin, unsigned end, int weigth);

};