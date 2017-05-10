#include "Movable_object.h"


Movable_object::Movable_object() {

	pos_x = 0;
	pos_y = 0;

	vel_x = 0;
	vel_y = 0;

	max_vel_x = 20;
	max_vel_y = 20;

	acc_x = 0;
	acc_y = 0;

	gravity = 0.8;
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

