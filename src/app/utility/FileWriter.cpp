#include "app/utility/FileWriter.h"

#include <fstream>

bool FileWriter::saveInt(vector<int> integers, string file_name){

    // Próbujemy stworzyć plik, do którego zapiszemy nasze liczby
    fstream file;
    file.open(file_name, ios::out);
    if(!file.good()) return false;

    // Zapisujemy
    int p = 0;
    for(auto integer : integers){
        file << integer << " ";
        if(p%100 == 99) file << "\n";
        p++;
    }
    file.close();

    return true;
}

bool FileWriter::save(vector<string> lines, string file_name){

    // Próbujemy stworzyć plik, do którego zapiszemy nasze liczby
    fstream file;
    file.open(file_name, ios::out|ios::app);
    if(!file.good()) return false;

    // Zapisujemy
    for(auto line : lines) file << line << endl;
    file.close();

    return true;

}

bool FileWriter::saveGraph(string file_name, int verticies, int start, int end, DynamicArray<EdgeData> edges){

    // Próbujemy stworzyć plik, do którego zapiszemy nasze liczby
    fstream file;
    file.open(file_name, ios::out);
    if(!file.good()) return false;

    // Zapisujemy
    file << verticies << " " << edges.getLength() << " " << start << " " << end << endl;
    for(int i = 0; i < edges.getLength(); i++)
        file << edges[i]->begin << " " << edges[i]->end << " " << edges[i]->weigth << endl;


    // Koniec
    file.close();
    return true;

}