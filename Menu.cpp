#include "Menu.h"
#include "media.h"
#include "init.h"



Menu::Menu() {
	//Load the background
	background = background_texture;
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
			set_next_state(STATE_EXIT);
		}
		//If the user pressed enter
		else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN))
		{
			//Move to the game screen
			set_next_state(STATE_GAME);
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

	//Render rectangle
	SDL_Rect rQuad = { 100, 100, 100, 100 };
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(main_renderer, &rQuad);
}
