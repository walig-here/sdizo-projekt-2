#include "app/utility/GraphGenerator.h"
#include "app/utility/Timer.h"

/**
 * @brief 
 * Typy algorytmów
 */
enum AlgorithmType{
    PRIM,
    KRUSKAL,
    DIJKSTRA,
    BELLMAN_FORD
};


/**
 * @brief 
 * Struktura zawierająca dane na temat grafu badanego w danej fazie badania.
 */
struct PhaseGraphData{

    /* POLA */
    GraphRepresentations representation;    // typ reprezentacji grafu używanego w trakcie badania
    unsigned verticies_count;               // liczba wierzchołków grafu używanego w trakcie badania
    float density;                          // gęstość grafu używanego w trakcie badania

    /* METODY */

    /**
     * @brief 
     * Konstruktor.
     */
    PhaseGraphData(GraphRepresentations representation, unsigned verticies_count, float density){
        this->representation = representation;
        this->verticies_count = verticies_count;
        this->density = density;
    }

    /**
     * @brief 
     * Konstruktuor domyślny
     */
    PhaseGraphData() {};

};


/**
 * @brief 
 * Struktura przechowująca rekord wynikowego pliku *.csv, zawierającego dane na temat złożoności
 * badanego algorytmu.
 */
struct ExaminationRecord{

    /* POLA */
    AlgorithmType algorithm;                // badany algorytm
    PhaseGraphData graph_data;              // dane o grafie, użytym w trakcie badania
    double time;                            // zmierzony czas

    /* METODY */

    /**
     * @brief 
     * Konstrutkor
     */
    ExaminationRecord(AlgorithmType algorithm, GraphRepresentations representation, unsigned verticies_count, float density, double time){
        this->algorithm = algorithm;
        this->time = time;

        graph_data.representation = representation;
        graph_data.verticies_count = verticies_count;
        graph_data.density = density;
    }

    /**
     * @brief 
     * Konwersja na typ string.
     */
    string toString();

};


/**
 * @brief 
 * Klasa bazowa dla modułów badających algorytmy grafowe.
 */
class Examination{

    /* POLA */
    private: string output_file;                                // ścieżka do pliku zawierającego wyniki
    private: Graph* graph;                                      // graf, na którym zostaną wykonane badania
    private: Timer timer;                                       // narzędzie do pomiaru czasu
    private: vector<ExaminationRecord> results;                 // pula danych zebrana dotychczas podczas badań
    private: int8_t phase;                                      // aktualna faza badania
    private: const static int8_t PHASE_COUNT = 40;              // łączna ilość faz badania
    private: static PhaseGraphData phase_graphs[PHASE_COUNT];   // dane na temat grafów badanych w poszczegółnych fazach

    /* METODY */

    /**
     * @brief 
     * Konstruktor. Służy do inicjalizacji podstawowych parametrów badania.
     */
    public: Examination();


    /**
     * @brief 
     * Destruktor.
     */
    public: ~Examination();


    /**
     * @brief 
     * Zapisuje wyniki badania do odpowiedniego pliku csv. Po zapisaniu wyników czyści
     * wektor z wynikami (results). 
     */
    private: bool saveResults();


    /**
     * @brief 
     * Przenosi badanie do kolejnej fazy. Zapisuje przy tym również wyniki z fazy poprzedniej.
     * W wypadku, gdy badanie było w ostatniej fazie i nie może już przejśc do kolejnej, zwrócony
     * zostanie fałsz. W przeciwnym razie zwracana jest prawda.
     */
    private: bool next_phase();


    /**
     * @brief 
     * Tworzy instancję grafu odpowiednią dla aktualnej fazy badania.
     * 
     * @param directed czy graf ma być skierowany
     * @param not_negative czy graf ma zawierać wyłącznie nieujemne krawędzie?
     */
    private: void generateGraph(bool directed, bool not_negative);


    /**
     * @brief 
     * Metoda przeprowadzająca właściwe badania.
     */
    public: void examineAlgorithm();

    /**
     * @brief 
     * Badanie algorytmu Prima.
     */
    private: void examinePrim();

    /**
     * @brief 
     * Badanie algorytmu Kruskala.
     */
    private: void examineKruskal();

    /**
     * @brief 
     * Badanie algorytmu Dijkstry.
     */
    private: void examineDijkstra();

    /**
     * @brief 
     * Badanie algorytmu Bellmana-Forda.
     */
    private: void examineBellmanFord();

};