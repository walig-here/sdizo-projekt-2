#include "data-structures/Matrix.h"

Matrix::Matrix(unsigned degree, int fill){

    // Jeżeli podano zerowy stopień, to toworzona jest macierz stopnia 1
    if( degree == 0 ) this->degree = 1;
    else this->degree = degree;

    // Wypełniamy macierz zerami w ilości degree^2
    elements = new DynamicArray(this->degree*this->degree, fill);

}

int* Matrix::get(unsigned row, unsigned column){
    
    // Ustalam indeks elementu wewnątrz tablicy elements i zwracam element
    return (*elements)[row * degree + column];

}

Matrix::~Matrix(){

    delete elements;

}