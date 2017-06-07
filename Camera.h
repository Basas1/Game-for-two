#pragma once
#include "SDL.h"
#include "Player.h"

class Camera {
public:
	Camera();

	int get_x();
	int get_y();

	double get_scale();

	//get obliterated, son
	SDL_Rect* get_rect();

	void follow(int vision_focus_x, int vision_focus_y);
	void set_scale(double target_scale);
	void set_scale_by_distance(double x_dist, double y_dist);

	double min_scale;
	double max_scale;

	//square of the camera
	SDL_Rect camera;

	//scale of rendered field
	double scale;

	//speed of camera movement
	double vel_x, vel_y;

	void move_to(int vision_focus_x, int vision_focus_y);

};

