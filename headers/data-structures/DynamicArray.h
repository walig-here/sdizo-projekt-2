#pragma once
#include <iostream>
#include <vector>

using namespace std;

/* Klasa przedstawiająca tablicę dynamiczną */
template <typename T> class DynamicArray{    

    /* POLA */
    private: T* array_address;        // adres pierwszej komórki w tablicy
    private: unsigned length;           // aktualna długość tablicy

    /* MEOTDY */

    //-----------------------------------------------------------------------
    // Konstruktor. Tworzy pustą tablicę dynamiczną.
    //-----------------------------------------------------------------------
    public: DynamicArray();

    
    //-----------------------------------------------------------------------
    // Konstruktor. Tworzy tablicę dynamiczną o zadanym rozmairze wypełnioną
    // elemtami o zadanej wartości.
    //-----------------------------------------------------------------------
    public: DynamicArray(unsigned length, T fill);


    //-----------------------------------------------------------------------
    // Konstruktor kopiujący.
    //-----------------------------------------------------------------------
    public: DynamicArray(DynamicArray* array);

    //-----------------------------------------------------------------------
    // Konstruktor tworzący tablice na podstawie zadanego ciągu liczb.
    //
    // Parametry:
    // elements - ciąg liczb, z którego ma zostać zbudowana tablica
    //-----------------------------------------------------------------------
    public: DynamicArray(vector<T> elements);


    //-----------------------------------------------------------------------
    // Destruktor. Zwalnia pamięć po tablicy dynamicznej.
    //-----------------------------------------------------------------------
    public: ~DynamicArray();


    //-----------------------------------------------------------------------
    // Dodaje nowy element na wskazane miejsce w tablicy.
    // 
    // Parametry:
    // new_element - nowa wartość, która ma zostać dodana do tablicy
    // index - pozycja w tablicy, na którą ma zostać dodany nowy element  
    //-----------------------------------------------------------------------
    public: void add(T new_element, unsigned index);


    //-----------------------------------------------------------------------
    // Dodaje element na początek tablicy.
    //
    // Parametry:
    // new_element - wartość dodawanego do tablicy elementu
    //-----------------------------------------------------------------------
    public: void push_front(T new_element);


    //-----------------------------------------------------------------------
    // Dodaje element na koniec tablicy.
    //
    // Parametry:
    // new_element - wartość dodawanego do tablicy elementu
    //-----------------------------------------------------------------------
    public: void push_back(T new_element);


    //-----------------------------------------------------------------------
    // Usunięcie elementu o podanym indeksie.
    //
    // Parametry:
    // index - pozycja elementu tablicy, który ma zostać usunięty
    //-----------------------------------------------------------------------
    public: void remove(unsigned index);


    //-----------------------------------------------------------------------
    // Usuwa element z początku tablicy.
    //-----------------------------------------------------------------------
    public: void pop_front();


    //-----------------------------------------------------------------------
    // Usuwa element z końca tablicy.
    //-----------------------------------------------------------------------
    public: void pop_back();


    //-----------------------------------------------------------------------
    // Wyświetla zawartość tablicy.
    //-----------------------------------------------------------------------
    public: void print();


    //-----------------------------------------------------------------------
    // Wyszukuje w tablicy wskazaną wartość. W wypadku, gdy taka wartośc nie
    // występuje w tablicy, zwróci nullptr.
    //
    // Parametry:
    // value - wartość, która ma zostać odnaleziona
    //-----------------------------------------------------------------------
    public: T* find(T value);


    //-----------------------------------------------------------------------
    // Zwraca długośc tablicy.
    //-----------------------------------------------------------------------
    public: unsigned getLength() { return length; }


    //-----------------------------------------------------------------------
    // Zwraca adres elementu o zadanym indeksie.
    //-----------------------------------------------------------------------
    public: T* operator[](unsigned index);


    //-----------------------------------------------------------------------
    // Zamienia miejscami elementy o wskazanych indeksach.
    //-----------------------------------------------------------------------
    public: void swap(unsigned index_1, unsigned index_2);


    /**
     * @brief 
     * Zwraca indeks elementu minimalnego z tablicy.
     * 
     * @return Indeks minimalnego elementu.
     */
    public: int min();

};