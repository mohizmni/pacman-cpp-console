#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

constexpr int MAX_STR = 50;
constexpr char KEY_ENTER = 13;
constexpr char KEY_TAB = 9;
constexpr char KEY_BACKSPACE = 8;

struct User {
    char user_name[MAX_STR];
    char user_id[MAX_STR];
};

void new_Game();
void perivious_Game();
void Star_Password(char pwd[MAX_STR]);
void Signup();
void User_Menu(const User& user);
void signin();
void delete_account();
