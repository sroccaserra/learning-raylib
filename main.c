#ifndef M_PI
#define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "raylib.h"

#define W 800
#define H 450
#define CENTER_X (W/2)
#define CENTER_Y (H/2)

#define FPS 60

static const char *title = "Moving particles";

#define NB_PARTICLES 120
#define Z_NEAR 10
#define Z_FAR 100
#define Z_MID ((Z_FAR - Z_NEAR)/2)

#define R_MIN 17
#define R_MAX 23

#define NEAR_COLOR (Color){ 255, 109, 194, 255 }
#define FAR_COLOR (Color){ 200, 30, 104, 255 }

#define A ((R_MIN - (float)R_MAX)/(Z_FAR - Z_NEAR))
#define B (R_MIN - Z_FAR*A)

struct state {
    Vector3 positions[NB_PARTICLES];
    float phases[NB_PARTICLES];
};

#define x_phase(phase) (CENTER_X*(1+sin(phase)))
#define z_phase(phase) (Z_NEAR + (Z_FAR - Z_NEAR)*sin(phase))

void init(struct state *s) {
    for (int i = 0; i < NB_PARTICLES; ++i) {
        float phase = (2*M_PI*rand())/RAND_MAX;
        s->phases[i] = phase;

        float x = x_phase(phase);
        float y = rand()%H;
        float z = z_phase(phase);
        s->positions[i] = (Vector3){x, y, z};
    }
}

void update(struct state *s) {
    for (int i = 0; i < NB_PARTICLES; ++i) {
        Vector3 *pos = &s->positions[i];
        s->phases[i] += 0.015;
        float phase = s->phases[i];
        pos->x = x_phase(phase);
        pos->z = z_phase(phase+M_PI/2);
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
                float z = (*pos).z;
                float r = A*z + B;
                Color color = (z > Z_MID) ? FAR_COLOR : NEAR_COLOR;
                DrawRectangle((*pos).x, (*pos).y, r, r, color);
            }
        EndDrawing();
        update(&state);
    }

    CloseWindow();

    return 0;
}
