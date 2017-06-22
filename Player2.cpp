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

	stand_animation = new Animated_texture(player2_idle_texture, 8, -75, -40);
	run_animation = new Animated_texture(player2_run_texture, 13, -75, -40);
	jump_animation_rise = new Animated_texture(player2_jump_rise_texture, 4, -75, -40);
	jump_animation_fall = new Animated_texture(player2_jump_fall_texture, 4, -75, -40);
	hit_animation = new Animated_texture(player2_hit_texture, 5, -75, -40);
	dive_animation = new Animated_texture(player2_dive_texture, 4, -75, -40);
	dive_end_animation = new Animated_texture(player2_dive_end_texture, 4, -75, -40);
	dive_smoke_animation = new Animated_texture(player2_dive_smoke_texture, 3, -75, -40);
	fireball_cast_animation1 = new Animated_texture(player2_cast_fireball_texture1, 3, -60, 30);
	fireball_cast_animation2 = new Animated_texture(player2_cast_fireball_texture2, 9, -26, 30);
	arrow->set_color(color_r, color_g, color_b);
	death->set_color(color_r, color_g, color_b);
	fireball = new Animated_texture(player2_fireball_texture, 4, -17, -17);
	fireball_trail = new Animated_texture(player2_fireball_trail_texture, 9, -25, -15);
	//fireball = new Animated_texture(player2_fireball_texture, 3, -25, -25);
	//fireball_trail = new Animated_texture(player2_fireball_trail_texture, 9, -35, -35);
	tp_ball_opening = new Animated_texture(t_ball_opening_texture2, 6, -32, -32);
	int order1[] = { 0, 0, 0, 0, 1, 2, 3, 4, 5 };
	tp_ball_opening->set_frame_order(order1, sizeof(order1) / sizeof(int));
	tp_ball_opened = new Animated_texture(t_ball_opened_texture2, 3, -32, -32);
	tp_ball_trail = new Animated_texture(player2_t_ball_trail_texture, 9, -35, -35);
	tp_ball_blast = new Animated_texture(player2_t_ball_blast_texture, 5);
	tp_blast_smoke = new Animated_texture(player2_blast_smoke_texture, 4);
	tp_trail->set_color(color_r, color_g, color_b);
	tp_line->set_color(color_r, color_g, color_b);
	stand_animation->set_ticks_per_frame(11);
	run_animation->set_ticks_per_frame(3);
	jump_effect_animation1->set_ticks_per_frame(3);
	jump_effect_animation2->set_ticks_per_frame(3);
	fireball_cast_animation1->set_ticks_per_frame(3);
	fireball_cast_animation2->set_ticks_per_frame(1);
	fireball_trail->set_ticks_per_frame(2);
	tp_ball_opening->set_ticks_per_frame(5);




	collision_box = { (int)pos_x, (int)pos_y, width, height };
}


bool Player2::kill(int change) {
	int score_change = 25;
	if (change) score_change = change;
	if (vulnerable && unkill_cooldown == 0) {
		if (t_ball != NULL) {
			if (t_ball->exist) {
				t_ball->kill();
				if (t_ball->stage_two) {
					t_ball->blast();
				}
				t_ball = NULL;
			}
		}
		while (state_stack.size() > 1) {
			delete state_stack.top();
			state_stack.pop();
		}
		state = new Respawn(*this, 3158, 606);
		state_stack.push(state);
		flip_right = false;
		dead = true;
		player1->score += score_change * 100;
		Points_gained* points;
		points = new Points_gained(pos_x, pos_y, this, score_change);
		objects.push_back(points);
		Mix_PlayChannel(-1, death_sound, 0);
		return true;
	}
	return false;
}

