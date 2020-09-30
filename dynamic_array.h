#pragma once
#include <stdlib.h>

typedef struct {
	float *array;
	size_t used;
	size_t size;
} Array;

void dynamic_array_init(Array *a, size_t initial_size);

void dynamic_array_insert(Array *a, float element);

void dynamic_array_free(Array *a);