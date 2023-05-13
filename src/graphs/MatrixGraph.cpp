#include "graphs/MatrixGraph.h"

MatrixGraph::MatrixGraph(unsigned verticies_count, vector<EdgeData> edges_data, bool directed){

    // Inicjalizacja macierzy - domyślnie graf nie zawiera żadnych krawędzi
    matrix = new Matrix(verticies_count, NO_CONNECTION);

    // Na podstawie danych wczytuje z pliku uzupełniam macierze
    // Jeżeli krawędź zawiera przynajmniej jeden wierzchołek, który nie istnieje w grafie, to zostaje pominięta
    int* control_element = nullptr;
    for(auto edge : edges_data){
        control_element = matrix->get(edge.begin, edge.end);
        if(control_element == nullptr) continue;

        *control_element = edge.weigth;
        if(!directed) *(matrix->get(edge.end, edge.begin)) = *control_element;
    }

}

MatrixGraph::~MatrixGraph(){

    delete matrix;

}

void MatrixGraph::print(){

    // Jeżeli graf jest pusty to go nie wyświetlam
    if(isNull()){
        printf("Graf jest pusty.");
        return;
    }

    // Graf wyświetlany w formie tabeli:
    //
    //        ┼──────┼──────┼──────┼──────┼
    //        ┼ XXXX ┼ XXXX ┼ .... ┼ XXXX ┼
    // ┼──────┼──────┼──────┼──────┼──────┼
    // ┼ XXXX ┼ vvvv ┼ vvvv ┼ .... ┼ vvvv ┼
    // ┼──────┼──────┼──────┼──────┼──────┼
    //   ....   ....   ....   ....   ....
    // ┼──────┼──────┼──────┼──────┼──────┼
    // ┼ XXXX ┼ vvvv ┼ vvvv ┼ .... ┼ vvv  ┼
    // ┼──────┼──────┼──────┼──────┼──────┼

    const unsigned FILED_WIDTH = 6;
    unsigned width = (matrix->getDegree() + 1) * FILED_WIDTH + matrix->getDegree() + 2;
    unsigned height = (matrix->getDegree()-1) * 2 + 5;

    for(unsigned i = 0; i < height; i++){
        for(unsigned j = 0; j < width; j++){

            // Obsługa pierwszego wiersza z nagłówkami
            if(i < 2 && j == 0) {
                printf("       ");
                j = 7;
            }

            // Separatory wertykalne
            if(j%7 == 0) printf("%c", 197);

            // Komórki
            else if(i%2 == 1) {
                
                // Wartość nagłówka kolumny
                if(i == 1) printf(" %4d ", j/7-1);

                // Wartość nagłówka wiersza
                else if(j == 1) printf(" %4d ", (i-3)/2);

                // Wartość komórki
                else {
                    if(*(matrix->get((i-3)/2, j/7-1)) != NO_CONNECTION) printf(" %4d ", *(matrix->get((i-3)/2, j/7-1)));
                    else printf("    - ");
                }

                // Przejście do kolejnej komórki
                j += 5;
            }

            // Separatory horyzontalne
            else printf("%c", 196);
        }
        printf("\n");
    }

}

MSTResult MatrixGraph::alogrithmPrim(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<PrimVertex> prim_array(matrix->getDegree(), PrimVertex());

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= prim_array.getLength()) return MSTResult(prim_array);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    prim_array[start]->weight = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć
    int minimum_vertex_index = -1;      // indeks wierzchołka o minimalnej wadze
    int neighbour_weight = 0;
    while ( (minimum_vertex_index = prim_array.min()) != -1 ){
        
        // Pobieram kolejnych sąsiadów. Jeżeli sąsiad jest nierozważony, to sprawdzam czy z aktualnego wierzchołka
        // nie prowadzi do niego krawędź o mniejszej wadze niż waga przypisana do sąsiada. Jeżeli tak, to 
        // poprzednikiem sąsiada jest aktualny wierzchołek, a wagą sąsiada jest waga krawędzi łączącej go z aktualnym
        // wierzchołkiem.
        for(int i = 0; i < matrix->getDegree(); i++){
            neighbour_weight = *(matrix->get(minimum_vertex_index, i));
            if(neighbour_weight == NO_CONNECTION) continue;
            if(prim_array[i]->processed) continue;
            if(prim_array[i]->weight <= neighbour_weight) continue;

            prim_array[i]->weight = neighbour_weight;
            prim_array[i]->predecessor = minimum_vertex_index;
        }

        // Wierzchołek uznawany jest za rozważony
        prim_array[minimum_vertex_index]->processed = true;

    }
    
    // Zwrócenie wyniku algorytmu
    return MSTResult(prim_array);

}