#include "Player.h"
#include "media.h"


Player::Player() : Movable_object() {
	width = 100;
	height = 100;

	texture = new Texture(player_texture);
	texture->set_width(width);
	texture->set_height(height);

	collision_box = { pos_x, pos_y, width, height };
}


void Player::handle_events(SDL_Event& event) {
	//If a key is pressed
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
	}

	//If a key was pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		//case SDLK_SPACE: vel_y = -16; break;
		}
	}
}

void Player::move() {

}

void Player::render() {
	texture->render(pos_x, pos_y);
}

Player::~Player() {
	delete texture;
}


