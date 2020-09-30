#pragma once
#include "gl_includes.h"
#include "block.h"
#include <stdlib.h>
#include "noise.h"

#define CHUNK_SIZE 32
#define CHUNK_VOLUME (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)
#define FLOATS_PER_VERTEX 9
#define FLOATS_PER_FACE (6 * FLOATS_PER_VERTEX)
#define FIELD 1
#define BEACH 4
#define MOUNTAIN 3

struct Chunk {

	uint8_t blocks[CHUNK_VOLUME];
	Array vertices;
	unsigned int vao, vbo;
	uint8_t should_render;
	uint8_t generated;
	uint8_t has_blocks;
	struct Chunk* neighbors[6];
	uint8_t left, right, front, back, top, bottom;
	int x, y, z;
};

void chunk_give_neighbor(struct Chunk* chunk, struct Chunk* neighbor, int side);

void chunk_init(struct Chunk* chunk, int x, int y, int z, struct Noise* height_noise, struct Noise* biome_noise);

void chunk_gen(struct Chunk* chunk, struct Noise* height_noise, struct Noise* biome_noise);

void chunk_build_mesh(struct Chunk* chunk);

void chunk_delete(struct Chunk* chunk);

void chunk_render(struct Chunk* chunk);

void chunk_get_biome(int x, int z, int* biome_id, struct Noise* biome_noise);