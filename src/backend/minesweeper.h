#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "data/structs.h"
#include "game/game_logic.h"
#include "misc/debug.h"

extern struct MineSweeper * mineGrid;
extern struct Game * gameVitals;


void processClick(int x, int y);
void * initGame();
void * initGrid();
void initGridConstants();
void getGrid();
void destroyGrid();
void displayAllBombs();
void displayCell(int row, int col);
void resetGameVitals();
void updateFirstClick();
void setGridCompletedTime(int timer);
int isFirstClick();
int getClickedCellValue(int clickedRow, int clickedCol);
int resetTimer();
int isGameOver();
int isGameCompleted();
int isClickedCellEmpty(int clicked);
int isClickedCellAClue(int clicked);
int isClickedCellABomb(int clicked);



