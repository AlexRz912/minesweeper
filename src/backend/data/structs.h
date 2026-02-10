#pragma once

#include "constants.h"

struct MineSweeper {
    int cells[BOMBS_COUNT];
    int mine[ROWS][COLS];
    float cell_size; 
    int cols;
    int rows;
    int timer;
    float grid_width;
    float grid_y;
    float grid_x;
};

struct Game {
    int gameEnd;
    int gameOver;
    int gameCompleted;
    int gameCompletedTime;
    int timer;
    int firstClick;
};

enum SurroundingClues {
        LEFT = -1,
        RIGHT = 1,
        TOP_LEFT = -10,
        TOP = -9,
        TOP_RIGHT = -8,
        BOTTOM_LEFT = 8,
        BOTTOM = 9,
        BOTTOM_RIGHT = 10,
        N_CLUES
    };

enum EdgePositions {
    FIRST_COL,
    LAST_COL,
    FIRST_ROW,
    LAST_ROW,
    NOT_AN_EDGE_POSITION
};

extern const enum EdgePositions cluesAllowed[][N_CLUES];

int alloc_failure(void * st); 
void reset_data(void * st);


