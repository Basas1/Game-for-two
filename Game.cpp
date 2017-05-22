#include "Game.h"
#include "media.h"
#include "init.h"



Game::Game() {
	//Load the background
	background = map;
	//Create player object
	player1 = new Player;
	player2 = new Player2;
	enemy = new Enemy;

	objects.reserve(10);
	static_objects.reserve(10);
	objects.insert(objects.end(), player1);
	objects.insert(objects.end(), player2);
	objects.insert(objects.end(), enemy);
}


Game::~Game() {
}

void Game::handle_events() {
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0) {

		if (event.type == SDL_QUIT) {
			//Quit the program
			set_next_state(STATE_EXIT);
		}

		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->is_exist()) {
				objects[i]->handle_events(event);
			}
		}

	}
	//player1->handle_events(event);


	////Handle events
	//SDL_PollEvent(&event);


	////Sint16 x;
	////x = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
	////printf("tr=%d; ", x);
	////x = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTX);
	////printf("lx=%d; ", x);
	////x = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_LEFTY);
	////printf("ly=%d; ", x);
	////x = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_RIGHTX);
	////printf("rx=%d; ", x);
	////x = SDL_GameControllerGetAxis(game_controller, SDL_CONTROLLER_AXIS_RIGHTY);
	////printf("ry=%d;\n", x);

	//if (event.type == SDL_CONTROLLERBUTTONDOWN) {
	//	printf("key=%d;\n", event.cbutton.button);
	//}


	////If the user has Xed out the window
	//if (event.type == SDL_QUIT) {
	//	//Quit the program
	//	set_next_state(STATE_EXIT);
	//}
	////If the user pressed enter
	//else if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_RETURN)) {
	//	//Move to the title screen
	//	set_next_state(STATE_MENU);
	//}

	//for (int i = 0; i < objects.size(); i++) {
	//	if (objects[i]->is_exist()) {
	//		objects[i]->handle_events(event);
	//	}
	//} 

}

void Game::logic() {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->is_exist()) {
			objects[i]->logic();
		}
	}

	//Delete not existing objects from vector
	for (int i = objects.size() - 1; i > 0; i--) {
		if (!objects[i]->is_exist()) {
			objects.erase(objects.begin() + i);
		}
	}

	//camera->follow(player1->get_x(), player1->get_y());
	camera->follow(player2->get_x(), player2->get_y());
}

void Game::render() {
	//Clear screen
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(main_renderer);


	//Render background
	SDL_RenderCopyEx(main_renderer, background, camera->get_rect(), NULL, 0.0, NULL, SDL_FLIP_NONE);

	//Render static objects
	for (int i = 0; i < static_objects.size(); i++) {
		if (static_objects[i]->is_exist()) {
			static_objects[i]->render();
		}
	}

	//Render Player and other objects
	for (int i = objects.size()-1; i >= 0; i--) {
		if (objects[i]->is_exist()) {
			objects[i]->render();
		}
	}

	//printf("object count: %d;\n", objects.size());

}
