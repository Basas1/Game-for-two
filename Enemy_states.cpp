#include "Enemy_states.h"
#include "Fireball.h"
#include "init.h"


void Enemy_states::change_state(Enemy& p, int state) {
	switch (state) {
	case STAND_STATE:
		E_Stand* stand_state;
		stand_state = new E_Stand;
		p.state_stack.push(stand_state);
		break;
	case RUN_STATE:
		E_Run* run_state;
		run_state = new E_Run;
		p.state_stack.push(run_state);
		break;
	case JUMP_STATE:
		E_Jump* jump_state;
		jump_state = new E_Jump;
		p.state_stack.push(jump_state);
		break;
	case HIT1_STATE:
		E_Hit1* hit1_state;
		hit1_state = new E_Hit1;
		p.state_stack.push(hit1_state);
		break;
	case FIRE_STATE:
		break;
	}
}


void E_On_ground::logic(Enemy& p) {
	p.move();
	if (p.vel_y != 0 && !p.check_map_collision_under()) {
		change_state(p, JUMP_STATE);
	}
}

void E_Stand::logic(Enemy& p) {
	if (p.vel_x != 0) {
		change_state(p, RUN_STATE);
	}
	E_On_ground::logic(p);
}

void E_Stand::render(Enemy& p) {
	p.stand_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.stand_animation->next_frame();
}

void E_Run::logic(Enemy& p) {
	E_On_ground::logic(p);
	if (p.vel_x == 0) {
		p.run_animation->set_frame(0);
		p.state_stack.pop();
	}
}

void E_Run::render(Enemy& p) {
	p.run_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.run_animation->next_frame();
}

void E_Jump::logic(Enemy& p) {
	//Speed limit
	if (p.vel_x > p.max_vel_x) p.vel_x = p.max_vel_x;
	if (p.vel_x < -p.max_vel_x) p.vel_x = -p.max_vel_x;

	p.move();
	if (p.check_map_collision_bottom()) {
		//p.vel_x = p.acc_x;
		p.state_stack.pop();
	}
}


void E_Jump::render(Enemy& p) {
	p.jump_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.jump_animation->next_frame();
}


void E_Hit1::logic(Enemy& p) {
	if (p.hit_animation->get_replay_count() > 0) {
		p.hit_animation->reset();
		p.state_stack.pop();
	}
	p.vel_x = 0;
	p.move();
}


void E_Hit1::render(Enemy& p) {
	p.hit_animation->render(p.pos_x, p.pos_y, p.flip_right);
	p.hit_animation->next_frame();
}

