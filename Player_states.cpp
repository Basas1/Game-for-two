#pragma once
#include "Player_states.h"
#include "Fireball.h"
#include "init.h"
#include "Enemy.h"
#include <vector>
#include "Platform.h"
#include "Teleport_ball.h"

void Player_states::change_state(Player& p, int state, int arg) {
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
		jump_state = new Jump(p);
		p.state_stack.push(jump_state);
		break;
	case HIT1_STATE:
		p.vulnerable = false;
		Hit1* hit1_state;
		hit1_state = new Hit1;
		p.state_stack.push(hit1_state);
		break;
	case HIT2_STATE:
		p.vulnerable = false;
		Hit2* hit2_state;
		hit2_state = new Hit2(arg);
		p.state_stack.push(hit2_state);
		break;
	case FIRE_STATE:
		break;
	}
}

void Player_states::create_fireball(Player& p, int side) {
	p.fireball_casting = true;
	Fireball *ball = NULL;

	if (side == UP || side == DOWN) {
		ball = new Fireball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, side, &p);
	}
	else {
		if (p.flip_right) {
			if (p.state_stack.top()->type == STAND_STATE || p.state_stack.top()->type == JUMP_STATE) {
				ball = new Fireball(p.pos_x + p.width + 1, p.pos_y + p.height / 2, side, &p);
			}
			else {
				ball = new Fireball(p.pos_x + p.width + 1, p.pos_y + p.height / 3, side, &p);
			}
		}
		else {
			if (p.state_stack.top()->type == STAND_STATE || p.state_stack.top()->type == JUMP_STATE) {
				ball = new Fireball(p.pos_x - 1, p.pos_y + p.height / 2, side, &p);
			}
			else {
				ball = new Fireball(p.pos_x - 1, p.pos_y + p.height / 3, side, &p);
			}
		}
	}
	objects.insert(objects.end(), ball);
	p.fireball_cooldown = game_time.get_ticks();
}


void Player_states::cast_fireball(Player& p) {
	if (p.fireball_cooldown <= 0) {
		p.fireball_casting = true;
		if (p.controller == NULL) {
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
				create_fireball(p, UP);
			}
			else if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
				create_fireball(p, DOWN);
			}
			else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
				create_fireball(p, UP_RIGHT);
			}
			else if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
				create_fireball(p, UP_LEFT);
			}
			else if (!currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
				create_fireball(p, DOWN_RIGHT);
			}
			else if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
				create_fireball(p, DOWN_LEFT);
			}
			else {
				if (p.flip_right) {
					create_fireball(p, RIGHT);
				}
				else {
					create_fireball(p, LEFT);
				}
			}
		}
		else {
			int ox, oy, dz;
			dz = JOYSTICK_DEAD_ZONE;
			ox = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTX);
			oy = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTY);
			if (oy < -dz && ox < dz && ox > -dz) {
				create_fireball(p, UP);
			}
			else if (oy > dz && ox < dz && ox > -dz) {
				create_fireball(p, DOWN);
			}
			else if (oy < -dz && ox > dz / 2) {
				create_fireball(p, UP_RIGHT);
			}
			else if (oy < -dz && ox < -dz / 2) {
				create_fireball(p, UP_LEFT);
			}
			else if (oy > dz && ox > dz / 2) {
				create_fireball(p, DOWN_RIGHT);
			}
			else if (oy > dz && ox < -dz / 2) {
				create_fireball(p, DOWN_LEFT);
			}

			else {
				if (p.flip_right) {
					create_fireball(p, RIGHT);
				}
				else {
					create_fireball(p, LEFT);
				}
			}
		}
	}
}

void Player_states::cast_teleport_ball(Player& p) {
	if (p.t_ball == NULL) {
		if (p.teleport_cooldown <= 0) {
			if (p.controller == NULL) {
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP);
				}
				else if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN);
				}
				else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP_RIGHT);
				}
				else if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP_LEFT);
				}
				else if (!currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN_RIGHT);
				}
				else if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN_LEFT);
				}
				else {
					if (p.flip_right) {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, RIGHT);
					}
					else {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, LEFT);
					}
				}
			}
			else {
				int ox, oy, dz;
				dz = JOYSTICK_DEAD_ZONE;
				ox = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTX);
				oy = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTY);
				if (oy < -dz && ox < dz && ox > -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP);
				}
				else if (oy > dz && ox < dz && ox > -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN);
				}
				else if (oy < -dz && ox > dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP_RIGHT);
				}
				else if (oy < -dz && ox < -dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP_LEFT);
				}
				else if (oy > dz && ox > dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN_RIGHT);
				}
				else if (oy > dz && ox < -dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN_LEFT);
				}
				else {
					if (p.flip_right) {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, RIGHT);
					}
					else {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, LEFT);
					}
				}
			}
			objects.insert(objects.end(), p.t_ball);
			p.teleport_cooldown = game_time.get_ticks();
		}
	}
	else {
		p.teleport_to_ball();
		p.t_ball->kill();
		p.t_ball = NULL;
	}
}

