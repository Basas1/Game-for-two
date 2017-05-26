#pragma once
#include "Game_object.h"
#include "init.h"



Game_object::Game_object() {
	exist = true;
	collidable = false;
	type = OTHER;
}

bool Game_object::is_exist() {
	return exist;
}

bool Game_object::kill() {
	exist = false;
	return true;
}


std::vector<Game_object*> Game_object::get_collisions(SDL_Rect* check_box) {
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
bool Game_object::check_collision(SDL_Rect a, SDL_Rect b) {
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
