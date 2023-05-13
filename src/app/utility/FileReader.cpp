
#include <string>
#include <fstream>

#include "app/utility/FileReader.h"
#include "app/utility/StringParser.h"

list<string> FileReader::readAllLines( const string file_name ){

    // Sprawdzam, czy plik istnieje
    list<string> list;
    fstream file(file_name);
    if(!file.good()) 
        return list;

    // Wczytuję kolejne linie
    string line; 
    while( getline( file, line ) && !file.fail() ) list.push_back(line);

    // Zamykam plik
    file.close();
    return list;

}


vector<int> FileReader::readAllIntegers( string file ){
    
    // Wczytuję dane z pliku
    list<string> lines = readAllLines(file);
    vector<int> integers;
    if(lines.size() == 0) return integers;

    // Wydzielam z poszczególnych linii kolejne liczby całkowite
    vector<int> line_integers;
    for(auto line : lines){
        
        line_integers = StringParser::parseInt(line);
        if(line_integers.size() == 0) continue;

        // Wczytuje tyle liczb ile wynosi amount
        for(auto integer : line_integers) {
            integers.push_back(integer);
        }
        line_integers.clear();

    }
    return integers;

}

vector<EdgeData> FileReader::readGraphData(string file, unsigned& vetricies, unsigned& begin, unsigned& end){

    // Wczytuję dane z pliku
    list<string> lines = readAllLines(file);
    if(lines.size() == 0) {
        vetricies = begin = end = 0;
        return vector<EdgeData>();
    }

    // Z pierwszej linii wczytuję kolejno:
    // - liczbę wierzchołków
    // - liczbę krawędzi
    // - wierzchołek początkowy
    // - wierzchołek końcowy
    // Jeżeli linia nie zawiera tych danych, to uznajemy ją za niepoprawną
    unsigned edges_amount = 0;
    vector<int> line_integers = StringParser::parseInt(lines.front());
    if(line_integers.size() < 4){
        vetricies = begin = end = 0;
        return vector<EdgeData>();
    }

    vetricies = line_integers[0];    
    begin = line_integers[2];
    end = line_integers[3];
    edges_amount = line_integers[1];

    // Z kolejnych linii wczytujemy informacje na temat krawędzi:
    // - początek
    // - koniec
    // - wagę
    // Jeżeli linia nie zawiera tych danych, to uznajemy ją za niepoprawną
    vector<EdgeData> edges;
    for(auto line = ++lines.begin(); edges_amount > 0 && line != lines.end(); line++){
        line_integers = StringParser::parseInt(*line);
        if(line_integers.size() < 3){
            vetricies = begin = end = 0;
            return vector<EdgeData>();
        }

        edges.push_back(EdgeData(line_integers[0], line_integers[1], line_integers[2]));
        edges_amount--;
    }
    return edges;

}