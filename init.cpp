#pragma once
#include "init.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Menu.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include "wtypes.h"

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

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
bool fullscreen;
int WINDOW_START_X;
int WINDOW_START_Y;

//check if string is number
bool is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool init() {
	//Initialization flag
	bool success = true;

	// Get the size of screen
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	
	GetWindowRect(hDesktop, &desktop);
		// The top left corner will have coordinates (0,0)
		// and the bottom right corner will have coordinates:
	int NATIVE_WIDTH = desktop.right;
	int NATIVE_HEIGHT = desktop.bottom;

	//Read settings from .ini file
	std::string line;
	std::ifstream file("config.ini");

	bool config_succ = true;
	if (file.is_open())
	{
		int k = 0;
		while (getline(file, line)) {
			if (k == 1) { 
				if (is_number(line)) {
					SCREEN_WIDTH = std::stoi(line);
					std::cout << "Screen width = " << SCREEN_WIDTH << '\n';
				}
				else config_succ = false;
			}			
			if (k == 2) { 
				if (is_number(line)) {
					SCREEN_HEIGHT = std::stoi(line);
					std::cout << "Screen height = " << SCREEN_HEIGHT << '\n';
				}
				else config_succ = false;
			}
			
			if (k == 4) { 
				if (is_number(line)) {
					fullscreen = std::stoi(line);
					std::cout << "Full screen? -> " << fullscreen << '\n';
				}
				else config_succ = false;
			}			
			k++;
		}
	file.close();
	}
	else config_succ = false;
	if (!config_succ) {
		//Set defaults
		SCREEN_WIDTH = NATIVE_WIDTH;
		SCREEN_HEIGHT = NATIVE_HEIGHT;
		fullscreen = false;
		std::cout << "Error reading config.ini file! Using defaults instead: " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << ", windowed\n";
	}

	//Set window deafault position
	WINDOW_START_X = (NATIVE_WIDTH - SCREEN_WIDTH) / 2;
	WINDOW_START_Y = (NATIVE_HEIGHT - SCREEN_HEIGHT) / 2;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
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
				Mix_AllocateChannels(8);
			}
		}
	}
	if (!load_media()) {
		printf("Failed to load media!\n");
		success = false;
	}

	digits = new Animated_texture(digits_texture, 11);
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
