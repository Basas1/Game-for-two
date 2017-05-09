#include "Player.h"
#include "media.h"


Player::Player() {
	pos_x = 0;
	pos_y = 0;

	width = 100;
	height = 100;

	vel_x = 0;
	vel_y = 0;

	max_vel_x = 20;
	max_vel_y = 20;

	acc_x = 0;
	acc_y = 0;

	gravity = 0.8;

	texture = new Texture(player_texture);
	texture->set_width(width);
	texture->set_height(height);

	collision_box = { pos_x, pos_y, width, height };
}


Player::~Player() {
	delete texture;
}


void Player::move() {

}


void Player::handle_events(SDL_Event& e) {
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
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch (e.key.keysym.sym) {
		//case SDLK_SPACE: vel_y = -16; break;
		}
	}
}


void Player::render() {
	texture->render(pos_x, pos_y);
}


