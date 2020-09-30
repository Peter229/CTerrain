#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include "window.h"
#include "cglm/cglm.h"
#include "dynamic_array.h"

int main(int arc, char *argv[]) {

	window_create(800, 600);

	window_loop();

	window_destroy();

	return 0;
}
