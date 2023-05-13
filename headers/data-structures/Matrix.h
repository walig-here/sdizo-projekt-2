#include "data-structures/DynamicArray.h"

/**
 * @brief 
 * Klasa reprezentująca statyczną (stały rozmiar) macierz kwadratową przechowywującą liczby typu int.
 */
class Matrix{

    /* POLA */
    private: DynamicArray<int>* elements;       // tablica przechowująca elementy macierzy
    private: unsigned degree;                   // stopień macierzy

    /* METODY */

    /**
     * @brief 
     * Konstruktor macierzy kwadratowej, wypełnionej zadaną wartością. W wypadku
     * podania stopnia macierzy równego 0, stworzona zostanie macierz pusta 0x0.
     * 
     * @param degree stopień macierzy
     * @param fill wartość, jaką ma zostać wypełniona macierz
     */
    public: Matrix(unsigned degree, int fill = 0);


    /**
     * @brief
     * Destruktor.
     */
    public: ~Matrix();


    /**
     * @brief 
     * Zwraca wartośc stopnia macierzy.
     */
    public: unsigned getDegree() { return degree; }


    /**
     * @brief 
     * Pozwala na dostęp do elementu macierzy o zadanym indeksie.
     * 
     * @param row wiersz
     * @param column kolumna
     * 
     * @return Adres wskazanego elementu lub nullptr w wypadku, gdy
     * element o wskazanym indeksie nie istnieje.
     */
    public: int* get(unsigned row, unsigned column);

};