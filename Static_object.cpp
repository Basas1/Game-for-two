#pragma once
#include "Static_object.h"
#include "media.h"


Blast::Blast(int x, int y) : Static_object() {
	blast_t = new Animated_texture(blast_texture, 4);
	width = blast_t->get_width();
	height = blast_t->get_height();

	pos_x = x - width / 2;
	pos_y = y - height / 2;

	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Blast::logic() {
	if (blast_t->get_replay_count() < 1) {
		std::vector<Game_object*> collisions;
		SDL_Rect hit_box = collision_box;
		collisions = get_collisions(&hit_box);
		if (collisions.size() != 0) {
			for (int i = 0; i < collisions.size(); i++) {
				if (collisions[i]->type == ENEMY || collisions[i]->type == PLAYER) {
					collisions[i]->kill();
				}
			}
		}
	}
	else {
		exist = false;
		//delete this;
	}
}

void Blast :: render() {
	blast_t->render(pos_x, pos_y);
	blast_t->next_frame();
}

Blast::~Blast() {
	delete blast_t;
	blast_t = NULL;
}


Capture_platform::Capture_platform(int x, int y, int w, int h) : Static_object() {
	type = PLATFORM;
	pos_x = x;
	pos_y = y;
	width = w;
	height = h;
	collision_box = { (int)pos_x, (int)pos_y, width, height };
}

void Capture_platform::logic() {
	int player_index = -1;
	int i;
	bool one_player = false;

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
				if (time - collision_list[player_index]->time_on_platform >= 2000) {
					collision_list[player_index]->score += 1;
				}
			}
		}
	}
}



Fireball_trail::Fireball_trail(int x, int y, Game_object* p) : Static_object() {
	parent = p;
	pos_x = x;
	pos_y = y;
	if (parent == player1) {
		f_trail = new Animated_texture(player_fireball_trail_texture, 9, -35, -35);
	}
	else {
		f_trail = new Animated_texture(player2_fireball_trail_texture, 9, -35, -35);
	}
	f_trail->set_ticks_per_frame(2);
}

void Fireball_trail::render() {
	if (f_trail->get_replay_count() > 0) {
		exist = false;
		//delete this;
	}
	else {
		f_trail->render(pos_x, pos_y);
		f_trail->next_frame();
	}
}

Fireball_trail::~Fireball_trail() {
	delete f_trail;
	f_trail = NULL;
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



