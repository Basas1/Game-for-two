#include "Camera.h"
#include "init.h"

Camera::Camera() {
	vel_x, vel_y = 0;
	scale = 1;
	camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	if ((double)SCREEN_WIDTH / (double)map_surface->w < (double)SCREEN_HEIGHT / (double)map_surface->h) {
		min_scale = (double)SCREEN_WIDTH / (double)map_surface->w;
	}
	else {
		min_scale = (double)SCREEN_HEIGHT / (double)map_surface->h;
	}
	max_scale = 1;
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
	int x, y;
	if (camera.x < vision_focus_x) vel_x = 10;
	if (camera.x > vision_focus_x) vel_x = -10;
	if (camera.y < vision_focus_x) vel_y = 10;
	if (camera.y > vision_focus_x) vel_y = -10;
	if (vel_x < 10) vel_x = 0;
	if (vel_y < 10) vel_y = 0;
	x = camera.x + vel_x;
	y = camera.y + vel_y;
	move_to(vision_focus_x, vision_focus_y);
}

void Camera::set_scale_by_distance(double x_dist, double y_dist) {
	double x_scale, y_scale;

	x_scale = (SCREEN_WIDTH / 8 * 5) / x_dist;
	y_scale = (SCREEN_HEIGHT / 8 * 5) / y_dist;
	
	if (x_scale < min_scale) x_scale = min_scale;
	else if (x_scale > max_scale) x_scale = max_scale;
	if (y_scale < min_scale) y_scale = min_scale;
	else if (y_scale > max_scale) y_scale = max_scale;
	x_scale < y_scale ? set_scale(x_scale) : set_scale(y_scale);

}

void Camera::set_scale(double target_scale) {
	scale = target_scale;
}

void Camera::move_to(int x, int y) {
	camera.x = x - ((SCREEN_WIDTH / 2) / scale);
	camera.y = y - ((SCREEN_HEIGHT / 2) / scale);

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
