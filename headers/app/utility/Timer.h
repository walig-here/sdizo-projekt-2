#include <iomanip>

enum TimeUnits{
    miliseconds,
    microseconds,
    seconds
};

// "Stoper" służący do pomiaru czasów wykonywania framentów kodu
class Timer{

    /* POLA */
    private: long long int last_start;              // ostatni moment uruchomienia stopera
    private: long long int last_result;             // ostatni wynik pomiaru
    private: long long int frequency;               // częstotliwość taktowania procesora

    /* METODY */

    // Konstruktor
    public: Timer();

    // Destruktor
    public: ~Timer();

    // Rozpoczęcie odliczania zegara
    public: void start();

    // Zakończenie odliczania zegara
    public: void stop();

    // Pobranie wyniku
    public: double getResult(TimeUnits unit);

};