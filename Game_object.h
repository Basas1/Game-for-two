#pragma once
#include <SDL.h>

class Game_object {
public:
	Game_object();
	virtual void handle_events(SDL_Event& event) = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~Game_object() {};
	bool is_exist();
protected:
	bool exist;
};

