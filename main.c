#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#define W 800
#define H 450
#define FPS 60

static const char *title = "Moving particles";

#define NB_PARTICLES 120
#define Z_NEAR 10
#define Z_FAR 100
#define R_MIN 10
#define R_MAX 30

// 10 -> 10
// 100 -> 30
//
// az_near+b = r_max
// az_far+b = r_min
//
// a100 - a10 = r_min - r_max
// a(z_far-z_near) = r_min - r_max
// a = (r_min - r_max)/(z_far-z_near)
// z_far(r_min - r_max)/(z_far-z_near) + b = r_min
// b = r_min - z_far(r_min - r_max)/(z_far-z_near)

#define A ((R_MIN - (float)R_MAX)/(Z_FAR - Z_NEAR))
#define B (R_MIN - Z_FAR*A)

struct state {
    Vector3 positions[NB_PARTICLES];
};

void init(struct state *s) {
    for (int i = 0; i < NB_PARTICLES; ++i) {
        float x = rand()%W;
        float y = rand()%H;
        float z = Z_NEAR + rand()%(Z_FAR - Z_NEAR);
        s->positions[i] = (Vector3){x, y, z};
    }
}

int main()
{
    InitWindow(W, H, title);
    SetTargetFPS(FPS);
    struct state state = {0};

    init(&state);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = 0; i < NB_PARTICLES; ++i) {
                Vector3 *pos = &state.positions[i];
                float r = A*(*pos).z + B;
                DrawRectangle((*pos).x, (*pos).y, r, r, WHITE);
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
