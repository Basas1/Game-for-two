#include "Player.h"
#include "media.h"


Player::Player() : Movable_object() {
	width = 64;
	height = 128;

	texture = new Texture(player_texture);
	texture->set_width(width);
	texture->set_height(height);

	collision_box = { pos_x, pos_y, width, height };
}


void Player::handle_events(SDL_Event& event) {
	//If a key is pressed
	int a_x = 0;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		a_x -= acceleration;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		a_x += acceleration;
	}
	acc_x = a_x;

	//If a key was pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE: vel_y = -16; break;
		}
	}


}

void Player::move() {
	vel_x += acc_x;

	//Calculate friction
	if (vel_x > 0) vel_x -= friction;
	else if (vel_x < 0) vel_x += friction;
	if (-friction <= vel_x && vel_x <= friction) vel_x = 0;

	//Speed limit
	if (vel_x > max_vel_x) vel_x = max_vel_x;
	if (vel_x < -max_vel_x) vel_x = -max_vel_x;
	
	//Gravity effect
	vel_y += gravity;

	//Change player position
	pos_x += vel_x;
	pos_y += vel_y;

	//Check for level border
	if (pos_x < 0) pos_x = 0;
	if (pos_x > SCREEN_WIDTH - width) pos_x = SCREEN_WIDTH - width;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > SCREEN_HEIGHT - height) pos_y = SCREEN_HEIGHT - height;
}

void Player::render() {
	texture->render(pos_x, pos_y);
}

Player::~Player() {
	delete texture;
}


