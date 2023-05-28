#include "graphs/MatrixGraph.h"
#include "data-structures/Heap.h"

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

    // Sprawdzam, czy graf nie jest pusty
    if(isNull()) {
        DynamicArray<EdgeData> empty_result;
        return MSTResult(empty_result);
    }

    // Inicjalizuje struktury niezbędne do wykonania algorytmu
    DynamicArray<EdgeData> mst_edges(matrix->getDegree()-1, EdgeData());            // krawędzie składające się na MST
    int edges_already_added = 0;                                                    // liczba dotychczas wyznaczonych krawędzi MST
    DynamicArray<int> vertex_status(matrix->getDegree(), 0);                        // tablica zawierająca stan wierzchołka
    Heap queue(matrix->getDegree()*matrix->getDegree()/2 - matrix->getDegree()/2);  // kolejka priorytetowa


    // Wprowadzam wierzchołek startowy z wagą 0 i poprzenikiem NULL do kolejki
    queue.add(VertexData(start, 0, NULL_VERTEX));

    // Algorytm kończy się, gdy drzewo zawiera wsystkie wierzchołki, czyli gdy |E| = |V|-1
    VertexData current_vertex;          // rozważany wierzchołek
    VertexData* neighbour;              // sąsiad rozważanego wierzchołka
    while ( edges_already_added != matrix->getDegree()-1 && queue.root() != nullptr){
        
        // Ściągam wierzchołek o minimalnej wadze z głowy kolejki
        current_vertex = *queue.root();
        queue.pop_root();

        // Jeżeli ten wierzchołek jest już zawarty w MST, to go pomijam
        if(*vertex_status[current_vertex.vertex] == 1) continue;

        // Sprawdzam wszystkich sąsiadów wierzchołka, ktorzy nie są oznaczeni jako należący do MST
        for(int i = 0; i < matrix->getDegree(); i++){
            if(*matrix->get(current_vertex.vertex, i) == NO_CONNECTION) continue;
            if(*vertex_status[i] == 1) continue;

            // Jeżeli sąsiad nie jest częścią MST, to dodaję krawędź do niego prowadzącą do kolejki
            queue.add(VertexData(
                i, 
                *matrix->get(current_vertex.vertex, i), 
                current_vertex.vertex
            ));
        }

        // Nadaję wierzchołkowi status należącego do MST
        *vertex_status[current_vertex.vertex] = 1;

        // Zapisuje dane o krawędzi prowadzącej do wierzchołka do MST
        // Dla wierzchołka startowego ten krok jest pomijany
        if(current_vertex.predecessor == NULL_VERTEX) continue;
        mst_edges[edges_already_added]->begin = current_vertex.predecessor;
        mst_edges[edges_already_added]->end = current_vertex.vertex;
        mst_edges[edges_already_added]->weigth = current_vertex.weight;
        edges_already_added++;
    }

    // Zwracam tablice wynikową
    return mst_edges;

}

PathfindingResult MatrixGraph::algorithmDijkstra(unsigned start){

    // Sprawdzam, czy graf nie jest pusty
    if(isNull()) {
        DynamicArray<VertexData> empty_result(matrix->getDegree(), VertexData());
        return PathfindingResult(empty_result, start);
    }

    // Inicjalizuje struktury niezbędne do wykonania algorytmu
    DynamicArray<VertexData> result(matrix->getDegree(), VertexData());             // tablica zawierająca wynik
    DynamicArray<int> vertex_status(matrix->getDegree(), 0);                        // tablica zawierająca stan wierzchołka
    Heap queue(matrix->getDegree()*matrix->getDegree());                            // kolejka priorytetowa


    // Wprowadzam wierzchołek startowy z wagą 0 i poprzenikiem NULL do kolejki
    queue.add(VertexData(start, 0, NULL_VERTEX));

    // Algorytm kończy się po opróżnieniu kolejki
    VertexData current_vertex;         // rozważany wierzchołek
    VertexData* neighbour;              // sąsiad rozważanego wierzchołka
    while ( queue.root() != nullptr ){
        
        // Ściągam wierzchołek o minimalnej wadze z głowy kolejki
        current_vertex = *queue.root();
        queue.pop_root();

        // Jeżeli wierzchołek był już odwiedzony, to pomijamy jego rozważenie
        if(*vertex_status[current_vertex.vertex] == 1) continue;

        // Sprawdzam wszystkich sąsiadów wierzchołka, ktorzy nie są oznaczeni jako odwiedzeni
        for(int i = 0; i < matrix->getDegree(); i++){
            if(*matrix->get(current_vertex.vertex, i) == NO_CONNECTION) continue;
            if(*vertex_status[i] == 1) continue;

            // W ramach optymalizacji pomijam sprawdzenie, czy sąsiad znajduje się juz w kolejce.
            // Zamiast tradycyjnej relaksacji po prostu dodaję dane o dordze prowadzącej do sąsiada od
            // aktualnego wierzchołka. Kolejka sama umieści go w odpowiednim miejscu, co spowoduje, że
            // ta kopia wierzchołka o najmniejszej wadze zostanie pobrana pobrana z kolejki przed kopiami
            // o większych wagach. Następnie wierzchołek zostanie oznaczony jako odwiedzony, co spodowuje, że
            // owe gorsze pod względem wagowym kopie nie zostaną rozważone po wyciągnięciu z kolejki.
            queue.add(VertexData(
                    i, 
                    *matrix->get(current_vertex.vertex, i) + current_vertex.weight, 
                    current_vertex.vertex
            ));
        }

        // Zapisuje przypisane wierzchołkowi wartości do tablicy wynikowej i uznaje go za odwiedzonego
        *vertex_status[current_vertex.vertex] = 1;
        result[current_vertex.vertex]->predecessor = current_vertex.predecessor;
        result[current_vertex.vertex]->weight = current_vertex.weight;
    }

    // Zwracam tablice wynikową
    return PathfindingResult(result, start);

}

