#include "gtest/gtest.h"
#include "app/utility/FileReader.h"

// Wczytanie danych o grafie
TEST(LoadGraph, ValidFileExist){

    unsigned vetricies, begin, end;
    vector<EdgeData> edges = FileReader::readGraphData("D:/Struktury Danych i Zlozonosc Obliczeniowa/sdizo-projekt-2/out/graph.txt", vetricies, begin, end);

    vector<EdgeData> proper_edges = {
        EdgeData(1, 1, 1),
        EdgeData(3, 0, 2),
        EdgeData(3, 4, 4),
        EdgeData(4, 1, 3),
        EdgeData(4, 2 ,5),
        EdgeData(2, 4, 6)
    };

    // Sprawdzenie
    ASSERT_EQ(vetricies, 5);
    ASSERT_EQ(begin, 0);
    ASSERT_EQ(end, 1);
    ASSERT_EQ(edges.size(), 6);

    for(int i = 0; i < edges.size(); i++){
        ASSERT_EQ(edges[i].begin, proper_edges[i].begin);
        ASSERT_EQ(edges[i].end, proper_edges[i].end);
        ASSERT_EQ(edges[i].weigth, proper_edges[i].weigth);
    }

}

// Wyczytywanie danych o grafie z nieistniejącego pliku
TEST(LoadGraph, FileDoesntExist){

    unsigned vetricies, begin, end;
    vector<EdgeData> edges = FileReader::readGraphData("sdadsadsa.txt", vetricies, begin, end);

    // Sprawdzenie
    ASSERT_EQ(vetricies, 0);
    ASSERT_EQ(begin, 0);
    ASSERT_EQ(end, 0);
    ASSERT_EQ(edges.size(), 0);

}

// Wyczytywanie danych o grafie z niepoprawnego pliku
TEST(LoadGraph, InvalidFile){

    unsigned vetricies, begin, end;
    vector<EdgeData> edges = FileReader::readGraphData("D:/Struktury Danych i Zlozonosc Obliczeniowa/sdizo-projekt-2/out/graph_1.txt", vetricies, begin, end);

    // Sprawdzenie
    ASSERT_EQ(vetricies, 0);
    ASSERT_EQ(begin, 0);
    ASSERT_EQ(end, 0);
    ASSERT_EQ(edges.size(), 0);

}

// Entry point modułu testującego klasę Arithmetic
int main(int argc, char const *argv[])
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}