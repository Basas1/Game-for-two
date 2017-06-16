#pragma once
#include "Player_states.h"
#include "Fireball.h"
#include "init.h"
#include <vector>
#include <tuple>
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
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, UP);
				}
				else if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, DOWN);
				}
				else if (currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, UP_RIGHT);
				}
				else if (currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, UP_LEFT);
				}
				else if (!currentKeyStates[SDL_SCANCODE_UP] && currentKeyStates[SDL_SCANCODE_RIGHT] && !currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, DOWN_RIGHT);
				}
				else if (!currentKeyStates[SDL_SCANCODE_UP] && !currentKeyStates[SDL_SCANCODE_RIGHT] && currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_DOWN]) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, DOWN_LEFT);
				}
				else {
					if (p.flip_right) {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, RIGHT);
					}
					else {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, LEFT);
					}
				}
			}
			else {
				int ox, oy, dz;
				dz = JOYSTICK_DEAD_ZONE;
				ox = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTX);
				oy = SDL_GameControllerGetAxis(p.gamepad, SDL_CONTROLLER_AXIS_LEFTY);
				if (oy < -dz && ox < dz && ox > -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, UP);
				}
				else if (oy > dz && ox < dz && ox > -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, DOWN);
				}
				else if (oy < -dz && ox > dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, UP_RIGHT);
				}
				else if (oy < -dz && ox < -dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, UP_LEFT);
				}
				else if (oy > dz && ox > dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, DOWN_RIGHT);
				}
				else if (oy > dz && ox < -dz / 2) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, DOWN_LEFT);
				}
				else {
					if (p.flip_right) {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, RIGHT);
					}
					else {
						p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, &p, LEFT);
					}
				}
			}
			objects.insert(objects.end(), p.t_ball);
			//p.teleport_cooldown = game_time.get_ticks();
		}
	}
	else {
		Teleportation* tp_state;
		tp_state = new Teleportation(p);
		p.state_stack.push(tp_state);
		p.t_ball->kill();
		p.t_ball = NULL;
	}
}

std::tuple<double, double> Player_states::teleport_to_ball(Player& p) {
	double nx = p.t_ball->pos_x, ny = p.t_ball->pos_y;
	for (int i = 0; i <= p.width / 2; i++) {
		if (p.check_map_collision(nx + i, ny)) {
			nx = nx - p.width / 2 + i;
			break;
		}
		if (p.check_map_collision(nx - i, ny)) {
			nx = nx + p.width / 2 - i;
			break;
		}
	}
	for (int i = 0; i <= p.height / 2; i++) {
		if (p.check_map_collision(nx, ny + i)) {
			ny = ny - p.height / 2 + i;
			break;
		}
		if (p.check_map_collision(nx, ny - i)) {
			ny = ny + p.height / 2 - i;
			break;
		}
	}
	double end_x, end_y;
	end_x = nx - p.width / 2;
	end_y = ny - p.height / 2;
	return std::make_tuple(end_x, end_y);
}

