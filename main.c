#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include "window.h"
#include "cglm/cglm.h"
#include "dynamic_array.h"

struct Balls {

	Array b;
	int a;
};

struct Big {

	struct Balls* b[10];
	float bc;
};

int main(int arc, char *argv[]) {
	
	/*struct Big big;
	big.bc = 1.0f;

	big.b[0] = malloc(sizeof(struct Balls));
	big.b[0]->a = 5;
	big.b[1] = malloc(sizeof(struct Balls));
	big.b[1]->a = 7;

	dynamic_array_init(&big.b[0]->b, 2);

	dynamic_array_insert(&big.b[0]->b, 1.0f);

	dynamic_array_init(&big.b[1]->b, 2);

	dynamic_array_insert(&big.b[1]->b, 3.0f);

	printf("%f\n", big.b[0]->b.array[0]);
	printf("%f\nBreak\n", big.b[1]->b.array[0]);

	dynamic_array_insert(&big.b[0]->b, 2.0f);

	printf("%f\n", big.b[0]->b.array[0]);
	printf("%f\n", big.b[0]->b.array[1]);
	printf("%f\nBreak\n", big.b[1]->b.array[0]);

	for (int i = 0; i < 1000; i++) {
		dynamic_array_insert(&big.b[0]->b, (float)i);
		printf("%f\n", big.b[0]->b.array[i]);
	}
	printf("%f\nBreak\n", big.b[1]->b.array[0]);

	dynamic_array_free(&big.b[0]->b);
	dynamic_array_init(&big.b[0]->b, 2);
	dynamic_array_insert(&big.b[0]->b, 2.0f);

	printf("%f\n", big.b[0]->b.array[0]);
	printf("%f\nBreak\n", big.b[1]->b.array[0]);

	dynamic_array_free(&big.b[0]->b);
	dynamic_array_free(&big.b[1]->b);


	/*dynamic_array_insert(a[0], 2.0);
	for (int i = 0; i < 100; i++) {
		dynamic_array_insert(a[0], (float)i);
	}

	printf("%d\n", sizeof(a[0]));

	for (int i = 0; i < 100; i++) {
		printf("%f\n", a[0]->array[i]);
	}
	printf("%f\nBreak\n", a[1]->array[0]);

	for (int i = 0; i < 2; i++) {
		dynamic_array_free(a[i]);
	}*/

	window_create(800, 600);

	window_loop();

	window_destroy();

	return 0;
}

/*
#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

static const char* vertex_shader =
"#version 330 core\n"
"layout (location = 0) in vec3 vPos;\n"
"layout (location = 1) in vec4 vColour;\n"
"layout (location = 2) in vec2 vUv;\n"
"uniform mat4 mvp;\n"
"void main() {\n"
"	gl_Position = mvp * vec4(vPos, 1.0);\n"
"	vec4 c = vColour;\n"
"	vec2 u = vUv;\n"
"}\n";

static const char* fragment_shader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";


void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct Camera {
	vec3 *pos;
	vec3 *dir;
	float yaw;
	float pitch;
};

bool keys[256] = { 0 };

int main(int arc, char *argv[]) {

	int width = 800, height = 600;

	if (!glfwInit()) {

		return -1;
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(width, height, "Game", NULL, NULL);
	if (!window) {

		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);

	glfwSetKeyCallback(window, key_callback);

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	float pos[18] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	float colour[24] = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	float uv[12] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	unsigned int vao, pVbo, cVbo, uVbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &pVbo);
	glGenBuffers(1, &cVbo);
	glGenBuffers(1, &uVbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, pVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, cVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colour), colour, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, uVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	unsigned int vertexShader, fragmentShader, program;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(program);

	glClearColor(0.0, 0.0, 1.0, 1.0);

	mat4 perspective, view, model, mvp;
	glm_mat4_identity(model);
	glm_perspective(1.5708f, (float)width / (float)height, 0.1f, 100.0f, perspective);
	vec3 eye, center, up, dest;
	eye[0] = 0.0f;
	eye[1] = 0.0f;
	eye[2] = 2.0f;
	center[0] = 0.0f;
	center[1] = 0.0f;
	center[2] = -1.0f;
	//glm_vec3_add(eye, center, center);
	up[0] = 0.0f;
	up[1] = 1.0f;
	up[2] = 0.0f;
	//glm_lookat(eye, center, up, view);
	//glm_mat4_mulN((mat4 *[]) { &perspective, &view, &model }, 3, mvp);

	struct Camera camera = { eye, center, 0.0f, 0.0f };

	double last_time = glfwGetTime();

	unsigned int frames = 0;

	while (!glfwWindowShouldClose(window)) {

		frames = frames + 1;

		if (glfwGetTime() - last_time > 1.0) {

			printf("FPS %u\n", frames);
			frames = 0;
			last_time = glfwGetTime();
		}

		glClear(GL_COLOR_BUFFER_BIT);

		if (keys[GLFW_KEY_W] == true) {
			vec3 scaled;
			glm_vec3_scale_as(camera.dir, 0.001f, scaled);
			glm_vec3_add(camera.pos, scaled, camera.pos);
		}
		if (keys[GLFW_KEY_S] == true) {
			vec3 scaled;
			glm_vec3_scale_as(camera.dir, 0.001f, scaled);
			glm_vec3_sub(camera.pos, scaled, camera.pos);
		}

		glm_vec3_add(camera.pos, camera.dir, dest);
		glm_lookat(camera.pos, dest, up, view);
		glm_mat4_mulN((mat4 *[]) { &perspective, &view, &model }, 3, mvp);

		glUniformMatrix4fv(glGetUniformLocation(program, "mvp"), 1, GL_FALSE, (float *)mvp);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &pVbo);
	glDeleteBuffers(1, &cVbo);
	glDeleteBuffers(1, &uVbo);
	glDeleteProgram(program);

	//End of program
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void error_callback(int error, const char* description) {

	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {

		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	switch (action) {
	case GLFW_PRESS:
		keys[key] = true;
		break;
	case GLFW_RELEASE:
		keys[key] = false;
		break;
	default:
		break;
	}
}*/