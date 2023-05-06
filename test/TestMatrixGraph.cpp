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
    MatrixGraph graph(vertitices, edges);

    // Sprawdzenie
    ASSERT_EQ(graph.isNull(), false);
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
    MatrixGraph graph(vertitices, edges);

    // Sprawdzenie
    ASSERT_EQ(graph.isNull(), false);
    for(int i = 0; i < vertitices; i++)
        for(int j = 0; j < vertitices; j++)
            ASSERT_EQ(*graph.getAdjentancyMatrix()->get(i,j), elements[i * vertitices + j]);
}

// Tworzenie grafu, którego ilość wierzchołków ustalono na 0 (graf pusty)
TEST(CreateGraph, NullGraph){

    vector<EdgeData> edges = {
        EdgeData(0, 1, 3)
    };
    MatrixGraph graph(0, edges);

    // Sprawdzenie
    ASSERT_EQ(graph.isNull(), true);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
