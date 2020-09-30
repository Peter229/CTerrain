#pragma once
#include "chunk.h"
#include "cglm/cglm.h"
#include <stdlib.h>
#include "noise.h"

//Has to be odd
#define WORLD_WIDTH 17
#define MAX_CHUNKS (WORLD_WIDTH * WORLD_WIDTH * WORLD_WIDTH)

struct World {

	//Use array as map
	/*
	[0,0,0,0,0
	 0,0,0,0,0
	 0,0,0,0,0
	 0,0,0,0,0
	 0,0,0,0,0]
	*/
	struct Chunk* chunks[MAX_CHUNKS];
	size_t num_chunks_to_loaded;
	vec3 old_pos;
	struct Noise world_height_noise;
	struct Noise world_biome_noise;
	vec3 old_player_pos;
};

void world_give_neighbors(struct World* world);

void world_generate(struct World* world, vec3 player_pos);

void world_generate_noise(struct World* world);

void world_render(struct World* world, unsigned int* shader);

void world_delete(struct World* world);

void world_gen_update(struct World* world, vec3 player_pos);

void world_find_new_chunk(struct World* world, int pos, int player_chunk_x, int player_chunk_y, int player_chunk_z);