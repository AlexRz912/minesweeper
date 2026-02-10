# Minesweeper

## Overview
A hardcore Minesweeper game implemented in C using SDL3 for graphics rendering. This is my first experience with SDL library. The player reveals squares on a grid to find hidden mines while avoiding detonation.

## Gameplay
- Click on squares to reveal hidden mines or safe numbers
- Numbers indicate how many adjacent mines are nearby
- Clear all non-mine squares to win
- Hit a mine = game over

## Technical Implementation

### Main Challenges
- **SDL3 Graphics Rendering** (First Time!): GUI-based game interface with real-time rendering
- **Font Rendering**: SDL3_TTF integration for dynamic text display
- **Game State Management**: Complex state tracking for revealed squares, flagged mines, and game status
- **Modular Architecture**: Separated backend logic from frontend rendering components
- **Dynamic Grid System**: Scalable board generation with configurable difficulty
- **Dynamic Memory Allocation**: Managing structure allocation and deallocation for game data

### Project Structure
```
minesweeper/
├── src/
│   ├── render.c                 # Main rendering and game loop
│   ├── backend/
│   │   ├── minesweeper.c        # Core game logic
│   │   ├── minesweeper.h
│   │   ├── data/
│   │   │   ├── constants.h      # Game constants (board size, colors)
│   │   │   ├── structs.c        # Data structure implementations
│   │   │   └── structs.h        # Structure definitions
│   │   ├── game/
│   │   │   ├── game_logic.c     # Win/loss detection, mine placement
│   │   │   ├── game_logic.h
│   │   │   ├── helpers.c        # Utility functions
│   │   │   ├── helpers.h
│   │   │   ├── utils.c
│   │   │   └── utils.h
│   │   └── misc/
│   │       ├── debug.c          # Debug utilities
│   │       └── debug.h
│   └── frontend/
│       ├── assets/              # Game assets
│       └── components/
│           ├── box.c            # UI box rendering
│           ├── box.h
│           └── constants.h      # Frontend constants
└── minesweeper.exe              # Compiled executable
```

## Installation & Setup

### Requirements
- **SDL3 Runtime**: The game requires SDL3.dll and SDL3_ttf.dll to run
- **Windows**: Built for Windows (x86_64)

### Installation Steps
1. Download `minesweeper.exe`
2. Ensure the following DLL file is in the same directory as the executable:
   - `SDL3.dll`
3. Run `minesweeper.exe`

If you get a "missing DLL" error, copy the necessary SDL3 libraries from:
- `C:\Users\rodri\Documents\Projects\computer_science\SDL\x86_64-w64-mingw32\lib\`
- `C:\Users\rodri\Documents\Projects\computer_science\SDL_TTF\SDL3_ttf-3.2.2\x86_64-w64-mingw32\lib\`

## How to play
- **Left Click**: Reveal a square
- Clear all safe squares to win
- Avoid clicking on mines!

---
*Minesweeper in C - Learning SDL3 graphics, game state management, modular architecture, and event handling*
