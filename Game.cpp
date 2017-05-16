#include "Game.h"
#include "media.h"
#include "init.h"
#include "Player.h"




Game::Game() {
	//Load the background
	background = map;
	player = new Player;

	objects.reserve(10);
	objects.insert(objects.end(), player);
}


Game::~Game() {
}

void Game::handle_events() {
	//While there's events to handle
	while (SDL_PollEvent(&event)) {
		//If the user has Xed out the window
		if (event.type == SDL_QUIT) {
			//Quit the program
			set_next_state(STATE_EXIT);
		}
		//If the user pressed enter
		else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)) {
			//Move to the title screen
			set_next_state(STATE_MENU);
		}

		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->is_exist()) {
			objects[i]->handle_events(event);
			}
		}

	}
}

void Game::logic() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->is_exist()) {
			objects[i]->logic();
		}
	}


	camera->follow(player->get_x(), player->get_y());
}

void Game::render() {
	//Clear screen
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(main_renderer);

	//Render background
	SDL_RenderCopyEx(main_renderer, background, camera->get_rect(), NULL, 0.0, NULL, SDL_FLIP_NONE);

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->is_exist()) {
			objects[i]->render();
		}
	}

	printf("object count: %d;\n", objects.size());

}
