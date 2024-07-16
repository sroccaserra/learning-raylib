#include "raylib.h"

#define W 800
#define H 450
#define FPS 60

static const char *title = "raylib [core] example - basic window";

int main()
{
    InitWindow(W, H, title);
    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
