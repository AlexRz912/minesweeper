#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "./backend/minesweeper.h"
#include "./backend/data/structs.h"
#include "./backend/misc/debug.h"
#include "./frontend/components/box.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Uint64 startTime = 0;

// Prototypes
void processClick(int x, int y);
int isClickOnPlayButton(int clickX, int clickY);
void startTimer();
void clickOnZeroDisplayCells(int row, int col);
void RenderGridCols(int grid_x, int cols);
void RenderGridRows(int grid_y, int rows);
void RenderBox(float box_x, float box_y, float box_size);
void RenderText(int green, int red, int blue, int padding, int x, int y, int info);
void RenderMineSweeperGrid();
// init function : interesting for metadata + dimensions
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Minesweeper", "1.0", "Minesweeper");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Minesweeper 1.0", 640, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Minesweeper 1.0: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderLogicalPresentation(renderer, 640, 600, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    initGame();
    initGrid();
    initGridConstants();
    getGrid();

    if (mineGrid == NULL) {
        printf("Allocation Error");
        return SDL_APP_FAILURE;
    }
    printGrid(mineGrid);
    getBoxesDimensions(mineGrid);

    return SDL_APP_CONTINUE;
}

// Handling Input
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    int gameOver = 0;
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            switch (event->key.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    //Free structures
                    return SDL_APP_SUCCESS;
            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            switch (event->button.button) {
                case SDL_BUTTON_LEFT:
                    float clickX = event->button.x;
                    float clickY = event->button.y;

                    processClick(clickX, clickY);
                    break;
                case SDL_BUTTON_RIGHT:
                    return SDL_APP_SUCCESS;
            }
            break;
    }
    return SDL_APP_CONTINUE;
}

void processClick(int clickX, int clickY)
{
    if (isClickOnPlayButton(clickX, clickY)) {
        destroyGrid();
        getGrid();
        resetGameVitals();
        startTime = 0;
        return;
    }

    if (isGameOver() || isGameCompleted()) {
        return;
    }

    int clickedCol = (clickX - mineGrid->grid_x) / mineGrid->cell_size;
    int clickedRow = (clickY - mineGrid->grid_y) / mineGrid->cell_size;
    
    if (clickedRow < 0 || clickedRow >= ROWS || clickedCol < 0 || clickedCol >= COLS) {
        return;
    }

    if (isFirstClick()) {
        startTimer();
        updateFirstClick();
    }
    
    int clickedCell = getClickedCellValue(clickedRow, clickedCol);

    if (isClickedCellAClue(clickedCell) || isClickedCellEmpty(clickedCell)) {
        displayCell(clickedRow, clickedCol);
        
        if (isGameCompleted()) {
            Uint64 elapsedSeconds = (SDL_GetTicks() - startTime) / 1000;
            if (elapsedSeconds > 999) {
                elapsedSeconds = 999;
            }
            setGridCompletedTime((int)elapsedSeconds);
        }
    }
    if (isClickedCellABomb(clickedCell)) {
        displayAllBombs();
        gameVitals->gameOver = 1;
    }
}

int isClickOnPlayButton(int clickX, int clickY) {
    float posX = boxDimensions->positions[MIDDLE_BOX];
    float boxSize = boxDimensions->boxSize;
    float posY = boxDimensions->boxY;
    
    if ((clickX >= posX) && (clickX <= posX + boxSize) && (clickY >= posY) && (clickY <= posY + boxSize)) { 
        return 1;
    }
    return 0;
}

void startTimer() {
    startTime = SDL_GetTicks();
}

void clickOnZeroDisplayCells(int row, int col) {
    int colBombIndex = 0;
    for (int colCellIndex = 0; colCellIndex < COLS; colCellIndex++) 
    {
        if (mineGrid->mine[row][colCellIndex] >= 18) {
            colBombIndex = colCellIndex;
            continue;
        }
        
        if (mineGrid->mine[row][colCellIndex] < 10) {
            continue;
        }
        if ((col < colCellIndex) && (colCellIndex > colBombIndex)) {
            break;
        }
        displayCell(row, colCellIndex);
    }
}

