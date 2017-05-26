#pragma once
#include "Game.h"
#include "media.h"
#include "init.h"
#include "math.h"
#include "tools.h"


Game::Game() {
	//Load the background
	background = map;
	background2 = background_texture;

	//Create player object
	player1 = new Player(0,0,0);
	player2 = new Player2(0,0,1);

	platform = new Capture_platform(1445, 900, 1675, 300);

	objects.reserve(10);
	static_objects.reserve(10);
	objects.insert(objects.end(), player1);
	objects.insert(objects.end(), player2);
	objects.insert(objects.end(), platform);
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
	double p1_x, p2_x, p1_y, p2_y;
	p1_x = (double)player1->get_x();
	p2_x = (double)player2->get_x();
	p1_y = (double)player1->get_y();
	p2_y = (double)player2->get_y();
	double dist_x = fabs(p1_x - p2_x);
	double dist_y = fabs(p1_y - p2_y);
	double dist = sqrt(dist_x*dist_x + dist_y*dist_y);

	sc1 = 1 / (dist / (SCREEN_HEIGHT / 5 * 5 - SCREEN_HEIGHT / 3 * 1));
	if (sc1 <= 0.5) {
		sc1 = 0.5;
	}
	else if (sc1 >= 1) {
		sc1 = 1;
	}

	camera->set_scale(sc1);

	//printf("%f\n", camera->get_scale());
	camera->follow(follow_x, follow_y);

	//printf("P1 SCORE: %f;\tP2 SCORE: %f;\n", player1->score, player2->score);
	//printf("P1 ON PLAT = %d;\tP2 ON PLAT = %d;\n", player1->on_platform, player2->on_platform);
}

void Game::render() {
	//Clear screen
	SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 0xFF);
	SDL_RenderClear(main_renderer);
	
	//Render background
	SDL_RenderCopyEx(main_renderer, background2, NULL, NULL, 0.0, NULL, SDL_FLIP_NONE);

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
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->is_exist()) {
			objects[i]->render();
		}
	}



	//Render score
	int p1_score, p2_score;
	p1_score = (int)player1->score;
	p1_score /= 100;
	p2_score = (int)player2->score;
	p2_score /= 100;
	printf("P1 SCORE: %d;\tP2 SCORE: %d;\n", p1_score, p2_score);

	char buff[100];
	snprintf(buff, sizeof(buff), "PLAYER 1 SCORE: %d", p1_score);
	std::string score1 = buff;
	snprintf(buff, sizeof(buff), "PLAYER 2 SCORE: %d", p2_score);
	std::string score2 = buff;

	//render_text(25, 25, score1);
	//render_text(SCREEN_WIDTH - 315, 25, score2);

}
