#include <iostream>
#include "graphs/Graph.h"
#include <vector>
#include <list>


using namespace std;

// Klasa wczytująca zawartość plików
class FileReader{

    /* METODY */
    
    // Konstruktor
    private: FileReader() {}

    // Destruktor
    private: ~FileReader() {}

    /// @brief 
    /// Wczytuje zawartość wskazanego pliku i zwraca ją w postaci listy linii.
    /// W wypadku, gdy plik nie istnieje zwraca wskaźnik nullptr.
    ///
    /// @param file nazwa pliku, z którego wczytane zostaną linie
    ///
    /// @return 
    /// Listę pobranych linii lub wskaźnik nullptr, gdy plik jest pusty
    public: static list<string> readAllLines( const string file );


    // Wczytuje wszystkie liczby całowite z pliku
    public: static vector<int> readAllIntegers( string file );

    /**
     * @brief 
     * Wczytuje z pliku podstawowe dane nt grafu takie jak: liczba wierzchołków,
     * wierzchołek początkowy, wierzchołek końcowy, lista krawędzi. Zwracane są one do zadanych do metody
     * zmiennych. Jeżeli wystąpi błąd w odczycie danych, to wszystkie parametry wyjściowe
     * przyjmą wartość 0, a lista krawędzi będzie pusta.
     * 
     * @param file nazwa pliku, z którego wczytane zostaną linie
     * @param vetricies zmienna przechowująca liczbę wierzchołków
     * @param begin zmienna przechowująca wierzchołek początkowy
     * @param end zmienna przechowująca wierzchołek końcowy
     * 
     * @return Zwraca listę z danymi na temat 
     */
    public: static vector<EdgeData> readGraphData(string file, unsigned& vetricies, unsigned& begin, unsigned& end);

};