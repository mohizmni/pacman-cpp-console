#include <Windows.h>
#include <conio.h>
#include "user.h"
#include "Game.h"

using namespace std;

void Star_Password(char pwd[MAX_STR]){
    int i = 0;
    char ch;
    while (true) {
        ch = _getch();

        if (ch == KEY_TAB || ch == KEY_ENTER){
            pwd[i] = '\0';
            cout << endl;
            break;
        }
        else if (ch == KEY_BACKSPACE ){
            if (i > 0) {
                i--;
                cout << "\b \b";
            }
        }
        else if(i < MAX_STR - 1) {
            pwd[i] = ch;
            i++;
            cout << "*";
        }
    }
}

void Signup() {
    system("cls");
    User newuser{};

    cout << "===== Create Account =====\n\n";
    cout << "Username: ";
    cin >> newuser.user_name;

    ifstream userFileRead("user.bin", ios::binary);
    if (!userFileRead.is_open()) {
        User existUser;
        while (userFileRead.read(reinterpret_cast<char*>(&existUser), sizeof(User))) {
            if (strcmp(existUser.user_name, newuser.user_name) == 0) {
                cout << "Username is already taken. Please choose another.\n";
                Sleep(1500);
                return;
            }
        }
        userFileRead.close();
    }

    cout << "Password: ";
    char pass[MAX_STR];
    Star_Password(pass);

    cout << "Confirm Password: ";
    char pass2[MAX_STR];
    Star_Password(pass2);

    if (strcmp(pass2, pass) == 0) {
        strcpy_s(newuser.user_id, MAX_STR, pass);

        ofstream userFileWrite("user.bin", ios::binary | ios::app);
        if (!userFileWrite.is_open()) {
            cout << "Error opening file for writing.\n";
            return;
        }
        userFileWrite.write(reinterpret_cast<const char*>(&newuser), sizeof(User));
        userFileWrite.close();

        cout << "\nAccount Created successfully!\n";
        Sleep(1000);
    }
    else {
        cout << "\nPasswords don't match.\n";
        Beep(750, 300);
        Sleep(1000);
    }
}

void User_Menu(const User& user)
{
    while (true) {
        system("cls");
        cout << "=================================\n";
        cout << " Welcome " << user.user_name << '\n';
        cout << "=================================\n\n";

        cout << "\n\tClick To Play: \n";
        cout << "\t1. new game\n";
        cout << "\t2. perivious Game\n";
        cout << "\t3. Logout\n\n";
        cout << "Your Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInvalid Input.";
            Sleep(1000);
            continue;
        }

        switch (choice)
        {
        case 1:
            new_Game();
            break;
        case 2:
            perivious_Game();
            break;
        case 3:
            return;
        default:
            cout << "\nInvalid choise.";
            Sleep(1000);
            break;
        }
    }
}

void signin()
{
    system("cls");

    char username[MAX_STR];
    char password[MAX_STR];
    User user;

    cout << "===== Sign In =====\n\n";
    cout << "username: ";
    cin >> username;
    cout << "Password: ";
    Star_Password(password);

    ifstream userFile("user.bin", ios::binary);
    if (!userFile.is_open()) {
        cout << "\nNo user database found.\n";
        Beep(800, 300);
        Sleep(1000);
        return;
    }

    while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        bool usernameMatch = (strcmp(user.user_name, username) == 0);
        bool passwordMatch = (strcmp(user.user_id, password) == 0);

        if (usernameMatch && passwordMatch) {
            cout << "\nLogin Successful! Welcome " << user.user_name << "!\n";
            Sleep(1000);
            userFile.close();
            User_Menu(user);
            return;
        }
    }
    userFile.close();
    cout << "\nInvalid username or password.\n";
    Beep(800, 300);
    Sleep(1200);
}

void delete_account()
{
    system("cls");

    char username[MAX_STR];
    char password[MAX_STR];
    User user;

    cout << "===== Delete Account =====\n\n";
    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;
    Star_Password(password);

    ifstream userFile("user.bin", ios::binary);
    if (!userFile.is_open()) {
        cout << "\nNo user database found.\n";
        Sleep(1200);
        return;
    }

    ofstream tempFile("temp_user.bin", ios::binary);
    if (!tempFile.is_open()) {
        cout << "\nUnable to create temporary file.\n";
        userFile.close();
        Sleep(1200);
        return;
    }

    bool accountDeleted = false;

    while (userFile.read(reinterpret_cast<char*>(&user), sizeof(User))) {
        bool usernameMatch = (strcmp(user.user_name, username) == 0);
        bool passwordMatch = (strcmp(user.user_id, password) == 0);

        if (usernameMatch && passwordMatch) {
            accountDeleted = true;
            continue;
        }
        tempFile.write(reinterpret_cast<char*>(&user), sizeof(User));
    }

    userFile.close();
    tempFile.close();


    if (!accountDeleted) {
        remove("temp_user.bin");
        cout << "\nUsername or password is incorrect.\n";
        Beep(800, 300);
        Sleep(1200);
        return;
    }

    if (remove("user.bin") != 0 || rename("temp_user.bin", "user.bin") != 0) {
        cout << "\nError updating user database.\n";
        Sleep(1200);
        return;
    }
    cout << "\nYour account has been deleted successfully.\n";
    Sleep(1500);
}