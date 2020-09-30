#include "block.h"

void block_add_vertices(uint8_t block_id, uint8_t face, float x, float y, float z, struct Array* vertices) {

	block_add_face(block_id, face, x, y, z, vertices);
}

void block_insert_cube_top(uint8_t block_id, uint8_t face, float x, float y, float z, struct Array* vertices) {
	
	block_add_face(block_id, face, x, y, z, vertices);
}

void block_add_face(uint8_t block_id, uint8_t face, float x, float y, float z, struct Array* vertices) {

	switch (face) {
	case TOP:
		//Vert 1
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 0, vertices);

		//Vert 2
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 1, vertices);

		//Vert 3
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 2, vertices);

		//Vert 4
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 3, vertices);

		//Vert 5
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 4, vertices);

		//Vert 6
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 5, vertices);
		break;
	case BOTTOM:
		//Vert 1
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 0, vertices);

		//Vert 2
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 1, vertices);

		//Vert 3
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 2, vertices);

		//Vert 4
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 3, vertices);

		//Vert 5
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 4, vertices);

		//Vert 6
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 5, vertices);
		break;
	case RIGHT:
		//Vert 1
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 0, vertices);

		//Vert 2
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 1, vertices);

		//Vert 3
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 2, vertices);

		//Vert 4
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 3, vertices);

		//Vert 5
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 4, vertices);

		//Vert 6
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 5, vertices);
		break;
	case LEFT:
		//Vert 1
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 0, vertices);

		//Vert 2
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 1, vertices);

		//Vert 3
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 2, vertices);

		//Vert 4
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 3, vertices);

		//Vert 5
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 4, vertices);

		//Vert 6
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 5, vertices);
		break;
	case FRONT:
		//Vert 1
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 0, vertices);

		//Vert 2
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 1, vertices);

		//Vert 3
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 2, vertices);

		//Vert 4
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 3, vertices);

		//Vert 5
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 4, vertices);

		//Vert 6
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 1.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 5, vertices);
		break;
	case BACK:
		//Vert 1
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 0, vertices);

		//Vert 2
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 1, vertices);

		//Vert 3
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 2, vertices);

		//Vert 4
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 0.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 3, vertices);

		//Vert 5
		dynamic_array_insert(vertices, x + 0.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 4, vertices);

		//Vert 6
		dynamic_array_insert(vertices, x + 1.0f);
		dynamic_array_insert(vertices, y + 1.0f);
		dynamic_array_insert(vertices, z + 0.0f);

		block_add_colour(block_id, face, vertices);

		block_add_texture(block_id, face, 5, vertices);
		break;
	default:
		break;
	}
}

