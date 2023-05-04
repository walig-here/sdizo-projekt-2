#include "gtest/gtest.h"
#include "graphs/MatrixGraph.h"

// Sprawdzenie tworzenia macierzy o rozmiarze 0
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
    for(int i = 0; i < vertitices; i++)
        for(int j = 0; j < vertitices; j++)
            ASSERT_EQ(*graph.getAdjentancyMatrix()->get(i,j), elements[i * vertitices + j]);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
