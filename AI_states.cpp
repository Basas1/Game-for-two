#include "AI_states.h"
#include "init.h"
#include "Fireball.h"

void AI_move::logic(Enemy& e) {
	int vel = 2;
	int vision_x = 500;
	int vision_y = 100;
	std::vector<Game_object*> collisions;
	SDL_Rect hit_box1, hit_box2;
	hit_box1 = { (int)e.pos_x - vision_x, (int)e.pos_y - vision_y, vision_x * 2 + e.width, vision_y * 2 + e.height };
	hit_box2 = objects[0]->collision_box;

	int player_x, player_y;
	player_x = objects[0]->pos_x;
	player_y = objects[0]->pos_y;	

	bool attack = false;
	if (abs(player_x - e.pos_x) <= 500) {
		if (abs(player_y - e.pos_y) <= 100) {
			if (player_x < e.pos_x) {
				e.flip_right = false;
				attack = true;
			}
			else {
				e.flip_right = true;
				attack = true;
			}
		}
	}
	if (attack) {
		e.vel_x = 0;
		Fireball *ball;
		if (e.flip_right) {
			//ball = new Fireball(e.pos_x + e.width + 1, e.pos_y + e.height / 3, e.flip_right);
		}
		else {
			//ball = new Fireball(e.pos_x - 1, e.pos_y + e.height / 3, e.flip_right);
		}
		//objects.insert(objects.end(), ball);
	}
	if (!attack) {
		if (e.flip_right) e.vel_x = vel;
		else {
			e.vel_x = -vel;
		}
	}
	if (!e.can_go_right() || !e.can_go_left()) {
		e.vel_x = -e.vel_x;
	}





}