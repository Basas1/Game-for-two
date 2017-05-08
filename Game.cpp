#include "Game.h"
#include "media.h"
#include "init.h"



Game::Game() {
	//Load the background
	background = map;
}


Game::~Game() {
}

void Game::handle_events() {
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
			//Move to the title screen
			set_next_state(STATE_MENU);
		}
	}
}

void Game::logic() {
}

void Game::render() {
	//Clear screen
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(main_renderer);

	//Render background
	SDL_RenderCopy(main_renderer, background, NULL, NULL);

	//Render rectangle
	SDL_Rect rQuad = { 200, 200, 200, 200 };
	SDL_SetRenderDrawColor(main_renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(main_renderer, &rQuad);
}
