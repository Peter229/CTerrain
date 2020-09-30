#include "chunk.h"

void chunk_give_neighbor(struct Chunk* chunk, struct Chunk* neighbor, int side) {

	chunk->neighbors[side] = neighbor;
	if (side == FRONT) {
		chunk->front = 1;
	}
	if (side == BACK) {
		chunk->back = 1;
	}
	if (side == LEFT) {
		chunk->left = 1;
	}
	if (side == RIGHT) {
		chunk->right = 1;
	}
	if (side == TOP) {
		chunk->top = 1;
	}
	if (side == BOTTOM) {
		chunk->bottom = 1;
	}
	if (chunk->right && chunk->left && chunk->front && chunk->back && chunk->top && chunk->bottom) {

		chunk_build_mesh(chunk);
	}
}

void chunk_init(struct Chunk* chunk, int x, int y, int z, struct Noise* height_noise, struct Noise* biome_noise) {

	//printf("L\n");
	chunk->should_render = 0;
	chunk->generated = 0;
	chunk->has_blocks = 0;
	dynamic_array_init(&chunk->vertices, 16);
	chunk->x = x;
	chunk->y = y;
	chunk->z = z;
	chunk->left = chunk->right = chunk->front = chunk->back = chunk->top = chunk->bottom = 0;

	chunk_gen(chunk, height_noise, biome_noise);
}

void chunk_get_biome(int x, int z, int* biome_id, struct Noise* biome) {


	float frequency = 16.0;

	float val = fnlGetNoise2D(&biome->noise, (float)x / frequency, (float)z / frequency);

	val = (val + 1.0) / 2.0;

	if (val > 0.5) {

		*biome_id = FIELD;
	}
	else if (val > 0.4) {
		
		*biome_id =  BEACH;
	}
	else {
		*biome_id = MOUNTAIN;
	}
}

void chunk_gen(struct Chunk* chunk, struct Noise* height_noise, struct Noise* biome_noise) {

	double frequency = 16.0;

	for (int x = 0; x < CHUNK_SIZE; x++) {

		for (int y = 0; y < CHUNK_SIZE; y++) {

			for (int z = 0; z < CHUNK_SIZE; z++) {

				int biome = 1;
				chunk_get_biome((chunk->x * CHUNK_SIZE) + x, (chunk->z * CHUNK_SIZE) + z, &biome, biome_noise);

				double value = fnlGetNoise2D(&height_noise->noise, (x + chunk->x * CHUNK_SIZE), (z + chunk->z * CHUNK_SIZE));
				//printf("%f\n", value);
				value = (value + 1.0) / 2.0;
				value *= 20.0;
				value += 1760.0;
			

				int chunk_y = (chunk->y * CHUNK_SIZE) + y;

				if (chunk_y <= value) {
					chunk->has_blocks = 1;
				}
				
				if (chunk_y == (int)value) {

					chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)] = biome;
				}
				else if (chunk_y < value && chunk_y > value - 3) {

					chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)] = 2;
				}
				else if (chunk_y < value) {

					chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)] = 3;
				}
				else {
					chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)] = 0;
				}
			}
		}
	}

	//free(noise_data);

	chunk->generated = 1;

	//if (chunk->should_render) {
		//printf("Start build\n");
		//chunk_build_mesh(chunk);
	//}
}

void chunk_build_mesh(struct Chunk* chunk) {

	for (int x = 0; x < CHUNK_SIZE; x++) {

		for (int y = 0; y < CHUNK_SIZE; y++) {

			for (int z = 0; z < CHUNK_SIZE; z++) {

				uint8_t block_type = chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * z)];

				if (block_type > 0) {

					//No Block above - 1 to avoid chunk border case
					if (y < CHUNK_SIZE - 1) {
						if (chunk->blocks[x + CHUNK_SIZE * ((y + 1) + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, TOP, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (y > 0) {
						if (chunk->blocks[x + CHUNK_SIZE * ((y - 1) + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, BOTTOM, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (y == CHUNK_SIZE - 1 && chunk->top) {
						if (chunk->neighbors[TOP]->blocks[x + CHUNK_SIZE * (0 + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, TOP, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (y == 0 && chunk->bottom) {
						if (chunk->neighbors[BOTTOM]->blocks[x + CHUNK_SIZE * ((CHUNK_SIZE - 1) + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, BOTTOM, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}

					if (x < CHUNK_SIZE - 1) {
						if (chunk->blocks[(x + 1) + CHUNK_SIZE * (y + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, RIGHT, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (x > 0) {
						if (chunk->blocks[(x - 1) + CHUNK_SIZE * (y + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, LEFT, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (x == CHUNK_SIZE - 1 && chunk->right) {
						if (chunk->neighbors[RIGHT]->blocks[0 + CHUNK_SIZE * (y + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, RIGHT, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (x == 0 && chunk->left) {
						if (chunk->neighbors[LEFT]->blocks[(CHUNK_SIZE - 1) + CHUNK_SIZE * (y + CHUNK_SIZE * z)] == 0) {
							block_add_vertices(block_type, LEFT, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}

					if (z < CHUNK_SIZE - 1) {
						if (chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * (z + 1))] == 0) {
							block_add_vertices(block_type, FRONT, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (z > 0) {
						if (chunk->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * (z - 1))] == 0) {
							block_add_vertices(block_type, BACK, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (z == CHUNK_SIZE - 1 && chunk->front) {
						if (chunk->neighbors[FRONT]->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * (0))] == 0) {
							block_add_vertices(block_type, FRONT, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
					if (z == 0 && chunk->back) {
						if (chunk->neighbors[BACK]->blocks[x + CHUNK_SIZE * (y + CHUNK_SIZE * (CHUNK_SIZE - 1))] == 0) {
							block_add_vertices(block_type, BACK, (float)x, (float)y, (float)z, &chunk->vertices);
						}
					}
				}
			}
		}
	}

	if (chunk->vertices.used > 0) {

		chunk->should_render = 1;

		glGenVertexArrays(1, &chunk->vao);
		glGenBuffers(1, &chunk->vbo);

		glBindVertexArray(chunk->vao);

		glBindBuffer(GL_ARRAY_BUFFER, chunk->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * chunk->vertices.used, &chunk->vertices.array[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, FLOATS_PER_VERTEX * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}

void chunk_render(struct Chunk* chunk) {

	if (chunk->should_render) {

		glBindVertexArray(chunk->vao);
		glDrawArrays(GL_TRIANGLES, 0, chunk->vertices.used / FLOATS_PER_VERTEX);
	}
}

void chunk_delete(struct Chunk* chunk) {

	if (chunk->should_render) {

		glDeleteVertexArrays(1, &chunk->vao);
		glDeleteBuffers(1, &chunk->vbo);
	}
	dynamic_array_free(&chunk->vertices);
	chunk->should_render = 0;
	chunk->generated = 0;
	chunk->left = chunk->right = chunk->front = chunk->back = chunk->top = chunk->bottom = 0;
	chunk->has_blocks = 0;
}