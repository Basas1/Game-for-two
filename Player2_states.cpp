#pragma once
#include "Player2_states.h"
#include "Fireball.h"
#include "init.h"
#include "Enemy.h"
#include <vector>
#include "Platform.h"
#include "Teleport_ball.h"

void Player2_states::change_state(Player2& p, int state) {
	switch (state) {
	case STAND_STATE:
		P2_Stand* stand_state;
		stand_state = new P2_Stand;
		p.state_stack.push(stand_state);
		break;
	case RUN_STATE:
		P2_Run* run_state;
		run_state = new P2_Run;
		p.state_stack.push(run_state);
		break;
	case JUMP_STATE:
		P2_Jump* jump_state;
		jump_state = new P2_Jump;
		p.state_stack.push(jump_state);
		break;
	case HIT1_STATE:
		P2_Hit1* hit1_state;
		hit1_state = new P2_Hit1;
		p.state_stack.push(hit1_state);
		break;
	case FIRE_STATE:
		break;
	}
}

void Player2_states::handle_events(Player2& p, SDL_Event& event) {
	int ox, oy;
	ox = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTX);
	oy = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTY);
	if (ox > JOYSTICK_DEAD_ZONE) {
	}
	if (ox < -JOYSTICK_DEAD_ZONE) {
	}


	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		switch (event.cbutton.button) {
		case 1: {
			if (p.t_ball == NULL) {
				int ox, oy, dz;
				dz = JOYSTICK_DEAD_ZONE;
				ox = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTX);
				oy = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTY);

				if (oy < -dz && ox < dz && ox > -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP);
				}
				else if (oy > dz && ox < dz && ox > -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN);
				}
				else if (oy < -dz && ox > dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP_RIGHT);
				}
				else if (oy < -dz && ox < -dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, UP_LEFT);
				}
				else if (oy > dz && ox > dz) {
					p.t_ball = new Teleport_ball(p.pos_x + p.width / 2, p.pos_y + p.height / 2, DOWN_RIGHT);
				}
				else if (oy > dz && ox < -dz) {
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
				objects.insert(objects.end(), p.t_ball);
			}
			else {
				p.pos_x = p.t_ball->pos_x + p.width / 2;
				p.pos_y = p.t_ball->pos_y - p.height / 2;
				p.t_ball->kill();
				p.t_ball = NULL;
			}
			break;
		}
		case 2: {
			if (p.t_ball != NULL) {
				p.t_ball->kill();
				p.t_ball = NULL;
			}
			break;
		}
		}
	}
}


void P2_On_ground::logic(Player2& p) {
	p.vel_x = p.acc_x;
	p.move();
	if (p.vel_y != 0 && !p.check_map_collision_under()) {
		change_state(p, JUMP_STATE);
	}
}

void P2_On_ground::handle_events(Player2& p, SDL_Event& event) {
	//If a key is pressed
	int a_x = 0;

	int ox, oy;
	ox = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTX);
	oy = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTY);
	if (ox > JOYSTICK_DEAD_ZONE) {
			a_x += p.acceleration;
	}
	if (ox < -JOYSTICK_DEAD_ZONE) {
		a_x -= p.acceleration;
	}

	p.acc_x = a_x;

	//If a key was pressed
	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		switch (event.cbutton.button) {
		case 0: p.vel_y = -p.jump_vel; break;
		case 3: {
			Fireball *ball;
			if (p.flip_right) {
				ball = new Fireball(p.pos_x + p.width + 1, p.pos_y + p.height / 3, p.flip_right);
			}
			else {
				ball = new Fireball(p.pos_x - 1, p.pos_y + p.height / 3, p.flip_right);
			}
			objects.insert(objects.end(), ball);
			break;
		}
		case 10: {
			change_state(p, HIT1_STATE);
			break;
		}
		default:
			Player2_states::handle_events(p, event);
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



void P2_Stand::logic(Player2& p) {
	if (p.acc_x != 0) {
		change_state(p, RUN_STATE);
	}
	P2_On_ground::logic(p);
}

void P2_Stand::render(Player2& p) {
	p.stand_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.stand_animation->next_frame();
}

void P2_Run::logic(Player2& p) {
	P2_On_ground::logic(p);
	if (p.acc_x == 0) {
		p.run_animation->set_frame(0);
		p.state_stack.pop();
	}
}

void P2_Run::render(Player2& p) {
	p.run_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.run_animation->next_frame();
}

P2_Jump::P2_Jump() {
	jump_count = 9;
}

void P2_Jump::logic(Player2& p) {
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

void P2_Jump::handle_events(Player2& p, SDL_Event& event) {
	//If a key is pressed
	double a_x = 0;
	int ox, oy;
	ox = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTX);
	oy = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTY);
	if (ox > JOYSTICK_DEAD_ZONE) {
		a_x += p.acceleration;
	}
	if (ox < -JOYSTICK_DEAD_ZONE) {
		a_x -= p.acceleration;
	}
	p.acc_x = a_x;

	//If a key was pressed
	if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		switch (event.jbutton.button) {
		case 0: {
			if (jump_count > 0) {
				p.vel_y = -p.jump_vel;
				jump_count--;
			}
			break;
		}
		case 3: {
			Fireball *ball;
			if (p.flip_right) {
				ball = new Fireball(p.pos_x + p.width + 1, p.pos_y + p.height / 3, p.flip_right);
			}
			else {
				ball = new Fireball(p.pos_x - 1, p.pos_y + p.height / 3, p.flip_right);
			}
			objects.insert(objects.end(), ball);
			break;
		}
		case 10: {
			change_state(p, HIT1_STATE);
			break;
		}
		default:
			Player2_states::handle_events(p, event);
		}
	}
}

void P2_Jump::render(Player2& p) {
	p.jump_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.jump_animation->next_frame();
}


void P2_Hit1::logic(Player2& p) {
	if (p.hit_animation->get_replay_count() > 0) {
		p.hit_animation->reset();
		p.state_stack.pop();
	}
	if (p.hit_animation->get_frame_number() == 6) {
		std::vector<Game_object*> collisions;
		SDL_Rect hit_box;

		if (p.flip_right) {
			hit_box = { (int)p.pos_x + (int)p.width / 2, (int)p.pos_y + (int)(p.height / 2), (int)(p.width), (int)(p.height / 2) };
		}
		else {
			hit_box = { (int)p.pos_x - (int)(p.width / 2), (int)p.pos_y + (int)(p.height / 2), (int)(p.width), (int)(p.height / 2) };
		}
		collisions = p.get_collisions(&hit_box);
		if (collisions.size() != 0) {
			for (int i = 0; i < collisions.size(); i++) {
				if (collisions[i]->type == ENEMY) {
					collisions[i]->kill();
				}
			}
		}
	}
	p.vel_x = 0;
	p.move();
}


void P2_Hit1::render(Player2& p) {
	p.hit_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.hit_animation->next_frame();
}




