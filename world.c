#include "world.h"

void world_generate(struct World* world, vec3 player_pos) {

	int player_chunk_x = player_pos[0] / CHUNK_SIZE;
	int player_chunk_y = player_pos[1] / CHUNK_SIZE;
	int player_chunk_z = player_pos[2] / CHUNK_SIZE;

	glm_vec3_copy(player_pos, world->old_player_pos);

	int middle_array = WORLD_WIDTH / 2;
	for (int x = 0; x < WORLD_WIDTH; x++) {

		for (int y = 0; y < WORLD_WIDTH; y++) {

			for (int z = 0; z < WORLD_WIDTH; z++) {

				world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)] = malloc(sizeof(struct Chunk));
				chunk_init(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
				world->num_chunks_to_loaded++;
			}
		}
	}

	world_give_neighbors(world);
}

void world_generate_noise(struct World* world) {

	noise_gen_height_map(&world->world_height_noise, 523);
	noise_gen_height_map(&world->world_biome_noise, 123);
}

void world_give_neighbors(struct World* world) {

	for (int x = 0; x < WORLD_WIDTH; x++) {

		for (int y = 0; y < WORLD_WIDTH; y++) {

			for (int z = 0; z < WORLD_WIDTH; z++) {

				if ((!world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->should_render) && world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated && world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->has_blocks) {

					for (int i = 0; i < WORLD_WIDTH; i++) {

						for (int j = 0; j < WORLD_WIDTH; j++) {

							for (int k = 0; k < WORLD_WIDTH; k++) {

								int x_test = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x - world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->x;
								int y_test = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y - world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->y;
								int z_test = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z - world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->z;
								
								//ijk is left chunk
								if (x_test == 1 && y_test == 0 && z_test == 0) {

									chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)], LEFT);
								}
								else if (x_test == -1 && y_test == 0 && z_test == 0) {

									chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)], RIGHT);
								}
								else if (x_test == 0 && y_test == 1 && z_test == 0) {

									chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)], BOTTOM);
								}
								else if (x_test == 0 && y_test == -1 && z_test == 0) {

									chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)], TOP);
								}
								else if (x_test == 0 && y_test == 0 && z_test == 1) {

									chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)], BACK);
								}
								else if (x_test == 0 && y_test == 0 && z_test == -1) {

									chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)], FRONT);
								}
							}
						}
					}
				}
			}
		}
	}
						/*if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * (z - 1))]->generated) {

							chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * (z - 1))], BACK);
						}
					}
					if (z < WORLD_WIDTH - 1) {

						if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * (z + 1))]->generated) {

							chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * (z + 1))], FRONT);
						}
					}

					if (x > 0) {

						if (world->chunks[(x - 1) + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

							chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[(x - 1) + WORLD_WIDTH * (y + WORLD_WIDTH * z)], LEFT);
						}
					}
					if (x < WORLD_WIDTH - 1) {

						if (world->chunks[(x + 1) + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

							chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[(x + 1) + WORLD_WIDTH * (y + WORLD_WIDTH * z)], RIGHT);
						}
					}

					if (y > 0) {

						if (world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->generated) {

							chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)], BOTTOM);
						}
					}
					if (y < WORLD_WIDTH - 1) {

						if (world->chunks[x + WORLD_WIDTH * ((y + 1) + WORLD_WIDTH * z)]->generated) {

							chunk_give_neighbor(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], world->chunks[x + WORLD_WIDTH * ((y + 1) + WORLD_WIDTH * z)], TOP);
						}
					}
				}
			}
		}
	}*/
}

void world_render(struct World* world, unsigned int* shader) {

	for (int i = 0; i < world->num_chunks_to_loaded; i++) {
		
		if (world->chunks[i]->should_render) {

			mat4 model;
			vec3 translate;
			translate[0] = world->chunks[i]->x * CHUNK_SIZE;
			translate[1] = world->chunks[i]->y * CHUNK_SIZE;
			translate[2] = world->chunks[i]->z * CHUNK_SIZE;
			glm_translate_make(model, translate);
			glUniformMatrix4fv(glGetUniformLocation(*shader, "model"), 1, GL_FALSE, (float *)model);
			chunk_render(world->chunks[i]);
		}
	}
}

void world_delete(struct World* world) {

	for (int i = 0; i < world->num_chunks_to_loaded; i++) {

		if (world->chunks[i]->generated) {

			chunk_delete(world->chunks[i]);
		}

		free(world->chunks[i]);
	}
}

