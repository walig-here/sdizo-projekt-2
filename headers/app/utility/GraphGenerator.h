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
     * @param not_negative czy graf może zawierać wyłącznie krawędzie o nieujmenych wagach?
     */
    public: static Graph* generateGraph(GraphRepresentations representation, int size, bool directed, float density, bool not_negative);


    /**
     * @brief 
     * Losuje zbiór krawędzi o zadanej wielkości, łączących zadaną ilość wierzchołków. Wylosowane krawędzie
     * są unikalne.
     * 
     * @param verticies liczba wierzchołków
     * @param edges_count docelowa liczba krawędzi
     * @param max_egdes_count maksymalna liczba krawędzi
     * @param directed czy krawędzie mogą być skierowane
     * @param not_negative czy krawędzie mogą mieć wyłącznie nieujemne wagi?
     */
    private: static vector<EdgeData> getRandomEdges(int verticies, long long edges_count, long long max_egdes_count, bool directed, bool not_negative);


    /**
     * @brief 
     * Zwraca wszystkie możliwe kombinacje krawędzi w grafie o zadanej liczbie wierzchołków.
     * 
     * @param vertitices ilość wierzchołków
     * @param directed czy wierzchołki mają być skierowane
     * @param not_negative czy krawędzie mogą mieć wyłącznie nieujemne wagi?
     */
    private: static vector<EdgeData> getAllPossibleEdges(int verticies, bool directed, int max_egde_count, bool not_negative);

};