<img width="822" height="448" alt="Screenshot 2026-07-29 065450" src="https://github.com/user-attachments/assets/52e3c050-9a3d-4ce7-bcad-71711e13b323" /># Pacman C++ Console Game

A feature-complete, interactive Pac-Man arcade game built entirely in modern C++ for the Windows Console environment. This project features custom ASCII/Unicode rendering, ANSI color coding, dynamic level management, background sound playback, and high-score handling.

---

## Features

 * ANSI Color Engine: Smooth colored rendering using ANSI escape sequences and custom color definitions.
 * Audio Integration: Background music and sound effects powered by the Windows WinMM library (`PlaySound`).
 * Interactive Controls: Non-blocking real-time keyboard inputs (`_getch`).
 * Multi-Level Support: Features multiple levels (`Cherry`, `Strawberry`, `Orange`) with varying layout complexities.
 * Custom Intro Animation: Centered, flicker-free opening sequence rendered directly in the terminal buffer.
 * Score & User Tracking: Binary/structured file logging for player stats and game states.

## Screenshots

<table align="center">
  <tr>
    <td align="center" width="50%">
      <img src="[URL_FIRST_IMAGE](https://github.com/user-attachments/assets/e53416bf-368c-4bcf-a9e6-895748648a63)![Uploading Screenshot 2026-07-29 065450.png…]()
" height="300px" style="object-fit: contain;" alt="Gameplay" /><br/>
      <sub><b>Real-time Gameplay & Maze Logic</b></sub>
    </td>
    <td align="center" width="50%">
      <img src="[URL_SECOND_IMAGE](https://github.com/user-attachments/assets/43ceabcb-6c9c-4794-9f91-0681b8e632c)2" height="300px" style="object-fit: contain;" alt="Main Menu" /><br/>
      <sub><b>User Authentication & Main Menu</b></sub>
    </td>
  </tr>
</table>


---

## Built With

 *Language: C++17
 *Platform: Windows (Win32 API)
 *IDE: Microsoft Visual Studio
 *Libraries: `<windows.h>`, `<mmsystem.h>`, `<conio.h>`

---

## Project Structure

├── main.cpp          # Application entry point
├── Game.h / .cpp     # Core game logic, map rendering, and AI ghosts
├── menu.h / .cpp     # Menu navigation and level selector
├── user.h / .cpp     # User profile management and scoring system
├── colors.h / .cpp   # Color macros and ANSI palette definitions
├── music.wav         # Main background audio file
└── user.bin          # Saved user progress data

##  Getting Started
### Prerequisites
  Windows OS
  Visual Studio 2019/2022 (with Desktop development with C++ workload installed)
### Building & Running
 1. Clone the repository:
   git clone [https://github.com/YOUR_USERNAME/pacman-cpp-console.git](https://github.com/YOUR_USERNAME/pacman-cpp-console.git)
   cd pacman-cpp-console
   
   
 2. Open in Visual Studio:
   Double-click Pa.vcxproj or open the folder directly in Visual Studio.
 3. Compiler Settings (Important):
    Ensure /utf-8 flag is enabled in Properties -> C/C++ -> Command Line -> Additional Options.
    Link Winmm.lib for audio support (already configured in project properties).
 4. Build & Run:
   Press Ctrl + F5 or click Local Windows Debugger to start the game!

---

## How to Play
| Key | Action |
|---|---|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| Q | Quit Level / Return to Menu |

## Contributing
Contributions, issues, and feature requests are welcome! Feel free to check the issues page.
## License
Distributed under the MIT License. See LICENSE for more information.
