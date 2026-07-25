#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
#include "game.h"
#include "menu.h"

#pragma comment(lib , "winmm.lib")

using namespace std;

int total_pills = 0;
bool gameOver = false;
int lastPlayedLevel = 0;
PacmanGame game;

void showGameOverMessage() {
    while (_kbhit()) {
        _getch();
    }
    std::cout << "\n\n========================================\n";
    std::cout << "          " << Colors::RED << "G A M E   O V E R !" << Colors::RESET << "          \n";
    std::cout << "========================================\n";
    std::cout << "Press any key to return to menu...";
    _getch();
}

void Game_Bar() {
    const char* frames[] = { "\u25F7", "\u25F6", "\u25F5", "\u25F4" };
    for (int i = 0; i < 4; i++) {
        system("cls");
        cout << Colors::YELLOW << "\n\n\t\t---------------------\n";
        cout << "\t\t|      " << frames[i] << " ...        |\n";
        cout << Colors::YELLOW << "\t\t---------------------\n" << Colors::RESET;
        Sleep(300);
    }
}

void GhostRandomMove(int Hight, int weidth, PacmanMap* map) {
    int directions[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // up , down, left, right
    for (int i = 0; i < Hight; i++) {
        for (int j = 0; j < weidth; j++) {
            if (map->cells[i][j].type == GHOST) {
                int randome_direction = rand() % 4;
                int newX = j + directions[randome_direction][1];
                int newY = i + directions[randome_direction][0];
                // check if the new position is within the map and is not a wall 
                if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
                    if (map->cells[newY][newX].type == PILL || map->cells[newY][newX].type == EMPTY) {
                        //Cell temp = game.level1.cells[i][j];
                        map->cells[i][j].type = EMPTY;
                        map->cells[newY][newX].type = GHOST;
                    }
                }
            }
        }
    }
}

void printMap(PacmanMap* map) {
    system("cls");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            switch (map->cells[i][j].type) {
            case EMPTY:
                cout << " ";
                break;
            case WALL:
                cout << WALL_CHAR;
                break;
            case PILL:
                cout << PILL_CHAR;
                break;
            case PACMAN:
                cout << PACMAN_CHAR;
                break;
            case GHOST:
                cout << GHOST_CHAR;
                break;
            }
        }
        cout << endl;
    }

    cout << "\nControls: W(up), A(left), S(down), D(right), Q(quit)\n)";
    cout << "Score: " << map->score << "| Remaining Pills: " << map->total_pills << endl;
}

void Move_Pacman(PacmanGame* game, int Level, char direction) {
    PacmanMap* currentLevel = nullptr;
    if (Level == 1) currentLevel = &game->level1;
    else if (Level == 2) currentLevel = &game->level2;
    else if (Level == 3) currentLevel = &game->level3;
    else return;

    int newX = currentLevel->pacman_x;
    int newY = currentLevel->pacman_y;

    switch (tolower(direction)) {
    case 'w': newY--; break;
    case 's': newY++; break;
    case 'a': newX--; break;
    case 'd': newX++; break;
    default: return;
    }

    if (newX >= 0 && newX < MAP_WIDTH && newY >= 0 && newY < MAP_HEIGHT) {
        if (currentLevel->cells[newY][newX].type != WALL) {
            if (currentLevel->cells[newY][newX].type == PILL) {
                currentLevel->score += 10;
                currentLevel->total_pills--;
            }
            if (currentLevel->cells[newY][newX].type == GHOST) {
                cout << "\nGame Over! A Ghost caught you!\n";
                gameOver = true;
                return;
            }
            currentLevel->cells[currentLevel->pacman_y][currentLevel->pacman_x].type = EMPTY;
            currentLevel->pacman_x = newX;
            currentLevel->pacman_y = newY;
            currentLevel->cells[newY][newX].type = PACMAN;
        }
    } 
}

