#include <iostream>
#include <cstdlib>
#include "menu.h"
#include "colors.h"

void display_Menu()
{
    system("cls");

    std::cout << Colors::YELLOW << "\t\t==============================\n";
    std::cout << "\t\t=      WELCOME TO PACMAN      =\n";
    std::cout << "\t\t==============================\n" << Colors::RESET;

    std::cout << "\n\tPlease select an option:\n";

    std::cout << Colors::BLUE 
        << "\t1. Sign Up\n"
        << "\t2. Sign In\n"
        << "\t3. Delete Account\n"
        << "\t4. Exit\n"
        << Colors::RESET;
    
    std::cout << "\n\tYour choice: ";
}