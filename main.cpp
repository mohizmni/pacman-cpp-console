#include <iostream>
#include <windows.h>
#include "user.h"
#include "menu.h"
#include "colors.h"

void start();
void Signup();
void signin();
void delete_account();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    start();
    Sleep(1500);

    while (true) {
        display_Menu();

        int input;
        if (!(std::cin >> input)) {
            std::cin.clear();

            std::cin.ignore(1000, '\n');
            std::cout << Colors::RED << "Invalid Input\n" << Colors::RESET; //! Please enter a number.
            Sleep(1500);
            continue;
        }

        switch (input) {
        case 1:
            Signup();
            break;
        case 2:
            signin();
            break;
        case 3:
            delete_account();
            break;
        case 4:
            std::cout << Colors::GREEN << "Exiting Game...Goodbye!\n" << Colors::RESET;
            Sleep(1500);
            return 0;
        default:
            std::cout << Colors::RED << "Invalid Input! Please try again.\n" << Colors::RESET;
            Sleep(1500);
            break;
        }
    }

    return 0;
}

void start()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    const int max_steps = 30;
    const int delay_ms = 100; 

    for (int step = 0; step <= max_steps; step++) {
        system("cls");
        std::cout << "\n\n\t\t" << Colors::YELLOW << "---------------------------------------------" << Colors::RESET << "\n";

        std::cout << "\t\t" << Colors::YELLOW << "|" << Colors::RESET;

        for (int j = 0; j < step; j++) {
            std::cout << " ";
        }
        std::cout << Colors::YELLOW << "\u15E7" << Colors::RESET;

        std::cout << Colors::RED << " ...PACMAN... " << Colors::RESET;

        for (int j = 0; j < (max_steps - step); j++) {
            std::cout << " ";
        }
        std::cout << Colors::YELLOW << "|" << Colors::RESET << "\n";

        std::cout << "\t\t" << Colors::YELLOW << "---------------------------------------------" << Colors::RESET << "\n";

        Sleep(delay_ms);
    }
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}