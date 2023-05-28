#include "graphs/ListGraph.h"
#include "data-structures/Heap.h"

ListGraph::ListGraph(unsigned verticies_count, vector<EdgeData> edges_data, bool directed){

    // Jeżeli zadano ilość wierzchołków równą 0, to towrzę graf pusty
    this->verticies_count = verticies_count;
    if(verticies_count == 0){
        adjentency_lists = nullptr;
        return;
    }

    // Inicjalizacja zbioru list sąsiadów
    adjentency_lists = new List[verticies_count];

    // Na podstawie danych wczytuje z pliku uzupełniam listy
    // Jeżeli krawędź zawiera przynajmniej jeden wierzchołek, który nie istnieje w grafie, to zostaje pominięta
    for(auto edge : edges_data){
        if(edge.begin >= this->verticies_count || edge.end >= this->verticies_count) continue;
        
        adjentency_lists[edge.begin].push_back(edge.end, edge.weigth);
        if(!directed)adjentency_lists[edge.end].push_back(edge.begin, edge.weigth);
    }

}

ListGraph::~ListGraph(){

    delete[] adjentency_lists;

}

List* ListGraph::getAdjetencyList(unsigned vertex_index){

    // Jeżeli wierzchołek nie istnieje lub nie ma sąsiadów, to zwracany jest nullptr
    if(vertex_index >= verticies_count || adjentency_lists[vertex_index].front() == nullptr) return nullptr;

    // W przeciwnym wypadku zwracany jest adres listy
    return &(adjentency_lists[vertex_index]);

}

void ListGraph::print(){

    // Jeżeli graf jest pusty, to nie jest wyświetlany
    if(isNull()){
        cout << "Graf jest pusty." << endl;
    }

    // Graf wyświetlam jako listy sąsiadów w formie:
    //
    //      ┼───────────┼───────────┼──────┼───────────┼
    // XXXX ┼ vvvv vvvv ┼ vvvv vvvv ┼ .... ┼ vvvv vvvv ┼
    //      ┼───────────┼───────────┼──────┼───────────┼
    //
    //      ┼───────────┼
    // XXXX ┼ vvvv vvvv ┼
    //      ┼───────────┼
    
    const unsigned FIELD_WIDTH = 11;
    unsigned width = 0;
    for(int i = 0; i < verticies_count; i++){
        printf("\n");
        width = FIELD_WIDTH * adjentency_lists[i].size() + adjentency_lists[i].size() + 1;

        // górny separator poziomy
        printf("      ");
        for(int j = 0; j < width; j++){
            if(j % 12 == 0) printf("%c", 197);
            else printf("%c", 196);
        }
        printf("\n");

        printf(" %-4d %c", i, (width == 0 ? '\0': 197));
        for(int j = 0; adjentency_lists[i][j] != nullptr; j++)
            printf(" %-4d %4d %c", adjentency_lists[i][j]->end, adjentency_lists[i][j]->weigth, 197);
        printf("\n");

        // dolny separator poziomy
        printf("      ");
        for(int j = 0; j < width; j++){
            if(j % 12 == 0) printf("%c", 197);
            else printf("%c", 196);
        }
        printf("\n");
    }

}

