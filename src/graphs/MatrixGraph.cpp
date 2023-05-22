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
    DynamicArray<VertexData> prim_array(matrix->getDegree(), VertexData());

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= prim_array.getLength()) return MSTResult(prim_array);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    prim_array[start]->weight = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć
    int minimum_vertex_index = -1;      // indeks wierzchołka o minimalnej wadze
    int neighbour_weight = 0;
    while ( (minimum_vertex_index = prim_array.min()) != -1 ){
        
        // Jeżeli wybrany, minimalny wierzchołek ma wagę nieskończoność, to graf jest niespójny.
        // Wówczas algorytm nie może zostać poprawnie wykonany
        if(prim_array[minimum_vertex_index]->weight == INFINITY_W){
            DynamicArray<VertexData> empty_array(matrix->getDegree(), VertexData());
            return MSTResult(empty_array);
        }

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

PathfindingResult MatrixGraph::algorithmDijkstra(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> dijkstra_array(matrix->getDegree(), VertexData());

    // Sprawdzam, czy graf zawiera ujemne wierzchołki
    if(containNegativeEdges()) return PathfindingResult(dijkstra_array, start);

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= dijkstra_array.getLength()) return PathfindingResult(dijkstra_array, start);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    dijkstra_array[start]->weight = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć
    int minimum_vertex_index = -1;      // indeks wierzchołka o minimalnej wadze
    int path_thourgh_current_vertex = 0;    // długość ścieżki prowadzącej przez obecny wierzchołek
    while ( (minimum_vertex_index = dijkstra_array.min()) != -1 ){
        
        // Jeżeli minimalnym wierzchołkiem jest ten o wadze nieskończoność, to nie da się do
        // niego dotrzeć z wierzchołkach starowego. W takiej styuacji tego wierzchołka nie rozważamy.
        if(dijkstra_array[minimum_vertex_index]->weight == INFINITY_W) {
            dijkstra_array[minimum_vertex_index]->processed = true;
            continue;
        }

        // Pobieram kolejnych sąsiadów. Sprawdzam czy z aktualnego wierzchołka
        // nie prowadzi do sąsiada niego droga o mniejszej wadze niż dotychczasowa. Jeżeli tak, to 
        // poprzednikiem sąsiada jest aktualny wierzchołek, a drogą do sąsiada jest ta, biegnąca przez rozważany wierzchołek.
        for(int i = 0; i < matrix->getDegree(); i++){
            if(*(matrix->get(minimum_vertex_index, i)) == NO_CONNECTION) continue;
            path_thourgh_current_vertex = *(matrix->get(minimum_vertex_index, i)) + dijkstra_array[minimum_vertex_index]->weight;
            if(dijkstra_array[i]->weight <= path_thourgh_current_vertex) continue;

            dijkstra_array[i]->weight = path_thourgh_current_vertex;
            dijkstra_array[i]->predecessor = minimum_vertex_index;
        }

        // Wierzchołek uznawany jest za rozważony
        dijkstra_array[minimum_vertex_index]->processed = true;

    }

    return PathfindingResult(dijkstra_array, start);

}

DynamicArray<EdgeData> MatrixGraph::getEdgesList(bool directional){

    // towrzę tablicę krawędzi
    DynamicArray<EdgeData> edges;

    // zbieram wszystkie krawędzie 
    for(int vertex = 0; vertex < matrix->getDegree(); vertex++)
        for(int neighbour =  ( !directional ? vertex+1 : 0 ); neighbour < matrix->getDegree(); neighbour++)
            if(*(matrix->get(vertex, neighbour)) != NO_CONNECTION)
                edges.push_back(EdgeData(vertex, neighbour, *(matrix->get(vertex, neighbour))));
    
    // zwracam wynik 
    return edges;

}


