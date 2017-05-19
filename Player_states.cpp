#include "Player_states.h"
#include "Fireball.h"
#include "init.h"

void Player_states::change_state(Player& p, int state) {
	switch (state) {
	case STAND_STATE:
		Stand* stand_state;
		stand_state = new Stand;
		p.state_stack.push(stand_state);
		break;
	case RUN_STATE:
		Run* run_state;
		run_state = new Run;
		p.state_stack.push(run_state);
		break;
	case JUMP_STATE:
		Jump* jump_state;
		jump_state = new Jump;
		p.state_stack.push(jump_state);
		break;
	case FIRE_STATE:
		break;
	}
}


void On_ground::logic(Player& p) {
	p.vel_x = p.acc_x;
	p.move();
	if (p.vel_y != 0 && !p.check_map_collision_under()) {
		change_state(p, JUMP_STATE);
	}
}

void On_ground::handle_events(Player& p, SDL_Event& event) {
	//If a key is pressed
	int a_x = 0;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		a_x -= p.acceleration;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		a_x += p.acceleration;
	}
	p.acc_x = a_x;

	//If a key was pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
	//if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE: p.vel_y = -p.jump_vel; break;
		case SDLK_r: p.pos_x = 0; p.pos_y = 0; break;
		}
	}
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_y: p.pos_y -= 100; break;
		case SDLK_g: p.pos_x -= 10; break;
		case SDLK_h: p.pos_y += 10; break;
		case SDLK_j: p.pos_x += 10; break;
		case SDLK_w : {
			Fireball *ball;
			ball = new Fireball(p.pos_x + p.width / 2, p.pos_y + 10, p.flip_right);
			objects.insert(objects.end(), ball);
			break;
		}
		//case SDLK_h: {
		//	Fire* state;
		//	state = new Fire;
		//	p.state_stack.push(state);
		//	break;
		//}
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



void Stand::logic(Player& p) {
	if (p.acc_x != 0) {
		change_state(p, RUN_STATE);
	}
	On_ground::logic(p);
}

void Stand::render(Player& p) {
	p.stand_animation->render(p.center_x, p.center_y, p.flip_right);
	p.stand_animation->next_frame();
}

void Run::logic(Player& p) {
	On_ground::logic(p);
	if (p.acc_x == 0) {
		p.run_animation->set_frame(0);
		p.state_stack.pop();
	}
}

void Run::render(Player& p) {
	p.run_animation->render(p.center_x, p.center_y, p.flip_right);
	p.run_animation->next_frame();
}

Jump::Jump() {
	jump_count = 9;
}

void Jump::logic(Player& p) {	
	p.vel_x += p.acc_x;
	//Speed limit
	if (p.vel_x > p.max_vel_x) p.vel_x = p.max_vel_x;
	if (p.vel_x < -p.max_vel_x) p.vel_x = -p.max_vel_x;

	p.move();
	if (p.check_map_collision_bottom()) {
		//p.vel_x = p.acc_x;
		p.state_stack.pop();
	}
}

void Jump::handle_events(Player& p, SDL_Event& event) {
	//If a key is pressed
	double a_x = 0;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		a_x -= p.acceleration/20;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		a_x += p.acceleration/20;
	}
	p.acc_x = a_x;

	//If a key was pressed
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE: {
			if (jump_count > 0) {
				p.vel_y = -p.jump_vel;
				jump_count--;
			}
			break;
		}
		case SDLK_r: p.pos_x = 0; p.pos_y = 0; break;
		case SDLK_w: {
			Fireball *ball;
			ball = new Fireball(p.pos_x + p.width / 2, p.pos_y + 10, p.flip_right);
			objects.insert(objects.end(), ball);
			break;
		}

		}
	}
}

void Jump::render(Player& p) {
	p.jump_animation->render(p.center_x, p.center_y, p.flip_right);
	p.jump_animation->next_frame();
}


