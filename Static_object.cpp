#pragma once
#include "Static_object.h"
#include "media.h"

#define PI 3.14159265

Simple_animation::Simple_animation(int x, int y, Animated_texture* a_texture, int replay_count) : Static_object() {
	pos_x = x;
	pos_y = y;
	off_x = 0;
	off_y = 0;
	animation = a_texture;
	animation->reset();
	replays = replay_count;
}

void Simple_animation::logic() {
	if (animation->get_replay_count() >= replays) {
		exist = false;
	}
}

void Simple_animation::set_offset(int x, int y) {
	off_x = x;
	off_y = y;
}

void Simple_animation::render() {
	animation->render(pos_x + off_x, pos_y + off_y);
	animation->next_frame();
}

Blast::Blast(int x, int y, Player* p) : Static_object() {
	parent = p;
	blast_t = p->tp_ball_blast;
	blast_smoke_t = p->tp_blast_smoke;
	blast_t->reset();
	blast_smoke_t->reset();
	stage_two = false;

	width = blast_t->get_width();
	height = blast_t->get_height();

	pos_x = x - width / 2;
	pos_y = y - height / 2;

	hit_box1 = { (int)pos_x + 12, (int)pos_y + 60, 264, 168 };
	hit_box2 = { (int)pos_x + 60, (int)pos_y + 12, 168, 264 };
}

void Blast::logic() {
	if (!stage_two) {
		if (blast_t->get_replay_count() < 1) {
			std::vector<Game_object*> collisions;
			collisions = get_collisions(&hit_box1);
			if (collisions.size() != 0) {
				for (int i = 0; i < collisions.size(); i++) {
					if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
						collisions[i] == parent ? collisions[i]->kill() : collisions[i]->kill(50);
					}
				}
			}
			collisions = get_collisions(&hit_box2);
			if (collisions.size() != 0) {
				for (int i = 0; i < collisions.size(); i++) {
					if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
						collisions[i] == parent ? collisions[i]->kill() : collisions[i]->kill(50);
					}
				}
			}
		}
		else {
			stage_two = true;
		}
	}
	else {
		if (blast_smoke_t->get_replay_count() >= 1) {
			exist = false;
		}
	}
}

void Blast :: render() {
	if (!stage_two) {
		blast_t->render(pos_x, pos_y);
		blast_t->next_frame();
	}
	else {
		blast_smoke_t->render(pos_x, pos_y);
		blast_smoke_t->next_frame();
	}
}

Capture_platform::Capture_platform(int x, int y, int w, int h) : Static_object() {
	type = PLATFORM;
	pos_x = x;
	pos_y = y;
	width = w;
	height = h;
	collision_box = { (int)pos_x, (int)pos_y, width, height };
	p_texture = new Animated_texture(platform_texture, 6, 0, 0, 1, 6);
	p_texture2 = new Animated_texture(platform_diamond_texture, 6);
}

Capture_platform::~Capture_platform() {
	delete p_texture;
	delete p_texture2;
	p_texture = NULL;
	p_texture2 = NULL;
}

void Capture_platform::logic() {
	int player_index = -1;
	int i;
	bool one_player = false;
	p_texture->set_color(255, 255, 255);
	p_texture2->set_color(255, 255, 255);

	std::vector<Game_object*> collision_list;
	collision_list = get_collisions();
	
	if (collision_list.size() != 0) {
		for (i = 0; i < collision_list.size(); i++) {
			if (collision_list[i]->type == PLAYER) {
				player_index = i;
				one_player = true;
				i++;
				break;
			}
		}
		for (i; i < collision_list.size(); i++) {
			if (collision_list[i]->type == PLAYER) {
				collision_list[i]->on_platform = false;
				collision_list[player_index]->on_platform = false;
				one_player = false; 
				break;
			}
		}

		if (one_player) {
			int time = SDL_GetTicks();
			if (!collision_list[player_index]->on_platform) {
				collision_list[player_index]->time_on_platform = time;
				collision_list[player_index]->on_platform = true;
			}
			if (collision_list[player_index]->on_platform) {
				//printf("time=%d;\ttime on platform=%d;\n", time, collision_list[player_index]->time_on_platform);
				if (time - collision_list[player_index]->time_on_platform >= 500) {
					collision_list[player_index]->score += 3;
					if (collision_list[player_index] == player1) {
						p_texture->set_color(player1->color_r, player1->color_g, player1->color_b);
						p_texture2->set_color(player1->color_r, player1->color_g, player1->color_b);
					}
					else if (collision_list[player_index] == player2) {
						p_texture->set_color(player2->color_r, player2->color_g, player2->color_b);
						p_texture2->set_color(player2->color_r, player2->color_g, player2->color_b);
					}
				}
			}
		}
	}
}