void block_add_texture(uint8_t block_id, uint8_t face, uint8_t vert, struct Array* vertices) {

	float space = (float)TEXTURES_PER_ROW / (float)TEXTURE_MAP_SIZE;

	switch (block_id) {
	case 1:
	{
		switch (face) {
		case TOP:
		{
			int tex_id = block_id - 1;
			float u = fmodf((float)tex_id, (float)TEXTURES_PER_ROW);
			u = u / (float)TEXTURES_PER_ROW;
			float v = floor((float)tex_id / (float)TEXTURES_PER_ROW);
			v = v / (float)TEXTURES_PER_ROW;
			v = 1 - v;
			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			break;
		}
		case BOTTOM:
		{
			int tex_id = block_id + 1;
			float u = fmodf((float)tex_id, (float)TEXTURES_PER_ROW);
			u = u / (float)TEXTURES_PER_ROW;
			float v = floor((float)tex_id / (float)TEXTURES_PER_ROW);
			v = v / (float)TEXTURES_PER_ROW;
			v = 1 - v;
			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			break;
		}
		case RIGHT:
		{
			int tex_id = block_id;
			float u = fmodf((float)tex_id, (float)TEXTURES_PER_ROW);
			u = u / (float)TEXTURES_PER_ROW;
			float v = floor((float)tex_id / (float)TEXTURES_PER_ROW);
			v = v / (float)TEXTURES_PER_ROW;
			v = 1 - v;
			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			break;
		}
		case LEFT:
		{
			int tex_id = block_id;
			float u = fmodf((float)tex_id, (float)TEXTURES_PER_ROW);
			u = u / (float)TEXTURES_PER_ROW;
			float v = floor((float)tex_id / (float)TEXTURES_PER_ROW);
			v = v / (float)TEXTURES_PER_ROW;
			v = 1 - v;
			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			break;
		}
		case FRONT:
		{
			int tex_id = block_id;
			float u = fmodf((float)tex_id, (float)TEXTURES_PER_ROW);
			u = u / (float)TEXTURES_PER_ROW;
			float v = floor((float)tex_id / (float)TEXTURES_PER_ROW);
			v = v / (float)TEXTURES_PER_ROW;
			v = 1 - v;
			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			break;
		}
		case BACK:
		{
			int tex_id = block_id;
			float u = fmodf((float)tex_id, (float)TEXTURES_PER_ROW);
			u = u / (float)TEXTURES_PER_ROW;
			float v = floor((float)tex_id / (float)TEXTURES_PER_ROW);
			v = v / (float)TEXTURES_PER_ROW;
			v = 1 - v;
			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
		}
		default:
			break;
		}
		break;
	}
	default:
	{
		float u = fmodf((float)block_id, (float)TEXTURES_PER_ROW);
		u = u / (float)TEXTURES_PER_ROW;
		float v = floor((float)block_id / (float)TEXTURES_PER_ROW);
		v = v / (float)TEXTURES_PER_ROW;
		v = 1 - v;
		switch (face) {
		case TOP:

			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			break;
		case BOTTOM:

			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			break;
		case RIGHT:

			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			break;
		case LEFT:

			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			break;
		case FRONT:

			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			break;
		case BACK:

			if (vert == 0) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 1) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 2) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 3) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v - space);
			}
			else if (vert == 4) {

				dynamic_array_insert(vertices, u);
				dynamic_array_insert(vertices, v);
			}
			else if (vert == 5) {

				dynamic_array_insert(vertices, u + space);
				dynamic_array_insert(vertices, v);
			}
		default:
			break;
		}
		break;
	}
	}
}

void block_add_colour(uint8_t block_id, uint8_t face, struct Array* vertices) {

	/*float float_temp = 1.0f;
	int face_temp = face;
	void* point = &face_temp;
	float_temp = *(float*)point;

	dynamic_array_insert(vertices, float_temp);*/

	switch (face) {
	case TOP:
		dynamic_array_insert(vertices, 1.0f);
		dynamic_array_insert(vertices, 1.0f);
		dynamic_array_insert(vertices, 1.0f);
		dynamic_array_insert(vertices, 1.0f);
		break;
	case BOTTOM:
		dynamic_array_insert(vertices, 0.8f);
		dynamic_array_insert(vertices, 0.8f);
		dynamic_array_insert(vertices, 0.8f);
		dynamic_array_insert(vertices, 0.8f);
		break;
	case LEFT:
		dynamic_array_insert(vertices, 0.87f);
		dynamic_array_insert(vertices, 0.87f);
		dynamic_array_insert(vertices, 0.87f);
		dynamic_array_insert(vertices, 0.87f);
		break;
	case RIGHT:
		dynamic_array_insert(vertices, 0.88f);
		dynamic_array_insert(vertices, 0.88f);
		dynamic_array_insert(vertices, 0.88f);
		dynamic_array_insert(vertices, 0.88f);
		break;
	case FRONT:
		dynamic_array_insert(vertices, 0.82f);
		dynamic_array_insert(vertices, 0.82f);
		dynamic_array_insert(vertices, 0.82f);
		dynamic_array_insert(vertices, 0.82f);
		break;
	case BACK:
		dynamic_array_insert(vertices, 0.81f);
		dynamic_array_insert(vertices, 0.81f);
		dynamic_array_insert(vertices, 0.81f);
		dynamic_array_insert(vertices, 0.81f);
		break;
	default:
		dynamic_array_insert(vertices, 1.0f);
		dynamic_array_insert(vertices, 1.0f);
		dynamic_array_insert(vertices, 1.0f);
		dynamic_array_insert(vertices, 1.0f);
		break;
	}
}