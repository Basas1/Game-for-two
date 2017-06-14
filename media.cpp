#pragma once
#include "media.h"
#include "tools.h"
#include <SDL_image.h>


//Background texture
SDL_Texture* background_texture = NULL;
SDL_Texture* menu_background_texture = NULL;

//Globally used textures
SDL_Texture* map = NULL;
SDL_Texture* platform_texture = NULL;

//Menu textures
SDL_Texture* menu_play_t = NULL;
SDL_Texture* menu_or_t = NULL;
SDL_Texture* menu_leave_t = NULL;
SDL_Texture* pmenu_paused_t = NULL;
SDL_Texture* pmenu_continue_t = NULL;
SDL_Texture* pmenu_restart_t = NULL;
SDL_Texture* pmenu_exit_t = NULL;
SDL_Texture* emenu_congratulations_t = NULL;
SDL_Texture* emenu_p1w_t = NULL;
SDL_Texture* emenu_p2w_t = NULL;
SDL_Texture* emenu_play_again_t = NULL;
SDL_Texture* emenu_quit_t = NULL;


//Player textures
SDL_Texture* player_texture = NULL;
SDL_Texture* player_idle_texture = NULL;
SDL_Texture* player_run_texture = NULL;
SDL_Texture* player_jump_rise_texture = NULL;
SDL_Texture* player_jump_fall_texture = NULL;
SDL_Texture* player_jump_effect_ground_texture = NULL;
SDL_Texture* player_jump_effect_air_texture = NULL;
SDL_Texture* player_charge_texture = NULL;
SDL_Texture* player_cast_fireball_texture1 = NULL;
SDL_Texture* player_cast_fireball_texture2 = NULL;
SDL_Texture* player_dive_texture = NULL;
SDL_Texture* player_fireball_texture = NULL;
SDL_Texture* player_fireball_trail_texture = NULL;
SDL_Texture* player_t_ball_trail_texture = NULL;

//Player2 textures
SDL_Texture* player2_texture = NULL;
SDL_Texture* player2_idle_texture = NULL;
SDL_Texture* player2_run_texture = NULL;
SDL_Texture* player2_jump_rise_texture = NULL;
SDL_Texture* player2_jump_fall_texture = NULL;
SDL_Texture* player2_cast_fireball_texture1 = NULL;
SDL_Texture* player2_cast_fireball_texture2 = NULL;
SDL_Texture* player2_hit_texture = NULL;
SDL_Texture* player2_dive_texture = NULL;
SDL_Texture* player2_fireball_texture = NULL;
SDL_Texture* player2_fireball_trail_texture = NULL;
SDL_Texture* player2_t_ball_trail_texture = NULL;


SDL_Texture* arrow_texture = NULL;
SDL_Texture* help_texture = NULL;
SDL_Texture* t_ball_opening_texture = NULL;
SDL_Texture* t_ball_opened_texture = NULL;
SDL_Texture* t_ball_opening_texture2 = NULL;
SDL_Texture* t_ball_opened_texture2 = NULL;
SDL_Texture* tp_trail_texture = NULL;
SDL_Texture* tp_trail2_texture = NULL;
SDL_Texture* blast_texture = NULL;

SDL_Texture* digits_texture = NULL;
SDL_Texture* player1_score_texture = NULL;
SDL_Texture* player2_score_texture = NULL;

SDL_Texture* map_texture = NULL;

//Map surface 
SDL_Surface* map_surface = NULL;

//Globally used audio samples
//Mix_Chunk *sound = NULL;


