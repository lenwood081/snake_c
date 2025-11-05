
# 🐍 Snake — Classic Terminal Snake Game in C

A simple, classic **terminal-based Snake game**, written entirely in **C**.  
This game runs in the **Windows command line** and uses basic console input/output functions to render the board and handle player movement.

---

## 🎮 Gameplay

Control the snake using your keyboard:

| Key | Action |
|-----|---------|
| **W** | Move Up |
| **A** | Move Left |
| **S** | Move Down |
| **D** | Move Right |
| **X** | Quit Game |

Eat the `*` (fruit) to grow your snake and increase your score.  
Avoid colliding with the walls `#` or your own body — or the game ends!

---

## 🧱 Features

- Classic **Snake gameplay** with growing tail mechanics  
- Text-based board rendered directly in the console  
- Dynamic fruit spawning  
- Basic score tracking  
- Smooth movement using `Sleep()` timing and `getch()` input  
- Lightweight — written in pure C, no external libraries required  

---

## 🖥️ Requirements

- **Operating System:** Windows  
- **Compiler:** GCC (via MinGW), MSVC, or any standard C compiler  
- **C Standard:** C17 or newer  

> ⚠️ Note: This program uses `<conio.h>` and `<windows.h>`, which are **Windows-specific**.  
> To run on Linux or macOS, you’d need to replace those with cross-platform equivalents (like `ncurses`).

---

## 🧩 How to Compile and Run

### Using GCC (MinGW on Windows)

1. Open **Command Prompt** or **PowerShell**.  
2. Navigate to the folder containing your source file:
   ```bash
   cd path\to\snakey
3. Compile with GCC:
   ```bash
   gcc snake.c -o snake.exe
4. Run:
   ```bash
   snake.exe

## ⚙️ File Structure

snake/

├── snake.c        # main source file

└── README.md      # project documentation



