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
