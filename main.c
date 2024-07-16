#include "raylib.h"

#define W 800
#define H 450
#define FPS 60

static const char *title = "raylib [core] example - basic window";
static char *default_text = "Congrats! You created your first window!";

void draw_text(char *text, int x, int y) {
    DrawText(text, x, y, 20, LIGHTGRAY);
}

int main()
{
    InitWindow(W, H, title);
    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            draw_text(default_text, 190, 200);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