void Player_states::blast_teleport_ball(Player& p) {
	if (p.t_ball != NULL && p.t_ball->stage_two) {
		p.t_ball->blast();
		p.t_ball->kill();
		p.t_ball = NULL;
	}
}

void Player_states::handle_events(Player& p, SDL_Event& event) {
	if (p.controller == NULL) {
		//Handle Event for keyboard control
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_r: {
				cast_teleport_ball(p);
				break;
			}
			case SDLK_t: {
				blast_teleport_ball(p);
				break;
			}
			case SDLK_f: {
				Enemy* enemy;
				enemy = new Enemy;
				enemy->pos_x = p.pos_x + 100;
				enemy->pos_y = p.pos_y;
				objects.insert(objects.end(), enemy);
				break;
			}
			case SDLK_y: p.pos_y -= 100; break;
			case SDLK_g: p.pos_x -= 10; break;
			case SDLK_h: p.pos_y += 10; break;
			case SDLK_j: p.pos_x += 10; break;
			}
		}
	}
	else {
		//Handle event for gamepad control
		if (event.type == SDL_CONTROLLERBUTTONDOWN) {
			if (event.cbutton.which == p.gamepad_id) {
				switch (event.cbutton.button) {
				case 1: {
					cast_teleport_ball(p);
					break;
				}
				case 2: {
					blast_teleport_ball(p);
					break;
				}
				}
			}
		}
	}
}


void On_ground::logic(Player& p) {
	p.vel_x = p.acc_x;
	p.move();
	if (p.vel_y != 0) {
		change_state(p, JUMP_STATE);
	}
}

void On_ground::handle_events(Player& p, SDL_Event& event) {
	if (p.controller == NULL) {
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
			switch (event.key.keysym.sym) {
			case SDLK_SPACE: p.vel_y = -p.jump_vel; break;
			}
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w: {
				cast_fireball(p);
				break;
			}
			case SDLK_e: {
				if (p.hit_cooldown == 0) {
					change_state(p, HIT1_STATE);
				}
				break;
			}
			default:
				Player_states::handle_events(p, event);
			}
		}
	}
	else {
		int a_x = 0;
		int ox, oy;
		ox = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTX);
		oy = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTY);
		if (ox > JOYSTICK_DEAD_ZONE) {
			a_x += p.acceleration;
		}
		if (ox < -JOYSTICK_DEAD_ZONE) {
			a_x -= p.acceleration;
		}
		p.acc_x = a_x;

		//If a key was pressed
		if (event.type == SDL_CONTROLLERBUTTONDOWN) {
			if (event.cbutton.which == p.gamepad_id) {
				switch (event.cbutton.button) {
				case 0: p.vel_y = -p.jump_vel; break;
				case 3: {
					cast_fireball(p);
					break;
				}
				case 10: {
					if (p.hit_cooldown == 0) {
						change_state(p, HIT1_STATE);
					}
					break;
				}
				default:
					Player_states::handle_events(p, event);
				}
			}
		}

	}
}


void Stand::logic(Player& p) {
	if (p.acc_x != 0) {
		change_state(p, RUN_STATE);
	}
	On_ground::logic(p);
}

void Stand::render(Player& p) {
	p.stand_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.stand_animation->next_frame();

	if (p.fireball_casting) {
		p.fireball_cast_animation2->render(p.pos_x, p.pos_y, p.flip_right);
		p.fireball_cast_animation2->next_frame();
		if (p.fireball_cast_animation2->get_replay_count() > 0) {
			p.fireball_casting = false;
			p.fireball_cast_animation1->reset();
			p.fireball_cast_animation2->reset();
		}
	}
}

void Run::logic(Player& p) {
	On_ground::logic(p);
	if (p.acc_x == 0) {
		p.run_animation->set_frame(0);
		p.state_stack.pop();
	}
}

void Run::render(Player& p) {
	p.run_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.run_animation->next_frame();

	if (p.fireball_casting) {
		p.fireball_cast_animation1->render(p.pos_x, p.pos_y, p.flip_right);
		p.fireball_cast_animation1->next_frame();
		if (p.fireball_cast_animation1->get_replay_count() > 0) {
			p.fireball_casting = false;
			p.fireball_cast_animation1->reset();
			p.fireball_cast_animation2->reset();
		}
	}

}

