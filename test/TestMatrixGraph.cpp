#include "gtest/gtest.h"
#include "graphs/MatrixGraph.h"

// Sprawdzenie tworzenia grafu o 5 wierzchołkach
TEST(CreateGraph, FiveVertex){

    int elements[] = {
        NO_CONNECTION,  NO_CONNECTION,  1,              8,              NO_CONNECTION,
        NO_CONNECTION,  NO_CONNECTION,  NO_CONNECTION,  -4,             NO_CONNECTION,
        1,              NO_CONNECTION,  NO_CONNECTION,  NO_CONNECTION,  NO_CONNECTION,
        8,              -4,             NO_CONNECTION,  NO_CONNECTION,  6,
        NO_CONNECTION,  NO_CONNECTION,  NO_CONNECTION,  6,              NO_CONNECTION
    };
    vector<EdgeData> edges = {
        EdgeData(1, 3, -4),
        EdgeData(3, 0, 8),
        EdgeData(0, 2, 1),
        EdgeData(3, 4, 6)
    };
    unsigned vertitices = 5;
    MatrixGraph graph(vertitices, edges, false);

    // Sprawdzenie
    ASSERT_EQ(graph.isNull(), false);
    ASSERT_EQ(graph.verticiesCount(), vertitices);
    for(int i = 0; i < vertitices; i++)
        for(int j = 0; j < vertitices; j++)
            ASSERT_EQ(*graph.getAdjentancyMatrix()->get(i,j), elements[i * vertitices + j]);

}

// Sprawdzenie towrzenia grafu z zadaniem krawędzi, która nie istnieje
TEST(CreateGraph, EdgesDontExist){

    int elements[] = {
        NO_CONNECTION,  3,              11,
        3,              NO_CONNECTION,  0,
        11,             0,              NO_CONNECTION
    };
    vector<EdgeData> edges = {
        EdgeData(0, 1, 3),
        EdgeData(1, 2, 0),
        EdgeData(2, 0, 11),

        EdgeData(1, 5, 23),
        EdgeData(6, 7, 2)
    };
    unsigned vertitices = 3;
    MatrixGraph graph(vertitices, edges, false);

    // Sprawdzenie
    ASSERT_EQ(graph.isNull(), false);
    ASSERT_EQ(graph.verticiesCount(), vertitices);
    for(int i = 0; i < vertitices; i++)
        for(int j = 0; j < vertitices; j++)
            ASSERT_EQ(*graph.getAdjentancyMatrix()->get(i,j), elements[i * vertitices + j]);
}

// Tworzenie grafu, którego ilość wierzchołków ustalono na 0 (graf pusty)
TEST(CreateGraph, NullGraph){

    vector<EdgeData> edges = {
        EdgeData(0, 1, 3)
    };
    MatrixGraph graph(0, edges, false);

    // Sprawdzenie
    ASSERT_EQ(graph.isNull(), true);
    ASSERT_EQ(graph.verticiesCount(), 0);

}

// Algorytm Prima
TEST(Prim, FiveVertexGraph){

    // Inicjalizacja grafu
    vector<EdgeData> edges = {
        EdgeData(0,1,10),
        EdgeData(0,3,1),
        EdgeData(1,3,4),
        EdgeData(1,4,8),
        EdgeData(4,3,13),
        EdgeData(3,2,1)
    };
    unsigned verticies = 5;
    unsigned start = 0;
    MatrixGraph graph(verticies, edges, false);

    // Wykonanie algorytmu
    MSTResult result = graph.alogrithmPrim(start);

    // Sprawdzenie
    ASSERT_EQ(result.getMST(), 14);

    vector<EdgeData> mst_proper_edges = {
        EdgeData(0, 3, 1),
        EdgeData(1, 3, 4),
        EdgeData(1, 4, 8),
        EdgeData(2, 3, 1)
    };
    vector<EdgeData> mst_edges = result.getEdges();
    bool found;
    for(auto proper_edge : mst_proper_edges){
        found = false;
        for(auto edge : mst_edges){
            if(proper_edge.begin == edge.begin && proper_edge.end == edge.end && proper_edge.weigth == edge.weigth){
                found = true;
                break;
            }
        }
        ASSERT_TRUE(found);
    }

}

TEST(Prim, EmptyGraph){

    MatrixGraph graph(0, {}, false);
    MSTResult result = graph.alogrithmPrim(0);
    ASSERT_TRUE(result.isEmpty());

}

