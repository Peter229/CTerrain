#pragma once
#include "dynamic_array.h"
#include <stdint.h>
#include <math.h>

#define TOP 0
#define BOTTOM 1
#define RIGHT 2
#define LEFT 3
#define FRONT 4
#define BACK 5

#define TEXTURE_MAP_SIZE 256
#define TEXTURE_SIZE 16
#define TEXTURES_PER_ROW (TEXTURE_MAP_SIZE / TEXTURE_SIZE)

void block_add_vertices(uint8_t block_id, uint8_t face, float x, float y, float z, struct Array* vertices);

void block_insert_cube_top(uint8_t block_id, uint8_t face, float x, float y, float z, struct Array* vertices);

void block_add_colour(uint8_t block_id, uint8_t face, struct Array* vertices);

void block_add_texture(uint8_t block_id, uint8_t face, uint8_t vert, struct Array* vertices);

void block_add_face(uint8_t block_id, uint8_t face, float x, float y, float z, struct Array* vertices);