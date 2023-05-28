#include "examinations/Examination.h"
#include "app/utility/Console.h"
#include <string>

PhaseGraphData Examination::phase_graphs[Examination::PHASE_COUNT];

Examination::Examination(){

    // Iniclaizacja grafu
    graph = nullptr;

    // Wczytanie nazwy pliku wynikowego
    output_file = Console::getInput("Wprowadz nazwe pliku, do ktorego zotana zapisane wyniki:");

    // Ustalenie początkowej fazy badania
    phase = -1;

    // Ustalenie danych na temat badanych w poszczególnych fazach grafów
    int8_t p = 0;

                        /* ### macierzowe ### */
    phase_graphs[p] = PhaseGraphData(MATRIX,    100,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    100,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    100,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    100,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(MATRIX,    200,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    200,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    200,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    200,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(MATRIX,    300,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    300,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    300,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    300,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(MATRIX,    400,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    400,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    400,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    400,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(MATRIX,    500,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    500,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    500,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(MATRIX,    500,    0.99); p++;

                        /* ### listowe ### */
    phase_graphs[p] = PhaseGraphData(LIST,    100,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    100,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    100,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    100,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(LIST,    200,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    200,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    200,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    200,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(LIST,    300,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    300,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    300,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    300,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(LIST,    400,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    400,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    400,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    400,    0.99); p++;

    phase_graphs[p] = PhaseGraphData(LIST,    500,    0.25); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    500,    0.50); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    500,    0.75); p++;
    phase_graphs[p] = PhaseGraphData(LIST,    500,    0.99); p++;

}

Examination::~Examination(){

    if(graph != nullptr)
        delete graph;

}

#include "app/utility/FileWriter.h"
bool Examination::saveResults(){

    if(results.size() == 0) return false;
    string final_output_file =  output_file +
                                "-" + to_string(results[0].graph_data.verticies_count) + 
                                "-" + to_string((int)(results[0].graph_data.density * 100)) + 
                                "-" + ( results[0].graph_data.representation == MATRIX ? "matrix" : "list" ) +
                                ".csv";

    vector<string> lines(results.size()+1);
    lines[0] = "Algorytm, Reprezentacja, Wierzcholki, Gestosc, Czas";
    for(int i = 1; i < lines.size(); i++) lines[i] = results[i-1].toString();

    if(!FileWriter::save(lines, final_output_file)){
        cout << "Nastapil blad przy zapisywaniu wynikow badania!" << endl;
        return false;
    }
    cout << "Zapisano " << results.size() << " wynikow do pliku " << final_output_file << "!" << endl;
    results.clear();
    return true;

}

string ExaminationRecord::toString(){

    // Inicalizacja reprezentacji alfanumerycznej
    string string_representation = "";

    // Typ algorytmu
    switch (algorithm){
        // Prim
        case PRIM: string_representation += "P"; break;
        // Dijkstra
        case DIJKSTRA: string_representation += "D"; break;
        // Kruskal
        case KRUSKAL: string_representation += "K"; break;
        // Bellman-Ford
        case BELLMAN_FORD: string_representation += "BF"; break;
    }

    // Reprezentacja grafu
    switch (graph_data.representation){
        // Prim
        case MATRIX: string_representation += ",M"; break;
        // Dijkstra
        case LIST: string_representation += ",L"; break;
    }

    // Liczba wierzchołków
    string_representation += "," + to_string(graph_data.verticies_count);

    // Gęstość
    string_representation += "," + to_string(graph_data.density);

    // Czas
    string_representation += "," + to_string(time);

    return string_representation;

}

bool Examination::next_phase(){

    // Zapisanie wyniku poprzedniej fazy
    saveResults();

    // Przejście do kolejnej fazy
    phase++;

    // Sprawdzenie, czy wykonano już wszystkie fazy badania
    if(phase >= PHASE_COUNT) return false;
    return true;

}

#include "app/utility/Menu.h"
void Examination::examineAlgorithm(){

    // Ustalam algorytm rozważany w badaniu
    AlgorithmType algorithm;
    Menu menu("WYBIERZ ALGORYTM DO PRZEBADNAIA:");
    menu.addOption(PRIM, "Algorytm Prima");
    menu.addOption(KRUSKAL, "Algorytm Kruskala");
    menu.addOption(DIJKSTRA, "Algorytm Dijkstry");
    menu.addOption(BELLMAN_FORD, "Algorytm Bellmana-Forda");
    int user_choice = menu.getUserChoice();
    if(user_choice > BELLMAN_FORD && user_choice < 0) {
        cout << "Wybrano niepoprawna opcje!" << endl;
        Console::waitForUserResponse();
        return;
    }
    algorithm = (AlgorithmType) user_choice;

    // Przechodzimy przez wszystkie fazy badania
    while (next_phase()) {
        
        // Informacja dla użytkownika o aktualnej fazie
        cout << "Faza " << (int)phase << "/" << (int)PHASE_COUNT << "...\t\t ";

        // Dla każdej fazy wykonujemy 100 prób
        for(int i = 0; i < 100; i++){

            // Badanie określonego algorytmu
            switch (algorithm){
                case PRIM:          examinePrim();          break;
                case KRUSKAL:       examineKruskal();       break;
                case DIJKSTRA:      examineDijkstra();      break;
                case BELLMAN_FORD:  examineBellmanFord();   break;
            }

            // Informacja o postępie (co 10 istancji)
            if(i % 9 == 0) cout << "#";

        }
        cout << "\t";

    }

    // Koniec badania
    cout << "Badanie zakonczone!" << endl;
    Console::waitForUserResponse();

}

void Examination::examineBellmanFord(){

    // Generowanie grafu
    generateGraph(true, false);

    // Losowanie wierzchołka początkowego
    int start = RandomNumberGenerator::getIntegers(1, 0, graph->verticiesCount()-1)[0];

    // Pomiar
    timer.start();
    graph->algorithmBellmanFord(start);
    timer.stop();

    // Wytworzenie wyniku
    results.push_back(ExaminationRecord(
        PRIM,
        phase_graphs[phase].representation,
        phase_graphs[phase].verticies_count,
        phase_graphs[phase].density,
        timer.getResult(microseconds)
    ));

}

void Examination::examineDijkstra(){

    // Generowanie grafu
    generateGraph(true, true);

    // Losowanie wierzchołka początkowego
    int start = RandomNumberGenerator::getIntegers(1, 0, graph->verticiesCount()-1)[0];

    // Pomiar
    timer.start();
    graph->algorithmDijkstra(start);
    timer.stop();

    // Wytworzenie wyniku
    results.push_back(ExaminationRecord(
        PRIM,
        phase_graphs[phase].representation,
        phase_graphs[phase].verticies_count,
        phase_graphs[phase].density,
        timer.getResult(microseconds)
    ));

}

void Examination::examinePrim(){

    // Generowanie grafu
    generateGraph(false, false);

    // Losowanie wierzchołka początkowego
    int start = RandomNumberGenerator::getIntegers(1, 0, graph->verticiesCount()-1)[0];

    // Pomiar
    timer.start();
    graph->alogrithmPrim(start);
    timer.stop();

    // Wytworzenie wyniku
    results.push_back(ExaminationRecord(
        PRIM,
        phase_graphs[phase].representation,
        phase_graphs[phase].verticies_count,
        phase_graphs[phase].density,
        timer.getResult(microseconds)
    ));

}

void Examination::examineKruskal(){

    // Generowanie grafu
    generateGraph(false, false);

    // Pomiar
    timer.start();
    graph->algorithmKruskal();
    timer.stop();

    // Wytworzenie wyniku
    results.push_back(ExaminationRecord(
        PRIM,
        phase_graphs[phase].representation,
        phase_graphs[phase].verticies_count,
        phase_graphs[phase].density,
        timer.getResult(microseconds)
    ));

}

void Examination::generateGraph(bool directed, bool not_negative){

    // Zwalniam dotychczasową instację grafu
    if(graph != nullptr){
        delete graph;
        graph = nullptr;
    }

    // Na podstawie aktualnej fazy badania tworzymy odpowiedni graf
    graph = GraphGenerator::generateGraph(
        phase_graphs[phase].representation,
        phase_graphs[phase].verticies_count,
        directed,
        phase_graphs[phase].density,
        not_negative
    );

}