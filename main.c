#define STB_IMAGE_IMPLEMENTATION
#include "window.h"

int main(int arc, char *argv[]) {

	window_create(800, 600);

	window_loop();

	window_destroy();

	return 0;
}
