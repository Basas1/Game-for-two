#pragma once
#include "Movable_object.h"
class Fireball : public Movable_object {
public:
	Fireball(int x, int y, bool left);
	~Fireball();

	//Move method
	void move();

	//Render object
	void render();

private:
	bool exist;

};

