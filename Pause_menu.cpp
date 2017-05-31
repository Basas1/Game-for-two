#pragma once
#include "Pause_menu.h"
#include "media.h"
#include "init.h"
#include "Game.h"



Pause_menu::Pause_menu() {
	state = STATE_PAUSE;

	for (int i = 0; i < 10; i++) {
		items[i] = NULL;
	}

	game_is_paused = new Texture(pmenu_paused_t);
	game_is_paused->set_absolute_coord();


	int c = 0;
	Menu_item* continue_game;
	Menu_item* restart;
	Menu_item* exit;
	continue_game = new Menu_item(CONTINUE, 0, 0, pmenu_continue_t);
	continue_game->toggle();
	items[c++] = continue_game;
	restart = new Menu_item(RESTART, 0, 0, pmenu_restart_t);
	items[c++] = restart;
	exit = new Menu_item(EXIT, 0, 0, pmenu_exit_t);
	items[c++] = exit;

	int menu_height = 50;
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

int Pause_menu::check_if_choosed() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			if (items[i]->choosen) return i;
		}
	}
	return -1;
}

Pause_menu::~Pause_menu() {
}

void Pause_menu::handle_events() {
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
				game_time.toggle();
				programm_states.pop();
				break;
			}
			case SDLK_RETURN: {
				for (int i = 0; i < 10; i++) {
					if (items[i] != NULL) {
						if (items[i]->choosen) {
							if (items[i]->type == CONTINUE) {
								game_time.toggle();
								programm_states.pop();
								break;
							}
							if (items[i]->type == RESTART) {							
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
							if (items[i]->type == EXIT) {
								programm_states.pop();
								current_state = new Exit_state();
								programm_states.push(current_state);
								break;
							}
						}
					}
				}
			}
			case SDLK_UP: {
				int current;
				current = check_if_choosed();
				if (current == -1) {
					for (int i = 0; i < 10; i++) {
						if (items[i] != NULL) {
							if (items[i]->type == CONTINUE) items[i]->toggle();
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

				break;
			}
			case SDLK_DOWN: {
				int current;
				current = check_if_choosed();
				if (current == -1) {
					for (int i = 0; i < 10; i++) {
						if (items[i] != NULL) {
							if (items[i]->type == CONTINUE) items[i]->toggle();
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
				break;
			}
			}
		}
	}
}

void Pause_menu::logic() {
}

void Pause_menu::render() {

	game_is_paused->render(SCREEN_WIDTH / 2 - game_is_paused->width / 2, 50);

	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			items[i]->render();
		}
	}

}
