#include <stdio.h>
#include <stdlib.h>
#include "data/structs.h"
#include "game/game_logic.h"
#include "misc/debug.h"

extern const enum SurroundingClues directions[DIRECTIONS_COUNT];
struct MineSweeper * mineGrid = NULL;
struct Game * gameVitals = NULL;

int getRemainingCellsCount();

void * initGame()
{
    gameVitals = calloc(1, sizeof(struct Game));
    if (alloc_failure(gameVitals)) {
        printf("alloc failure for game states");
        return NULL;
    }
}

void * initGrid() 
{
    mineGrid = calloc(1, sizeof(struct MineSweeper));
    if (alloc_failure(mineGrid)) {
        printf("alloc failure for game states");
        return NULL;
    }
    //printGrid(mineGrid);
    //reset_data(mineGrid);
}

void initGridConstants() {
    mineGrid->cell_size = 50.0f;
    mineGrid->cols = COLS;
    mineGrid->rows = ROWS;
    mineGrid->grid_width = mineGrid->cols * mineGrid->cell_size;
    mineGrid->grid_y = 120;
    mineGrid->grid_x = (640 - mineGrid->grid_width) / 2;
}

void getGrid() {
    addBombsToGrid(mineGrid);
    addCluesToGrid(mineGrid, directions);
    hideGrid(mineGrid);
}

void destroyGrid() {
    //reset
    for (int i = 0; i < BOMBS_COUNT; i++) {
        mineGrid->cells[i] = 0;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mineGrid->mine[i][j] = 0;
        }
    }
}

void resetGameVitals() {
    gameVitals->gameCompleted = 0;
    gameVitals->gameOver = 0;
    gameVitals->firstClick = 0;
    gameVitals->timer = 0;
    gameVitals->gameCompletedTime = 0;
}

int getClickedCellValue(int clickedRow, int clickedCol) {
    return mineGrid->mine[clickedRow][clickedCol];
}

int resetTimer() {
    return 0;
}

int isFirstClick() {
    return (gameVitals->firstClick == 0);
}

void updateFirstClick() {
    gameVitals->firstClick = 1;
}

int isGameOver() {
    return gameVitals->gameOver;
}

int isGameCompleted() {
    if (getRemainingCellsCount() > BOMBS_COUNT) {
        return 0;
    }
    return 1;
}

int isClickedCellEmpty(int clicked) {
    return (clicked == 10); // 0 - EMPTY_BOMB_VALUE; 10 - HIDDEN_BOMB_ADDITION_OPERAND
}

int isClickedCellAClue(int clicked) {
    return ((clicked >= 10) && (clicked <= 14));
}

int isClickedCellABomb(int clicked) {
    return (clicked >= 18);
}

void displayCell(int row, int col) {
    if (mineGrid->mine[row][col] >= 18) {
        mineGrid->mine[row][col] = 8;  // Bombe révélée
    } else {
        mineGrid->mine[row][col] -= 10;  // Case normale révélée
    }
}

void displayAllBombs() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (mineGrid->mine[row][col] >= 18) {
                displayCell(row, col);
            }
        }
    }
}

void setGridCompletedTime(int timer) {
    gameVitals->gameCompletedTime = timer;
}

int getRemainingCellsCount() {
    int count = 0;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (mineGrid->mine[row][col] >= 10) {
                count++;
            }
        }
    }
    return count;
}