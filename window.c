#include "window.h"

struct Window window;

void window_create(unsigned int width, unsigned int height) {

	window.width = width;
	window.height = height;

	if (!glfwInit()) {

		return -1;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window.handle = glfwCreateWindow(width, height, "Game", NULL, NULL);
	if (!window.handle) {

		return -1;
	}

	glfwMakeContextCurrent(window.handle);
	gladLoadGL(glfwGetProcAddress);

	glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(window.handle, key_callback);
	glfwSetCursorPosCallback(window.handle, mouse_callback);

	glfwGetFramebufferSize(window.handle, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(0.0, 0.0, 1.0, 1.0);

	window.last_second = glfwGetTime();
	window.last_tick = glfwGetTime();

	window.frames = 0;

	shader_gen(&window.program);

	camera_init(width, height);

	world_generate_noise(&window.world);
	world_generate(&window.world, camera.pos);

	texture_load(&window.texture, "res/texture_map.png");
}

void window_loop() {

	while (!glfwWindowShouldClose(window.handle)) {

		window.frames++;

		if (glfwGetTime() - window.last_second > 1.0) {

			printf("FPS %u\n", window.frames);
			window.frames = 0;
			window.last_second = glfwGetTime();
		}

		if (glfwGetTime() - window.last_tick > 0.01666666666) {

			window_tick();
			window.last_tick = glfwGetTime();
		}

		window_update();

		window_render();

		glfwSwapBuffers(window.handle);
		glfwPollEvents();
	}
}

void window_tick() {

	camera_move(&window.keys);
	//world_gen_update(&window.world, camera.pos);
}

void window_update() {

}

void window_render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader_use(&window.program);

	mat4 vp;
	camera_view_projection_matrix(&vp);
	glUniformMatrix4fv(glGetUniformLocation(window.program, "vp"), 1, GL_FALSE, (float *)vp);
	glBindTexture(GL_TEXTURE_2D, window.texture);
	world_render(&window.world, &window.program);
}

void window_destroy() {

	texture_delete(&window.texture);
	shader_delete(&window.program);
	world_delete(&window.world);

	glfwDestroyWindow(window.handle);
	glfwTerminate();
}

void error_callback(int error, const char* description) {

	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* handle, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {

		glfwSetWindowShouldClose(handle, GLFW_TRUE);
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	switch (action) {
	case GLFW_PRESS:
		window.keys[key] = true;
		break;
	case GLFW_RELEASE:
		window.keys[key] = false;
		break;
	default:
		break;
	}
}

static void mouse_callback(GLFWwindow* handle, double xpos, double ypos) {

	window.mouse_pos[0] = xpos;
	window.mouse_pos[1] = ypos;
	camera_process_mouse(window.mouse_pos);
}