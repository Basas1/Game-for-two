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

class Fireball_trail : public Static_object {
public:
	Fireball_trail(int x, int y, Game_object* p);
	~Fireball_trail();
	void render();
	Animated_texture* f_trail;
};

class Teleport_trail : public Static_object {
public:
	Teleport_trail(int x, int y, double dest_x, double dest_y, Game_object* p);
	~Teleport_trail();
	void render();
	Animated_texture* tp_trail;
	double angle;
};

class Jump_effect : public Static_object {
public:
	Jump_effect(int x, int y, Animated_texture* animation);
	~Jump_effect() {};
	void render();
	Animated_texture* effect_animation;
};

class Help : public Static_object {
public:
	Help(Game_object* p);
	Animated_texture* help_t;
	void render();
};

