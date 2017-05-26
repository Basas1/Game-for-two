#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Game_object.h"
#include "Animated_texture.h"

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

class Blast : public Static_object {
public:
	void logic();
	Blast(int x, int y);
	~Blast();
	void render();
	Animated_texture* blast_t;
};

class Capture_platform : public Static_object {
public:
	Capture_platform(int x, int y, int w, int h);
	void logic();
};


