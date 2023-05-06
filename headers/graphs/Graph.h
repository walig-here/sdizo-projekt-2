
/**
 * @brief 
 * Klasa reprezentująca graf o nieokreślonej reprezentacji.
 */
class Graph{

    /**
     * Wirtualny konstruktor domyślny.
     */
    protected: Graph() {};


    /**
     * Wirtualny destruktor. 
     */
    protected: ~Graph() {};


    /**
     * @brief 
     * Zwraca informacje, czy graf jest pusty.
     */
    public: virtual bool isNull() = 0;


    /**
     * @brief 
     * Wykonuje algorytm Kruskalla na grafie.
     */
    public: virtual void algorithmKruskal() = 0;


    /**
     * @brief 
     * Wykonuje algorytm Prima na grafie.
     */
    public: virtual void alogrithmPrim() = 0;


    /**
     * @brief 
     * Wykonuje algorytm Dijkstry na grafie.
     */
    public: virtual void algorithmDijkstra() = 0;


    /**
     * @brief 
     * Wynokuje algorytm Bellmana-Forda na grafie.
     */
    public: virtual void algorithmBellmanFord() = 0;

};


/**
 * @brief 
 * Struktura zawierająca dane na temat pojedynczej krawedzi
 */
struct EdgeData{

    /* POLA */
    unsigned begin;     // wierzchołek początkowy
    unsigned end;       // wierzchołek końcowy
    int weigth;         // waga krawędzi

    /* KONSTRUKTOR */
    EdgeData(unsigned begin, unsigned end, int weigth);

};