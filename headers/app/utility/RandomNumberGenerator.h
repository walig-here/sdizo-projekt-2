#include <random>
#include <list>

using namespace std;

class RandomNumberGenerator{

    /* POLA */

    /* METODY */

    // Konstruktor
    private: RandomNumberGenerator() {};

    // Destruktor
    private: ~RandomNumberGenerator() {};

    // Generuje zadaną ilość losowych liczb całkowitych z zadanego zakresu
    public: static vector<int> getIntegers(long long unsigned count, long long int min, long long int max);

    // Generuje i zapisuje zadaną ilość losowych liczb całkowitych z zadanego zakresu, a nastepnie
    // zapisuje je do pliku
    public: static bool generateThenSaveIntegers(string file, long long unsigned count, long long min, long long max);

};