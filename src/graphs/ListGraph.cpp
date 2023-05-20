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
    prim_array[start]->weight = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć

    int minimum_vertex_index = -1;      // indeks wierzchołka o minimalnej wadze
    ListElement* edge = nullptr;              // krawędź prowadząca do sąsiada
    
    while ( (minimum_vertex_index = prim_array.min()) != -1 ){
        
        // Pobieram kolejnych sąsiadów. Jeżeli sąsiad jest nierozważony, to sprawdzam czy z aktualnego wierzchołka
        // nie prowadzi do niego krawędź o mniejszej wadze niż waga przypisana do sąsiada. Jeżeli tak, to 
        // poprzednikiem sąsiada jest aktualny wierzchołek, a wagą sąsiada jest waga krawędzi łączącej go z aktualnym
        // wierzchołkiem.
        for(int i = 0; (edge = adjentency_lists[minimum_vertex_index][i]) != nullptr; i++){
            if(prim_array[edge->end]->processed) continue;
            if(prim_array[edge->end]->weight <= edge->weigth) continue;

            prim_array[edge->end]->weight = edge->weigth;
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

    // Sprawdzam, czy wierzchołek startowy znajduje się w grafie
    if(start >= dijkstra_array.getLength()) return PathfindingResult(dijkstra_array, start);

    // Wybieram wierzchołek startowy. Ustawiam jego wagę na 0.
    dijkstra_array[start]->weight = 0;

    // Wybieram z tablicy stanów wierzchołków kolejne nierozważone wierzchołki o minimalnej wadze
    // Jeżeli wszystkie wierzchołki są rozpatrzone, to algorytm może się zakończyć
    int minimum_vertex_index = -1;              // indeks wierzchołka o minimalnej wadze
    int path_thourgh_current_vertex = 0;        // długość ścieżki prowadzącej przez obecny wierzchołek
    ListElement* edge = nullptr;                // krawędź prowadząca do sąsiada

    while ( (minimum_vertex_index = dijkstra_array.min()) != -1 ){
        
        // Pobieram kolejnych sąsiadów. Sprawdzam czy z aktualnego wierzchołka
        // nie prowadzi do sąsiada niego droga o mniejszej wadze niż dotychczasowa. Jeżeli tak, to 
        // poprzednikiem sąsiada jest aktualny wierzchołek, a drogą do sąsiada jest ta, biegnąca przez rozważany wierzchołek.
        for(int i = 0; (edge = adjentency_lists[minimum_vertex_index][i]) != nullptr; i++){
            path_thourgh_current_vertex = edge->weigth + dijkstra_array[minimum_vertex_index]->weight;
            if(dijkstra_array[edge->end]->weight <= path_thourgh_current_vertex) continue;

            dijkstra_array[edge->end]->weight = path_thourgh_current_vertex;
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
    bf_array[start]->weight = 0;

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
            if(bf_array[edge->begin]->weight == INFINITY) continue;
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