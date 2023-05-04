#include "app/utility/RandomNumberGenerator.h"
#include "app/utility/FileWriter.h"

vector<int> RandomNumberGenerator::getIntegers(long long unsigned count, long long int min, long long int max){

    // Sprawdzam, czy zadana ilość liczb jest niezerowa
    vector<int> list;
    if(count == 0) return list;

    // Dokonuję ewentualnej poprawki wybranego przedziału
    if(min > max) swap(min, max);

    // Generuję liczby
    random_device seed;
    mt19937 generator(seed());
    uniform_int_distribution<> distribution(min, max);

    for(int i = 0; i < count; i++) list.push_back(distribution(generator));
    return list;

}

bool RandomNumberGenerator::generateThenSaveIntegers(string file, long long unsigned count, long long int min, long long int max){

    vector<int> integers = getIntegers(count, min, max);
    if(integers.size() == 0) return false;
    integers.insert(integers.begin(), count);
    if(FileWriter::saveInt(integers, file)) return true;
    return false;

}