PathfindingResult MatrixGraph::algorithmBellmanFord(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> bf_array(matrix->getDegree(), VertexData());

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= bf_array.getLength()) return PathfindingResult(bf_array, start);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    bf_array[start]->weight = 0;

    // Pobieram tablicę krawędzi grafu
    DynamicArray<EdgeData> edges = getEdgesList(true);

    // Iteruję się |V|-1 razy przez tablicę z krawędziami, szukając coraz to bardziej korzystnych ścieżek do wszystkich wierzchołków.
    // Jeżeli w danej iteracji nie zostanie znaleziona żadna korzystniejsza ścieżka, to przerywam iterowanie przedwcześnie.
    EdgeData* edge;
    bool better_path_found;
    for(int i = 1; i < matrix->getDegree(); i++){

        // Sprawdzam kolejne krawędzie. Jeżeli do wierzchołek końcowy ma większą wagę niż suma wag wierzchołka końcowego i łączących
        // je krawędzi, to wagą wierzchołka końcowego staje się owa suma, a jego poprzednikiem staje się wierzchołek początkowy.
        // Jeżeli wierzchołek początkowy ma wagę nieskończoność, to pomijam jego rozważanie (na pewno nie ma mniejszej wagi niz wierzchołek końcowy)
        better_path_found = false;
        for(int edge_index = 0; edge_index < edges.getLength(); edge_index++){
            edge = edges[edge_index];
            if(bf_array[edge->begin]->weight == INFINITY_W) continue;
            if(bf_array[edge->end]->weight <= edge->weigth + bf_array[edge->begin]->weight) continue;

            better_path_found = true;
            bf_array[edge->end]->weight = edge->weigth + bf_array[edge->begin]->weight;
            bf_array[edge->end]->predecessor = edge->begin;
        }

        // Jeżeli nie znaleziono w danej iteracji nowych, lepszych ścieżek, to optymalnie jest nie wykonywać kolejnych przebiegów
        if(!better_path_found) break;

    }

    // Sprawdzam, czy nie wystąpił cykl ujemny
    for(int i = 0; i < edges.getLength(); i++){
        edge = edges[i];
        if(bf_array[edge->begin]->weight == INFINITY_W) continue;
        if(bf_array[edge->end]->weight <= edge->weigth + bf_array[edge->begin]->weight) continue;

        DynamicArray<VertexData> empty_result(matrix->getDegree(), VertexData());
        return PathfindingResult(empty_result, start);
    }

    // Zwracam wynik
    return PathfindingResult(bf_array, start);

}

#include "app/utility/SortingMachine.h"
MSTResult MatrixGraph::algorithmKruskal(){

    // Inicjalizuję tablice wyjściową algorytmu, przechowujacą krawędzie MST.
    // Inicjalizuję także tablice z posortowanymi niemalejąco krawędziami grafu oraz tablicę z danymi o wierzchołkach.
    DynamicArray<EdgeData> mst_edges;
    DynamicArray<VertexData> verticies(matrix->getDegree(), VertexData());
    DynamicArray<EdgeData> sorted_graph_edges = getEdgesList(false);
    SortingMachine::sort(sorted_graph_edges, 0, sorted_graph_edges.getLength()-1);

    // Każdy wierzchołek przypisuję do jego własnego poddrzewa
    for(int i = 0; i < verticies.getLength(); i++)
        verticies[i]->predecessor = i;

    // Dla kolejnych krawędzi sprawdzam, czy ich oba wierzchołki należą do tych samych poddrzew. Jeżeli nie należą, to łączymy ich 
    // poddrzewa w jedno włączając poddrzewa wierzchołka końcowego w poddrzewo wierzchołka początkowego. W takim wypadku dopisujemy
    // także rozważaną krawędź do zbioru krawędzi MST.
    EdgeData* edge;
    int previous_subtree_id;
    for(int i = 0; i < sorted_graph_edges.getLength(); i++){
        edge = sorted_graph_edges[i];
        if(verticies[edge->begin]->predecessor == verticies[edge->end]->predecessor) continue;

        mst_edges.push_back(*edge);
        previous_subtree_id = verticies[edge->end]->predecessor;
        for(int j = 0; j < verticies.getLength(); j++)
            if(verticies[j]->predecessor == previous_subtree_id)
                verticies[j]->predecessor = verticies[edge->begin]->predecessor;
    }

    // Sprawdzam, czy graf okazał się spójny. Jeżeli jest, to w wyniku przebiegu algorytmu
    // wszytskie wierzchołki powinny znaleźć się w jednym poddrzewie
    int result_tree_id = verticies[0]->predecessor;
    for(int i = 0; i < verticies.getLength(); i++){
        if(verticies[i]->predecessor == result_tree_id) continue;

        DynamicArray<EdgeData> empty_mst;
        return empty_mst;
    }

    // Zwracam wynik
    return mst_edges;

}

bool MatrixGraph::containNegativeEdges(){

    for(int i = 0; i < matrix->getDegree(); i++)
        for(int j = 0; j < matrix->getDegree(); j++)
            if(*matrix->get(i,j) != NO_CONNECTION && *matrix->get(i,j) < 0)
                return true;
    return false;

}