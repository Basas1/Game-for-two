#pragma once
#include "init.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Menu.h"
#include "Game.h"

Player* player1 = NULL;
Player2* player2 = NULL;


SDL_GameController* gamepad1 = NULL;
SDL_GameController* gamepad2 = NULL;
SDL_Joystick* joystick1 = NULL;
SDL_Joystick* joystick2 = NULL;

Texture* score1 = NULL;
Texture* score2 = NULL;

//timer for fps capping
Timer fps;
Timer game_time;

std::vector<Game_object*> objects;
std::vector<Game_object*> static_objects;

std::stack<Programm_state*> programm_states;

int state_id = STATE_NULL;
int next_state = STATE_NULL;
Programm_state* current_state = NULL;
SDL_Event event;

Camera* camera = NULL;

Animated_texture* digits = NULL;

//The window we'll be rendering to
SDL_Window* main_window = NULL;

//The window renderer
SDL_Renderer* main_renderer = NULL;

bool init() {
	//Initialization flag
	bool success = true;
	//SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		//success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Load joystick
		gamepad1 = SDL_GameControllerOpen(0);
		gamepad2 = SDL_GameControllerOpen(1);
		joystick1 = SDL_GameControllerGetJoystick(gamepad1);
		joystick2 = SDL_GameControllerGetJoystick(gamepad2);

		//Create window
		main_window = SDL_CreateWindow("Game 42", WINDOW_START_X, WINDOW_START_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (fullscreen) {
			SDL_SetWindowFullscreen(main_window, SDL_WINDOW_FULLSCREEN);
		}
		if (main_window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create vsynced renderer for window
			main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
			if (main_renderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(main_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				Mix_AllocateChannels(3);
				//Initialize SDL_ttf
			}
		}
	}
	if (!load_media()) {
		printf("Failed to load media!\n");
		success = false;
	}

	digits = new Animated_texture(digits_texture, 10);
	digits->set_absolute_coord();
	score1 = new Texture(player1_score_texture);
	score1->set_absolute_coord();
	score2 = new Texture(player2_score_texture);
	score2->set_absolute_coord();

	camera = new Camera;

	//Set start programm state
	current_state = new Menu();
	programm_states.push(current_state);
	SDL_ShowCursor(SDL_DISABLE);

	return success;
}

void close() {
	//Free loaded mediafiles
	free_loaded_media();
	//Destroy window	
	SDL_DestroyRenderer(main_renderer);
	SDL_DestroyWindow(main_window);
	main_window = NULL;
	main_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
