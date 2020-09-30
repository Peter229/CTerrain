#pragma once

#include "gl_includes.h"
#include "shader.h"
#include "world.h"
#include "camera.h"
#include "texture.h"
#include <stdio.h>

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* handle, double xpos, double ypos);

void window_create(unsigned int width, unsigned int height);
void window_destroy();
void window_loop();

void window_update();
void window_render();
void window_tick();

struct Window {

	GLFWwindow *handle;
	unsigned int width, height;
	bool keys[GLFW_KEY_LAST];
	double mouse_pos[2];
	unsigned int frames;
	double last_second, last_tick;

	unsigned int program;
	unsigned int texture;
	struct World world;
};

extern struct Window window;