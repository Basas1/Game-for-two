#pragma once
#include "Static_object.h"


class Platform : public Static_object {
public:
	Platform(int x, int y);
	~Platform();
	void render();
};

