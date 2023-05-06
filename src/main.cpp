#include <iostream>
#include "app/utility/Menu.h"
#include "app/utility/Console.h"

using namespace std;


// testowanie funkcji, które nie przeszły testu jednostkowego
void test(){
    
}

/**
 * @brief Zbiór opcji dostępnych w głównym menu aplikacji.
 */
enum mainMenuOptions{
    MENU_EXIT
};


/**
 * @brief Główna pętla aplikacji.
 */
int main(int argc, char const *argv[]){

    // Ustalenie opcji w menu głównym
    Menu main_menu("MENU GLOWNE:");
    main_menu.addOption(MENU_EXIT, "Zamknij program");

    // Główna pętla aplikacji
    bool is_running = true;
    while(is_running){

        Console::clearScreen();
        switch (main_menu.getUserChoice()){
        
            // Wyjście z aplikacji
            case MENU_EXIT: is_running = false; break;

            // Niezdefiniowana opcja
            default: Console::waitForUserResponse(); break;

        }

    }

    // Wyjście z aplikacji
    return 0;
}

