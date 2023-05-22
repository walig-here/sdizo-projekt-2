#include "app/utility/SortingMachine.h"


void SortingMachine::sort(DynamicArray<EdgeData>& edges, unsigned left, unsigned right){

    // Wyznaczam punkt podziału. Jeżeli nie jest już to możliwe, to kończę sortowanie
    int divsion_point = quickSortPartition(edges, left, right);
    if(divsion_point == -1) 
        return;

    // Sortowanie wyznaczonych podtablic
    sort(edges, left, divsion_point);
    sort(edges, divsion_point+1, right);

}

int SortingMachine::quickSortPartition(DynamicArray<EdgeData>& array, unsigned left, unsigned right){

    // Jeżeli relacja między granicami przedziału tablicy, który ma być podzielony jest niepoprawna, to 
    // podział nie będzie dokonany.
    if(right < left) return -1;

    // Jeżeli tablica jest mniej niż 2-elementowa, to zwaracam wartość -1. Nie ma czego dzielic.
    if(right - left + 1 < 2) return -1;

    // Sprawdzam poprawność parametrów left i right (czy są to poprawne indkesy tablicy)
    if(left >= array.getLength() || right >= array.getLength()){
        left = 0;
        right = array.getLength()-1;
    }

    // Ustalam piwot oraz pozycje dwóch zmiennych sortujących
    int pivot = array[left]->weigth;
    int left_pointer = left;
    int right_pointer = right;

    // Za pomocą zmiennych sortujących wszystkie elementy tablice mniejsze od piwota przenoszę na prawo, a
    // większe lub równe na prawo. Jeżeli po lewej stronie znajdziemy wartość >= i jednocześniej po prawej
    // znajdziemy wartość < od piwota, to zamieniamy je miejscami. Jeżeli któraś z tych wartości nie zostanie
    // znaleziona, to na pozycji prawej zmiennej sortującej wyznaczony zostaje punkt podziału tablicy.
    while (true){
        while( left_pointer < right && array[left_pointer]->weigth < pivot) left_pointer++;
        while( right_pointer > left && array[right_pointer]->weigth >= pivot) right_pointer--;

        if(left_pointer >= right_pointer) return right_pointer;

        array.swap(left_pointer, right_pointer);
        left_pointer++;
        right_pointer--;

    }
    
    return -1;

}