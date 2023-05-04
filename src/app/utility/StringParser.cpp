#include "app/utility/StringParser.h"

#include <sstream>

list<string> StringParser::parse(string to_parse){

    // Sprawdzam, czy ciąg znaków nie jest pusty
    list<string> words;
    if(to_parse == "") return words;

    // Pobieram kolejne wyrazy z ciągu znaków
    istringstream parser(to_parse);
    string word;
    while( parser >> word ) words.push_back(word);
    return words;

}

list<int> StringParser::parseInt(string to_parse){

    // Spośród wyrazów zawartych w ciągu znaków wybieram te, które są liczbami całkowitymi
    list<string> words = parse(to_parse);
    list<int> integers; 
    if(words.size() == 0) return integers;

    
    for(auto word : words){
        try{
            integers.push_back( stoi(word) );
        }catch(invalid_argument){
            continue;
        }
    }
    return integers;

}