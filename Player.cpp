#include "Player.h"
#include "media.h"


Player::Player() : Movable_object() {
	width = 40;
	height = 128;
	pos_x = 300;
	pos_y = 0;
	jump_vel = 7;

	texture = new Texture(player_texture);
	//texture->set_width(width);
	//texture->set_height(height);
	walk_animation = new Animated_texture(walk_texture, 10);
	//walk_animation->set_width(width);
	//walk_animation->set_height(height);
	walk_animation->set_clips();

	collision_box = { pos_x, pos_y, width, height };
	center_x = width / 2;
	center_y = height / 2;
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
		case SDLK_SPACE: vel_y = -jump_vel; break;
		case SDLK_r: pos_x = 0; pos_y = 0; break;
		}
	}
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w: pos_y -= 100; break;
		case SDLK_a: pos_x -= 10; break;
		case SDLK_s: pos_y += 10; break;
		case SDLK_d: pos_x += 10; break;
		}
	}

	//If a key was released
	//else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
	//	switch (event.key.keysym.sym) {
	//	case SDLK_RIGHT: acc_x = 0; break;
	//	case SDLK_LEFT: acc_x = 0; break;
	//	}
	//}

}

void Player::move() {
	//vel_x += acc_x;

	//Calculate friction
	//if (vel_x > 0) vel_x -= friction;
	//else if (vel_x < 0) vel_x += friction;
	//else if (-friction <= vel_x && vel_x <= friction) vel_x = 0;
	//if (-1 < vel_x && vel_x < 1) vel_x = 0;

	//Speed limit
	//if (vel_x > max_vel_x) vel_x = max_vel_x;
	//if (vel_x < -max_vel_x) vel_x = -max_vel_x;

	//Change player position
	//pos_x += round(vel_x);
	//pos_y += vel_y;

	vel_x = acc_x;
	Movable_object::move();
}

void Player::render() {
	center_x = pos_x + width / 2;
	center_y = pos_y + height / 2;

	if (acc_x > 0) {
		walk_animation->set_flip(SDL_FLIP_NONE);
		texture->set_flip(SDL_FLIP_NONE);
	}
	else if (acc_x < 0) {
		walk_animation->set_flip(SDL_FLIP_HORIZONTAL);
		texture->set_flip(SDL_FLIP_HORIZONTAL);
	}

	if (acc_x != 0) {
		walk_animation->render(center_x, center_y);
		walk_animation->next_frame();
	}
	else {
		texture->render(center_x, center_y);
		walk_animation->set_frame(0);
	}

	//if (check_map_collision_left()) printf("Left collision\n");
	//if (check_map_collision_right()) printf("Right collision\n");
	//if (check_map_collision_bottom()) printf("Bottom collision\n");
	//if (check_map_collision_upper()) printf("Upper collision\n");
}

Player::~Player() {
	delete texture;
}

int Player::round(float f) {
	return (f > 0.0) ? (f + 0.5) : (f - 0.5);
}

int Player::get_x() {
	center_x = pos_x + width / 2;
	return center_x;
}

int Player::get_y() {
	center_y = pos_y + height / 2;
	return center_y;
}