void Player_states::blast_teleport_ball(Player& p) {
	if (p.t_ball != NULL && p.t_ball->stage_two) {
		p.t_ball->kill();
		p.t_ball->blast();
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
				case 10: {
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
			case SDLK_SPACE: {
				Jump_effect* j_effect;
				j_effect = new Jump_effect((int)p.pos_x, (int)p.pos_y, p.jump_effect_animation1);
				objects.insert(objects.end(), j_effect);
				p.vel_y = -p.jump_vel; 
				break;
			}
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
				case 0: {
					Jump_effect* j_effect;
					j_effect = new Jump_effect((int)p.pos_x, (int)p.pos_y, p.jump_effect_animation1);
					objects.insert(objects.end(), j_effect);
					p.vel_y = -p.jump_vel;
					break;
				}
				case 3: {
					cast_fireball(p);
					break;
				}
				case 2: {
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
		delete p.state_stack.top();
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
		p.jump_animation_rise->reset();
	}
	else if (p.vel_y > 0 && !falling) {
		falling = true;
		p.jump_animation_rise->reset();
		p.jump_animation_fall->reset();
	}
	 
	if (p.acc_x == 0) {
		if (p.vel_x > -0.1 && p.vel_x < 0.1) p.vel_x = 0; else {
			p.vel_x -= (p.vel_x / fabs(p.vel_x) ) * 0.05;
		}
	}
	else {
		if (fabs(p.vel_x) <= fabs(p.max_vel_x)) {
			p.vel_x += (p.acc_x / fabs(p.acc_x)) * 0.25;
			if (p.vel_x > p.max_vel_x) p.vel_x = p.max_vel_x;
			if (p.vel_x < -p.max_vel_x) p.vel_x = -p.max_vel_x;
		}
	}
	p.move();

	if (p.check_map_collision_bottom()) {
		p.jump_animation_rise->reset();
		p.jump_animation_fall->reset();
		delete p.state_stack.top();
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
			//a_x -= p.acceleration / 20;
			a_x -= p.acceleration;
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
			//a_x += p.acceleration / 20;
			a_x += p.acceleration;
		}
		p.acc_x = a_x;

		//If a key was pressed
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE: {
				if (jump_count > 0) {
					Jump_effect* j_effect;
					j_effect = new Jump_effect((int)p.pos_x, (int)p.pos_y, p.jump_effect_animation2);
					objects.insert(objects.end(), j_effect);
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
						Jump_effect* j_effect;
						j_effect = new Jump_effect((int)p.pos_x, (int)p.pos_y, p.jump_effect_animation2);
						objects.insert(objects.end(), j_effect);
						p.vel_y = -p.jump_vel;
						jump_count--;
					}
					break;
				}
				case 3: {
					cast_fireball(p);
					break;
				}
				case 2: {
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
		delete p.state_stack.top();
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
			delete p.state_stack.top();
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
						delete p.state_stack.top();
						p.state_stack.pop();

						p.vel_y = -p.jump_vel;
						Jump* jump_state;
						jump_state = new Jump(p);
						jump_state->jump_count = 0;
						p.state_stack.push(jump_state);

						Jump_effect* j_effect;
						j_effect = new Jump_effect((int)p.pos_x, (int)p.pos_y, p.jump_effect_animation2);
						objects.insert(objects.end(), j_effect);
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
							delete p.state_stack.top();
							p.state_stack.pop();

							p.vel_y = -p.jump_vel;
							Jump* jump_state;
							jump_state = new Jump(p);
							jump_state->jump_count = 0;
							p.state_stack.push(jump_state);

							Jump_effect* j_effect;
							j_effect = new Jump_effect((int)p.pos_x, (int)p.pos_y, p.jump_effect_animation2);
							objects.insert(objects.end(), j_effect);
						}
						break;
					}
					}
				}
			}
		}
	}
}

Teleportation::Teleportation(Player& p) {
	p.vulnerable = false;
	horizontal = false;
	p.jump_animation_rise->set_alpha(180);
	p.hit_animation->set_alpha(180);
	p.hit_animation->set_color(p.color_r, p.color_g, p.color_b);
	start_x = p.pos_x;
	start_y = p.pos_y;
	std::tie(dest_x, dest_y) = teleport_to_ball(p);
	double dist_x = dest_x - start_x;
	double dist_y = dest_y - start_y;
	double dist = sqrt(dist_x*dist_x + dist_y*dist_y);
	//x to y distance ratio
	double x_part = fabs(dist_x) / (fabs(dist_x) + fabs(dist_y));
	
	if (fabs(dist_x) > 0) {
		if (fabs(dist) < 990) v_x = 18; else v_x = dist / 55;
	}
	if (fabs(dist_y) > 0) {
		if (fabs(dist) < 990) v_y = 18; else v_y = dist / 55;
	}

	if (fabs(dist_x) == 0) v_x = 0; else {
		v_x *= (dist_x / fabs(dist_x)) * x_part;
	}
	if (fabs(dist_y) == 0) v_y = 0; else {
		v_y *= (dist_y / fabs(dist_y)) * (1.0 - x_part);
	}
	//printf("dist=%f;\ndist_x=%f; dist_y=%f;\n",dist, dist_x, dist_y);
	//printf("vel_x=%f; vel_y=%f;\n", v_x, v_y);
	if (fabs(v_y) < 10) horizontal = true;
	p.vel_x = v_x;
	p.vel_y = v_y;
	if (dist_x < 0) p.flip_right = false;
	if (dist_x > 0) p.flip_right = true;

	Teleport_line* line;
	line = new Teleport_line(p.pos_x, p.pos_y, dest_x, dest_y, &p);
	static_objects.insert(static_objects.end(), line);

}