Jump::Jump(Player& p) {
	type = JUMP_STATE;
	jump_count = 1;
	if (p.vel_y <= 0) {
		falling = false;
	}
	else {
		falling = true;
	}
}

void Jump::logic(Player& p) {
	if (p.vel_y <= 0 && falling) {
		falling = false;
		p.jump_animation_fall->reset();
		//p.jump_animation_rise->reset();
	}
	else if (p.vel_y > 0 && !falling) {
		falling = true;
		p.jump_animation_rise->reset();
	}
	p.vel_x += p.acc_x;
	//Speed limit
	if (p.vel_x > p.max_vel_x) p.vel_x = p.max_vel_x;
	if (p.vel_x < -p.max_vel_x) p.vel_x = -p.max_vel_x;

	p.move();
	if (p.check_map_collision_bottom()) {
		//p.vel_x = p.acc_x;
		p.jump_animation_rise->reset();
		p.jump_animation_fall->reset();
		p.state_stack.pop();
	}
}

void Jump::handle_events(Player& p, SDL_Event& event) {
	if (p.controller == NULL) {
		//If a key is pressed
		double a_x = 0;
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP]) {
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		}
		if (currentKeyStates[SDL_SCANCODE_LEFT]) {
			a_x -= p.acceleration / 20;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			a_x += p.acceleration / 20;
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
			case SDLK_w: {
				cast_fireball(p);
				break;
			}
			case SDLK_e: {
				if (p.hit_cooldown == 0) {
					if (currentKeyStates[SDL_SCANCODE_DOWN]) {
						change_state(p, HIT2_STATE, jump_count);
					}
					else {
						change_state(p, HIT1_STATE);
					}
				}
				break;
			}
			default:
				Player_states::handle_events(p, event);
			}
		}
	}
	else {
		double a_x = 0;
		int ox, oy, dz;
		dz = JOYSTICK_DEAD_ZONE;
		ox = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTX);
		oy = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTY);
		if (ox > JOYSTICK_DEAD_ZONE) {
			a_x += p.acceleration;
		}
		if (ox < -JOYSTICK_DEAD_ZONE) {
			a_x -= p.acceleration;
		}
		p.acc_x = a_x;

		//If a key was pressed
		if (event.type == SDL_CONTROLLERBUTTONDOWN) {
			if (event.cbutton.which == p.gamepad_id) {
				switch (event.jbutton.button) {
				case 0: {
					if (jump_count > 0) {
						p.vel_y = -p.jump_vel;
						jump_count--;
					}
					break;
				}
				case 3: {
					cast_fireball(p);
					break;
				}
				case 10: {
					if (p.hit_cooldown == 0) {
						if (oy > dz) {
							change_state(p, HIT2_STATE, jump_count);
						}
						else {
							change_state(p, HIT1_STATE);
						}
					}
					break;
				}
				default:
					Player_states::handle_events(p, event);
				}
			}
		}
	}
}

void Jump::render(Player& p) {
	if (falling) {
		p.jump_animation_fall->render(p.pos_x, p.pos_y, p.flip_right);
		if (p.jump_animation_fall->get_frame_number() < 3) {
			p.jump_animation_fall->next_frame();
		}
	}
	else {
		p.jump_animation_rise->render(p.pos_x, p.pos_y, p.flip_right);
		if (p.jump_animation_rise->get_frame_number() < 3) {
			p.jump_animation_rise->next_frame();
		}
	}

	if (p.fireball_casting) {
		int cast_x = p.pos_x;
		if (p.flip_right) {
			cast_x -= p.width / 3;
		}
		else {
			cast_x += p.width / 3;
		}
		p.fireball_cast_animation2->render(cast_x, p.pos_y, p.flip_right);
		p.fireball_cast_animation2->next_frame();
		if (p.fireball_cast_animation2->get_replay_count() > 0) {
			p.fireball_casting = false;
			p.fireball_cast_animation1->reset();
			p.fireball_cast_animation2->reset();
		}
	}
}


void Hit1::logic(Player& p) {
	if (p.hit_animation->get_replay_count() > 0) {
		p.hit_animation->reset();
		p.vel_x = 0;
		p.hit_cooldown = game_time.get_ticks();
		p.vulnerable = true;
		p.state_stack.pop();
	}

	std::vector<Game_object*> collisions;
	SDL_Rect hit_box;

	if (p.flip_right) {
		hit_box = { (int)p.pos_x + (int)p.width / 2, (int)p.pos_y, (int)(p.width), (int)(p.height) };
	}
	else {
		hit_box = { (int)p.pos_x - (int)(p.width / 2), (int)p.pos_y, (int)(p.width), (int)(p.height) };
	}
	collisions = p.get_collisions(&hit_box);
	if (collisions.size() != 0) {
		for (int i = 0; i < collisions.size(); i++) {
			if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
				collisions[i]->kill();
			}
			if (collisions[i]->type == FIREBALL && collisions[i]->parent!=&p) {
				collisions[i]->parent = &p;
				collisions[i]->vel_x = -collisions[i]->vel_x * 7 / 5;
				collisions[i]->vel_y = -collisions[i]->vel_y * 7 / 5;
			}
		}
	}

	if (p.flip_right) {
		p.vel_x = p.acceleration * 2;
	}
	else {
		p.vel_x = -p.acceleration * 2;
	}
	p.vel_y = 0;
	p.move();
}


