#include "Timer.h"



Timer::Timer() {
	//Initialize the variables
	start_ticks = 0;
	paused_ticks = 0;

	paused = false;
	started = false;
}

void Timer::start() {
	//Start the timer
	started = true;

	//Unpause the timer
	paused = false;

	//Get the current clock time
	start_ticks = SDL_GetTicks();
	paused_ticks = 0;
}

void Timer::stop() {
	//Stop the timer
	started = false;

	//Unpause the timer
	paused = false;

	//Clear tick variables
	start_ticks = 0;
	paused_ticks = 0;
}

void Timer::toggle() {
	//If the timer is running and isn't already paused
	if (started && !paused)	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		paused_ticks = SDL_GetTicks() - start_ticks;
		start_ticks = 0;
	}
	//If the timer is running and paused
	else {
		//Unpause the timer
		paused = false;

		//Reset the starting ticks
		start_ticks = SDL_GetTicks() - paused_ticks;

		//Reset the paused ticks
		paused_ticks = 0;
	}
}

Uint32 Timer::get_ticks() {
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (started)
	{
		//If the timer is paused
		if (paused)
		{
			//Return the number of ticks when the timer was paused
			time = paused_ticks;
		} else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - start_ticks;
		}
	}

	return time;
}

bool Timer::is_started() {
	//get the state of timer
	return started;
}