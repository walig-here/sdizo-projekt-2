#include <iostream>
#include <list>

using namespace std;

// Klasa wyłuskująca z ciągu znaków pojedyńcze wyrazy
class StringParser{

    /* METODY */

    // Konstruktor
    private: StringParser() {};

    // Destrutkor
    private: ~StringParser() {};

    /// @brief
    /// Wydziela z ciągu znaków pojedyńcze wyrazy.
    ///
    /// @param to_parse ciąg znaków, z którego będziemy wydzielać wyrazy
    ///
    /// @return
    /// Listę wydzielonych wyrazów lub pustą listę w wypadku podania pustego ciągu znaków.
    public: static list<string> parse(string to_parse);


    /// @brief
    /// Wydziela z ciągu znaków wszystkie liczby całkowite
    ///
    /// @param to_parse ciąg znaków, z którego zostaną wydzielone liczby
    ///
    /// @return
    /// Tablicę wydzielonych liczb całkowitych zawartych w zadanym ciągu lub pustą listę w wypadku
    /// podania pustego ciągu znaków bądź ciągu niezawierającego żadnych liczb całkowitych.
    public: static list<int> parseInt(string to_parse);

};