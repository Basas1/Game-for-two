#pragma once
#include "Programm_state.h"
#include <SDL.h>
#include "Texture.h"
#include "Menu_item.h"

class Pause_menu : public Programm_state {
public:
	enum buttons {
		CONTINUE,
		RESTART,
		EXIT,
	};
	Pause_menu();
	~Pause_menu();
	void handle_events();
	void logic();
	void render();
	int check_if_choosed();
	void up();
	void down();
	void enter();
	void escape();

private:
	Menu_item* items[10];
	Texture* game_is_paused;

};

