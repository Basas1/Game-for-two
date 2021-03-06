#pragma once
#include <SDL.h>
#include "Texture.h"
#include "Game_object.h"
#include "Animated_texture.h"
#include "Player.h"

class Static_object : public Game_object {
public:
	void handle_events(SDL_Event& event) {};
	void logic() {};
	virtual void render() {};
	//True if object turn to rigrht side
	bool flip_right;
};

class Simple_animation : public Static_object {
public:
	Simple_animation(int x, int y, Animated_texture* a_texture, int replay_count = 1);
	void logic();
	void render();
	void set_offset(int x, int y);
	Animated_texture* animation;
	int replays;
	int off_x;
	int off_y;
};

class Points_gained : public Static_object {
public:
	Points_gained(int x, int y, Player* p, int gain);
	void render();
	int points;
	int replay;
	Uint8 color_r;
	Uint8 color_g;
	Uint8 color_b;
	Player* player;
};

class Blast : public Static_object {
public:
	Blast(int x, int y, Player* p);
	void logic();
	void render();
	Animated_texture* blast_t;
	Animated_texture* blast_smoke_t;
	bool stage_two;
	SDL_Rect hit_box1;
	SDL_Rect hit_box2;
};

class Capture_platform : public Static_object {
public:
	Capture_platform(int x, int y, int w, int h);
	~Capture_platform();
	void logic();
	void render();
	Animated_texture* p_texture;
	Animated_texture* p_texture2;
};

class Fireball_trail : public Static_object {
public:
	Fireball_trail(int x, int y, Player* p, double trail_angle);
	void render();
	Animated_texture* f_trail;
	Player* player;
	double angle;
	bool starting;
	int skip;
	int total_frame_count;
	int frame;
};

class Tp_ball_trail : public Static_object {
public:
	Tp_ball_trail(int x, int y, Player* p);
	bool starting;
	int skip;
	int total_frame_count;
	int frame;
	void render();
	Player* parent;
	Animated_texture* tp_trail;
};

class Teleport_trail : public Static_object {
public:
	Teleport_trail(int x, int y, double dest_x, double dest_y, Player* p);
	Player* father;
	void render();
	double alpha;
	double destx, desty;
	double angle;
};

class Teleport_line : public Static_object {
public:
	Teleport_line(int x, int y, double dest_x, double dest_y, Player* p);
	void render();
	Player* father;
	double angle;
	double alpha;
	double vx, vy;
	double destx, desty;
	int time_to_die;
	bool its_time;
};

class Jump_effect : public Static_object {
public:
	Jump_effect(int x, int y, Animated_texture* animation);
	void render();
	Animated_texture* effect_animation;
};

class Help : public Static_object {
public:
	Help(Player* p);
	~Help();
	Animated_texture* help_t;
	void render();
	Player* player;
};