// Algorytm Dijkstry
TEST(Dijkstra, FiveVertexGraph){

    // Inicjalizacja grafu
    vector<EdgeData> edges = {
        EdgeData(0,1,15),
        EdgeData(2,0,5),
        EdgeData(1,2,2),
        EdgeData(2,4,3),
        EdgeData(4,2,1),
        EdgeData(1,3,4),
        EdgeData(3,1,25),
        EdgeData(3,4,10),
        EdgeData(4,3,2)
    };
    unsigned v = 5;
    unsigned start = 3;
    MatrixGraph graph(v, edges, true);

    // Wykonanie algorytmu
    PathfindingResult result = graph.algorithmDijkstra(start);

    // Sprawdzenie
    vector<VertexData> verticies(5);
    verticies[0].weight = 16;           verticies[0].predecessor = 2;           verticies[0].processed = true;
    verticies[1].weight = 25;           verticies[1].predecessor = 3;           verticies[1].processed = true;
    verticies[2].weight = 11;           verticies[2].predecessor = 4;           verticies[2].processed = true;
    verticies[3].weight = 0;            verticies[3].predecessor = NULL_VERTEX; verticies[3].processed = true;
    verticies[4].weight = 10;           verticies[4].predecessor = 3;           verticies[4].processed = true;
    DynamicArray<VertexData> dijkstra_array(verticies); 
    PathfindingResult proper_result(dijkstra_array, start);

    for(int i = 0; i < v; i++){

        if(i == start) continue;
        ASSERT_EQ(result.getPathTo(i).getDistance(), proper_result.getPathTo(i).getDistance());
        ASSERT_EQ(result.getPathTo(i).getVerticies().size(), proper_result.getPathTo(i).getVerticies().size());

        for(int j = 0; j < result.getPathTo(i).getVerticies().size(); j++)
            ASSERT_EQ(result.getPathTo(i).getVerticies()[j], proper_result.getPathTo(i).getVerticies()[j]);

    }

}

// Zwracanie listy krawędzi
TEST(GetEdgeList, FiveVertexGraphNonDirected){

    // Stworzenie grafu
    vector<EdgeData> edges = {
        EdgeData(0,4,4),
        EdgeData(4,1,6),
        EdgeData(1,2,7),
        EdgeData(2,0,5),
        EdgeData(2,4,2),
        EdgeData(2,3,1),
        EdgeData(3,4,3)
    };
    unsigned verticies = 5;
    MatrixGraph graph(verticies, edges, false);

    // Pobranie listy
    DynamicArray<EdgeData> edges_from_graph = graph.getEdgesList(false);

    // Sprawdzenie
    ASSERT_EQ(edges.size(), edges_from_graph.getLength());
    bool found;
    for(int i = 0; i < edges_from_graph.getLength(); i++){
        found = false;
        for(auto edge : edges){
            if(edge.begin != edges_from_graph[i]->begin && edge.begin != edges_from_graph[i]->end) continue;
            if(edge.end != edges_from_graph[i]->end && edge.end != edges_from_graph[i]->begin) continue;
            if(edge.weigth != edges_from_graph[i]->weigth) continue;
            found = true;
            break;
        }
        ASSERT_TRUE(found);
    }

}

TEST(GetEdgeList, FiveVertexGraphDirected){

    // Stworzenie grafu
    vector<EdgeData> edges = {
        EdgeData(0,4,4),
        EdgeData(4,1,6),
        EdgeData(1,2,7),
        EdgeData(2,0,5),
        EdgeData(2,4,2),
        EdgeData(2,3,1),
        EdgeData(3,4,3)
    };
    unsigned verticies = 5;
    MatrixGraph graph(verticies, edges, true);

    // Pobranie listy
    DynamicArray<EdgeData> edges_from_graph = graph.getEdgesList(true);

    // Sprawdzenie
    ASSERT_EQ(edges.size(), edges_from_graph.getLength());
    bool found;
    for(int i = 0; i < edges_from_graph.getLength(); i++){
        found = false;
        for(auto edge : edges){
            if(edge.begin != edges_from_graph[i]->begin) continue;
            if(edge.end != edges_from_graph[i]->end) continue;
            if(edge.weigth != edges_from_graph[i]->weigth) continue;
            found = true;
            break;
        }
        ASSERT_TRUE(found);
    }

}

TEST(GetEdgeList, EmptyGraph){

    MatrixGraph graph(2, {}, true);
    ASSERT_EQ(graph.getEdgesList(true).getLength(), 0);

    MatrixGraph graph1(2, {}, false);
    ASSERT_EQ(graph1.getEdgesList(false).getLength(), 0);

}

// Algorytm Bellmana-Forda
TEST(BellmanFord, FiveVertexGraph){

    // Tworzenie grafu
    vector<EdgeData> edges = {
        EdgeData(0,2,2),
        EdgeData(2,0,-1),
        EdgeData(0,1,10),
        EdgeData(1,3,-1),
        EdgeData(3,2,11)
    };
    unsigned v = 4;
    MatrixGraph graph(v, edges, true);
    unsigned start = 2;

    // Wykonanie algorytmu
    PathfindingResult result = graph.algorithmBellmanFord(start);

    // Sprawdzenie
    vector<VertexData> verticies(5);
    verticies[0].weight = -1;           verticies[0].predecessor = 2;           
    verticies[1].weight = 9;            verticies[1].predecessor = 0;           
    verticies[2].weight = 0;            verticies[2].predecessor = NULL_VERTEX;           
    verticies[3].weight = 8;            verticies[3].predecessor = 1;      
    DynamicArray<VertexData> bf_array(verticies); 
    PathfindingResult proper_result(bf_array, start);

    for(int i = 0; i < v; i++){

        if(i == start) continue;
        ASSERT_EQ(result.getPathTo(i).getDistance(), proper_result.getPathTo(i).getDistance());
        ASSERT_EQ(result.getPathTo(i).getVerticies().size(), proper_result.getPathTo(i).getVerticies().size());

        for(int j = 0; j < result.getPathTo(i).getVerticies().size(); j++)
            ASSERT_EQ(result.getPathTo(i).getVerticies()[j], proper_result.getPathTo(i).getVerticies()[j]);

    }

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
