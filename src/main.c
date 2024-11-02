#include "raylib.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mpeg2dec/mpeg2.h>
#include <mpeg2dec/mpeg2convert.h>

#define WIDTH 700
#define HEIGHT 500
#define BUFFER_SIZE 4096
#define VID "data/test.mpg"

int main(void) {
  InitWindow(WIDTH, HEIGHT, "raylib example - basic template");
  mpeg2dec_t *decoder = mpeg2_init();
  if (!decoder) {
    TraceLog(LOG_ERROR, "could not init the decoder");
    exit(EXIT_FAILURE);
  }
  const mpeg2_info_t *info = mpeg2_info(decoder);
  mpeg2_state_t state;
  FILE *mpegfile = fopen(VID, "rb");
  if (!mpegfile) {
    TraceLog(LOG_ERROR, "could not open the video file!");
    exit(EXIT_FAILURE);
  }

  int frameCount, lastFrame = 0;
  Image img = {0};
  Texture texture = {0};
  size_t size;
  uint8_t buffer[BUFFER_SIZE];
  bool gotDims = false;

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    lastFrame = frameCount;
    while (lastFrame == frameCount) {
      state = mpeg2_parse(decoder);
      switch (state) {
      case STATE_BUFFER:
        size = fread(buffer, 1, BUFFER_SIZE, mpegfile);
        mpeg2_buffer(decoder, buffer, buffer + BUFFER_SIZE);
        if (size == 0) {
          rewind(mpegfile);
          frameCount = 0;
        }
        break;
      case STATE_SEQUENCE:
        mpeg2_convert(decoder, mpeg2convert_rgb24, NULL);
        break;
      case STATE_SLICE:
      case STATE_END:
      case STATE_INVALID_END:
        if (info->display_fbuf) {
          if (gotDims == false) {
            gotDims = true;
            img.width = info->sequence->width;
            img.height = info->sequence->height;
            img.mipmaps = 1;
            img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
            img.data = (unsigned char *)malloc(img.width * img.height * 3);

            texture = LoadTextureFromImage(img);
            UnloadImage(img);
          }
          UpdateTexture(texture, info->display_fbuf->buf[0]);
          frameCount++;
        }
        break;
      default:
        break;
      }
    }
    BeginDrawing();
    DrawFPS(10, 10);
    DrawTexturePro(texture, (Rectangle){0, 0, texture.width, texture.height},
                   (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                   (Vector2){0, 0}, 0, WHITE);

    EndDrawing();
  }

  UnloadTexture(texture);
  mpeg2_close(decoder);
  fclose(mpegfile);
  CloseWindow();
  return EXIT_SUCCESS;
}
