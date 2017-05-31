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
		textures[i] = NULL;
	}
	int c=0;
	play = new Texture(menu_play_t);
	textures[c++] = play;
	or = new Texture(menu_or_t);
	textures[c++] = or;
	leave = new Texture(menu_leave_t);
	textures[c++] = leave;

}


Menu::~Menu() {
}

void Menu::handle_events() {
	//While there's events to handle
	while (SDL_PollEvent(&event))
	{
		//If the user has Xed out the window
		if (event.type == SDL_QUIT)
		{
			//Quit the program
			programm_states.pop();
		}
		//If the user pressed enter
		else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN))
		{
			programm_states.pop();
			current_state = new Game();
			programm_states.push(current_state);
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

	int menu_height=0;
	for (int i = 0; i < 10; i++) {
		if (textures[i] != NULL) {
			menu_height += textures[i]->height;
		}
	}

	int c_x = SCREEN_WIDTH / 2;
	int start_y = (int)((SCREEN_HEIGHT - menu_height) / 2);

	for (int i = 0; i < 10; i++) {
		if (textures[i] != NULL) {
			textures[i]->render(c_x - textures[i]->width / 2, start_y);
			start_y += textures[i]->height;
		}
	}

}