void Teleportation::logic(Player& p) {
	double compare_x, compare_y;
	v_x == 0 ? compare_x = -1 : compare_x = fabs(v_x);
	v_y == 0 ? compare_y = -1 : compare_y = fabs(v_y);

	if (fabs(p.pos_x - dest_x) > compare_x && fabs(p.pos_y - dest_y) > compare_y && !(v_x == 0 && v_y == 0)) {
		Teleport_trail* trail;
		trail = new Teleport_trail(p.pos_x - 6 * v_x + v_x/2, p.pos_y - 6 * v_y + v_y / 2, dest_x, dest_y, &p);
		static_objects.insert(static_objects.end(), trail);


		p.pos_x += p.vel_x;
		p.pos_y += p.vel_y;

		//Teleport_trail* trail;
		trail = new Teleport_trail(p.pos_x - 6*v_x, p.pos_y - 6*v_y, dest_x, dest_y, &p);
		static_objects.insert(static_objects.end(), trail);


	}
	else {
		p.pos_x = dest_x;
		p.pos_y = dest_y;
		p.vulnerable = true;
		if (fabs(p.vel_x) > p.acceleration) p.vel_x = p.acceleration * (p.vel_x / fabs(p.vel_x));
		if (fabs(p.vel_y) > p.acceleration) p.vel_y = p.acceleration * (p.vel_y / fabs(p.vel_y));
		p.jump_animation_rise->reset();
		p.hit_animation->reset();
		p.jump_animation_rise->set_alpha(255);
		p.hit_animation->set_alpha(255);
		p.hit_animation->set_color(255, 255, 255);
		p.teleport_cooldown = game_time.get_ticks();
		delete p.state_stack.top();
		p.state_stack.pop();
	}
}

void Teleportation::render(Player& p) {
	if (!horizontal) {
		p.jump_animation_rise->render(p.pos_x, p.pos_y, p.flip_right);
		p.jump_animation_rise->next_frame();
	}
	else {
		p.hit_animation->render(p.pos_x, p.pos_y, p.flip_right);
		p.hit_animation->next_frame();
	}
}


Respawn::Respawn(Player& p, double spawn_x, double spawn_y) {
	p.vulnerable = false;
	start_x = p.pos_x;
	start_y = p.pos_y;
	dest_x = spawn_x;
	dest_y = spawn_y;
	double dist_x = dest_x - start_x;
	double dist_y = dest_y - start_y;
	v_x = dist_x / 150;
	v_y = dist_y / 150;
	p.vel_x = v_x;
	p.vel_y = v_y;
}

void Respawn::logic(Player& p) {
	double compare_x, compare_y;
	v_x == 0 ? compare_x = -1 : compare_x = fabs(v_x);
	v_y == 0 ? compare_y = -1 : compare_y = fabs(v_y);

	if (fabs(p.pos_x - dest_x) > compare_x && fabs(p.pos_y - dest_y) > compare_y && !(v_x == 0 && v_y == 0)) {
		p.pos_x += p.vel_x;
		p.pos_y += p.vel_y;
	}
	else {
		p.pos_x = dest_x;
		p.pos_y = dest_y;
		p.vulnerable = true;
		p.vel_x = 0;
		p.vel_y = 0;
		p.unkill_cooldown = game_time.get_ticks();
		p.dead = false;
		delete p.state_stack.top();
		p.state_stack.pop();
	}
}


