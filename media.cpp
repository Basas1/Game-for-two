#pragma once
#include "media.h"
#include "tools.h"
#include <SDL_image.h>


//Background texture
SDL_Texture* background_texture = NULL;
SDL_Texture* menu_background_texture = NULL;

//Globally used textures
SDL_Texture* map = NULL;
SDL_Texture* platform = NULL;

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
SDL_Texture* player_stand_texture = NULL;
SDL_Texture* player_run_texture = NULL;
SDL_Texture* player_jump_rise_texture = NULL;
SDL_Texture* player_jump_fall_texture = NULL;
SDL_Texture* player_jump_effect_texture1 = NULL;
SDL_Texture* player_jump_effect_texture2 = NULL;
SDL_Texture* player_hit_texture = NULL;
SDL_Texture* player_cast_fireball_texture1 = NULL;
SDL_Texture* player_cast_fireball_texture2 = NULL;
SDL_Texture* player_dive_texture = NULL;
SDL_Texture* player_mark_texture = NULL;
SDL_Texture* player_fireball_texture = NULL;
SDL_Texture* player_fireball_trail_texture = NULL;

//Player2 textures
SDL_Texture* player2_texture = NULL;
SDL_Texture* player2_stand_texture = NULL;
SDL_Texture* player2_run_texture = NULL;
SDL_Texture* player2_jump_rise_texture = NULL;
SDL_Texture* player2_jump_fall_texture = NULL;
SDL_Texture* player2_cast_fireball_texture1 = NULL;
SDL_Texture* player2_cast_fireball_texture2 = NULL;
SDL_Texture* player2_hit_texture = NULL;
SDL_Texture* player2_dive_texture = NULL;
SDL_Texture* player2_mark_texture = NULL;
SDL_Texture* player2_fireball_texture = NULL;
SDL_Texture* player2_fireball_trail_texture = NULL;

SDL_Texture* arrow_texture = NULL;
SDL_Texture* help_texture = NULL;
SDL_Texture* t_ball_opening_texture = NULL;
SDL_Texture* t_ball_opened_texture = NULL;
SDL_Texture* tp_trail_texture = NULL;
SDL_Texture* tp_trail2_texture = NULL;
SDL_Texture* blast_texture = NULL;
//Enemy1 textures
SDL_Texture* enemy_stand_texture = NULL;
SDL_Texture* enemy_run_texture = NULL;
SDL_Texture* enemy_hit_texture = NULL;

SDL_Texture* digits_texture = NULL;
SDL_Texture* player1_score_texture = NULL;
SDL_Texture* player2_score_texture = NULL;

SDL_Texture* platform_texture = NULL;
SDL_Texture* map_texture = NULL;

//Map surface 
SDL_Surface* map_surface = NULL;

//Globally used font
TTF_Font* font1 = NULL;

//Globally used audio samples
//Mix_Chunk *sound = NULL;


