#pragma once
#include <SDL.h>
#include <string>
#include <SDL_mixer.h>
#include "Programm_state.h"
#include "tools.h"
#include "media.h"
#include "camera.h"
#include <vector>
#include <stack>
#include "Game_object.h"
#include "Static_object.h"
#include "Player.h"
#include "Player2.h"
#include "Timer.h"
#include "Animated_texture.h"

//Players
extern Player* player1;
extern Player2* player2;

//Game Controller 1 handler
extern SDL_GameController* gamepad1;
extern SDL_GameController* gamepad2;
extern SDL_Joystick* joystick1;
extern SDL_Joystick* joystick2;

//Vector of all objects in game
extern std::vector<Game_object*> objects;
extern std::vector<Game_object*> static_objects;

extern std::stack<Programm_state*> programm_states;

//timer for fps capping
extern Timer fps;
extern Timer game_time;

//Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern bool fullscreen;

//Fps constants
const int SCREEN_FPS = 60;
//const int SCREEN_FPS = 10;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Window position
extern int WINDOW_START_X;
extern int WINDOW_START_Y;

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 16000;

//Game states
enum game_states {
	STATE_NULL,
	STATE_MENU,
	STATE_GAME,
	STATE_EXIT,
};

enum sides {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UP_RIGHT,
	UP_LEFT,
	DOWN_RIGHT,
	DOWN_LEFT,
};


//Types of objects
enum object_types {
	PLAYER,
	ENEMY,
	FIREBALL,
	TELEPORT,
	OTHER,
	PLATFORM,
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

extern Animated_texture* digits;
extern Texture* score1;
extern Texture* score2;

bool init();

void close();