void Capture_platform::render() {
	p_texture->render(1313, 1188);
	p_texture2->render(1174, 1180);
	p_texture->next_frame();
	p_texture2->next_frame();
}


Fireball_trail::Fireball_trail(int x, int y, Player* p, double trail_angle) : Static_object() {
	parent = p;
	player = p;
	pos_x = x;
	pos_y = y;
	angle = trail_angle;
	f_trail = p->fireball_trail;
	starting = true;
	total_frame_count = f_trail->total_frames;
	skip = 1;
	frame = 0;
}

void Fireball_trail::render() {
	f_trail->set_frame(frame);
	f_trail->render(pos_x, pos_y, true, angle);
	if (starting) {
		starting = false;
	}
	else {
		if (!(skip++ % 1)) {
			frame++;
		}
	}
	if (frame >= total_frame_count) {
		exist = false;
	}
}

Jump_effect::Jump_effect(int x, int y, Animated_texture* animation) {
	pos_x = x;
	pos_y = y;
	effect_animation = animation;
}

void Jump_effect::render() {
	if (effect_animation->get_replay_count() > 0) {
		effect_animation->reset();
		exist = false;
	}
	else {
		effect_animation->render(pos_x, pos_y);
		effect_animation->next_frame();
	}
}

Help::Help(Player* p) {
	type = HELP;
	parent = p;
	player = p;
	help_t = new Animated_texture(help_texture, 1, -225, -40);
}

void Help::render() {
	if (!player->dead) {
		help_t->render(parent->pos_x, parent->pos_y);
	}
}

Help::~Help() {
	delete help_t;
	help_t = NULL;
}

Teleport_trail::Teleport_trail(int x, int y, double dest_x, double dest_y, Player* p) : Static_object() {
	parent = p;
	father = p;
	pos_x = x;
	pos_y = y;
	destx = dest_x;
	desty = dest_y;
	angle = 0.0;
	alpha = 20;
	double dist_y, dist_x;
	double param, result;
	dist_x = dest_x - x;
	dist_y = dest_y - y;
	param = dist_y / dist_x;
	result = atan(param) * 180 / PI;
	if (dist_x < 0) {
		result += 180;
	}
	angle = result;

}

void Teleport_trail::render() {
	father->tp_trail->set_alpha((int)alpha);
	alpha -= 0.7;
	father->tp_trail->render(pos_x - 100, pos_y - 50, true, angle);
	father->tp_trail->next_frame();
	
	if (alpha <= 0) exist = false;
}


Teleport_line::Teleport_line(int x, int y, double dest_x, double dest_y, Player* p) : Static_object() {
	time_to_die = 40;
	its_time = false;
	parent = p;
	father = p;
	pos_x = x;
	pos_y = y;
	destx = dest_x;
	desty = dest_y;
	angle = 0.0;
	double dist_y, dist_x;
	double param, result;
	dist_x = dest_x - x;
	dist_y = dest_y - y;
	param = dist_y / dist_x;
	result = atan(param) * 180 / PI;
	if (dist_x < 0) {
		result += 180;
	}
	angle = result;
	alpha = 20;
	father->tp_line->set_alpha(alpha);
	vx = (dest_x - x) / 40;
	vy = (dest_y - y) / 40;	
}

void Teleport_line::render() {
	double i = pos_x, j = pos_y;
	while (fabs(destx-i) > 100 || fabs(desty - j) > 100) {
		father->tp_line->render(i - 100, j - 50, true, angle);
		i += vx;
		j += vy;
	}
	if ((destx - 100 < parent->pos_x && parent->pos_x < destx + 100) && (desty - 100 < parent->pos_y && parent->pos_y< desty + 100)) {
		its_time = true;
	}
	if (its_time) {
		if (time_to_die-- > 0) {
			father->tp_line->set_alpha(alpha);
			if (alpha > 1) alpha -= 0.5;
		} else {
			exist = false;
		}
	}
}


Tp_ball_trail::Tp_ball_trail(int x, int y, Player* p) : Static_object() {
	parent = p;
	starting = true;
	pos_x = x;
	pos_y = y;
	tp_trail = parent->tp_ball_trail;
	total_frame_count = tp_trail->total_frames;
	skip = 1;
	frame = 0;
}

void Tp_ball_trail::render() {
	tp_trail->set_frame(frame);
	tp_trail->render(pos_x, pos_y);
	if (starting) {
		starting = false;
	}
	else {
		if (!(skip++ % 1)) {
			frame++;
		}
	}
	if (frame >= total_frame_count) {
		exist = false;
	}
}

