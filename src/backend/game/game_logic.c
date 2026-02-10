#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"
#include "game_logic.h"
#include "../data/structs.h"

void addBombsToGrid(struct MineSweeper * mineGrid) 
{
    srand(time(NULL));
    //FISHER-YATES SHUFFLE
    int allPositions[GRID_CELLS];
    for (int i = 0; i < GRID_CELLS; i++) {
        allPositions[i] = i;
    }
    
    for (int cell = 0; cell < BOMBS_COUNT; cell++) {
        int randCell = cell + rand() % (GRID_CELLS - cell);
        int swappedCell = allPositions[cell];
        allPositions[cell] = allPositions[randCell];
        allPositions[randCell] = swappedCell;
        mineGrid->cells[cell] = allPositions[cell];
        
        int position = allPositions[cell];
        int row = position / COLS;
        int col = position % COLS;
        mineGrid->mine[row][col] = 8;
    }
}

void addCluesToGrid(struct MineSweeper * mineGrid, const enum SurroundingClues dirs[]) {
    for (int bombIndex = 0; bombIndex < BOMBS_COUNT; bombIndex++) {
        int cellIndex = mineGrid->cells[bombIndex];
        int count;
        int* allowedDirs = getAllowedDirections(cellIndex, &count);
        updateCluesAroundBomb(mineGrid, cellIndex, allowedDirs, count);
    }
}

void hideGrid(struct MineSweeper * mineGrid) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            mineGrid->mine[row][col] += 10;
        }
    }
}