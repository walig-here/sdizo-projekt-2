#include <iostream>
#include "data-structures/List.h"


using namespace std;

List::List(){

    head = nullptr;
    tail = nullptr;

}

List::List(List* &source) : List(){

    // Wykonujemy kopię wszystkich elementów
    ListElement* source_element = source->head;
    while(source_element != nullptr){
        this->push_back(source_element->end, source_element->weigth);
        source_element = source_element->next;
    }

}

List::~List(){

    // Zwalniamy kolejne elementy zaczynając od głowy
    while(pop_front());

}

ListElement* List::front(){

    return head;

}

ListElement* List::back(){

    return tail;

}

ListElement* List::operator[](unsigned index){

    // Jeżeli indeks jest równy 0, to zwracamy głowę
    if(index == 0) return front();

    // Przeszukujemy listę zaczynając od elementu za głową
    // Kończymy przeszukiwanie, gdy odnajdziemy element o danym indeksie, lub znajdziemy się poza listą
    ListElement* element = head->next;
    for(int i = 1; i != index && element != nullptr; i++)
        element = element->next;
    return element;

}

ListElement* List::find(int end, int weigth){

    // Sprawdzamy, czy nie jest to wartość zapisana w ogonie
    if(tail != nullptr && tail->isEqual(end, weigth)) return tail;

    // Przeszukujemy listę w poszukiwaniu elementu o wskazanej wartości
    // W wypadku, gdy taka w liście nie wystąpi, zwórcony zostanie nullptr
    ListElement* found_element = head;
    while (found_element != nullptr && !found_element->isEqual(end, weigth))
        found_element = found_element->next;
    return found_element;

}

void List::add(int end, int weigth, unsigned new_element_index){

    // Jeżeli dodajemy na początek to lepiej jest użyć metody push_front
    if(new_element_index == 0) return push_front(end, weigth);


    // Szukamy elementów, które będą sąsiadami nowego elementu, aby "umieścić" między nimi nowy element
    ListElement* prev_element = head;           // sąsiad "z lewej"
    ListElement* next_element = nullptr;        // sąsiad "z prawej"
    for(int i = 0; prev_element != nullptr; i++){

        if(i == new_element_index-1) {
            next_element = prev_element->next;        
            break;
        }
        prev_element = prev_element->next;

    }

    // Jeżeli sąsiad z prawej jest null to de facto dodajemy na koniec kolejki
    // Tyczy się to także sytuacji gdy wprowadzono indeks większy od indeksu ogona
    if(next_element == nullptr) return push_back(end, weigth);

    // Umieszamy nowy element między znalezionymi sąsiadami
    ListElement* new_element = new ListElement(prev_element, end, weigth, next_element);
    prev_element->next = new_element;
    next_element->prev = new_element;

}

void List::push_front(int end, int weigth){

    ListElement* new_element = new ListElement(nullptr, end, weigth, head);
    if(head != nullptr) head->prev = new_element;
    head = new_element;

    // Sprawdzam, czy dodany element nie jest jednocześnie ogonem
    if(head->next == nullptr) tail = head;

}

void List::push_back(int end, int weigth){

    ListElement* new_element = new ListElement(tail, end, weigth, nullptr);
    if(tail != nullptr) tail->next = new_element;
    tail = new_element;

    // Sprawdzam, czy dodany element nie jest jednocześnie głową
    if(tail->prev == nullptr) head = tail;

}

bool List::pop_front(){

    // Gdy lista jest pusta, to nie ma czego usuwać
    if(head == nullptr) return false;

    // Jeżeli głowa była jednymy elementem, to musimy "wyzerować" także ogon
    // W przeciwnym wypadku należy przepiąć wskaźnik elementu "za" głową
    if(head->next == nullptr) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
    return true;

}

bool List::pop_back(){

    // Gdy lista jest pusta to nie ma czego usuwać
    if(tail == nullptr) return false;

    // Jeżeli ogon był jedynym elementem to musimy "wyzerować" także głowę
    // W przeciwnym wypadku należy przepiąć wskaźnik elementu "przed" ogonem
    if(tail->prev == nullptr){
        delete tail;
        tail = nullptr;
        head = nullptr;
    }
    else{
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
    return true;

}

bool List::remove(unsigned wanted_index){

    if(head == nullptr) return false;

    // Jeżeli usuwamy z pierwszej pozycji, to lepiej jest użyć pop_front()
    if(wanted_index == 0) return pop_front();

    // Szukamy sądiadów z lewej i prawej elementu, który usuwamy
    // Następnie przepinamy ich wskaźniki i usuwamy element
    // Sprawdzam także, czy element nie jest ogonem, bo wtedy lepiej jest użyć metody pop_back()
    ListElement* element = head->next;
    for(int index = 1; element != nullptr; index++){
        
        if(wanted_index == index){
            if(element == tail) return pop_back();
            element->prev->next = element->next;
            element->next->prev = element->prev;
            delete element;
            return true;
        }
        element = element->next;

    }  

    // Element nie istnieje
    return false;

}

unsigned List::size(){

    unsigned length = 0;
    for(; this->operator[](length) != nullptr; length++);
    return length;

}