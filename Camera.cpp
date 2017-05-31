#include "Camera.h"
#include "init.h"

Camera::Camera() {
	vel_x, vel_y = 0;
	scale = 1;
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	if ((double)SCREEN_WIDTH / (double)map_surface->w < (double)SCREEN_HEIGHT / (double)map_surface->h) {
		printf("1;\n");
		min_scale = (double)SCREEN_WIDTH / (double)map_surface->w;
	}
	else {
		printf("2;\n");
		min_scale = (double)SCREEN_HEIGHT / (double)map_surface->h;
	}
	max_scale = 1;
	printf("min=%f; max=%f;\n", min_scale, max_scale);
}

int Camera::get_x() {
	return camera.x;
}

int Camera::get_y() {
	return camera.y;
}

double Camera::get_scale() {
	return scale;
}

SDL_Rect* Camera::get_rect() {
	return &camera;
}

void Camera::follow(int vision_focus_x, int vision_focus_y) {
	move_to(vision_focus_x, vision_focus_y);
}

void Camera::set_scale(double target_scale) {
	scale = target_scale;
}

void Camera::move_to(int vision_focus_x, int vision_focus_y) {
	camera.x = vision_focus_x - ((SCREEN_WIDTH / 2) / scale);
	camera.y = vision_focus_y - ((SCREEN_HEIGHT / 2) / scale);

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > map_surface->w - camera.w / scale) {
		camera.x = map_surface->w - camera.w / scale;
	}
	if (camera.y > map_surface->h - camera.h / scale) {
		camera.y = map_surface->h - camera.h / scale;
	}
}
