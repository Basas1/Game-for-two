#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "init.h"
#include "tools.h"
#include "media.h"

int main(int argc, char* args[]) {

	SDL_Surface* screen_surface = NULL;

	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//While application is running
		while (state_id != STATE_EXIT) {

			//Do state event handling
			current_state->handle_events();

			//Do state logic
			current_state->logic();

			//Change state if needed
			change_state();

			//Do state rendering
			current_state->render();

			//Update screen
			screen_surface = SDL_GetWindowSurface(main_window);

			SDL_RenderPresent(main_renderer);
		}
	}

	//Free resources and close SDL
	close();

	//system("pause");
	return 0;
}