MSTResult ListGraph::alogrithmPrim(unsigned start){

    // Sprawdzam, czy graf nie jest pusty
    if(isNull()) {
        DynamicArray<EdgeData> empty_result;
        return MSTResult(empty_result);
    }

    // Inicjalizuje struktury niezbędne do wykonania algorytmu
    DynamicArray<EdgeData> mst_edges(verticies_count-1, EdgeData());    // krawędzie składające się na MST
    int edges_already_added = 0;                                        // liczba dotychczas wyznaczonych krawędzi MST
    DynamicArray<int> vertex_status(verticies_count, 0);                // tablica zawierająca stan wierzchołka
    Heap queue(verticies_count*verticies_count/2+verticies_count/2);    // kolejka priorytetowa


    // Wprowadzam wierzchołek startowy z wagą 0 i poprzenikiem NULL do kolejki
    queue.add(VertexData(start, 0, NULL_VERTEX));

    // Algorytm kończy się, gdy drzewo zawiera wsystkie wierzchołki, czyli gdy |E| = |V|-1
    VertexData current_vertex;          // rozważany wierzchołek
    VertexData* neighbour;              // sąsiad rozważanego wierzchołka
    while ( edges_already_added != verticies_count-1 && queue.root() != nullptr){
        
        // Ściągam wierzchołek o minimalnej wadze z głowy kolejki
        current_vertex = *queue.root();
        queue.pop_root();

        // Jeżeli ten wierzchołek jest już zawarty w MST, to go pomijam
        if(*vertex_status[current_vertex.vertex] == 1) continue;

        // Sprawdzam wszystkich sąsiadów wierzchołka, ktorzy nie są oznaczeni jako należący do MST
        for(int i = 0; adjentency_lists[current_vertex.vertex][i] != nullptr; i++){
            if(*vertex_status[adjentency_lists[current_vertex.vertex][i]->end] == 1) continue;

            // Jeżeli sąsiad nie nalezy do MST, to dodaję krawędź do niego prowadzącą do kolejki
            queue.add(VertexData(
                adjentency_lists[current_vertex.vertex][i]->end, 
                adjentency_lists[current_vertex.vertex][i]->weigth, 
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

PathfindingResult ListGraph::algorithmDijkstra(unsigned start){

    // Sprawdzam, czy graf nie jest pusty
    if(isNull()) {
        DynamicArray<VertexData> empty_result(verticies_count, VertexData());
        return PathfindingResult(empty_result, start);
    }

    // Inicjalizuje struktury niezbędne do wykonania algorytmu
    DynamicArray<VertexData> result(verticies_count, VertexData());     // tablica zawierająca wynik
    DynamicArray<int> vertex_status(verticies_count, 0);                // tablica zawierająca stan wierzchołka
    Heap queue(verticies_count*verticies_count);                        // kolejka priorytetowa


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
        for(int i = 0; adjentency_lists[current_vertex.vertex][i] != nullptr; i++){
            if(*vertex_status[adjentency_lists[current_vertex.vertex][i]->end] == 1) continue;

            // W ramach optymalizacji pomijam sprawdzenie, czy sąsiad znajduje się juz w kolejce.
            // Zamiast tradycyjnej relaksacji po prostu dodaję dane o dordzę prowadzącej do sąsiada od
            // aktualnego wierzchołka. Kolejka sama umieści go w odpowiednim miejscu, co spowoduje, że
            // ta kopie wierzchołka o najmniejszej wadze zostanie pobrana pobrana z kolejki przed kopiami
            // o większych wagach. Następnie wierzchołek zostanie oznaczony jako odwiedzony, co spodowuje, że
            // owe gorsze pod względem wagowym kopie nie zostaną rozważone.
            queue.add(VertexData(
                    adjentency_lists[current_vertex.vertex][i]->end, 
                    adjentency_lists[current_vertex.vertex][i]->weigth + current_vertex.weight, 
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

DynamicArray<EdgeData> ListGraph::getEdgesList(bool directional){

    // Tworzę tablicę krawędzi
    int edge_count;
    if(directional) edge_count = verticies_count*verticies_count;
    else edge_count = verticies_count*verticies_count/2 - verticies_count/2;
    DynamicArray<EdgeData> edges(edge_count, EdgeData());

    // Zbieram wszystkie krawędzie 
    int current_edge = 0;
    for(int vertex = 0; vertex < verticies_count; vertex++){
        for(int i = 0; adjentency_lists[vertex][i] != nullptr; i++){
            if(!directional && adjentency_lists[vertex][i]->end <= vertex) continue;

            edges[current_edge]->begin = vertex;
            edges[current_edge]->end = adjentency_lists[vertex][i]->end;
            edges[current_edge]->weigth = adjentency_lists[vertex][i]->weigth;
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

PathfindingResult ListGraph::algorithmBellmanFord(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> bf_array(verticies_count, VertexData());

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    bf_array[start]->weight = 0;

    // Pobieram tablicę krawędzi grafu
    DynamicArray<EdgeData> edges = getEdgesList(true);

    // Iteruję się |V|-1 razy przez tablicę z krawędziami, szukając coraz to bardziej korzystnych ścieżek do wszystkich wierzchołków.
    // Jeżeli w danej iteracji nie zostanie znaleziona żadna korzystniejsza ścieżka, to przerywam iterowanie przedwcześnie.
    EdgeData* edge;
    bool better_path_found;
    for(int i = 1; i <= verticies_count; i++){

        // Jeżeli w iteracji |V|-1 poprawił się jakiś cykl i znajeźliśmy się w iteracji |V|-tej, to 
        // oznacza to istnienie cyklu ujemnego w grafie
        if(i == verticies_count){
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
#include "app/utility/Timer.h"
MSTResult ListGraph::algorithmKruskal(){
    
    // Jeżeli graf jest pusty, to nie ma sensu wykonywać algorytmu
    if(isNull()){
        DynamicArray<EdgeData> empty_result;
        return empty_result;
    }

    // Inicjalizuje struktury danych niezbędne do wykonania algorytmu
    DynamicArray<EdgeData> mst_edges(verticies_count-1, EdgeData());    // zbiór krawędzi mst
    unsigned mst_edges_already_added = 0;                               // liczba już wyznaczonych krawędzi MST
    DynamicArray<EdgeData> graph_edges = getEdgesList(false);           // zbiór krawędzi grafu
    DisjointSets subtrees(verticies_count);                             // dane o przynależności wierzchołków do poddrzew                

    // Sortowanie listy krawędzi
    SortingMachine::sort(graph_edges, 0, graph_edges.getLength()-1);
    
    // Sprawdzam kolejne krawędzie z posortowanej tablicy do dojścia do jej końca lub wyznaczenie wszystkich krawędzi MST
    EdgeData* edge;
    int end_subtree, being_subtree;
    for(int i = 0; mst_edges_already_added != verticies_count-1 && i < graph_edges.getLength(); i++){

        // Pobieram krawędź
        edge = graph_edges[i];

        // Sprawdzam do jakich poddrzew należą krańce krawędzi
        end_subtree = subtrees.getSet(edge->end);
        being_subtree = subtrees.getSet(edge->begin);

        // Jeżeli wierzchołek początkowy i końcowy krawędzi nie są w tym samym poddrzewie, to dodaję krawędź do MST.
        // Następnie łącze ich poddrzewa, włączając poddrzewo wierzchołka końcowego w poddrzewo wierzchołka początkowego.
        if(end_subtree == being_subtree) continue;    

        *mst_edges[mst_edges_already_added] = *edge;
        mst_edges_already_added++;

        subtrees.unionSets(end_subtree, being_subtree);

    }

    // Zwracam wynik
    return mst_edges;

}

bool ListGraph::containNegativeEdges(){

    for(int i = 0; i < verticies_count; i++)
        for(int j = 0; adjentency_lists[i][j] != nullptr; j++)
            if(adjentency_lists[i][j]->weigth < 0)
                return true;
    return false;


}