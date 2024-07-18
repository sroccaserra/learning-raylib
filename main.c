#ifndef M_PI
#define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "raylib.h"
#include "rlgl.h"

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

struct particule {
    float phase;
    Vector3 position;
};

struct state {
    Camera3D camera;
    float phase;
    struct particule particules[NB_PARTICLES];
};

#define x_phase(phase) (CENTER_X*(1+sin(phase)))
#define z_phase(phase) (Z_NEAR + (Z_FAR - Z_NEAR)*sin(phase))

void init(struct state *s) {
    *s = (struct state){0};
    rlDisableBackfaceCulling();
    s->camera = (Camera3D){
        .position = {10.f*sin(s->phase), 10.f*cos(s->phase), 10.f},
        .target = {0},
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.f,
        .projection = CAMERA_PERSPECTIVE,
    };

    for (int i = 0; i < NB_PARTICLES; ++i) {
        struct particule *p = &s->particules[i];
        float phase = (2*M_PI*rand())/RAND_MAX;
        p->phase = phase;

        float x = x_phase(phase);
        float y = rand()%H;
        float z = z_phase(phase);
        p->position = (Vector3){x, y, z};
    }
}

int cmp_z(const void *a, const void *b) {
    struct particule *lhs = (struct particule *)a;
    struct particule *rhs = (struct particule *)b;
    return rhs->position.z - lhs->position.z;
}

void update(struct state *s) {
    s->phase -= 0.025;
    s->camera.position = (Vector3){10.f*sin(s->phase), 10.f, 10.f*cos(s->phase)};
    for (int i = 0; i < NB_PARTICLES; ++i) {
        struct particule *p = &s->particules[i];
        Vector3 *pos = &p->position;
        p->phase += 0.015;
        float phase = p->phase;
        pos->x = x_phase(phase);
        pos->z = z_phase(phase+M_PI/2);
    }
    qsort(s->particules, NB_PARTICLES, sizeof(struct particule), cmp_z);
}

void draw_quad(Vector3 a, Vector3 b, Vector3 c, Vector3 d, Color color) {
    DrawTriangle3D(a, b, c, color);
    DrawTriangle3D(c, d, a, color);
}

void draw_3D_scene(struct state *s) {
    BeginMode3D(s->camera);

    Vector3 pos = {0};
    DrawCube(pos, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(pos, 2.0f, 2.0f, 2.0f, MAROON);

    float r = 3.f;
    Vector3 a = {0, 0, 0 },
            b = {0, r, 0 },
            c = {r, r, 0 },
            d = {r, 0, 0 };
    DrawGrid(100, .50f);
    draw_quad(a, b, c, d, WHITE);

    EndMode3D();
}

void draw_2D_scene(struct state *s) {
    for (int i = 0; i < NB_PARTICLES; ++i) {
        struct particule *p = &s->particules[i];
        Vector3 *pos = &p->position;
        float z = (*pos).z;
        float r = (A*z + B);
        Color color = (z > Z_MID) ? FAR_COLOR : NEAR_COLOR;
        DrawRectangle((*pos).x, (*pos).y, r, r, color);
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
            draw_3D_scene(&state);
            draw_2D_scene(&state);
        EndDrawing();

        update(&state);
    }

    CloseWindow();
    return 0;
}
