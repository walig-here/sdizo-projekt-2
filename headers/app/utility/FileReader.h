#include <iostream>
#include <list>
#include <vector>

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

};