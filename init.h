#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_mixer.h>
#include "Programm_state.h"
#include "tools.h"
#include "media.h"
#include "camera.h"


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Level dimension constants
const int LEVEL_WIDTH = 3200;
const int LEVEL_HEIGHT = 900;


//Fps constants
const int SCREEN_FPS = 200;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Window position
const int WINDOW_START_X = (1920 - SCREEN_WIDTH) / 2;
const int WINDOW_START_Y = (1080 - SCREEN_HEIGHT) / 2;

//Game states
enum GameStates {
	STATE_NULL,
	STATE_MENU,
	STATE_GAME,
	STATE_EXIT,
};

//State variables
extern int state_id;
extern int next_state;

//Game state object
extern Programm_state* current_state;

//Event handler
extern SDL_Event event;

//The window we'll be rendering to
extern SDL_Window* main_window;

//The window renderer
extern SDL_Renderer* main_renderer;

//Main camera
extern Camera* camera;

bool init();

void close();
