#include "data-structures/DynamicArray.h"
#include "graphs/Graph.h"

/** 
 * Inipirowane implementacją zamieszczoną na portalu:
 * https://eduinf.waw.pl/inf/alg/001_search/0141.php
 */

/**
 * @brief 
 * Zbiór rozłączny.
 */
struct DisjointSet{

    /* POLA */
    int representant;   // reprezentant zbioru
    int rank;           // ranga zbioru

    /* METODY */
    
    /**
     * @brief 
     * Konstruktor
     */
    DisjointSet(){
        this->representant = NULL_VERTEX;
        rank = 0;
    }

};


/**
 * @brief 
 * Zbiór zbiorów rozłącznych
 */
class DisjointSets{

    /* POLA */
    private: DisjointSet* sets;
    private: int size;

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Tworzy zbiór zbiorów rozłącznych o zadanej wielkości.
     */
    public: DisjointSets(int amount_of_sets);


    /**
     * @brief 
     * Destruktor.
     */
    public: ~DisjointSets();


    /**
     * @brief 
     * Zwraca reprezentanta zbioru, do którego należy zadany wierzchołek.
     * 
     * @param vertex wierzchołek, którego reprezentanta szukamy
     */
    public: int getSet(int vertex);


    /**
     * @brief 
     * Łączenie zbiorów o zadanych reprezentantach
     * 
     * @param representant_1 reprezenant pierwszego zbioru
     * @param representant_2 reprezenant drugiego zbioru
     */
    public: void unionSets(int representant_1, int representant_2);

};