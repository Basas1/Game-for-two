#include "Game.h"
#include "media.h"
#include "init.h"
#include "math.h"



Game::Game() {
	//Load the background
	background = map;
	//Create player object
	player1 = new Player();
	player2 = new Player2(0,0,1);
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
	//Handle events

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
	SDL_PollEvent(&event);
	player1->handle_events(event);

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

	int follow_x, follow_y;
	follow_x = (player1->get_x() + player2->get_x()) / 2;
	follow_y = (player1->get_y() + player2->get_y()) / 2;

	double sc1,sc2;
	int p1_x, p2_x, p1_y, p2_y;
	p1_x = (int)player1->get_x();
	p2_x = (int)player2->get_x();
	p1_y = (int)player1->get_y();
	p2_y = (int)player2->get_y();

	if (abs(p1_x - p2_x) <= SCREEN_WIDTH / 3 * 1) {
		sc1 = 1;
	} else if (abs(p1_x - p2_x) >= SCREEN_WIDTH / 5 * 4) {
		sc1 = 0.5;
	}
	else {
		sc1 = 0.75;
	}

	if (abs(p1_y - p2_y) <= SCREEN_HEIGHT / 3 * 2) {
		sc2 = 1;
	}
	else if (abs(p1_y - p2_y) >= SCREEN_HEIGHT / 5 * 4) {
		sc2 = 0.5;
	}
	else {
		sc2 = 0.75;
	}

	if (sc1 < sc2) {
		camera->set_scale(sc1);
	}
	else {
		camera->set_scale(sc2);
	}

	//printf("%f\n", camera->get_scale());
	camera->follow(follow_x, follow_y);
}

void Game::render() {
	//Clear screen
	SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(main_renderer);
	
	//Render background
	SDL_Rect back;
	back = *camera->get_rect();
	back.w /= camera->get_scale();
	back.h /= camera->get_scale();
	//SDL_RenderCopyEx(main_renderer, background, camera->get_rect(), NULL, 0.0, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(main_renderer, background, &back, NULL, 0.0, NULL, SDL_FLIP_NONE);

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
