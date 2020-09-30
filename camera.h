#pragma once
#include "cglm/cglm.h"
#include <math.h>
#include "gl_includes.h"

struct Camera {
	mat4 perspective;
	mat4 view;
	vec3 pos;
	vec3 dir;
	vec3 right;
	vec3 up;
	float yaw;
	float pitch;
	float speed;
	double last_mouse[2];
};

extern struct Camera camera;

void camera_move(bool keys[GLFW_KEY_LAST]);
void camera_update_vectors();
void camera_process_mouse(double mouse_pos[2]);
void camera_view_projection_matrix(mat4 *vp);
void camera_init(unsigned int width, unsigned int height);