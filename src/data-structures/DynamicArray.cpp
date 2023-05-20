#include "data-structures/DynamicArray.h"
#include "app/utility/FileReader.h"
#include "data-structures/AlgorithmResults.h"

#include <cstring>
#include <iostream>

using namespace std;

class EdgeData;

template class DynamicArray<int>;
template class DynamicArray<VertexData>;
template class DynamicArray<EdgeData>;

template<typename T> DynamicArray<T>::DynamicArray(){

    array_address = nullptr;
    length = 0;

}

template<typename T> DynamicArray<T>::DynamicArray(unsigned length, T fill) {

    this->length = length;
    array_address = new T[length];
    for(int i = 0; i < length; i++) array_address[i] = fill;

}

template<typename T> DynamicArray<T>::DynamicArray(DynamicArray *array) : DynamicArray() {

    if(array == nullptr || array->length == 0) return;

    length = array->length;
    array_address = new T[length];
    for(int i = 0; i < array->length; i++)
        array_address[i] = array->array_address[i];

}

template<typename T> DynamicArray<T>::DynamicArray(vector<T> elements) : DynamicArray() {

    // Wczytujemy dane 
    if(elements.size() == 0) return;

    length = elements.size();
    array_address = new T[length];

    for(int i = 0; i < length; i++)
        array_address[i] = elements[i];

}

template<typename T> DynamicArray<T>::~DynamicArray(){

    // Zwolnienie obaszaru pamięci zajmowanego przez tablice
    if(array_address == nullptr) return;
    delete[] array_address;
    array_address = nullptr;

}

template<typename T> void DynamicArray<T>::swap(unsigned index_1, unsigned index_2){

    // Sprawdzam poprawność zadanych indeksów
    if(index_1 >= length) return;  
    if(index_2 >= length) return;    

    // Zamieniam miejscami wskazane elementy
    T temp = array_address[index_1];
    array_address[index_1] = array_address[index_2];
    array_address[index_2] = temp;

}

template<typename T> void DynamicArray<T>::add(T new_element, unsigned index){

    // Jeżeli indeks to 0, to dodajemy na początek
    if(index == 0) return push_front(new_element);

    // Jeżeli indeks nie mieści się w tablicy to dodajemy na koniec
    if(index >= length) return push_back(new_element);

    // Relokacja tablicę i przesuwam wszystkie elementy na pozycjach większych niz index o 1 pozycję
    T* new_address = new T[++length];
    new_address[index] = new_element;

    for(int i = 0; i < length-1; i++)
        new_address[( i >= index ? i+1 : i)] = array_address[i]; 
    
    // Zwalniam poprzednią lokalizację i ustalam nowy adres
    delete[] array_address;
    array_address = new_address;

}

template<typename T> void DynamicArray<T>::push_front(T new_element){

    // Relokuję tablicę i przesuwam dotyczas istniejące elementy o jedną pozycję w prawo
    T* new_address = new T[++length];
    new_address[0] = new_element;
    for(int i = 1; i < length; i++)
        new_address[i] = array_address[i-1];

    // Zwalniam poprzednią lokalizację tablicy i ustalam nową wartość adresu
    delete[] array_address;
    array_address = new_address;

}

template<typename T> void DynamicArray<T>::push_back(T new_element){

    // Relokuję tablicę i kopiuję dotychczas istniejące elementy
    // Na koniec tablicy dodaję nowy element
    T* new_address = new T[++length];
    for(int i = 0; i < length-1; i++)
        new_address[i] = array_address[i];
    new_address[length-1] = new_element;

    // Zwalniam poprzednią lokalizację tablicy i ustalam nową wartość adresu
    delete[] array_address;
    array_address = new_address;

}

template<typename T> void DynamicArray<T>::remove(unsigned index){

    // Jeżeli indeks 0, to usuwamy z początku
    if(index == 0) return pop_front();

    // Jeżeli wskazano ostatni element to pop_back()
    if(index == length-1) return pop_back();

    // Jeżeli wskazano indeks większy od maksymalnego, to nie usuwamy
    if(index >= length) return;

    // Relokuję tablicę i kopiuje dotychczas istniejące elementy poza tym usuniętym
    // Wszystkie elementy zajdujące się za usuniętym elementem są przesunięte o 1 pozycję w lewo
    T* new_address = new T[--length];
    for(int i = 0; i < length; i++)
        new_address[i] = array_address[ ( i >= index ? i+1 : i ) ]; 
    
    // Zwalniam poprzednią lokalizację tablicy i ustalam nową wartość adresu
    delete[] array_address;
    array_address = new_address;

    // Jeżeli tablica po wykonaniu usunięcia jest pusta to ustawiam jej adres na nullptr
    if(length == 0) array_address = nullptr;

}

template<typename T> void DynamicArray<T>::pop_front(){

    // Z pustej tablicy nie usuwam
    if(length == 0) return;

    // Relokuję tablicę i kopiuje wszystkie dotchczas istniejące elementy poza pierwszym
    // Każdy element jest przesunięty o 1 pozycję w lewo
    T* new_address = new T[--length];
    for(int i = 0; i < length; i++)
        new_address[i] = array_address[i+1];
    
    // Zwalniam poprzednią lokalizację tablicy i ustalam nową wartość adresu
    delete[] array_address;
    array_address = new_address;

    // Jeżeli tablica po wykonaniu usunięcia jest pusta to ustawiam jej adres na nullptr
    if(length == 0) array_address = nullptr;

}

template<> void DynamicArray<int>::print(){

    printf("Zawartosc tablicy:\n");
    if(length == 0) {
        printf("pusta\n");
        return;
    }

    for(int i = 0; i < length; i++) 
        cout << array_address[i] << ", ";
    printf("\n");

}

template<typename T> void DynamicArray<T>::pop_back(){

    // Z pustej tablicy nie usuwam
    if(length == 0) return;

    // Relokuję tablicę i kopiuje wszystkie dotchczas istniejące elementy poza ostatnim
    T* new_address = new T[--length];
    for(int i = 0; i < length; i++)
        new_address[i] = array_address[i];
    
    // Zwalniam poprzednią lokalizację tablicy i ustalam nową wartość adresu
    delete[] array_address;
    array_address = new_address;

    // Jeżeli tablica po wykonaniu usunięcia jest pusta to ustawiam jej adres na nullptr
    if(length == 0) array_address = nullptr;

}

template<> int* DynamicArray<int>::find(int value){

    for(int i = 0; i < length; i++)
        if(array_address[i] == value) return array_address+i;
    return nullptr;

}

template<typename T> T* DynamicArray<T>::operator[](unsigned index){

    if(this == nullptr) return nullptr;
    if(index >= length) return nullptr;
    return &(array_address[index]);

}

template<> int DynamicArray<VertexData>::min(){

    // Z pustej tablicy nie da się wyznaczyć minimum
    if(array_address == nullptr) return -1;

    // Znajdujemy pierwszy nierozważony wierzchołek
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to zwrócony zostanie nullptr, tablica nie ma minimum
    int index = 0;
    int minimum_index = -1;
    for(; index < getLength(); index++){
        if(array_address[index].processed) continue;

        minimum_index = index;
        break;
    }
    if(minimum_index == -1) return minimum_index;

    // Porównując go resztą nierozważonych wierzchołków wybieramy minimum
    index++;
    for(; index < getLength(); index++){
        if(array_address[index].processed) continue;
        if(array_address[minimum_index].weight <= array_address[index].weight) continue;

        minimum_index = index;
    }
    return minimum_index;

}