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

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
