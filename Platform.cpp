#pragma once
#include "Platform.h"
#include "init.h"



Platform::Platform(int x, int y) : Static_object(){
	collidable = true;
	pos_x = x;
	pos_y = y;
	flip_right = true;
	
	texture = new Texture(platform);
	width = texture->get_width();
	height = texture->get_height();

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Platform::render() {
	texture->render(pos_x, pos_y, flip_right);
}

Platform::~Platform() {
}
