#include <stdio.h>
#include "helpers.h"

const enum SurroundingClues directions[DIRECTIONS_COUNT] = {
    LEFT, RIGHT, TOP_LEFT, TOP, TOP_RIGHT, BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT
};


int* getAllowedDirections(int cellIndex, int * count) {
    static int allowed[DIRECTIONS_COUNT];
    *count = 0;
    
    for (int dirIndex = 0; dirIndex < DIRECTIONS_COUNT; dirIndex++) {
        int isAllowed = isIllegalDir(cellIndex, directions[dirIndex]);
        addAllowedDirection(isAllowed, allowed, count, directions[dirIndex]);
    }
    return allowed;
}

void addAllowedDirection(int isAllowed, int* allowed, int* count, int dir) {
    if (isAllowed) {
        allowed[*count] = dir;
        (*count)++;
    }
}

void updateCluesAroundBomb(struct MineSweeper * mineGrid, int cellIndex, int* allowedDirs, int count) {
    for (int i = 0; i < count; i++) {
        int neighborIndex = cellIndex + allowedDirs[i];
        updateClue(mineGrid, neighborIndex);
    }
}

void updateClue(struct MineSweeper * mineGrid, int neighborIndex) {
    int row = getRow(neighborIndex);
    int col = getCol(neighborIndex);
    if (!mineIsBomb(mineGrid, row, col)) {
        mineGrid->mine[row][col] += 1;
    }
}

int isIllegalDir(int cellIndex, int dir) {
    int isAllowed  = 1;
    int isFirstCol = (cellIndex % COLS == 0);
    int isLastCol  = ((cellIndex + 1) % COLS == 0);
    int isFirstRow = (cellIndex < COLS);
    int isLastRow  = (cellIndex >= GRID_CELLS - COLS);

    if (isFirstCol && (dir == LEFT || dir == TOP_LEFT || dir == BOTTOM_LEFT)) isAllowed = 0;
    if (isLastCol && (dir == RIGHT || dir == TOP_RIGHT || dir == BOTTOM_RIGHT)) isAllowed = 0;
    if (isFirstRow && (dir == TOP || dir == TOP_LEFT || dir == TOP_RIGHT)) isAllowed = 0;
    if (isLastRow && (dir == BOTTOM || dir == BOTTOM_LEFT || dir == BOTTOM_RIGHT)) isAllowed = 0;

    return isAllowed;
}