DynamicArray<EdgeData> MatrixGraph::getEdgesList(bool directional){

    // Tworzę tablicę krawędzi
    int edge_count;
    if(directional) edge_count = matrix->getDegree()*matrix->getDegree();
    else edge_count = matrix->getDegree()*matrix->getDegree()/2 - matrix->getDegree()/2;
    DynamicArray<EdgeData> edges(edge_count, EdgeData());

    // Zbieram wszystkie krawędzie 
    int current_edge = 0;
    for(int vertex = 0; vertex < matrix->getDegree() && current_edge < edge_count; vertex++){
        for(int neighbour =  ( !directional ? vertex+1 : 0 ); neighbour < matrix->getDegree() && current_edge < edge_count; neighbour++){
            if(*(matrix->get(vertex, neighbour)) == NO_CONNECTION) continue;

            edges[current_edge]->begin = vertex;
            edges[current_edge]->end = neighbour;
            edges[current_edge]->weigth = *(matrix->get(vertex, neighbour));
            current_edge++;
        }
    }

    // Niekoniecznie graf ma maksymalną liczbę krawędzi, więc zwaracam tablicę o takiej
    // wielkości, jaka była rzeczywista ilość krawędzi
    DynamicArray<EdgeData> properly_sized_edges(current_edge, EdgeData());
    for(int i = 0; i < properly_sized_edges.getLength(); i++){
        properly_sized_edges[i]->begin = edges[i]->begin;
        properly_sized_edges[i]->end = edges[i]->end;
        properly_sized_edges[i]->weigth = edges[i]->weigth;
    }
    return properly_sized_edges;

}


PathfindingResult MatrixGraph::algorithmBellmanFord(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> bf_array(matrix->getDegree(), VertexData());

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    bf_array[start]->weight = 0;

    // Pobieram tablicę krawędzi grafu
    DynamicArray<EdgeData> edges = getEdgesList(true);

    // Iteruję się |V|-1 razy przez tablicę z krawędziami, szukając coraz to bardziej korzystnych ścieżek do wszystkich wierzchołków.
    // Jeżeli w danej iteracji nie zostanie znaleziona żadna korzystniejsza ścieżka, to przerywam iterowanie przedwcześnie.
    EdgeData* edge;
    bool better_path_found;
    for(int i = 1; i <= matrix->getDegree(); i++){

        // Jeżeli w iteracji |V|-1 poprawił się jakiś cykl i znajeźliśmy się w iteracji |V|-tej, to 
        // oznacza to istnienie cyklu ujemnego w grafie
        if(i == matrix->getDegree()){
            DynamicArray<VertexData> empty_result;
            return PathfindingResult(empty_result, start);
        }

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

    // Zwracam wynik
    return PathfindingResult(bf_array, start);

}

#include "app/utility/SortingMachine.h"
#include "data-structures/DisjointSet.h"
MSTResult MatrixGraph::algorithmKruskal(){

    // Jeżeli graf jest pusty, to nie ma sensu wykonywać algorytmu
    if(isNull()){
        DynamicArray<EdgeData> empty_result;
        return empty_result;
    }

    // Inicjalizuje struktury danych niezbędne do wykonania algorytmu
    DynamicArray<EdgeData> mst_edges(matrix->getDegree()-1, EdgeData());    // zbiór krawędzi mst
    unsigned mst_edges_already_added = 0;                                   // liczba już wyznaczonych krawędzi MST
    DynamicArray<EdgeData> graph_edges = getEdgesList(false);               // zbiór krawędzi grafu
    DisjointSets subtrees(matrix->getDegree());                             // dane o przynależności wierzchołków do poddrzew                

    // Sortowanie listy krawędzi
    SortingMachine::sort(graph_edges, 0, graph_edges.getLength()-1);
    
    // Sprawdzam kolejne krawędzie z posortowanej tablicy do dojścia do jej końca lub wyznaczenie wszystkich krawędzi MST
    EdgeData* edge;
    int end_subtree, begin_subtree;
    for(int i = 0; mst_edges_already_added != matrix->getDegree()-1 && i < graph_edges.getLength(); i++){

        // Pobieram krawędź
        edge = graph_edges[i];

        // Sprawdzam do jakich poddrzew należą krańce krawędzi
        end_subtree = subtrees.getSet(edge->end);
        begin_subtree = subtrees.getSet(edge->begin);

        // Jeżeli wierzchołek początkowy i końcowy krawędzi nie są w tym samym poddrzewie, to dodaję krawędź do MST.
        // Następnie łącze ich poddrzewa, włączając poddrzewo o mniejszej randze do poddrzewa o większej randze
        if(end_subtree == begin_subtree) continue;    

        *mst_edges[mst_edges_already_added] = *edge;
        mst_edges_already_added++;

        subtrees.unionSets(end_subtree, begin_subtree);

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