void Hit1::render(Player& p) {
	p.hit_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.hit_animation->next_frame();
}

Hit2::Hit2(int jump) {
	type = HIT2_STATE;
	landing = false;
	if (jump == 0) {
		can_cancel = false;
	}
	else {
		can_cancel = true;
	}
}


void Hit2::render(Player& p) {
	if (!landing) {
		p.dive_animation->render(p.pos_x, p.pos_y, p.flip_right);
		p.dive_animation->next_frame();
	}
	else {
		p.dive_end_animation->render(p.pos_x, p.pos_y, p.flip_right);
		p.dive_end_animation->next_frame();
	}
}

void Hit2::logic(Player& p) {
	if (!landing) {
		p.vel_x = 0;
		if (p.vel_y <= 8) p.vel_y = 8;
		if (p.check_map_collision_bottom()) {
			landing = true;
			//p.dive_animation->reset();
			//p.hit_cooldown = game_time.get_ticks();
			//p.vulnerable = true;
			//p.state_stack.pop();
		}
		std::vector<Game_object*> collisions;
		SDL_Rect hit_box;
		hit_box = { (int)p.pos_x - (int)(p.width / 2), (int)p.pos_y, (int)(p.width) * 2, (int)(p.height) };
		collisions = p.get_collisions(&hit_box);
		if (collisions.size() != 0) {
			for (int i = 0; i < collisions.size(); i++) {
				if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
					collisions[i]->kill();
				}
				if (collisions[i]->type == FIREBALL && collisions[i]->parent != &p) {
					collisions[i]->parent = &p;
					collisions[i]->vel_x = -collisions[i]->vel_x * 7 / 5;
					collisions[i]->vel_y = -collisions[i]->vel_y * 7 / 5;
				}
			}
		}
		p.move();
	}
	else {
		if (p.dive_end_animation->get_replay_count() > 0) {
			p.dive_end_animation->reset();
			p.dive_animation->reset();
			p.hit_cooldown = game_time.get_ticks();
			p.vulnerable = true;
			p.state_stack.pop();
		}
		std::vector<Game_object*> collisions;
		SDL_Rect hit_box;
		hit_box = { (int)p.pos_x - (int)(p.width / 2), (int)p.pos_y, (int)(p.width) * 2, (int)(p.height) };
		collisions = p.get_collisions(&hit_box);
		if (collisions.size() != 0) {
			for (int i = 0; i < collisions.size(); i++) {
				if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
					collisions[i]->kill();
				}
				if (collisions[i]->type == FIREBALL && collisions[i]->parent != &p) {
					collisions[i]->parent = &p;
					collisions[i]->vel_x = -collisions[i]->vel_x * 7 / 5;
					collisions[i]->vel_y = -collisions[i]->vel_y * 7 / 5;
				}
			}
		}
	}
}


void Hit2::handle_events(Player& p, SDL_Event& event) {
	if (!landing) {
		if (p.controller == NULL) {
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
				case SDLK_SPACE: {
					if (can_cancel) {
						p.hit_animation->reset();
						p.hit_cooldown = game_time.get_ticks();
						p.vulnerable = true;
						p.state_stack.pop();

						p.vel_y = -p.jump_vel;
						Jump* jump_state;
						jump_state = new Jump(p);
						jump_state->jump_count = 0;
						p.state_stack.push(jump_state);
					}
					break;
				}
				}
			}
		}
		else {
			//If a key was pressed
			if (event.type == SDL_CONTROLLERBUTTONDOWN) {
				if (event.cbutton.which == p.gamepad_id) {
					switch (event.jbutton.button) {
					case 0: {
						if (can_cancel) {
							p.hit_animation->reset();
							p.hit_cooldown = game_time.get_ticks();
							p.vulnerable = true;
							p.state_stack.pop();

							p.vel_y = -p.jump_vel;
							Jump* jump_state;
							jump_state = new Jump(p);
							jump_state->jump_count = 0;
							p.state_stack.push(jump_state);
						}
						break;
					}
					}
				}
			}
		}
	}
}



