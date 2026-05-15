# CMDominion

**CMDominion** is a lightweight, terminal-based adaptation of the famous deck-building card game *Dominion*. This project brings the full strategic experience of the board game to your command line, allowing for fast-paced sessions without the need for a graphical interface.

<p align="center">
    <img width="461" height="452" alt="image" src="https://github.com/user-attachments/assets/4a9787c9-911c-4721-b3c8-4b468507b7d0" />
</p>

---

## Features

- **Local Multiplayer:** Play with 2 to 4 players on the same machine.
- **Pure C++:** Built with performance and memory management in mind.
- **Authentic Mechanics:** - Full Deck-Building cycle (Draw, Action, Buy, Cleanup).
    - Includes core Kingdom cards, Treasures (Copper, Silver, Gold), and Victory cards (Estate, Duchy, Province).
    - Automatic deck shuffling and turn management.
- **CLI Interface:** A minimalist, retro aesthetic designed for enthusiasts.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C++ compiler supporting C++20
- GNU Make
- On Windows: MSYS2 with MinGW/UCRT64 installed

### Windows Setup (MSYS2)

1. Install MSYS2:
https://www.msys2.org/

2. Open the **MSYS2 UCRT64** terminal

3. Update packages:
```
pacman -Syu
```
(If prompted, close and reopen the terminal, then run the command again.)

4. Install GCC and Make:
```
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
```
5. (Optional) Add the following path to your Windows environment variables if you want to run commands directly from cmd:
```
C:\msys64\ucrt64\bin
```
### Clone the repository
```
git clone https://github.com/yoanlouvois/CMDominionGame.git
cd CMDominionGame
```
### Compile
```
make
```
If `make` does not work on Windows cmd:
```
mingw32-make
```
### Run the game
```
./Dominion
```
On Windows cmd:
```
Dominion.exe
```
### Clean build files
```
make clean
```
or on Windows:
```
mingw32-make clean
```
