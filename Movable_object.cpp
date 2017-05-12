#include "Movable_object.h"
#include "media.h"
#include "tools.h"


Movable_object::Movable_object() {

	pos_x = 0;
	pos_y = 0;

	vel_x = 0;
	vel_y = 0;

	max_vel_x = 5;
	max_vel_y = 20;

	acc_x = 0;
	acc_y = 0;

	acceleration = 10;
	gravity = 0.1;
	friction = 0.5;
}

bool Movable_object::check_map_collision(int x, int y) {
	if (x > 0 && x < map_surface->w && y > 0 && y < map_surface->h) {
		return (getpixel(map_surface, x, y) != 15);
	}
	return true;
}
 
bool Movable_object::check_map_collision_bottom() {
	for (int i = pos_x; i <= pos_x + width; i+= width/4) {
		if (check_map_collision(i, pos_y + height)) return true;
	}
	return false;
}

bool Movable_object::check_map_collision_upper() {
	for (int i = pos_x; i <= pos_x + width; i += width / 4) {
		if (check_map_collision(i, pos_y)) return true;
	}
	return false;
}

//Return object's coordinate x
void Movable_object::move() {
	//Gravity effect
	vel_y += gravity;
	if (vel_y > 0) {
		int old_y = pos_y;
		for (pos_y; pos_y <= old_y + vel_y; pos_y++) {
			if (check_map_collision_bottom()) {
				vel_y = 0;
				break;
			}
		}
	}
	else {
		int old_y = pos_y;
		for (pos_y; pos_y >= old_y + vel_y; pos_y--) {
			if (check_map_collision_upper()) {
				vel_y = 0;
				break;
			}
		}
	}

}




//Return object's coordinate x
int Movable_object::get_x() {
	return pos_x;
}

//Return object's coordinate y
int Movable_object::get_y() {
	return pos_y;
}

//Check for collision with other objects
bool Movable_object::check_collision() {
	return false;
}

