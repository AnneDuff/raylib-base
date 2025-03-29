#include "entrypoint.h"
#include "raylib.h"

#include <time.h>

#define RECT_SIZE 30
#define MAX_COL 30
#define MAX_ROW 30
#define WIN_W MAX_COL * RECT_SIZE
#define WIN_H MAX_ROW * RECT_SIZE

bool cells[MAX_ROW][MAX_COL] = {0}; 



void raylib_start(void){
    InitWindow(WIN_W,WIN_H,"Conway's Game of Life!");
    SetTargetFPS(5);

    SetRandomSeed(time(NULL));

    //COLORS
    Color alive = {96, 247, 197, 255};
    Color dead = {90, 111, 153, 255};

    for(int i = 0; i < MAX_ROW; ++i){
        for(int j = 0; j < MAX_COL; ++j){
            cells[i][j] = GetRandomValue(0,1);
        }
    }

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(dead);

        for(int y = 0; y < MAX_ROW; y++){
            for(int x = 0; x < MAX_COL; ++x){
                float offset = (y % 2 == 0) * RECT_SIZE;
                if(x % 2 == 0){
                    Rectangle squares = CLITERAL(Rectangle){
                        .x=(float)(x * RECT_SIZE + offset), .y=(float)(y * RECT_SIZE),
                        .width=RECT_SIZE, .height=RECT_SIZE
                    };
                    DrawRectangleLinesEx(
                        squares,
                        2,
                        YELLOW
                    );
                }
                else{
                    Rectangle squares = CLITERAL(Rectangle){
                        .x = (float)(x * RECT_SIZE - offset), .y = (float)(y * RECT_SIZE),
                        .width = RECT_SIZE, .height = RECT_SIZE
                    };
                    DrawRectangleLinesEx(
                        squares,
                        2,
                        YELLOW
                    );
                }

                int neighbors = 0;
                int pos = 1;
                for(int i = 0; i < 2;i++){
                    if(cells[y-pos][x] == 1){
                        neighbors++;
                    }
                    if(cells[y][x-pos] == 1){
                        neighbors++;
                    }
                    if(cells[y-pos][x-pos] == 1){
                        neighbors++;
                    }
                    if(cells[y-pos][x+pos] == 1){
                        neighbors++;
                    }
                    pos-=2;
                }
                
                if(neighbors<2){
                    DrawRectangle(x * RECT_SIZE, y * RECT_SIZE, RECT_SIZE, RECT_SIZE, dead);
                    cells[x][y]=0;
                }
                if(neighbors>3){
                    DrawRectangle(x * RECT_SIZE, y * RECT_SIZE, RECT_SIZE, RECT_SIZE, dead);
                    cells[x][y]=0;
                }
                if(cells[y][x] == 0 && neighbors == 3){
                    DrawRectangle(x * RECT_SIZE, y * RECT_SIZE, RECT_SIZE, RECT_SIZE, alive);
                    cells[x][y]=1;
                }
            }
        }
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}

//SOURCE: https://www.youtube.com/watch?v=daFYGrXq0aw (pour la logique à 1:03 et 36:31)