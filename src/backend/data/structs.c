#include <stddef.h>
#include <stdlib.h>
#include "structs.h"

const enum EdgePositions cluesAllowed[][N_CLUES] = {
    [FIRST_COL] = {
        TOP,
        TOP_RIGHT,
        RIGHT,
        BOTTOM,
        BOTTOM_RIGHT
    },
    [LAST_COL] = {
        TOP,
        TOP_LEFT,
        LEFT,
        BOTTOM,
        BOTTOM_LEFT
    },
    [FIRST_ROW] = {
        LEFT,
        RIGHT,
        BOTTOM,
        BOTTOM_LEFT,
        BOTTOM_RIGHT
    },
    [LAST_ROW] = {
        TOP_LEFT,
        TOP,
        TOP_RIGHT,
        LEFT,
        RIGHT
    }
};

int alloc_failure(void * st) {
    if (st == NULL) {
        return 1;
    }
    return 0;
}

void reset_data(void * st) {
    free(st);
}