bool load_media() {
	//Loading success flag
	bool success = true;

	//Load background texture
	//background_texture = load_texture("Images/kek.jpg");
	background_texture = load_texture("Images/sas.jpg");
	if (background_texture == NULL) {
		printf("Failed to load bg texture!\n");
		success = false;
	}
	menu_background_texture = load_texture("Images/space.jpg");
	if (menu_background_texture == NULL) {
		printf("Failed to load bg texture!\n");
		success = false;
	}

	//Loading other textures
	map_texture = load_texture("Images/map_box_transparent.gif");
	if (map_texture == NULL) {
		printf("Failed to load map texture!\n");
		success = false;
	}
	platform_texture = load_texture("Images/flag.gif");
	if (platform_texture == NULL) {
		printf("Failed to load map texture!\n");
		success = false;
	}
	platform = load_texture("Images/platform.bmp");
	if (platform == NULL) {
		printf("Failed to load platform texture!\n");
		success = false;
	}

	//PLAYER1 TEXTURES:
	player_texture = load_texture("Images/stand.gif");
	if (player_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_stand_texture = load_texture("Images/stand.gif");
	if (player_stand_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_run_texture = load_texture("Images/run.gif");
	if (player_run_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_rise_texture = load_texture("Images/airborne_rise.gif");
	if (player_jump_rise_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_fall_texture = load_texture("Images/airborne_fall.gif");
	if (player_jump_fall_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_effect_texture1 = load_texture("Images/jump_effect1.gif");
	if (player_jump_effect_texture1 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_effect_texture2 = load_texture("Images/jump_effect2.gif");
	if (player_jump_effect_texture2 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_cast_fireball_texture1 = load_texture("Images/shot_run.gif");
	if (player_cast_fireball_texture1 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_cast_fireball_texture2 = load_texture("Images/shot_horizontal.gif");
	if (player_cast_fireball_texture2 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_hit_texture = load_texture("Images/stab.gif");
	if (player_hit_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_dive_texture = load_texture("Images/diveattack.gif");
	if (player_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_mark_texture = load_texture("Images/player1_mark.png");
	if (player_mark_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_fireball_texture = load_texture("Images/fireball.gif");
	if (player_fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player_fireball_trail_texture = load_texture("Images/fireball_trail.gif");
	if (player_fireball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}

	//PLAYER2 TEXTURES
	player2_texture = load_texture("Images/stand2.gif");
	if (player2_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_stand_texture = load_texture("Images/stand2.gif");
	if (player2_stand_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_run_texture = load_texture("Images/run2.gif");
	if (player2_run_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_jump_rise_texture = load_texture("Images/airborne_rise2.gif");
	if (player2_jump_rise_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_jump_fall_texture = load_texture("Images/airborne_fall2.gif");
	if (player2_jump_fall_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_cast_fireball_texture1 = load_texture("Images/shot_run2.gif");
	if (player2_cast_fireball_texture1 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_cast_fireball_texture2 = load_texture("Images/shot_horizontal2.gif");
	if (player2_cast_fireball_texture2 == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_hit_texture = load_texture("Images/stab2.gif");
	if (player2_hit_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_dive_texture = load_texture("Images/diveattack.gif");
	if (player2_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_mark_texture = load_texture("Images/player2_mark.png");
	if (player2_mark_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_fireball_texture = load_texture("Images/fireball2.gif");
	if (player_fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player2_fireball_trail_texture = load_texture("Images/fireball_trail2.gif");
	if (player_fireball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}



	//Menu textures
	//Start menu
	menu_play_t = load_texture("Images/play.png");
	if (menu_play_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	menu_or_t = load_texture("Images/or.png");
	if (menu_or_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	menu_leave_t = load_texture("Images/leave.png");
	if (menu_leave_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	//Pause menu
	pmenu_paused_t = load_texture("Images/gamepaused.png");
	if (pmenu_paused_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	pmenu_continue_t = load_texture("Images/continue.png");
	if (pmenu_continue_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	pmenu_restart_t = load_texture("Images/restart.png");
	if (pmenu_restart_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	pmenu_exit_t = load_texture("Images/exit.png");
	if (pmenu_exit_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	//Win menu
	emenu_congratulations_t = load_texture("Images/congratulations.png");
	if (emenu_congratulations_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_p1w_t = load_texture("Images/player1won.png");
	if (emenu_p1w_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_p2w_t = load_texture("Images/player2won.png");
	if (emenu_p2w_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_play_again_t = load_texture("Images/play_again.png");
	if (emenu_play_again_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}
	emenu_quit_t = load_texture("Images/quit.png");
	if (emenu_quit_t == NULL) {
		printf("Failed to load menu texture!\n");
		success = false;
	}

	//Score textures
	player1_score_texture = load_texture("Images/player1score.png");
	player2_score_texture = load_texture("Images/player2score.png");
	digits_texture = load_texture("Images/digits.png");

	help_texture = load_texture("Images/help.gif");
	if (help_texture == NULL) {
		printf("Failed to load help texture!\n");
		success = false;
	}
	arrow_texture = load_texture("Images/arrow.gif");
	if (arrow_texture == NULL) {
		printf("Failed to load arrow texture!\n");
		success = false;
	}
	blast_texture = load_texture("Images/blast.png");
	if (blast_texture == NULL) {
		printf("Failed to load blast texture!\n");
		success = false;
	}
	t_ball_opening_texture = load_texture("Images/tp_opening.gif");
	if (t_ball_opening_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	t_ball_opened_texture = load_texture("Images/tp_spinning.gif");
	if (t_ball_opened_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	tp_trail_texture = load_texture("Images/tp_trail.png");
	if (tp_trail_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}
	tp_trail2_texture = load_texture("Images/tp_trail2.png");
	if (tp_trail2_texture == NULL) {
		printf("Failed to load teleport texture!\n");
		success = false;
	}




	//Open fonts
	font1 = TTF_OpenFont("Images/arial.ttf", 28);
	if (font1 == NULL ) {
		printf("Failed to load fonts!\n");
		success = false;
	}
	
	//Load music samples
	//sound = Mix_LoadWAV("Audio/sound.wav");
	//if (sound == NULL) {
	//	printf("Failed to load music samples!\n");
	//	success = false;
	//}
	
	//Load map surface
	map_surface = IMG_Load("Images/map_box.bmp");
	
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