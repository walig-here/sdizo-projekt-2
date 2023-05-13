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