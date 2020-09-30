#include "camera.h"

struct Camera camera;

void camera_init(unsigned int width, unsigned int height) {

	vec3 pos;
	pos[0] = 1800.0f;
	pos[1] = 1800.0f;
	pos[2] = 1800.0f;
	glm_vec3_copy(pos, camera.pos);

	vec3 dir;
	dir[0] = 0.0f;
	dir[1] = 0.0f;
	dir[2] = -1.0f;
	glm_vec3_copy(dir, camera.dir);

	vec3 right;
	right[0] = 1.0f;
	right[1] = 0.0f;
	right[2] = 0.0f;
	glm_vec3_copy(right, camera.right);

	vec3 up;
	up[0] = 0.0f;
	up[1] = 1.0f;
	up[2] = 0.0f;
	glm_vec3_copy(up, camera.up);

	camera.yaw = 180.0f;
	camera.pitch = 0.0f;

	camera.speed = 2.0f;

	mat4 perspective;
	glm_perspective((float)((90.0 * M_PI) / 180.0), (float)width / (float)height, 0.1f, 400.0f, perspective);
	glm_mat4_copy(perspective, camera.perspective);

	camera_update_vectors();
}

void camera_process_mouse(double mouse_pos[2]) {

	double offset_x = mouse_pos[0] - camera.last_mouse[0];
	double offset_y = mouse_pos[1] - camera.last_mouse[1];

	camera.last_mouse[0] = mouse_pos[0];
	camera.last_mouse[1] = mouse_pos[1];

	double mouse_sensitivity = 0.001;

	offset_x *= mouse_sensitivity;
	offset_y *= mouse_sensitivity;

	camera.yaw = fmod((double)camera.yaw + offset_x, 2 * M_PI);

	camera.pitch -= offset_y;

	if (camera.pitch >= M_PI_2 - 0.01) {

		camera.pitch = M_PI_2 - 0.01;
	}else if (camera.pitch <= -M_PI_2 + 0.01) {

		camera.pitch = -M_PI_2 + 0.01;
	}

	camera_update_vectors();
}

void camera_view_projection_matrix(mat4 *vp) {

	glm_mat4_mul(camera.perspective, camera.view, *vp);
}

void camera_update_vectors() {

	vec3 front;
	front[0] = cosf(camera.yaw) * cosf(camera.pitch);
	front[1] = sinf(camera.pitch);
	front[2] = sinf(camera.yaw) * cosf(camera.pitch);
	glm_vec3_normalize_to(front, camera.dir);

	vec3 world_up;
	world_up[0] = 0.0f;
	world_up[1] = 1.0f;
	world_up[2] = 0.0f;

	glm_vec3_crossn(camera.dir, world_up, camera.right);
	glm_vec3_crossn(camera.right, camera.dir, camera.up);

	glm_look(camera.pos, camera.dir, camera.up, camera.view);
}

void camera_move(bool keys[GLFW_KEY_LAST]) {

	if (keys[GLFW_KEY_W] == true) {

		vec3 scaled;
		glm_vec3_scale_as(camera.dir, camera.speed, scaled);
		glm_vec3_add(camera.pos, scaled, camera.pos);
	}
	if (keys[GLFW_KEY_S] == true) {

		vec3 scaled;
		glm_vec3_scale_as(camera.dir, camera.speed, scaled);
		glm_vec3_sub(camera.pos, scaled, camera.pos);
	}
	if (keys[GLFW_KEY_D] == true) {

		vec3 scaled;
		glm_vec3_scale_as(camera.right, camera.speed, scaled);
		glm_vec3_add(camera.pos, scaled, camera.pos);
	}
	if (keys[GLFW_KEY_A] == true) {

		vec3 scaled;
		glm_vec3_scale_as(camera.right, camera.speed, scaled);
		glm_vec3_sub(camera.pos, scaled, camera.pos);
	}

	//printf("%f %f %f\n", camera.pos[0], camera.pos[1], camera.pos[2]);

	glm_look(camera.pos, camera.dir, camera.up, camera.view);
}