// Define level 1 
void cherry() {
    game.level1.pacman_y = 8;
    game.level1.pacman_x = 14;

    const char maze[MAP_HEIGHT][MAP_WIDTH + 1] = {
        "##############################",
        "#............#...............#",
        "#.####.#####.#.#####.#######.#",
        "#.####.#####.#.#####.#######.#",
        "#......#....#.....#..........#",
        "######.#.#########.###.#####.#",
        "#......#.........#...#.......#",
        "#.#########.#####.#.#####.####",
        "#..........#...#...#.........#",
        "######.#####.#.#.#.###.#######",
        "#......#.....#...#...#.......#",
        "#.#########.###.###.##########",
        "#......#...#.................#",
        "##############################"
    };

    game.level1.total_pills = 0;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game.level1.cells[i][j].x = j;
            game.level1.cells[i][j].y = i;

            if (maze[i][j] == '#') game.level1.cells[i][j].type = WALL;
            else if (maze[i][j] == '.') {
                game.level1.cells[i][j].type = PILL;
                game.level1.total_pills++;
            }
            else game.level1.cells[i][j].type = EMPTY;
        }
    }
    game.level1.cells[game.level1.pacman_y][game.level1.pacman_x].type = PACMAN;
    srand(static_cast<unsigned int>(time(NULL)));
    int ghostCount = 0;
    while (ghostCount < 3) {
        int rx = rand() % MAP_WIDTH;
        int ry = rand() % MAP_HEIGHT;
        if (game.level1.cells[ry][rx].type == PILL || game.level1.cells[ry][rx].type == EMPTY) {
            game.level1.cells[ry][rx].type = GHOST;
            ghostCount++;
        }
    }
    game.level1.score = 0;

    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    while (true) {
        printMap(&game.level1);
        char input = _getch();
        if (input == 'q' || input == 'Q') {
            PlaySound(NULL, 0, 0);
            return;
        }

        Move_Pacman(&game, 1, input);
        GhostRandomMove(MAP_HEIGHT, MAP_WIDTH, &game.level1);

        if (game.level1.total_pills <= 0) {
            PlaySound(NULL, 0, 0);
            cout << "\nCongratulations! You Win Level 1!\n";
            system("pause");
            return;
        }
        if (gameOver) {
            PlaySound(NULL, 0, 0);
            showGameOverMessage();
            gameOver = false;
            return;
        }
        Sleep(50);
    }
}

// Level 2
void strawberry() {
    game.level2.pacman_y = 6;
    game.level2.pacman_x = 15;

    const char maze2[MAP_HEIGHT][MAP_WIDTH + 1] = {
        "##############################",
        "#.............#..............#",
        "#.#######.#####.#.#####..#####",
        "#.#######.#####.#.#####..#####",
        "#.......#.........#.....#....#",
        "###.###.#.#####.###.###.#.####",
        "#...#...#...#.....#...#......#",
        "###.#.#.#####.#.###.###.######",
        "#...#.....#...#.........#....#",
        "###.#####.#.##############..##",
        "#...............#......#.....#",
        "#########..########..#########",
        "#.............#..............#",
        "##############################"
    };

    game.level2.total_pills = 0;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game.level2.cells[i][j].x = j;
            game.level2.cells[i][j].y = i;

            if (maze2[i][j] == '#') game.level2.cells[i][j].type = WALL;
            else if (maze2[i][j] == '.') {
                game.level2.cells[i][j].type = PILL;
                game.level2.total_pills++;
            }
            else game.level2.cells[i][j].type = EMPTY;
        }
    }

    game.level2.cells[game.level2.pacman_y][game.level2.pacman_x].type = PACMAN;
    // Place 3 Random Ghosts

    srand(static_cast<unsigned int>(time(NULL)));
    int ghostCount = 0;
    while (ghostCount < 3) {
        int rx = rand() % MAP_WIDTH;
        int ry = rand() % MAP_HEIGHT;
        if (game.level2.cells[ry][rx].type == PILL || game.level2.cells[ry][rx].type == EMPTY) {
            game.level2.cells[ry][rx].type = GHOST;
            ghostCount++;
        }
    }
    game.level2.score = 0;

    PlaySound(TEXT("music2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    while (true) {
        printMap(&game.level2);
        char input = _getch();
        if (input == 'q' || input == 'Q') {
            PlaySound(NULL, 0, 0);
            return;
        }
        Move_Pacman(&game, 2, input);
        GhostRandomMove(MAP_HEIGHT, MAP_WIDTH, &game.level2);

        if (game.level2.total_pills <= 0) {
            PlaySound(NULL, 0, 0);
            cout << "\nCongratulations! You Win Level 2!\n";
            system("pause");
            return;
        }
        if (gameOver) {
            PlaySound(NULL, 0, 0);
            showGameOverMessage();
            gameOver = false;
            return;
        }
        Sleep(50);
    }
}

