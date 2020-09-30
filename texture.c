#include "texture.h"

void texture_load(unsigned int *texture, const char* path) {

	glGenTextures(1, texture);
	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(1);
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data) {

		//Check image format
		GLenum format;
		if (nrComponents == 1) {

			format = GL_RED;
		}
		else if (nrComponents == 3) {

			format = GL_RGB;
		}
		else if (nrComponents == 4) {

			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else {
		printf("Texture failed to load at path: %s\n", path);
		stbi_image_free(data);
	}
}

void texture_delete(unsigned int *texture) {

	glDeleteTextures(1, texture);
}