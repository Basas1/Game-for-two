#pragma once
#include "Winning_menu.h"
#include "media.h"
#include "init.h"
#include "Game.h"



Winning_menu::Winning_menu(int id) {
	state = STATE_PAUSE;

	for (int i = 0; i < 10; i++) {
		items[i] = NULL;
	}

	congratulations = new Texture(emenu_congratulations_t);
	congratulations->set_absolute_coord();

	if (id == 1) {
		winner = new Texture(emenu_p1w_t);
		winner->set_absolute_coord();
	}
	else {
		winner = new Texture(emenu_p2w_t);
		winner->set_absolute_coord();
	}



	int c = 0;
	Menu_item* play_again;
	Menu_item* quit;

	play_again = new Menu_item(PLAY_AGAIN, 0, 0, emenu_play_again_t);
	items[c++] = play_again;
	quit = new Menu_item(QUIT, 0, 0, emenu_quit_t);
	items[c++] = quit;

	int menu_height = 200;
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			menu_height += items[i]->height;
		}
	}

	int c_x = SCREEN_WIDTH / 2;
	int start_y = (int)((SCREEN_HEIGHT - menu_height) / 2);

	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			items[i]->set_x(c_x - items[i]->width / 2);
			items[i]->set_y(start_y);
			start_y += items[i]->height;
		}
	}

}

int Winning_menu::check_if_choosed() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			if (items[i]->choosen) return i;
		}
	}
	return -1;
}

Winning_menu::~Winning_menu() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			delete items[i];
			items[i] = NULL;
		}
	}
	delete congratulations;
	delete winner;
	congratulations = NULL;
	winner = NULL;
}

void Winning_menu::up() {
	int current;
	current = check_if_choosed();
	if (current == -1) {
		for (int i = 0; i < 10; i++) {
			if (items[i] != NULL) {
				if (items[i]->type == PLAY_AGAIN) items[i]->toggle();
			}
		}
	}
	else {
		bool changed = false;
		if (current != 0) {
			for (int j = current - 1; j >= 0; j--) {
				if (items[j] != NULL) {
					if (items[j]->choosable) {
						items[current]->toggle();
						items[j]->toggle();
						break;
					}
				}
			}
		}
	}
}

void Winning_menu::down() {
	int current;
	current = check_if_choosed();
	if (current == -1) {
		for (int i = 0; i < 10; i++) {
			if (items[i] != NULL) {
				if (items[i]->type == PLAY_AGAIN) items[i]->toggle();
			}
		}
	}
	else {
		bool changed = false;
		for (int j = current + 1; j < 10; j++) {
			if (items[j] != NULL) {
				if (items[j]->choosable) {
					items[current]->toggle();
					items[j]->toggle();
					break;
				}
			}
		}
	}
}

void Winning_menu::enter() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			if (items[i]->choosen) {
				if (items[i]->type == PLAY_AGAIN) {
					while (programm_states.size() > 0) {
						if (programm_states.top()->state == STATE_GAME) {
							delete programm_states.top();
						}
						programm_states.pop();
					}
					current_state = new Game();
					programm_states.push(current_state);
					break;
				}
				if (items[i]->type == QUIT) {
					programm_states.pop();
					current_state = new Exit_state();
					programm_states.push(current_state);
					break;
				}
			}
		}
	}
}

void Winning_menu::escape() {
	game_time.toggle();
	programm_states.pop();
}



void Winning_menu::handle_events() {
	//While there's events to handle
	while (SDL_PollEvent(&event)) {
		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			//Quit the program
			programm_states.pop();
			current_state = new Exit_state();
			programm_states.push(current_state);
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: {
				escape();
				break;
			}
			case SDLK_RETURN: {
				enter();
				break;
			}
			case SDLK_UP: {
				up();
				break;
			}
			case SDLK_DOWN: {
				down();
				break;
			}
			}
		}
		else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
			switch (event.cbutton.button) {
			case 6: {
				escape();
				break;
			}
			case 0: {
				enter();
				break;
			}
			case 11: {
				up();
				break;
			}
			case 12: {
				down();
				break;
			}
			}
		}
	}
}

void Winning_menu::logic() {
}

void Winning_menu::render() {
	int render_y;
	render_y = 50;
	congratulations->render(SCREEN_WIDTH / 2 - congratulations->width / 2, 50);
	render_y += congratulations->height;
	winner->render(SCREEN_WIDTH / 2 - winner->width / 2, render_y);

	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			items[i]->render();
		}
	}

}
