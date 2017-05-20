#include "Game_object.h"


Game_object::Game_object() {
	exist = true;
	type = OTHER;
}

bool Game_object::is_exist() {
	return exist;
}

void Game_object::kill() {
	exist = false;
}