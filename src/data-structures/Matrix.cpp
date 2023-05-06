#include "data-structures/Matrix.h"

Matrix::Matrix(unsigned degree, int fill){

    // Jeżeli podano zerowy stopień, to toworzona jest macierz pusta
    // W przeciwnym wypadku tworzona jest macierz zadanego stopnia
    this->degree = degree;
    if( degree == 0 ) {
        elements = nullptr;
        return;
    }

    // Wypełniamy macierz zerami w ilości degree^2
    elements = new DynamicArray(this->degree*this->degree, fill);

}

int* Matrix::get(unsigned row, unsigned column){
    
    // Sprawdzam czy nie zadano niepoprawnego idneksu kolumny lub wiersza
    if(row >= degree || column >= degree) 
        return nullptr;

    // Ustalam indeks elementu wewnątrz tablicy elements i zwracam element
    return (*elements)[row * degree + column];

}

Matrix::~Matrix(){

    delete elements;

}