bool load_media() {
	//Loading success flag
	bool success = true;

	//Load background texture
	//background_texture = load_texture("Images/kek.jpg");
	background_texture = load_texture("Images/map/background.jpg");
	if (background_texture == NULL) {
		printf("Failed to load bg texture!\n");
		success = false;
	}
	menu_background_texture = load_texture("Images/Texts_and_menus/space.jpg");
	if (menu_background_texture == NULL) {
		printf("Failed to load bg texture!\n");
		success = false;
	}

	//Loading other textures
	map_texture = load_texture("Images/map/map_box_transparent.gif");
	if (map_texture == NULL) {
		printf("Failed to load map texture!\n");
		success = false;
	}
	platform_texture = load_texture("Images/map/platform.gif");
	if (platform_texture == NULL) {
		printf("Failed to load platform texture!\n");
		success = false;
	}

	//PLAYER1 TEXTURES:
	player_idle_texture = load_texture("Images/players/idle.gif");
	if (player_idle_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_run_texture = load_texture("Images/players/run.gif");
	if (player_run_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_rise_texture = load_texture("Images/players/airborne_rise.gif");
	if (player_jump_rise_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_fall_texture = load_texture("Images/players/airborne_fall.gif");
	if (player_jump_fall_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_cast_fireball_texture1 = load_texture("Images/players/shot_run.gif");
	if (player_cast_fireball_texture1 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_cast_fireball_texture2 = load_texture("Images/players/shot_horizontal.gif");
	if (player_cast_fireball_texture2 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_charge_texture = load_texture("Images/players/charge.gif");
	if (player_charge_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_dive_texture = load_texture("Images/players/diveattack.gif");
	if (player_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_fireball_texture = load_texture("Images/players/fireball.gif");
	if (player_fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player_fireball_trail_texture = load_texture("Images/players/fireball_trail.gif");
	if (player_fireball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player_t_ball_trail_texture = load_texture("Images/players/tp_ball_trail.gif");
	if (player_t_ball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	blast_texture = load_texture("Images/players/blast.png");
	if (blast_texture == NULL) {
		printf("Failed to load blast texture!\n");
		success = false;
	}
	t_ball_opening_texture = load_texture("Images/players/tp_opening.gif");
	if (t_ball_opening_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	t_ball_opened_texture = load_texture("Images/players/tp_spinning.gif");
	if (t_ball_opened_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}

	//PLAYER2 TEXTURES
	player2_idle_texture = load_texture("Images/players/idle2.gif");
	if (player2_idle_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_run_texture = load_texture("Images/players/run2.gif");
	if (player2_run_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_jump_rise_texture = load_texture("Images/players/airborne_rise2.gif");
	if (player2_jump_rise_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_jump_fall_texture = load_texture("Images/players/airborne_fall2.gif");
	if (player2_jump_fall_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_cast_fireball_texture1 = load_texture("Images/players/shot_run2.gif");
	if (player2_cast_fireball_texture1 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_cast_fireball_texture2 = load_texture("Images/players/shot_horizontal2.gif");
	if (player2_cast_fireball_texture2 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_hit_texture = load_texture("Images/players/charge2.gif");
	if (player2_hit_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_dive_texture = load_texture("Images/players/diveattack.gif");
	if (player2_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_fireball_texture = load_texture("Images/players/fireball2.gif");
	if (player_fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player2_fireball_trail_texture = load_texture("Images/players/fireball_trail2.gif");
	if (player_fireball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player2_t_ball_trail_texture = load_texture("Images/players/tp_ball_trail2.gif");
	if (player2_t_ball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	t_ball_opening_texture = load_texture("Images/players/tp_opening.gif");
	if (t_ball_opening_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	t_ball_opened_texture = load_texture("Images/players/tp_spinning.gif");
	if (t_ball_opened_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	t_ball_opening_texture2 = load_texture("Images/players/tp_opening2.gif");
	if (t_ball_opening_texture2 == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	t_ball_opened_texture2 = load_texture("Images/players/tp_spinning2.gif");
	if (t_ball_opened_texture2 == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}

	//Players' shared textures
	arrow_texture = load_texture("Images/players/arrow.gif");
	if (arrow_texture == NULL) {
		printf("Failed to load arrow texture!\n");
		success = false;
	}
	player_jump_effect_ground_texture = load_texture("Images/players/jump_effect_ground.gif");
	if (player_jump_effect_ground_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_effect_air_texture = load_texture("Images/players/jump_effect_air.gif");
	if (player_jump_effect_air_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	tp_trail_texture = load_texture("Images/players/tp_trail.png");
	if (tp_trail_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	tp_trail2_texture = load_texture("Images/players/tp_trail2.png");
	if (tp_trail2_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	blast_texture = load_texture("Images/players/blast.gif");
	if (blast_texture == NULL) {
		printf("Failed to load blast texture!\n");
		success = false;
	}


	//Menu textures
	//Start menu
	menu_play_t = load_texture("Images/Texts_and_menus/play.png");
	if (menu_play_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	menu_or_t = load_texture("Images/Texts_and_menus/or.png");
	if (menu_or_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	menu_leave_t = load_texture("Images/Texts_and_menus/leave.png");
	if (menu_leave_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	//Pause menu
	pmenu_paused_t = load_texture("Images/Texts_and_menus/gamepaused.png");
	if (pmenu_paused_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	pmenu_continue_t = load_texture("Images/Texts_and_menus/continue.png");
	if (pmenu_continue_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	pmenu_restart_t = load_texture("Images/Texts_and_menus/restart.png");
	if (pmenu_restart_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	pmenu_exit_t = load_texture("Images/Texts_and_menus/exit.png");
	if (pmenu_exit_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	//Win menu
	emenu_congratulations_t = load_texture("Images/Texts_and_menus/congratulations.png");
	if (emenu_congratulations_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_p1w_t = load_texture("Images/Texts_and_menus/player1won.png");
	if (emenu_p1w_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_p2w_t = load_texture("Images/Texts_and_menus/player2won.png");
	if (emenu_p2w_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_play_again_t = load_texture("Images/Texts_and_menus/play_again.png");
	if (emenu_play_again_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_quit_t = load_texture("Images/Texts_and_menus/quit.png");
	if (emenu_quit_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}

	//Score textures
	player1_score_texture = load_texture("Images/Texts_and_menus/player1score.png");
	player2_score_texture = load_texture("Images/Texts_and_menus/player2score.png");
	digits_texture = load_texture("Images/Texts_and_menus/digits.png");

	help_texture = load_texture("Images/Texts_and_menus/help.gif");
	if (help_texture == NULL) {
		printf("Failed to load help texture!\n");
		success = false;
	}


	//Load music samples
	//sound = Mix_LoadWAV("Audio/sound.wav");
	//if (sound == NULL) {
	//	printf("Failed to load music samples!\n");
	//	success = false;
	//}
	
	//Load map surface
	map_surface = IMG_Load("Images/map/map_box.bmp");
	
	return success;
}

void free_loaded_media() {
	//Free loaded images
	SDL_DestroyTexture(background_texture);
	background_texture = NULL;

	//Free the music samples
	//Mix_FreeChunk(sound);
	//sound = NULL;

	//Free fonts
	//TTF_CloseFont(font1);
	//font1 = NULL;
}