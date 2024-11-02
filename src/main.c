#include "raylib.h"
#include <stdlib.h>

#define WIDTH 700
#define HEIGHT 500

int main(void) {
  InitWindow(WIDTH, HEIGHT, "raylib example - basic template");
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);
    DrawText("https://github.com/kaandesu/raylib-template.git", 100,
             (HEIGHT / 2) - 10, 20, BLACK);
    EndDrawing();
  }
  CloseWindow();
  return EXIT_SUCCESS;
}
