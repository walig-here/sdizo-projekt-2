#include "graphs/ListGraph.h"

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

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> prim_array(verticies_count, VertexData());

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= prim_array.getLength()) return MSTResult(prim_array);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    prim_array[start]->value = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć

    int minimum_vertex_index = -1;              // indeks wierzchołka o minimalnej wadze
    ListElement* edge = nullptr;                // krawędź prowadząca do sąsiada
    
    while ( (minimum_vertex_index = prim_array.min()) != -1 ){
        
        // Jeżeli wybrany, minimalny wierzchołek ma wagę nieskończoność, to graf jest niespójny.
        // Wówczas algorytm nie może zostać poprawnie wykonany
        if(prim_array[minimum_vertex_index]->value == INFINITY_W){
            DynamicArray<VertexData> empty_array(verticies_count, VertexData());
            return MSTResult(empty_array);
        }

        // Pobieram kolejnych sąsiadów. Jeżeli sąsiad jest nierozważony, to sprawdzam czy z aktualnego wierzchołka
        // nie prowadzi do niego krawędź o mniejszej wadze niż waga przypisana do sąsiada. Jeżeli tak, to 
        // poprzednikiem sąsiada jest aktualny wierzchołek, a wagą sąsiada jest waga krawędzi łączącej go z aktualnym
        // wierzchołkiem.
        for(int i = 0; (edge = adjentency_lists[minimum_vertex_index][i]) != nullptr; i++){
            if(prim_array[edge->end]->processed) continue;
            if(prim_array[edge->end]->value <= edge->weigth) continue;

            prim_array[edge->end]->value = edge->weigth;
            prim_array[edge->end]->predecessor = minimum_vertex_index;
        }

        // Wierzchołek uznawany jest za rozważony
        prim_array[minimum_vertex_index]->processed = true;

    }
    
    // Zwrócenie wyniku algorytmu
    return MSTResult(prim_array);

}

PathfindingResult ListGraph::algorithmDijkstra(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> dijkstra_array(verticies_count, VertexData());

    // Sprawdzam, czy graf zawiera ujemne wierzchołki
    if(containNegativeEdges()) return PathfindingResult(dijkstra_array, start);

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= dijkstra_array.getLength()) return PathfindingResult(dijkstra_array, start);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    dijkstra_array[start]->value = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć
    int minimum_vertex_index = -1;              // indeks wierzchołka o minimalnej wadze
    int path_thourgh_current_vertex = 0;        // długość ścieżki prowadzącej przez obecny wierzchołek
    ListElement* edge = nullptr;                // krawędź prowadząca do sąsiada

    while ( (minimum_vertex_index = dijkstra_array.min()) != -1 ){
        
        // Jeżeli minimalnym wierzchołkiem jest ten o wadze nieskończoność, to nie da się do
        // niego dotrzeć z wierzchołkach starowego. W takiej styuacji tego wierzchołka nie rozważamy.
        if(dijkstra_array[minimum_vertex_index]->value == INFINITY_W) {
            dijkstra_array[minimum_vertex_index]->processed = true;
            continue;
        }

        // Pobieram kolejnych sąsiadów. Sprawdzam czy z aktualnego wierzchołka
        // nie prowadzi do sąsiada niego droga o mniejszej wadze niż dotychczasowa. Jeżeli tak, to 
        // poprzednikiem sąsiada jest aktualny wierzchołek, a drogą do sąsiada jest ta, biegnąca przez rozważany wierzchołek.
        for(int i = 0; (edge = adjentency_lists[minimum_vertex_index][i]) != nullptr; i++){
            path_thourgh_current_vertex = edge->weigth + dijkstra_array[minimum_vertex_index]->value;
            if(dijkstra_array[edge->end]->value <= path_thourgh_current_vertex) continue;

            dijkstra_array[edge->end]->value = path_thourgh_current_vertex;
            dijkstra_array[edge->end]->predecessor = minimum_vertex_index;
        }

        // Wierzchołek uznawany jest za rozważony
        dijkstra_array[minimum_vertex_index]->processed = true;

    }

    return PathfindingResult(dijkstra_array, start);

}

DynamicArray<EdgeData> ListGraph::getEdgesList(bool directional){

    // towrzę tablicę krawędzi
    DynamicArray<EdgeData> edges;

    // zbieram wszystkie krawędzie 
    for(int vertex = 0; vertex < verticies_count; vertex++){
        for(int i = 0; adjentency_lists[vertex][i] != nullptr; i++)
            if(!(!directional && adjentency_lists[vertex][i]->end <= vertex))
                edges.push_back(EdgeData(vertex, adjentency_lists[vertex][i]->end, adjentency_lists[vertex][i]->weigth));
    }
    
    // zwracam wynik 
    return edges;

}