// Game loop
SDL_AppResult SDL_AppIterate(void *appstate)
{
    int game_end = 0;
    if (game_end) {
        return SDL_APP_SUCCESS;
    }
    
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);
    RenderGridCols(mineGrid->grid_x, mineGrid->cols);
    RenderGridRows(mineGrid->grid_y, mineGrid->rows);
    RenderMineSweeperGrid();

    for (int i = 0; i < BOX_COUNT; i++) {
        RenderBox(
            boxDimensions->positions[i],
            boxDimensions->boxY,
            boxDimensions->boxSize
        );
    }

    int red = 0;
    int green = 130;
    int blue = 255;

    SDL_SetRenderScale(renderer, 1.5f, 1.5f);
    SDL_SetRenderDrawColor(renderer, green, red, blue, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, (boxDimensions->positions[MIDDLE_BOX] + 12) / 1.5f, (boxDimensions->boxY + 35) / 1.5f, "%s", "reset");
    SDL_SetRenderScale(renderer, 3.0f, 3.0f);
    
    if (!isGameOver() && startTime > 0 && !isGameCompleted()) {
        Uint64 elapsedSeconds = (SDL_GetTicks() - startTime) / 1000;
        if (elapsedSeconds > 999) {
            elapsedSeconds = 999;
        }
        gameVitals->timer = (int)elapsedSeconds;
    }

    
    RenderText(red, green, blue, 30, boxDimensions->positions[LEFT_BOX], boxDimensions->boxY, BOMBS_COUNT);
    if (isGameCompleted() || startTime == 0) {
        RenderText(red, green, blue, 30, boxDimensions->positions[RIGHT_BOX], boxDimensions->boxY, gameVitals->gameCompletedTime);
    } else {
        RenderText(red, green, blue, 30, boxDimensions->positions[RIGHT_BOX], boxDimensions->boxY, gameVitals->timer);
    }
    
    
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    SDL_RenderPresent(renderer);
    
    return SDL_APP_CONTINUE;
}

//UTILISATION DE SDL_AppQuit pour clean la mémoire
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    reset_data(mineGrid);
    reset_data(gameVitals);
    reset_data(boxDimensions);
    /* SDL will clean up the window/renderer for us. */
}

// FONCTIONS DE RENDU
void RenderGridCols(int grid_x, int cols) {
    for (int i = 0; i <= cols; i++) {
        float x = grid_x + i * mineGrid->cell_size;
        SDL_RenderLine(
            renderer, 
            x, 
            mineGrid->grid_y, 
            x, 
            mineGrid->grid_y + mineGrid->rows * mineGrid->cell_size);
    }
}

void RenderGridRows(int grid_y, int rows) {
    for (int i = 0; i <= rows; i++) {
        float y = grid_y + i * mineGrid->cell_size;
        SDL_RenderLine(
            renderer, 
            mineGrid->grid_x, 
            y, 
            mineGrid->grid_x + mineGrid->cols * mineGrid->cell_size, 
            y
        );
    }
}

void RenderBox(float box_x, float box_y, float box_size) {
    SDL_FRect box = { box_x, box_y, box_size, box_size };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderRect(renderer, &box);
}

void RenderText(int green, int red, int blue, int padding, int x, int y, int info) {
    if (info >= 10) {
        padding = 18;
    }
    if (info >= 100) {
        padding = 6;
    }
    SDL_SetRenderDrawColor(renderer, green, red, blue, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugTextFormat(renderer, (x + padding) / 3.0f, (y + 30) / 3.0f, "%d", info);
}

void RenderMineSweeperGrid() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int padding_x = mineGrid->grid_x + mineGrid->cell_size * j + mineGrid->cell_size / 2 - 4;
            int padding_y = mineGrid->grid_y + mineGrid->cell_size * i + mineGrid->cell_size / 2 - 4;

            SDL_SetRenderScale(renderer, 2.0f, 2.0f);
            switch (mineGrid->mine[i][j]) {
                case 0:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDebugTextFormat(renderer, (padding_x) / 2.0f, (padding_y) / 2.0f, "%d", mineGrid->mine[i][j]);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderDebugTextFormat(renderer, (padding_x) / 2.0f, (padding_y) / 2.0f, "%d", mineGrid->mine[i][j]);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDebugTextFormat(renderer, (padding_x) / 2.0f, (padding_y) / 2.0f, "%d", mineGrid->mine[i][j]);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDebugTextFormat(renderer, (padding_x) / 2.0f, (padding_y) / 2.0f, "%d", mineGrid->mine[i][j]);
                    break;
                case 4:
                    SDL_SetRenderDrawColor(renderer, 128, 0, 128, SDL_ALPHA_OPAQUE);
                    SDL_RenderDebugTextFormat(renderer, (padding_x) / 2.0f, (padding_y) / 2.0f, "%d", mineGrid->mine[i][j]);
                    break;
                case 8:
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDebugTextFormat(renderer, (padding_x) / 2.0f, (padding_y) / 2.0f, "%c", '*');
                    break;
                case 10 ... 18: //NON STANDARD CODE, IS A GNU EXTENSION THAT WORKS WITH GCC COMPILER
                    break;
                default:
                    break;
            }
            
            SDL_SetRenderScale(renderer, 1.0f, 1.0f);
        }
    }
}

