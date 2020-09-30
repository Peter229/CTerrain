#include "shader.h"

//static const char* vertex_shader =
//"#version 330 core\n"
//"layout (location = 0) in vec3 vPos;\n"
//"layout (location = 1) in int vColour;\n"
//"layout (location = 2) in vec2 vUv;\n"
//"out vec2 Uv;\n"
//"out vec4 Colour;\n"
//"uniform mat4 vp;\n"
//"uniform mat4 model;\n"
//"void main() {\n"
//"	gl_Position = vp * model * vec4(vPos, 1.0);\n"
//"	if (vColour == 0) {\n"
//"		Colour = vec4(1.0, 1.0, 1.0, 1.0);\n"
//"	}\n"
//"	if (vColour == 1) {\n"
//"		Colour = vec4(0.6, 0.6, 0.6, 1.0);\n"
//"	}\n"
//"	if (vColour == 2) {\n"
//"		Colour = vec4(0.88, 0.88, 0.88, 1.0);\n"
//"	}\n"
//"	if (vColour == 3) {\n"
//"		Colour = vec4(0.86, 0.86, 0.86, 1.0);\n"
//"	}\n"
//"	if (vColour == 4) {\n"
//"		Colour = vec4(0.84, 0.84, 0.84, 1.0);\n"
//"	}\n"
//"	if (vColour == 5) {\n"
//"		Colour = vec4(0.82, 0.82, 0.82, 1.0);\n"
//"	}\n"
//"	Uv = vUv;\n"
//"}\n";

static const char* vertex_shader =
"#version 330 core\n"
"layout (location = 0) in vec3 vPos;\n"
"layout (location = 1) in vec4 vColour;\n"
"layout (location = 2) in vec2 vUv;\n"
"out vec2 Uv;\n"
"out vec4 Colour;\n"
"uniform mat4 vp;\n"
"uniform mat4 model;\n"
"void main() {\n"
"	gl_Position = vp * model * vec4(vPos, 1.0);\n"
"	Colour = vColour;\n"
"	Uv = vUv;\n"
"}\n";

static const char* fragment_shader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 Uv;\n"
"in vec4 Colour;\n"
"uniform sampler2D inTexture;\n"
"void main() {\n"
"	vec4 texel = texture(inTexture, Uv);\n"
"	texel = texel * vec4(Colour.xyz, 1);\n"
"	FragColor = texel;\n"
"}\n";

void shader_gen(unsigned int *program) {

	unsigned int vertexShader, fragmentShader;
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

	*program = glCreateProgram();
	glAttachShader(*program, vertexShader);
	glAttachShader(*program, fragmentShader);
	glLinkProgram(*program);
	glGetProgramiv(*program, GL_COMPILE_STATUS, &success);
	if (!success) {

		glGetProgramInfoLog(*program, 512, NULL, infoLog);
		printf("%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void shader_delete(unsigned int *program) {

	glDeleteProgram(*program);
}

void shader_use(unsigned int *program) {

	glUseProgram(*program);
}