PathfindingResult ListGraph::algorithmBellmanFord(unsigned start){

    // Inicjalizacja tablicy ze stanami wierzchołków
    DynamicArray<VertexData> bf_array(verticies_count, VertexData());

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= bf_array.getLength()) return PathfindingResult(bf_array, start);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    bf_array[start]->value = 0;

    // Pobieram tablicę krawędzi grafu
    DynamicArray<EdgeData> edges = getEdgesList(true);

    // Iteruję się |V|-1 razy przez tablicę z krawędziami, szukając coraz to bardziej korzystnych ścieżek do wszystkich wierzchołków.
    // Jeżeli w danej iteracji nie zostanie znaleziona żadna korzystniejsza ścieżka, to przerywam iterowanie przedwcześnie.
    EdgeData* edge;
    bool better_path_found;
    for(int i = 1; i < verticies_count; i++){

        // Sprawdzam kolejne krawędzie. Jeżeli do wierzchołek końcowy ma większą wagę niż suma wag wierzchołka końcowego i łączących
        // je krawędzi, to wagą wierzchołka końcowego staje się owa suma, a jego poprzednikiem staje się wierzchołek początkowy.
        // Jeżeli wierzchołek początkowy ma wagę nieskończoność, to pomijam jego rozważanie (na pewno nie ma mniejszej wagi niz wierzchołek końcowy)
        better_path_found = false;
        for(int edge_index = 0; edge_index < edges.getLength(); edge_index++){
            edge = edges[edge_index];
            if(bf_array[edge->begin]->value == INFINITY_W) continue;
            if(bf_array[edge->end]->value <= edge->weigth + bf_array[edge->begin]->value) continue;

            better_path_found = true;
            bf_array[edge->end]->value = edge->weigth + bf_array[edge->begin]->value;
            bf_array[edge->end]->predecessor = edge->begin;
        }

        // Jeżeli nie znaleziono w danej iteracji nowych, lepszych ścieżek, to optymalnie jest nie wykonywać kolejnych przebiegów
        if(!better_path_found) break;

    }

    // Sprawdzam, czy nie wystąpił cykl ujemny
    for(int i = 0; i < edges.getLength(); i++){
        edge = edges[i];
        if(bf_array[edge->begin]->value == INFINITY_W) continue;
        if(bf_array[edge->end]->value <= edge->weigth + bf_array[edge->begin]->value) continue;
        DynamicArray<VertexData> empty_result(verticies_count, VertexData());
        return PathfindingResult(empty_result, 0);
    }

    // Zwracam wynik
    return PathfindingResult(bf_array, start);

}

#include "app/utility/SortingMachine.h"
MSTResult ListGraph::algorithmKruskal(){
    
    // Jeżeli graf jest pusty, to nie ma sensu wykonywać na nim algorytmu
    if(isNull()){
        DynamicArray<EdgeData> empty_mst;
        return empty_mst;
    }

    // Inicjalizuję tablice wyjściową algorytmu, przechowujacą krawędzie MST.
    // Inicjalizuję także tablice z posortowanymi niemalejąco krawędziami grafu oraz tablicę z danymi o wierzchołkach.
    DynamicArray<EdgeData> mst_edges;
    DynamicArray<VertexData> verticies(verticies_count, VertexData());
    DynamicArray<EdgeData> sorted_graph_edges = getEdgesList(false);
    SortingMachine::sort(sorted_graph_edges, 0, sorted_graph_edges.getLength()-1);

    // Każdy wierzchołek przypisuję do jego własnego poddrzewa
    for(int i = 0; i < verticies.getLength(); i++)
        verticies[i]->value = i;

    // Dla kolejnych krawędzi sprawdzam, czy ich oba wierzchołki należą do tych samych poddrzew. Jeżeli nie należą, to łączymy ich 
    // poddrzewa w jedno włączając poddrzewa wierzchołka końcowego w poddrzewo wierzchołka początkowego. W takim wypadku dopisujemy
    // także rozważaną krawędź do zbioru krawędzi MST.
    EdgeData* edge;
    int previous_subtree_id;
    for(int i = 0; i < sorted_graph_edges.getLength(); i++){
        edge = sorted_graph_edges[i];
        if(verticies[edge->begin]->value == verticies[edge->end]->value) continue;

        mst_edges.push_back(*edge);
        previous_subtree_id = verticies[edge->end]->value;
        for(int j = 0; j < verticies.getLength(); j++)
            if(verticies[j]->value == previous_subtree_id)
                verticies[j]->value = verticies[edge->begin]->value;
    }

    // Sprawdzam, czy graf okazał się spójny. Jeżeli jest, to w wyniku przebiegu algorytmu
    // wszytskie wierzchołki powinny znaleźć się w jednym poddrzewie
    int result_tree_id = verticies[0]->value;
    for(int i = 0; i < verticies.getLength(); i++){
        if(verticies[i]->value == result_tree_id) continue;

        DynamicArray<EdgeData> empty_mst;
        return empty_mst;
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