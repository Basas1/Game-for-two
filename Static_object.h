#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Game_object.h"

class Static_object : public Game_object {
public:
	void handle_events(SDL_Event& event) {};
	void logic() {};
	virtual ~Static_object() {};
	virtual void render() {};

	//True if object turn to rigrht side
	bool flip_right;

	//Object's texture
	Texture* texture;
};

