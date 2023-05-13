#include "gtest/gtest.h"
#include "graphs/ListGraph.h"

// Sprawdzenie tworzenia grafu o 5 wierzchołkach
TEST(Create, CrateFiveVertexGraph){

    unsigned verticies_count = 5;
    vector<List> proper_lists; proper_lists.resize(verticies_count);
    proper_lists[0].push_back(2,4); proper_lists[0].push_back(3,5);
    proper_lists[1].push_back(4,2); proper_lists[1].push_back(3,-3); proper_lists[1].push_back(2,-11);
    proper_lists[2].push_back(0,4); proper_lists[2].push_back(1,-11);
    proper_lists[3].push_back(0,5); proper_lists[3].push_back(1,-3);
    proper_lists[4].push_back(1,2);

    vector<EdgeData> edges = {
        EdgeData(0, 2, 4),
        EdgeData(2, 1, -11),
        EdgeData(1, 4, 2),
        EdgeData(0, 3, 5),
        EdgeData(1, 3, -3)
    };
    ListGraph graph(verticies_count, edges, false);

    // Sprawdzenie
    ASSERT_EQ(graph.verticiesCount(), 5);
    for(int i = 0; i < proper_lists.size(); i++){
        ASSERT_NE(graph.getAdjetencyList(i), nullptr);

        for(int j = 0; proper_lists[i][j] != nullptr; j++){
            ASSERT_NE(graph.getAdjetencyList(i)->find(proper_lists[i][j]->end, proper_lists[i][j]->weigth), nullptr);
        }
    }

}

// Sprawdzenie tworzenia grafu, do którego zadano krawędzie o niepoprawnych krańcach
TEST(Create, CreateWithInvalidEdges){

    unsigned verticies_count = 5;
    vector<List> proper_lists; proper_lists.resize(verticies_count);
    proper_lists[0].push_back(2,4); proper_lists[0].push_back(3,5);
    proper_lists[1].push_back(4,2); proper_lists[1].push_back(3,-3); proper_lists[1].push_back(2,-11);
    proper_lists[2].push_back(0,4); proper_lists[2].push_back(1,-11);
    proper_lists[3].push_back(0,5); proper_lists[3].push_back(1,-3);
    proper_lists[4].push_back(1,2);

    vector<EdgeData> edges = {
        EdgeData(0, 2, 4),
        EdgeData(2, 1, -11),
        EdgeData(1, 4, 2),
        EdgeData(0, 3, 5),
        EdgeData(1, 3, -3),

        EdgeData(33, 5, 5),
        EdgeData(0, 6, 5),
        EdgeData(11, 4, 56)
    };
    ListGraph graph(verticies_count, edges, false);

    // Sprawdzenie
    ASSERT_EQ(graph.verticiesCount(), 5);
    for(int i = 0; i < proper_lists.size(); i++){
        ASSERT_NE(graph.getAdjetencyList(i), nullptr);

        for(int j = 0; proper_lists[i][j] != nullptr; j++){
            ASSERT_NE(graph.getAdjetencyList(i)->find(proper_lists[i][j]->end, proper_lists[i][j]->weigth), nullptr);
        }
    }

    ASSERT_EQ(graph.getAdjetencyList(33), nullptr);
    ASSERT_EQ(graph.getAdjetencyList(11), nullptr);
    ASSERT_EQ(graph.getAdjetencyList(6), nullptr);
    ASSERT_EQ(graph.getAdjetencyList(5), nullptr);

    ASSERT_EQ(graph.getAdjetencyList(0)->find(6, 5), nullptr);
    ASSERT_EQ(graph.getAdjetencyList(4)->find(11, 56), nullptr);

}

// Sprawdzenie tworzenia grafu pustego
TEST(Create, EmptyGraph){

    vector<EdgeData> edges = {
        EdgeData(0, 2, 4),
        EdgeData(2, 1, -11),
        EdgeData(1, 4, 2),
        EdgeData(0, 3, 5),
        EdgeData(1, 3, -3),

        EdgeData(33, 5, 5),
        EdgeData(0, 6, 5),
        EdgeData(11, 4, 56)
    };
    ListGraph graph(0, edges, false);

    // Sprawdzenie
    ASSERT_TRUE(graph.isNull());
    ASSERT_EQ(graph.verticiesCount(), 0);

}

