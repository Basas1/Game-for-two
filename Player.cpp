#include "Player.h"
#include "media.h"


Player::Player() : Movable_object() {
	width = 86;
	height = 128;
	pos_x = 500;
	pos_y = 900;
	t = pos_x;

	jump_vel = 10;

	texture = new Texture(player_texture);
	texture->set_width(width);
	texture->set_height(height);
	walk_animation = new Animated_texture(walk_texture,8);
	walk_animation->set_width(width);
	walk_animation->set_height(height);
	walk_animation->set_clips();



	collision_box = { pos_x, pos_y, width, height };


	frame = 0;
	flip = SDL_FLIP_NONE;

	gSpriteClips = new SDL_Rect[8];

	//Set standing sprite clip
	for (int i = 0; i < 8; i++) {
		gSpriteClips[i].x = i * width;
		gSpriteClips[i].y = 0;
		gSpriteClips[i].w = width;
		gSpriteClips[i].h = height;
	}


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
	//if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE: vel_y = -jump_vel; break;
		case SDLK_q: acceleration -= 0.5; break;
		case SDLK_w: acceleration += 0.5; break;
		//case SDLK_RIGHT: acc_x = acceleration; break;
		//case SDLK_LEFT: acc_x = -acceleration; break;
		}
		int t;
		t = acceleration;
		//printf("acc=%d\n", t);
	}

	////If a key was pressed
	//if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
	//	//Adjust the velocity
	//	switch (event.key.keysym.sym) {
	//	case SDLK_SPACE: vel_y = -jump_vel; break;
	//	case SDLK_RIGHT: acc_x = acceleration; break;
	//	case SDLK_LEFT: acc_x = -acceleration; break;
	//	}
	//}
	//else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
	//	//Adjust the velocity
	//	switch (event.key.keysym.sym) {
	//	case SDLK_RIGHT: acc_x = 0; break;
	//	case SDLK_LEFT: acc_x = 0; break;
	//	}
	//}

}

void Player::move() {
	vel_x += acc_x;

	//Calculate friction
	//if (vel_x > 0) vel_x -= friction;
	//else if (vel_x < 0) vel_x += friction;
	//else if (-friction <= vel_x && vel_x <= friction) vel_x = 0;
	//if (-1 < vel_x && vel_x < 1) vel_x = 0;

	//Speed limit
	if (vel_x > max_vel_x) vel_x = max_vel_x;
	if (vel_x < -max_vel_x) vel_x = -max_vel_x;

	//Gravity effect
	//vel_y += gravity;

	//Change player position
	//pos_x += round(vel_x);
	//pos_y += vel_y;

	//for (pos_y; pos_y >= pos_y + vel_y; pos_y--) {
	//	if (check_map_collision_bottom()) {
	//		//vel_y = 0;
	//		break;
	//	}
	//}

	Movable_object::move();




	//Check for level border
	if (pos_x < 0) { pos_x = 0; t = 0; vel_x = 0; }
	if (pos_x > SCREEN_WIDTH - width) { 
		pos_x = SCREEN_WIDTH - width;
	t = 0;
	vel_x = 0; }
	//if (pos_y < 0) { pos_y = 0; vel_y = 0; }
	if (pos_y < 0) { pos_y = 0; }
	if (pos_y > SCREEN_HEIGHT - height) { pos_y = SCREEN_HEIGHT - height; vel_y = 0; }
}

void Player::render() {

	if (vel_x > 0) {
		flip = SDL_FLIP_NONE;
	}
	else if (vel_x < 0) {
		flip = SDL_FLIP_HORIZONTAL;
	}


	int slow = 5;
	int kadr = frame / slow;
	
	int t1, t2;
	t1 = (frame - 1) / slow;
	t2 = frame / slow;

	//printf("t1=%d t2=%d (f=%d)\n", t1, t2, frame);
	if (t1 != t2 || frame == 0) {
		//printf("->t1=%d t2=%d (f=%d)\n", t1, t2, frame);
		//pos_x += acc_x;
	}

	//acceleration = 5;
	//pos_x += acc_x;
	//pos_x += acc_x / slow;
	t += acc_x / slow;
	pos_x = t;



	if (frame / slow > 7) {
		currentClip = &gSpriteClips[7 - (kadr - 7)];
	}
	else {
		currentClip = &gSpriteClips[kadr];
	}

	//Go to next frame
	++frame;
	if (frame / slow >= 8) {
		frame = 0;
	}

	if (acc_x != 0) {
		//currentClip = &gSpriteClips[0];
		//texture->render(pos_x, pos_y, currentClip, 0.0, NULL, flip);
		walk_animation->render(pos_x, pos_y, 0.0, NULL, flip);
		walk_animation->next_frame();
	}
	else {
		//currentClip = &gSpriteClips[7];
		//texture->render(pos_x, pos_y, currentClip, 0.0, NULL, flip);
		texture->render(pos_x, pos_y, NULL, 0.0, NULL, flip);
		walk_animation->set_frame(0);
	}

	//check_map_collision(pos_x, pos_y);
	//printf("collision = %d\n", check_map_collision(pos_x, pos_y));
	printf("collision = %d\n", check_map_collision_bottom());



	//texture->render(pos_x, pos_y);
}

Player::~Player() {
	delete texture;
}

int Player::round(float f) {
	return (f > 0.0) ? (f + 0.5) : (f - 0.5);
}

