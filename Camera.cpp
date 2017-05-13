#include "Camera.h"
#include "init.h"

Camera::Camera() {
	vel_x, vel_y = 0;
	scale = 100;
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

int Camera::get_x() {
	return camera.x;
}

int Camera::get_y() {
	return camera.y;
}

SDL_Rect* Camera::get_rect() {
	return &camera;
}

void Camera::follow(int vision_focus_x, int vision_focus_y) {
	move_to(vision_focus_x, vision_focus_y);
}

void Camera::set_scale(int target_scale) {
	scale = target_scale;
}

void Camera::move_to(int vision_focus_x, int vision_focus_y) {
	camera.x = vision_focus_x - (SCREEN_WIDTH / 2);
	camera.y = vision_focus_y - (SCREEN_HEIGHT / 2);

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > LEVEL_WIDTH - camera.w) {
		camera.x = LEVEL_WIDTH - camera.w;
	}
	if (camera.y > LEVEL_HEIGHT - camera.h) {
		camera.y = LEVEL_HEIGHT - camera.h;
	}
}