// Sprawdzenie tworzenia grafu skierowanego o 5 wierzchołkach
TEST(CreateDirected, CrateFiveVertexGraph){

    unsigned verticies_count = 5;
    vector<List> proper_lists; proper_lists.resize(verticies_count);
    proper_lists[1].push_back(1,1);
    proper_lists[2].push_back(4,6);
    proper_lists[3].push_back(0,2); proper_lists[3].push_back(4,4);
    proper_lists[4].push_back(1,3); proper_lists[4].push_back(2,5);

    vector<EdgeData> edges = {
        EdgeData(1, 1, 1),
        EdgeData(3, 0, 2),
        EdgeData(3, 4, 4),
        EdgeData(4, 1, 3),
        EdgeData(4, 2, 5),
        EdgeData(2, 4, 6)
    };
    ListGraph graph(verticies_count, edges, true);

    // Sprawdzenie
    ASSERT_EQ(graph.verticiesCount(), 5);
    for(int i = 0; i < proper_lists.size(); i++){
        if(proper_lists[i].front() != nullptr) ASSERT_NE(graph.getAdjetencyList(i), nullptr);

        for(int j = 0; proper_lists[i][j] != nullptr; j++){
            ASSERT_NE(graph.getAdjetencyList(i)->find(proper_lists[i][j]->end, proper_lists[i][j]->weigth), nullptr);
        }
    }

}

// Sprawdzenie tworzenia grafu skierowanego z zadaniem niepoprawnych krawędzi
TEST(CreateDirected, CrateInvalidEdges){

    unsigned verticies_count = 5;
    vector<List> proper_lists; proper_lists.resize(verticies_count);
    proper_lists[1].push_back(1,1);
    proper_lists[2].push_back(4,6);
    proper_lists[3].push_back(0,2); proper_lists[3].push_back(4,4);
    proper_lists[4].push_back(1,3); proper_lists[4].push_back(2,5);

    vector<EdgeData> edges = {
        EdgeData(1, 1, 1),
        EdgeData(3, 0, 2),
        EdgeData(3, 4, 4),
        EdgeData(4, 1, 3),
        EdgeData(4, 2, 5),
        EdgeData(2, 4, 6),

        EdgeData(33, 5, 5),
        EdgeData(0, 6, 5),
        EdgeData(11, 4, 56)
    };
    ListGraph graph(verticies_count, edges, true);

    // Sprawdzenie
    ASSERT_EQ(graph.verticiesCount(), 5);
    for(int i = 0; i < proper_lists.size(); i++){
        if(proper_lists[i].front() != nullptr) ASSERT_NE(graph.getAdjetencyList(i), nullptr);

        for(int j = 0; proper_lists[i][j] != nullptr; j++){
            ASSERT_NE(graph.getAdjetencyList(i)->find(proper_lists[i][j]->end, proper_lists[i][j]->weigth), nullptr);
        }
    }

    ASSERT_EQ(graph.getAdjetencyList(33), nullptr);
    ASSERT_EQ(graph.getAdjetencyList(11), nullptr);
    ASSERT_EQ(graph.getAdjetencyList(0), nullptr);

}

// Sprawdzenie tworzenia grafu pustego
TEST(CreateDirected, EmptyGraph){

    vector<EdgeData> edges = {
        EdgeData(0, 2, 4),
        EdgeData(2, 1, -11),
        EdgeData(1, 4, 2),
        EdgeData(0, 3, 5),
        EdgeData(1, 3, -3)
    };
    ListGraph graph(0, edges, true);

    // Sprawdzenie
    ASSERT_TRUE(graph.isNull());
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
    ListGraph graph(verticies, edges, false);

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

    ListGraph graph(0, {}, false);
    MSTResult result = graph.alogrithmPrim(0);
    ASSERT_TRUE(result.isEmpty());

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}