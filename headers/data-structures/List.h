#pragma once
#include <iostream>
#include <vector>

using namespace std;

/* Struktura reprezentująca element listy sąsiadów */
struct ListElement{
    int end;                        // wierzchołek końcowy krawędzi
    int weigth;                     // waga krawędzi
    ListElement* next;              // adres kolejnego elementu
    ListElement* prev;              // adres poprzedniego elementu 

    // Konstruktor elementu listy
    ListElement(ListElement* prev, int end, int weigth, ListElement* next){
        this->end = end;
        this->weigth = weigth;
        this->next = next;
        this->prev = prev;
    }

    // Sprawdzenie równości elementu
    bool isEqual(int end, int weight) { return this->end == end && this->weigth == weight; }

};

/* Klasa list dwukierunkowych będąca listami sąsiadów */
class List{

    /* POLA */

    public: ListElement* head;      // Głowa listy
    public: ListElement* tail;      // Ogon listy


    /* METODY */

    //-----------------------------------------------------------------------
    // Konstruktor. Tworzy pustą listę dwukierunkową.
    //-----------------------------------------------------------------------
    public: List();


    //-----------------------------------------------------------------------
    // Konstruktor kopiujący.
    //-----------------------------------------------------------------------
    public: List(List* &to_copy); 


    //-----------------------------------------------------------------------
    // Destruktor. Zwalnia pamięć po liście dwukierunkowej.
    //-----------------------------------------------------------------------
    public: ~List();


    /**
     * @brief 
     * Zwraca adres elementu listy o zadanym indeksie. Jeżeli taki element nie istnieje, to
     * zostaje zwrócony nullptr.
     * 
     * @param index
     */
    public: ListElement* operator[](unsigned index);


    //-----------------------------------------------------------------------
    // Wyszukuje w liście element o wskazanej wartości i zwraca jego adres.
    // W wypadku nie znalezienia żadnego elementu zwróci nullptr.
    //
    // Parametry:
    // value - wartość, jaką ma mieć wyszukiwany element
    //-----------------------------------------------------------------------
    public: ListElement* find(int end, int weigth);


    //-----------------------------------------------------------------------
    // Pobranie wartości z głowy. W wypadku, gdy lista jest pusta zwrócony
    // zostanie nullptr.
    //-----------------------------------------------------------------------
    public: ListElement* front();


    //-----------------------------------------------------------------------
    // Pobranie wartości z ogona. W wypadku, gdy lista jest pusta zwrócony
    // zostanie nullptr.
    //-----------------------------------------------------------------------
    public: ListElement* back();


    //-----------------------------------------------------------------------
    // Dodaje element na początek listy
    //
    // Parametry:
    // new_element - wartość nowego elementu
    //-----------------------------------------------------------------------
    public: void push_front(int end, int weigth);


    //-----------------------------------------------------------------------
    // Dodaje element na koniec listy.
    //
    // Parametry:
    // new_element - wartość nowego elementu
    //-----------------------------------------------------------------------
    public: void push_back(int end, int weigth);


    //-----------------------------------------------------------------------
    // Usuwa element z początku listy. Zwraca true, gdy usunięcie 
    // przebiegło pomyślnie. W przeciwnym wypadku zwraca false.
    //-----------------------------------------------------------------------
    public: bool pop_front();


    //-----------------------------------------------------------------------
    // Usuwa element z końca listy. Zwraca true, gdy usunięcie 
    // przebiegło pomyślnie. W przeciwnym wypadku zwraca false.
    //-----------------------------------------------------------------------
    public: bool pop_back();


    //-----------------------------------------------------------------------
    // Dodanie elementu na wskazaną pozycję listy. Podanie indeksu równego 
    // lub większego od indeksu ogona poskutkuje dodanie elementu na koniec
    // listy.
    // 
    // Parametry:
    // new_element - wartośc nowego elementu
    // index - indeks na jaki ma dostać dodany nowy element
    //-----------------------------------------------------------------------
    public: void add(int end, int weigth, unsigned index);


    //-----------------------------------------------------------------------
    // Usunięcie elementu o zadanym indeksie z listy. Zwraca false, jeżeli
    // akcja usunięcia zakończyła się niepowodzeniem. W przeciwnym wypadku
    // zwraca true.
    //
    // Parametry:
    // index - indeks elementu, który ma zostać usunięty
    //-----------------------------------------------------------------------
    public: bool remove(unsigned index);

};