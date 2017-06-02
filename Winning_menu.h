#pragma once
#include "Programm_state.h"
#include <SDL.h>
#include "Texture.h"
#include "Menu_item.h"

class Winning_menu : public Programm_state {
public:
	enum buttons {
		CNGRATULATIONS,
		PLAYER,
		PLAY_AGAIN,
		QUIT,
	};
	Winning_menu(int id);
	~Winning_menu();
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
	Texture* congratulations;
	Texture* winner;

};

