#pragma once
#include "Movable_object.h"


class Player : public Movable_object {
public:
	Player();
	~Player();


	//Event handler
	void handle_events(SDL_Event& event);

	//Move method
	void move();

	//Render object
	void render();
private:
	int round(float f);

	//Jump speed
	int jump_vel;


	int frame;
	SDL_Rect gSpriteClips[8];
	//SDL_Rect SpriteClips[6];
	SDL_Rect* currentClip;
	SDL_RendererFlip flip;

};

