#include <vector>
#include <iostream>

#include "graphs/Graph.h"

using namespace std;

// Klasa służąca do zapisu danych do pliku
class FileWriter{

    /* METODY */

    // Konstruktor
    private: FileWriter() {}

    // Destruktor
    private: ~FileWriter() {}

    // Zapisuje dane liczbowe do pliku
    public: static bool saveInt(vector<int> integers, string file);

    // Zapisuje dane alfanumeryczne do pliku
    public: static bool save(vector<string> lines, string file);

    // Zapisuje graf do pliku
    public: static bool saveGraph(string file_name, int verticies, int start, int end, DynamicArray<EdgeData> edges);

};
