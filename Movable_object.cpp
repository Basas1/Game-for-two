#include "Movable_object.h"
#include "media.h"
#include "tools.h"


Movable_object::Movable_object() : Game_object() {
	pos_x = 0;
	pos_y = 0;

	vel_x = 0;
	vel_y = 0;

	max_vel_x = 5;
	max_vel_y = 20;

	acc_x = 0;
	acc_y = 0;

	acceleration = 2;
	gravity = 0.1;
	friction = 0.5;
	can_rise = 25;
}

//Check for map collision in coordinate (x,y)
bool Movable_object::check_map_collision(int x, int y) {
	if (x >= 0 && x < map_surface->w && y >= 0 && y < map_surface->h) {
		return (getpixel(map_surface, x, y) != 15);
	}
	return true;
}

//Check bottom of object collision box for collision with map
bool Movable_object::check_map_collision_bottom() {
	for (int i = pos_x; i <= pos_x + width; i++) {
		if (check_map_collision(i, pos_y + height)) return true;
	}
	return false;
}

//Check bottom of object collision box for collision with map
bool Movable_object::check_map_collision_under() {
	for (int i = pos_y+height; i <= pos_y + height + can_rise; i++) {
		if (check_map_collision(pos_x + width/2, i)) return true;
	}
	return false;
}

//Check upper of object collision box for collision with map
bool Movable_object::check_map_collision_upper() {
	for (int i = pos_x; i <= pos_x + width; i ++) {
		if (check_map_collision(i, pos_y - 1)) return true;
	}
	return false;
}

bool Movable_object::check_map_collision_all() {
	if (check_map_collision_right()) return true;
	if (check_map_collision_left()) return true;
	if (check_map_collision_upper()) return true;
	if (check_map_collision_bottom()) return true;
	return false;
}


//Check left side of object collision box for collision with map
bool Movable_object::check_map_collision_left() {
	for (int i = pos_y; i <= pos_y + height - can_rise; i += height / 20) {
		if (check_map_collision(pos_x - 1, i)) return true;
	}
	for (int i = pos_y + height - can_rise; i <= pos_y + height - 1; i++) {
		if (check_map_collision(pos_x - 1, i)) {
			for (int j = pos_y; j > i - height; j--) {
				if (check_map_collision(pos_x - 1, j)) return true;
			}
			break;
		}
	}
	return false;
}

//Check right side of object collision box for collision with map
bool Movable_object::check_map_collision_right() {
	for (int i = pos_y; i <= pos_y + height - can_rise; i += height / 20) {
		if (check_map_collision(pos_x + width + 1, i)) return true;
	}
	for (int i = pos_y + height - can_rise; i <= pos_y + height - 1; i++) {
		if (check_map_collision(pos_x + width + 1, i)) {
			for (int j = pos_y; j > i - height; j--) {
				if (check_map_collision(pos_x + width + 1, j)) return true;
			}
			break;
		}
	}
	return false;
}

//Move object according to it's velocity
void Movable_object::move() {
	//Gravity effect
	vel_y += gravity;
	if (vel_y > 0) {
		if (!check_map_collision_bottom()) {
			double old_y = pos_y;
			pos_y += vel_y - floor(vel_y);
			for (int i = 0; i < floor(vel_y); i++) {
				if (check_map_collision_bottom()) {
					vel_y = 0;
					break;
				}
				pos_y++;
			}

		}
		else {
			vel_y = 0;
		}
	}
	else if (vel_y < 0) {
		if (!check_map_collision_upper()) {
			double old_y = pos_y; 
			pos_y += vel_y - ceil(vel_y);
			for (int i = 0; i > ceil(vel_y); i--) {
				if (check_map_collision_upper()) {
					vel_y = 0;
					break;
				}
				pos_y--;
			}
		}
		else {
			vel_y = 0;
		}
	}


	//Right movement
	int old_x = pos_x;
	if (vel_x > 0) {
		for (pos_x; pos_x <= old_x + vel_x; pos_x++) {
			if (check_map_collision_right()) {
				vel_x = 0;
				break;
			}
			if (!check_map_collision(pos_x + width + 1, pos_y + height - can_rise) &&
				check_map_collision(pos_x + width / 2, pos_y + height - 1)) {
				for (int i = pos_y + height - can_rise; i < pos_y + height; i++) {
					if (check_map_collision(pos_x + width / 2, i)) {
						pos_y = i - height;
						break;
					}
				}
			}
		}
	}
	//Left movement
	else if (vel_x < 0) {
		for (pos_x; pos_x >= old_x + vel_x; pos_x--) {
			if (check_map_collision_left()) {
				vel_x = 0;
				break;
			}
			if (!check_map_collision(pos_x - 1, pos_y + height - can_rise) &&
				check_map_collision(pos_x + width / 2, pos_y + height - 1)) {
				for (int i = pos_y + height - can_rise; i < pos_y + height; i++) {
					if (check_map_collision(pos_x + width / 2, i)) {
						pos_y = i - height;
						break;
					}
				}
			}

		}
	}
}


//Check for collision with other objects
bool Movable_object::check_collision() {
	return false;
}

void Movable_object::handle_events(SDL_Event& event) {
}