//Level 3
void orange() {
    game.level3.pacman_y = 6;
    game.level3.pacman_x = 15;

    const char maze3[MAP_HEIGHT][MAP_WIDTH + 1] = {
       "##############################",
        "#..........##................#",
        "##..#####..##..######..#######",
        "#..##..##..##..##..##..##....#",
        "#..##..##..######..##..##..###",
        "######..##..##..##..##..##...#",
        "#......##..##..######...######",
        "#..########..##..##..##..##..#",
        "#...............#..######..###",
        "######..########..##..##..####",
        "#...............##...........#",
        "#########....##########..#####",
        "#.............#..............#",
        "##############################"
    };

    game.level3.total_pills = 0;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            game.level3.cells[i][j].x = j;
            game.level3.cells[i][j].y = i;

            if (maze3[i][j] == '#') game.level3.cells[i][j].type = WALL;
            else if (maze3[i][j] == '.') {
                game.level3.cells[i][j].type = PILL;
                game.level3.total_pills++;
            }
            else game.level3.cells[i][j].type = EMPTY;
        }
    }
    game.level3.cells[game.level3.pacman_y][game.level3.pacman_x].type = PACMAN;

    srand(static_cast<unsigned int>(time(NULL)));
    int ghostCount = 0;
    while (ghostCount < 3) {
        int rx = rand() % MAP_WIDTH;
        int ry = rand() % MAP_HEIGHT;
        if (game.level3.cells[ry][rx].type == PILL || game.level3.cells[ry][rx].type == EMPTY) {
            game.level3.cells[ry][rx].type = GHOST;
            ghostCount++;
        }
    }
    game.level3.score = 0;

    PlaySound(TEXT("music2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    while (true) {
        printMap(&game.level3);
        char input = _getch();
        if (input == 'q' || input == 'Q') {
            PlaySound(NULL, 0, 0);
            return;
        }

        Move_Pacman(&game, 3, input);
        GhostRandomMove(MAP_HEIGHT, MAP_WIDTH, &game.level3);

        if (game.level3.total_pills <= 0) {
            PlaySound(NULL, 0, 0);
            cout << "\nCongratulations! You Completed the Game!\n";
            system("pause");
            return;
        }
        if (gameOver) {
            PlaySound(NULL, 0, 0);
            showGameOverMessage();
            gameOver = false;
            return;
        }
        Sleep(50);
    }
}

void new_Game() {
    while (true) {
        system("cls");
        cout << "\n\t\t\tChoose a Level: \n\n";
        cout << Colors::RED << "\t1. Cherry \n";
        cout << Colors::PINK << "\t2. Strawberry \n";
        cout << Colors::ORANGE << "\t3. Orange \n" << Colors::RESET;
        cout << "\t4. Go Back\n\n" << Colors::RESET;
        cout << "Your Choice: ";

        int input;
        cin >> input;
        if (!(cin >> input)) {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        Game_Bar();

        switch (input) {
        case 1:
            lastPlayedLevel = 1;
            cherry();
            break;
        case 2:
            lastPlayedLevel = 2;
            strawberry();
            break;
        case 3:
            lastPlayedLevel = 3;
            orange();
            break;
        case 4:
            return;
        default:
            cout << "Invalid Choice!\n";
            Sleep(1500);
            break;
        }
    }
}

void perivious_Game() {
    if (lastPlayedLevel == 0) {
        cout << "\nNo previous game session found!\n";
        Sleep(1500);
        return;
    }
    cout << "\nLoading previous level...\n";
    Sleep(1000);

    switch (lastPlayedLevel) {
    case 1: cherry(); break;
    case 2: strawberry(); break;
    case 3: orange(); break;
    }
}