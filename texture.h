#pragma once
#include "gl_includes.h"
#include "stb_image.h"

void texture_load(unsigned int *texture, const char* path);

void texture_delete(unsigned int *texture);