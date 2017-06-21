#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "init.h"
#include "tools.h"
#include "media.h"
#include "Timer.h"

int main(int argc, char* args[]) {

	SDL_Surface* screen_surface = NULL;

	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
		system("pause");
	}
	else {
		//While application is running
		while (programm_states.top()->state != STATE_EXIT) {
			fps.start();

			//Do state event handling
			programm_states.top()->handle_events();


			//Do state logic
			programm_states.top()->logic();

			//Do state rendering
			programm_states.top()->render();

			//Update screen
			//screen_surface = SDL_GetWindowSurface(main_window);

			SDL_RenderPresent(main_renderer);

			if ( fps.get_ticks() < SCREEN_TICKS_PER_FRAME)
			{
				//Wait remaining time
				SDL_Delay(SCREEN_TICKS_PER_FRAME - fps.get_ticks());
			}
		}
	}

	//Free resources and close SDL
	close();

	//system("pause");
	return 0;
}