#pragma once
#include "app/utility/RandomNumberGenerator.h"
#include "graphs/ListGraph.h"
#include "graphs/MatrixGraph.h"

/**
 * @brief 
 * Typy reprezentacji grafów możliwych do wygenerowania
 */
enum GraphRepresentations{
    MATRIX,
    LIST
};

/**
 * @brief 
 * Klasa do generowania losowych grafów.
 */
class GraphGenerator{

    /**
     * @brief 
     * Zwraca losowy graf. Jeżeli gęstość wyniesie mniej niz 0, to zostanie ustalona na 0.
     * Jeżeli przekroczy 1, to zostanie ustalona na 1. W wypadku ustawienia size mniejszego niż 0
     * ten parametr zostanie ustalony na 0.
     * 
     * @param representation reprezentacja, w jakiej ma być zapisany graf
     * @param size wielkość grafu, liczba wierzchołków
     * @param directed czy graf jest skierowany?
     * @param density gęstość wygenerowanego grafu z zakresu od 0 do 1
     */
    public: static Graph* generateGraph(GraphRepresentations representation, int size, bool directed, float density);


    /**
     * @brief 
     * Losuje zbiór krawędzi o zadanej wielkości, łączących zadaną ilość wierzchołków. Wylosowane krawędzie
     * są unikalne.
     * 
     * @param verticies liczba wierzchołków
     * @param edges_count liczba krawędzi
     * @param directed czy krawędzie mogą być skierowane
     */
    private: static vector<EdgeData> getRandomEdges(int verticies, long long edges_count, bool directed);


    /**
     * @brief 
     * Zwraca prawdę, gdy krawędź zawierająca dane wierzchołki nie znajduje się w zadanym zbiorze.
     * 
     * @param edges_set przeszukiwany zbiór krawędzi
     * @param start początek krawędzi
     * @param end koniec krawędzi
     * @param directed czy krawędź jest skierowana
     */
    private: static bool edgeExistIn(vector<EdgeData> edges_set, int start, int end, bool directed);

};