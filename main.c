#include "raylib.h"

#define W 800
#define H 450
#define FPS 60

static const char *title = "raylib [core] example - basic window";
static char *default_text = "Congrats! You created your first window!";

static const char *spritesheet_filename = "Sprite-0001.png";
static const Rectangle sprite1 = {0.f, 0.f, 8.f, 8.f};

void draw_text(char *text, int x, int y) {
    DrawText(text, x, y, 20, LIGHTGRAY);
}

int main()
{
    InitWindow(W, H, title);
    Texture2D spritesheet = LoadTexture(spritesheet_filename);
    Vector2 pos = {0, 0};
    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            draw_text(default_text, 190, 200);
            DrawTextureRec(spritesheet, sprite1, pos, WHITE);
            pos.x += 1;
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
