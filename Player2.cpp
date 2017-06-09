#pragma once
#include "Player2.h"
#include "media.h"
#include "init.h"
#include "Player_states.h"



Player2::Player2(int x, int y, int control) : Player(x, y, control) {
	pos_x = 3158;
	pos_y = 606;
	flip_right = false;
	color_r = 255;
	color_g = 50;
	color_b = 50;

	stand_animation = new Animated_texture(player2_stand_texture, 8, -75, -40);
	stand_animation->set_ticks_per_frame(25);
	run_animation = new Animated_texture(player2_run_texture, 13, -75, -40);
	run_animation->set_ticks_per_frame(13);
	jump_animation_rise = new Animated_texture(player2_jump_rise_texture, 4, -75, -40);
	jump_animation_fall = new Animated_texture(player2_jump_fall_texture, 4, -75, -40);
	hit_animation = new Animated_texture(player2_hit_texture, 5, -75, -40);
	dive_animation = new Animated_texture(player2_dive_texture, 1, -75, -40);
	dive_end_animation = new Animated_texture(blast_texture, 4, -100, -40);
	fireball_cast_animation1 = new Animated_texture(player2_cast_fireball_texture1, 3, -60, 30);
	fireball_cast_animation2 = new Animated_texture(player2_cast_fireball_texture2, 9, -26, 30);
	fireball_cast_animation2->set_ticks_per_frame(2);
	arrow->set_color(color_r, color_g, color_b);
	tp_trail->set_color(color_r, color_g, color_b);
	tp_line->set_color(color_r, color_g, color_b);
	mark = new Animated_texture(player2_mark_texture, 1);

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}


bool Player2::kill() {
	if (vulnerable && unkill_cooldown == 0) {
		if (t_ball != NULL) {
			if (t_ball->exist) {
				t_ball->kill();
				t_ball->blast();
				t_ball = NULL;
			}
		}
		state = new Respawn(*this, 3158, 606);
		state_stack.push(state);
		flip_right = false;
		player1->score += 2500;
		unkill_cooldown = game_time.get_ticks();
		return true;
	}
	return false;
}

