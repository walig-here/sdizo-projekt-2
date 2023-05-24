#pragma once
#include "data-structures/DynamicArray.h"
#include <math.h>
#include "graphs/Graph.h"

// Klasa reprezentująca kopiec minimalny o statycznym rozmiarze
class Heap{

    /* POLA */
    private: DynamicArray<VertexData>* elements;        // implementacja kopca w formie tablicy
    private: unsigned current_size;                     // aktualna wielkość kopca

    /* METODY */

    //-----------------------------------------------------------------------
    // Konstruktor. Tworzy kopiec o z góry zdefiniowanej, maksymalnej
    // liczbie elementów.
    //-----------------------------------------------------------------------
    public: Heap(unsigned max_size);


    //-----------------------------------------------------------------------
    // Destruktor. Zwalnia pamięć po kopcu.
    //-----------------------------------------------------------------------
    public: ~Heap();


    //-----------------------------------------------------------------------
    // Dodaje do kopca nowy element. Od razu po dodaniu elementu naprawia
    // kopiec.
    //
    // Parametry:
    // new_element - wartość elementu, który ma zostać dodany do kopca
    //-----------------------------------------------------------------------
    public: void add(VertexData new_element);


    //-----------------------------------------------------------------------
    // Usuwa korzeń kopca. Od razu po usunięciu korzenia naprawia kopiec.
    //
    // Zwraca:
    // Informacje o wyniku operacji. True, gdy się powiodła. False, gdy nie.
    //-----------------------------------------------------------------------
    public: bool pop_root();


    //-----------------------------------------------------------------------
    // Znajduje wierzchołek o zadanym indeksie w kopcu i zwraca jego adres.
    // W przypadku, gdy element o zadanej wartości nie znajduje się w kopcu
    // zwrócony zostaje nullptr.
    //
    // Parametry:
    // vertex - indeks szukanego wierzchołka
    //-----------------------------------------------------------------------
    public: VertexData* find(int vertex);


    //-----------------------------------------------------------------------
    // Dokonuje naprawy całego kopca za pomocą algorytmu Floyda.
    //-----------------------------------------------------------------------
    private: void buildHeapFloyd();


    #define LEFT_CHILD_INDEX(i) (2 * i + 1)
    //-----------------------------------------------------------------------
    // Znajduje lewego potomka elementu o zadanym indeksie. Jeżeli element
    // nie ma lewego potomka zwrócony zostanie nullptr.
    // 
    // Parametry:
    // index - indeks elementu, którego potomka szukamy
    //
    // Zwraca:
    // Adres lewego potomka elementu o indeksie index lub nullptr, gdy lewy
    // potomek nie istnieje.
    //-----------------------------------------------------------------------
    private: VertexData* getLeftChild(unsigned index);

    
    #define RIGHT_CHILD_INDEX(i) (2 * i + 2)  
    //-----------------------------------------------------------------------
    // Znajduje prawego potomka elementu o zadanym indeksie. Jeżeli element
    // nie ma prawego potomka zwrócony zostanie nullptr.
    // 
    // Parametry:
    // index - indeks elementu, którego potomka szukamy
    //
    // Zwraca:
    // Adres prawego potomka elementu o indeksie index lub nullptr, gdy prawy
    // potomek nie istnieje.
    //-----------------------------------------------------------------------
    private: VertexData* getRightChild(unsigned index);


    #define PARENT_INDEX(i) ( floor( (i - 1)/2 ) )
    //-----------------------------------------------------------------------
    // Znajduje rodzica elementu o zadanym indeksie lub nullptr, gdy zadany
    // element jest korzeniem.
    // 
    // Parametry:
    // index - indeks elementu, którego rodzica szukamy
    //
    // Zwraca:
    // Adres rodzica elementu o indeksie index lub nullptr, gdy element jest
    // korzeniem.
    //-----------------------------------------------------------------------
    private: VertexData* getParent(unsigned index) { return elements->operator[](PARENT_INDEX(index)); };


    //-----------------------------------------------------------------------
    // Zwraca tablice z elemetami kopca.
    //
    // Zwraca:
    // Kopie tablicy z elementami kopca.
    //-----------------------------------------------------------------------
    public: DynamicArray<VertexData> getElements() { return elements; }


    //-----------------------------------------------------------------------
    // Wykonuje naprawę kopca w dół zaczynając od elementu o zadanym
    // indeksie.
    //
    // Parametry:
    // node_index - indeks elementu, od którego ma rozpocząć się naprawa
    //-----------------------------------------------------------------------
    private: void repairDownwards(unsigned node_index);


    //-----------------------------------------------------------------------
    // Wykonuje naprawę kopca w górę zaczynając od elementu o zadanym
    // indeksie.
    //
    // Parametry:
    // node_index - indeks elementu, od którego ma rozpocząć się naprawa
    //-----------------------------------------------------------------------
    private: void repairUpwards(unsigned node_index);


    //-----------------------------------------------------------------------
    // Znajduje indeks najmniejszego (co do wagi) potomka elementu o 
    // zadanym indeksie. Jeżeli zadany element jest liściem zwrócona zostanie
    // wartość IS_LEAF.
    // 
    // Parametry:
    // node_index - indeks elementu, którego najmniejsego potomka szukamy
    //
    // Zwraca:
    // Indeks największego potomka elementu o indeksie node_index lub IS_LEAF
    // gdy ten element jest liściem.
    //-----------------------------------------------------------------------
    private: int getMinChildIndex(unsigned node_index);
    #define IS_LEAF -123


    //-----------------------------------------------------------------------
    // Zwraca odniesienie do korzenia kopca. W wypadku, gdy kopiec jest pusty
    // zwrócony zostanie nullptr.
    //
    // Zwraca:
    // Adres elementu, będącego korzeniem kopca lub nullptr, gdy kopiec jest
    // pusty.
    //-----------------------------------------------------------------------
    public: VertexData* root();

};

enum HeapActions{
    EXIT_HEAP,
    EXAMINE_HEAP,
    ADD_HEAP,
    REMOVE_HEAP,
    FIND_HEAP,
    LOAD_HEAP
};