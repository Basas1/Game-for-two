#include "Programm_state.h"
#include "init.h"
#include "Menu.h"
#include "Game.h"


void set_next_state(int new_state)
{
	//If the user doesn't want to exit
	if (next_state != STATE_EXIT)
	{
		//Set the next state
		next_state = new_state;
	}
}

void change_state()
{
	//If the state needs to be changed
	if (next_state != STATE_NULL)
	{
		//Delete the current state
		//if (next_state != STATE_EXIT && next_state != STATE_GAME)
		if (next_state != STATE_EXIT)
		{
			delete current_state;
		}

		//Change the state
		switch (next_state)
		{
		case STATE_MENU:
			current_state = new Menu();
			break;

		case STATE_GAME:
			current_state = new Game();
			break;
		}

		//Change the current state ID
		state_id = next_state;

		//NULL the next state ID
		next_state = STATE_NULL;
	}
}