void world_find_new_chunk(struct World* world, int pos, int player_chunk_x, int player_chunk_y, int player_chunk_z) {

	int middle_array = WORLD_WIDTH / 2;

	for (int i = 0; i < WORLD_WIDTH; i++) {

		for (int j = 0; j < WORLD_WIDTH; j++) {

			for (int k = 0; k < WORLD_WIDTH; k++) {

				bool found = true;

				int try_gen_x = player_chunk_x + (i - middle_array);
				int try_gen_y = player_chunk_y + (j - middle_array);
				int try_gen_z = player_chunk_z + (k - middle_array);

				for (int x = 0; x < MAX_CHUNKS; x++) {
					int test_x = world->chunks[x]->x;
					int test_y = world->chunks[x]->y;
					int test_z = world->chunks[x]->z;
					if (try_gen_x == test_x && try_gen_y == test_y && try_gen_z == test_z) {
						found = false;
					}
				}

				if (found) {
					chunk_init(world->chunks[pos], try_gen_x, try_gen_y, try_gen_z, &world->world_height_noise, &world->world_biome_noise);
					return;
				}
			}
		}
	}
}

void world_gen_update(struct World* world, vec3 player_pos) {

	int old_player_chunk_x = world->old_player_pos[0] / CHUNK_SIZE;
	int old_player_chunk_y = world->old_player_pos[1] / CHUNK_SIZE;
	int old_player_chunk_z = world->old_player_pos[2] / CHUNK_SIZE;
	int player_chunk_x = player_pos[0] / CHUNK_SIZE;
	int player_chunk_y = player_pos[1] / CHUNK_SIZE;
	int player_chunk_z = player_pos[2] / CHUNK_SIZE;
	int middle_array = WORLD_WIDTH / 2;

	glm_vec3_copy(player_pos, world->old_player_pos);

	if (old_player_chunk_x != player_chunk_x || old_player_chunk_y != player_chunk_y || old_player_chunk_z != player_chunk_z) {

		//printf("%d %d %d\n", player_chunk_x, player_chunk_y, player_chunk_z);

		for (int x = 0; x < WORLD_WIDTH; x++) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

						if (abs(player_chunk_x - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x) > middle_array || abs(player_chunk_z - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z) > middle_array || abs(player_chunk_y - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y) > middle_array) {

							chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							world_find_new_chunk(world, x + WORLD_WIDTH * (y + WORLD_WIDTH * z), player_chunk_x, player_chunk_y, player_chunk_z);
						}
					}
				}
			}
		}
		world_give_neighbors(world);
	}

	/*if (old_player_chunk_x != player_chunk_x || old_player_chunk_y != player_chunk_y || old_player_chunk_z != player_chunk_z) {

		printf("Cu7ll\n");

		for (int x = 0; x < WORLD_WIDTH; x++) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

						if (abs(player_chunk_x - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x) >= middle_array || abs(player_chunk_z - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z) >= middle_array || abs(player_chunk_y - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y) >= middle_array) {

							//printf("AHHH\n");
							chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
						}
					}
					/*if (!world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

						int try_gen_x = 0;
						int try_gen_y = 0;
						int try_gen_z = 0;

						for (int i = 0; i < WORLD_WIDTH; i++) {

							for (int j = 0; j < WORLD_WIDTH; j++) {

								for (int k = 0; k < WORLD_WIDTH; k++) {
									//printf("Uhhh\n");

									if (world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->generated) {

										int potential_x = world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->x;
										int potential_z = world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->y;
										int potential_y = world->chunks[i + WORLD_WIDTH * (j + WORLD_WIDTH * k)]->z;

										if (!(try_gen_x == potential_x && try_gen_y == potential_y && try_gen_z == potential_z)) {

											try_gen_x = player_chunk_x + (i - middle_array);
											try_gen_y = player_chunk_y + (j - middle_array);
											try_gen_z = player_chunk_z + (k - middle_array);
											//printf("HELP\n");
										}
									}
								}
							}
						}
						if (try_gen_x != 0 || try_gen_y != 0 || try_gen_z != 0) {
							printf("Hello\n");
							printf("%d %d %d \n", try_gen_x, try_gen_y, try_gen_z);
							chunk_init(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], try_gen_x, try_gen_y, try_gen_z, &world->world_height_noise, &world->world_biome_noise);
						}
					}
					printf("Hmm\n");*/
				/*}
			}
		}
		//world_give_neighbors(world);

		glm_vec3_copy(player_pos, world->old_player_pos);
	}*/


	//if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->x == player_chunk_x && world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->y == player_chunk_y && world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->z == player_chunk_z) {
	//	alligned = true;
	//}

	//printf("PLAYER %d %d %d\n", player_chunk_x, player_chunk_y, player_chunk_z);

	//printf("CHUNK %d %d %d\n", world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->x, world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->y, world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->z);

	//if (!alligned) {

		//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

		//Player has moved up
		/*if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->y < player_chunk_y) {

			printf("UP\n");

			for (int x = 0; x < WORLD_WIDTH; x++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					for (int y = 0; y < WORLD_WIDTH; y++) {

						//printf("START %d %d %d\n", world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z);

						if (y == 0) {

							if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

								chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
								//free(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
								//free(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
								printf("aaaaa %d %d %d\n", world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z);
							}
						}
						else if (y == WORLD_WIDTH - 1) {
							//printf("NEW CHUNK\n");
							world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
							//chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							//free(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							printf("ggggg %d %d %d\n", world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->z);
							world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)] = realloc(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], sizeof(struct Chunk));
							chunk_init(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
							printf("ccccc %d %d %d\n", world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z);
						}
						else {
							//printf("fffff %d %d %d\n", world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->z);
							//printf("hhhhh %d %d %d\n", world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z);
							//world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)] = malloc(world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)], sizeof(struct Chunk));
							world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
							//chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							//printf("eeeee %d %d %d\n", world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->x, world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->y, world->chunks[x + WORLD_WIDTH * ((y - 1) + WORLD_WIDTH * z)]->z);

						}
					}
				}
			}
		}//Player has moved down*/
		/*else if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)]->y > player_chunk_y) {

			printf("DOWN\n");
			for (int x = 0; x < WORLD_WIDTH; x++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					for (int y = WORLD_WIDTH - 1; y >= 0; y--) {

						if (y == WORLD_WIDTH - 1) {

							if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

								chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
								//free(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							}
						}
						else if (y == 0) {

							world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)] = malloc(sizeof(struct Chunk));
							chunk_init(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
						}
						else {
							world->chunks[x + WORLD_WIDTH * ((y + 1) + WORLD_WIDTH * z)] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
						}
					}
				}
			}
		}*/
		/*
		//Player has moved right
		if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)].x < player_chunk_x) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					for (int x = 0; x < WORLD_WIDTH; x++) {

						if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)].generated) {

							if (x == 0) {

								chunk_delete(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							}
							else if (x == WORLD_WIDTH - 1) {
								chunk_init(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
							}
							else {
								world->chunks[(x - 1) + WORLD_WIDTH * (y + WORLD_WIDTH * z)] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
							}
						}
					}
				}
			}
		}//Player has moved left
		else if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)].x > player_chunk_x) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					for (int x = WORLD_WIDTH - 1; x >= 0; x--) {

						if (x == WORLD_WIDTH - 1) {

							if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)].generated) {

								chunk_delete(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							}
						}
						else if (x == 0) {
							chunk_init(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
						}
						else {
							world->chunks[(x + 1) + WORLD_WIDTH * (y + WORLD_WIDTH * z)] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
						}
					}
				}
			}
		}

		//Player has moved forward
		if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)].z < player_chunk_z) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int x = 0; x < WORLD_WIDTH; x++) {

					for (int z = 0; z < WORLD_WIDTH; z++) {

						if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)].generated) {

							if (z == 0) {

								chunk_delete(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							}
							else if (z == WORLD_WIDTH - 1) {
								chunk_init(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
							}
							else {
								world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * (z - 1))] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
							}
						}
					}
				}
			}
		}//Player has moved backward
		else if (world->chunks[middle_array + WORLD_WIDTH * (middle_array + WORLD_WIDTH * middle_array)].z > player_chunk_z) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int x = 0; x < WORLD_WIDTH; x++) {

					for (int z = WORLD_WIDTH - 1; z >= 0; z--) {

						if (z == WORLD_WIDTH - 1) {

							if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)].generated) {

								chunk_delete(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
							}
						}
						else if (z == 0) {
							chunk_init(&world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
						}
						else {
							world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * (z + 1))] = world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)];
						}
					}
				}
			}
		}
		*/
		/*printf("NOT ALLIGNED\n");

		for (int x = 0; x < WORLD_WIDTH; x++) {

			for (int y = 0; y < WORLD_WIDTH; y++) {

				for (int z = 0; z < WORLD_WIDTH; z++) {

					if (world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->generated) {

						if (abs(player_chunk_x - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->x) > middle_array || abs(player_chunk_z - world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]->z) > middle_array) {

							chunk_delete(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)]);
						}
					}

					//chunk_init(world->chunks[x + WORLD_WIDTH * (y + WORLD_WIDTH * z)], player_chunk_x + (x - middle_array), player_chunk_y + (y - middle_array), player_chunk_z + (z - middle_array), &world->world_height_noise, &world->world_biome_noise);
				}
			}
		}
		world_give_neighbors(world);
	}*/
}