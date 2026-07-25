#pragma once

#include <iostream>
#include "colors.h"

const std::string PACMAN_CHAR = std::string(Colors::YELLOW) + "\u25D0" + Colors::RESET;
const std::string GHOST_CHAR = std::string(Colors::RED) + "\U0001F47B" + Colors::RESET;
const std::string PILL_CHAR = std::string(Colors::PINK) + "\u2022" + Colors::RESET;
const std::string WALL_CHAR = std::string(Colors::BLUE) + "\u2593" + Colors::RESET;

constexpr int MAP_WIDTH = 30;
constexpr int MAP_HEIGHT = 14;

extern int total_pills;
extern bool gameOver;
extern int lastPlayedLevel;

// Define cell types
enum CELLTYPE {
    EMPTY,
    WALL,
    PILL,
    PACMAN,
    GHOST,
};

// Define a structure for each cell
struct Cell {
    CELLTYPE type;
    int x;
    int y;
};

// Define a structure for the game map
struct PacmanMap {
    Cell cells[MAP_HEIGHT][MAP_WIDTH];
    int pacman_x;
    int pacman_y;
    int score;
    int total_pills;
};

// Define a structure for different levles
struct PacmanGame {
    PacmanMap level1;
    PacmanMap level2;
    PacmanMap level3;
};

extern PacmanGame game;

void showGameOverMessage();
void Game_Bar();
void GhostRandomMove(int Hight, int weidth, PacmanMap* map);
void printMap(PacmanMap* map);
void Move_Pacman(PacmanGame* game, int Level, char direction);
void cherry();
void strawberry();
void orange();
void new_Game();
void perivious_Game();