#pragma once
#include "Menu.h"
#include "media.h"
#include "init.h"
#include "Game.h"



Menu::Menu() {
	state = STATE_MENU;
	//Load the background
	background = menu_background_texture;

	for (int i = 0; i < 10; i++) {
		items[i] = NULL;
	}
	int c=0;
	Menu_item* play;
	Menu_item* or;
	Menu_item* leave;
	play = new Menu_item(PLAY, 0, 0, menu_play_t);
	play->toggle();
	items[c++] = play;
	or = new Menu_item(OR, 0, 0, menu_or_t, false);
	items[c++] = or;
	leave = new Menu_item(LEAVE, 0, 0, menu_leave_t);
	items[c++] = leave;

	int menu_height = 0;
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

int Menu::check_if_choosed() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			if (items[i]->choosen) return i;
		}
	}
	return -1;
}

Menu::~Menu() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			delete items[i];
			items[i] = NULL;
		}
	}
}

void Menu::up() {
	int current;
	current = check_if_choosed();
	if (current == -1) {
		for (int i = 0; i < 10; i++) {
			if (items[i] != NULL) {
				if (items[i]->type == PLAY) items[i]->toggle();
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

void Menu::down() {
	int current;
	current = check_if_choosed();
	if (current == -1) {
		for (int i = 0; i < 10; i++) {
			if (items[i] != NULL) {
				if (items[i]->type == PLAY) items[i]->toggle();
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

void Menu::enter() {
	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			if (items[i]->choosen) {
				if (items[i]->type == PLAY) {
					delete programm_states.top();
					programm_states.pop();
					current_state = new Game();
					programm_states.push(current_state);
					break;
				}
				if (items[i]->type == LEAVE) {
					delete programm_states.top();
					programm_states.pop();
					current_state = new Exit_state();
					programm_states.push(current_state);
					break;
				}
			}
		}
	}
}

void Menu::handle_events() {
	//While there's events to handle
	while (SDL_PollEvent(&event))
	{
		//If the user has Xed out the window
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			delete programm_states.top();
			programm_states.pop();
			current_state = new Exit_state();
			programm_states.push(current_state);
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
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

void Menu::logic() {
}

void Menu::render() {
	//Clear screen
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(main_renderer);

	//Render background
	SDL_RenderCopy(main_renderer, background, NULL, NULL);

	for (int i = 0; i < 10; i++) {
		if (items[i] != NULL) {
			items[i]->render();
		}
	}

}
