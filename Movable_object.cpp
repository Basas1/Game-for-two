#include "Movable_object.h"
#include "media.h"
#include "tools.h"
#include "init.h"


Movable_object::Movable_object() : Game_object() {
	type = OTHER;
	pos_x = 0;
	pos_y = 0;

	vel_x = 0;
	vel_y = 0;

	max_vel_x = 2;
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
	for (int i = pos_x; i <= pos_x + width; i++) {
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
	for (int i = pos_y; i <= pos_y + height - can_rise; i ++) {
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
	for (int i = pos_y; i <= pos_y + height - can_rise; i ++) {
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
	//Turn object to the side of movement
	if (acc_x > 0) {
		flip_right = true;
	}
	else if (acc_x < 0) {
		flip_right = false;
	}

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
		//Expiremental solution for map edge cases
		if ((check_map_collision(pos_x - 1, pos_y + height) || check_map_collision(pos_x - 1, pos_y + height - 1)) &&
			!check_map_collision(pos_x + width / 2, pos_y + height) && !check_map_collision(pos_x + width, pos_y + height)) {
			pos_y+= acceleration;
			pos_x+= acceleration/2; 
		}
		if ((check_map_collision(pos_x + width + 1, pos_y + height) || check_map_collision(pos_x + width + 1, pos_y + height - 1)) &&
			!check_map_collision(pos_x + width / 2, pos_y + height) && !check_map_collision(pos_x, pos_y + height)) {
			pos_y += acceleration;
			pos_x -= acceleration/2;
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
	collision_box = { (int)pos_x, (int)pos_y, width, height };
}



std::vector<Game_object*> Movable_object::get_collisions(SDL_Rect* check_box) {
	if (check_box == NULL) check_box = &collision_box;
	std::vector<Game_object*> collisions;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->is_exist()) {
			if (objects[i]->type == PLAYER || objects[i]->type == ENEMY || objects[i]->type == FIREBALL)
				if (check_collision(*check_box, objects[i]->collision_box)) {
					if (this != objects[i]) {
						collisions.insert(collisions.end(), objects[i]);
					}
				}
		}
	}
	return collisions;
}



//Check for collision with other objects
bool Movable_object::check_collision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//Here is where the collision detection happens.This code calculates the top / bottom and left / right of each of the collison boxes.
	//If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
