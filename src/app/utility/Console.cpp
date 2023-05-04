#define WINDOWS
#ifdef WINDOWS 
    #include <windows.h>
#endif
#include <iostream>
#include <string>

#include "app/utility/Console.h"

const string Console::INVALID_FORMAT = "Niepoprawny format danych wejsciowych!";

void Console::clearScreen(){
    // Obsługa konsoli dla dystrybucji na system MS Windows
    #ifdef WINDOWS  
        system("cls");
    #endif
    // Obsługa konstoli dla dystrybucji na systemy Linux
    #ifdef LINUX
        system("clear");
    #endif
}

void Console::waitForUserResponse(){

    fflush(stdin);
    printf("Wcisnij dowolny klawisz, aby kontynuowac...");
    getchar();

}

int Console::getIntInput(string msg){

    int int_input;
    try{
        int_input = stoi(getInput(msg));
    } catch(invalid_argument){
        throw invalid_argument(INVALID_FORMAT);
    }

    return int_input;

}

string Console::getInput(string msg){

    string user_input;
    if(msg != "") cout << msg << "\n>";
    cin >> user_input;

    return user_input;

}