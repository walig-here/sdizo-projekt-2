#include "gtest/gtest.h"
#include "app/utility/SortingMachine.h"

// Sortowanie tablicy krawędzi
TEST(SortEdges, SevenEdges){

    // Tworzenie tablicy krawędzi
    vector<EdgeData> edges = {
        EdgeData(4, 0, 1),
        EdgeData(0, 2, 1),
        EdgeData(0, 1, 8),
        EdgeData(1, 4, 10),
        EdgeData(1, 3, 5),
        EdgeData(1, 2, -2),
        EdgeData(3, 4, 25)
    };
    DynamicArray<EdgeData> edge_array(edges);

    // Sortowanie
    SortingMachine::sort(edge_array, 0, edge_array.getLength()-1);

    // Sprawdzenie
    vector<EdgeData> sorted_array = {
        EdgeData(1, 2, -2),
        EdgeData(4, 0, 1),
        EdgeData(0, 2, 1),
        EdgeData(1, 3, 5),
        EdgeData(0, 1, 8),
        EdgeData(1, 4, 10),
        EdgeData(3, 4, 25)
    };

    ASSERT_EQ(sorted_array.size(), edge_array.getLength());
    for(int i = 0; i < edge_array.getLength(); i++)
        ASSERT_EQ(edge_array[i]->weigth, sorted_array[i].weigth);

}

// Sortowanie pustej tablicy krawędzi
TEST(SortEdges, Empty){

    // Tworzenie tablicy krawędzi
    vector<EdgeData> edges = {
        
    };
    DynamicArray<EdgeData> edge_array(edges);

    // Sortowanie
    SortingMachine::sort(edge_array, 0, edge_array.getLength()-1);

    // Sprawdzenie
    ASSERT_EQ(0, edge_array.getLength());

}

// Sortowanie pustej tablicy 1-elementowej
TEST(SortEdges, OneEdge){

    // Tworzenie tablicy krawędzi
    vector<EdgeData> edges = {
        EdgeData(1,1,1)
    };
    DynamicArray<EdgeData> edge_array(edges);

    // Sortowanie
    SortingMachine::sort(edge_array, 0, edge_array.getLength()-1);

    // Sprawdzenie
    ASSERT_EQ(1, edge_array.getLength());

}

// Sortowanie tablicy krawędzi (3-elementy)
TEST(SortEdges, TwoEdges){

    // Tworzenie tablicy krawędzi
    vector<EdgeData> edges = {
        EdgeData(4, 0, 4),
        EdgeData(0, 2, 8),
        EdgeData(0, 1, 1)
    };
    DynamicArray<EdgeData> edge_array(edges);

    // Sortowanie
    SortingMachine::sort(edge_array, 0, edge_array.getLength()-1);

    // Sprawdzenie
    vector<EdgeData> sorted_array = {
        EdgeData(0, 1, 1),
        EdgeData(4, 0, 4),
        EdgeData(0, 2, 8)
    };

    ASSERT_EQ(sorted_array.size(), edge_array.getLength());
    for(int i = 0; i < edge_array.getLength(); i++)
        ASSERT_EQ(edge_array[i]->weigth, sorted_array[i].weigth);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}