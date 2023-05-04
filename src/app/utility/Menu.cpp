#include <string.h>

#include "app/utility/Menu.h"
#include "app/utility/Console.h"

Menu::Menu(string header){

    this->header = header;

}


Menu::~Menu(){

    // Czyszczenie listy opcji
    for(auto element : options) delete element;
    options.clear();

}


void Menu::addOption(const unsigned int token, string desc){

    if(desc == "") desc = "Opcja " + to_string(token);
    MenuElement* new_element = new MenuElement(token, desc);
    options.push_back(new_element);

}

void Menu::print(){

    // Format menu:
    // NAGŁÓWEK
    // Instrukcja obsługi
    // [t1] desc1
    // ...
    // [tn] descn
    // > 

    const string MANUAL = "Wybierz jedna z ponizszych opcji wprowadzajac odpowiadajacy jej symbol.";

    printf("%s\n", header.c_str());
    printf("%s\n", MANUAL.c_str());
    for(auto element : options) printf("[ %d ]\t%s\n", element->token, element->desc.c_str());
    printf("> ");

}

int Menu::getUserChoice(){

    // Użytkownik dokonuje wyboru
    int chosen_token;
    print();

    // Sprawdzam, czy użtykownik nie wybrał symbolu o niedozwolonym formacie (nie liczbę)
    // lub symbolu, który nie występuje w menu
    try{
        chosen_token = Console::getIntInput();
    }catch (invalid_argument e){
        cout << e.what() << endl;
        chosen_token = -1;
    }
    if(!isValidToken(chosen_token)) return chosen_token;

    // Zwracam symbol
    return chosen_token;

}

bool Menu::isValidToken(const int token){

    const string SYMBOL_DOES_NOT_EXIST = "Symbol nie istnieje!";

    // Czy istnieje w menu?
    for(auto element : options){
        if(token != element->token) continue;
        return true;
    }

    // Nie istnieje w menu
    printf("%s\n", SYMBOL_DOES_NOT_EXIST.c_str());
    return false;

}