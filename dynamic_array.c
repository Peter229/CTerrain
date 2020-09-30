#include "dynamic_array.h"

void dynamic_array_init(Array *a, size_t initial_size) {

	a->array = malloc(initial_size * sizeof(float));
	if (!a->array) {
		printf("Out of memory!\n");
	}
	a->used = 0;
	a->size = initial_size;
}

void dynamic_array_insert(Array *a, float element) {

	if (a->used == a->size) {

		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(float));
		if (!a->array) {
			printf("Out of memory!\n");
		}
	}
	a->array[a->used++] = element;
}

void dynamic_array_free(Array *a) {

	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}