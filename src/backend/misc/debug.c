#include "debug.h"

void printGrid(struct MineSweeper * mineGrid) {
    printf("\n=== GRILLE MINESWEEPER ===\n");
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int value = mineGrid->mine[row][col];
            if (value == 8) {
                printf(" * ");
            } else {
                printf(" %d ", value);
            }
        }
        printf("\n");
    }
    printf("=========================\n");
}