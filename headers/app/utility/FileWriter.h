#include <vector>
#include <iostream>

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

};
