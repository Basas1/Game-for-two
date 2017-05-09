#include "Movable_object.h"


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

