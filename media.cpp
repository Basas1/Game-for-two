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
SDL_Texture* platform_diamond_texture = NULL;


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
SDL_Texture* player_dive_end_texture = NULL;
SDL_Texture* player_dive_smoke_texture = NULL;
SDL_Texture* player_fireball_texture = NULL;
SDL_Texture* player_fireball_trail_texture = NULL;
SDL_Texture* player_t_ball_trail_texture = NULL;
SDL_Texture* player_t_ball_blast_texture = NULL;
SDL_Texture* player_blast_smoke_texture = NULL;
SDL_Texture* t_ball_opening_texture = NULL;
SDL_Texture* t_ball_opened_texture = NULL;
SDL_Texture* tp_trail_texture = NULL;


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
SDL_Texture* player2_dive_end_texture = NULL;
SDL_Texture* player2_dive_smoke_texture = NULL;
SDL_Texture* player2_fireball_texture = NULL;
SDL_Texture* player2_fireball_trail_texture = NULL;
SDL_Texture* player2_t_ball_trail_texture = NULL;
SDL_Texture* player2_t_ball_blast_texture = NULL;
SDL_Texture* player2_blast_smoke_texture = NULL;
SDL_Texture* t_ball_opening_texture2 = NULL;
SDL_Texture* t_ball_opened_texture2 = NULL;
SDL_Texture* tp_trail2_texture = NULL;


SDL_Texture* arrow_texture = NULL;
SDL_Texture* help_texture = NULL;
SDL_Texture* death_texture = NULL;
SDL_Texture* blast_texture = NULL;

SDL_Texture* digits_texture = NULL;
SDL_Texture* player1_score_texture = NULL;
SDL_Texture* player2_score_texture = NULL;

SDL_Texture* map_texture = NULL;

//Map surface 
SDL_Surface* map_surface = NULL;

//Globally used audio
Mix_Chunk* charge_sound = NULL;
Mix_Chunk* death_sound = NULL;
Mix_Chunk* dive_attack_sound = NULL;
Mix_Chunk* dive_attack_finish_sound = NULL;
Mix_Chunk* fireball_cast_sound = NULL;
Mix_Chunk* fireball_destruction_sound = NULL;
Mix_Chunk* jump_sound = NULL;
Mix_Chunk* teleport_blast_sound = NULL;
Mix_Chunk* teleportation_sound = NULL;
Mix_Chunk* winning_sound = NULL;
Mix_Chunk* pause_music = NULL;
Mix_Chunk* game_music = NULL;




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
	map_texture = load_texture("Images/map/map_box_transparent.png");
	if (map_texture == NULL) {
		printf("Failed to load map texture!\n");
		success = false;
	}
	platform_texture = load_texture("Images/map/platform.gif");
	if (platform_texture == NULL) {
		printf("Failed to load platform texture!\n");
		success = false;
	}
	platform_diamond_texture = load_texture("Images/map/diamond.gif");
	if (platform_diamond_texture == NULL) {
		printf("Failed to load platform_diamond texture!\n");
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
	player_dive_texture = load_texture("Images/players/dive.gif");
	if (player_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_dive_end_texture = load_texture("Images/players/dive_end.gif");
	if (player_dive_end_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_dive_smoke_texture = load_texture("Images/players/dive_end_smoke.gif");
	if (player_dive_smoke_texture == NULL) {
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
		printf("Failed to load tp_ball trail texture!\n");
		success = false;
	}
	player_t_ball_blast_texture = load_texture("Images/players/tp_ball_blast.gif");
	if (player_t_ball_blast_texture == NULL) {
		printf("Failed to load tp_bal blast texture!\n");
		success = false;
	}
	player_blast_smoke_texture = load_texture("Images/players/blast_smoke.gif");
	if (player_blast_smoke_texture == NULL) {
		printf("Failed to load blast smoke texture!\n");
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
	player2_dive_texture = load_texture("Images/players/dive2.gif");
	if (player2_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_dive_end_texture = load_texture("Images/players/dive_end2.gif");
	if (player2_dive_end_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_dive_smoke_texture = load_texture("Images/players/dive_end_smoke2.gif");
	if (player2_dive_smoke_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_fireball_texture = load_texture("Images/players/fireball2.png");
	if (player_fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player2_fireball_trail_texture = load_texture("Images/players/fireball_trail2.png");
	if (player_fireball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	player2_t_ball_trail_texture = load_texture("Images/players/tp_ball_trail2.gif");
	if (player2_t_ball_trail_texture == NULL) {
		printf("Failed to load tp_ball trail texture!\n");
		success = false;
	}
	player2_t_ball_blast_texture = load_texture("Images/players/tp_ball_blast2.gif");
	if (player2_t_ball_blast_texture == NULL) {
		printf("Failed to load tp_bal blast texture!\n");
		success = false;
	}
	player2_blast_smoke_texture = load_texture("Images/players/blast_smoke2.gif");
	if (player2_blast_smoke_texture == NULL) {
		printf("Failed to load blast smoke texture!\n");
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
	help_texture = load_texture("Images/Texts_and_menus/help.gif");
	if (help_texture == NULL) {
		printf("Failed to load help texture!\n");
		success = false;
	}
	death_texture = load_texture("Images/players/ded.gif");
	if (death_texture == NULL) {
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

	//Load map surface
	map_surface = IMG_Load("Images/map/map_box.bmp");
	
	//Load music samples
	charge_sound = Mix_LoadWAV("Audio/charge.wav");
	if (charge_sound == NULL) {
		printf("Failed to load charge sound sample!\n");
		success = false;
	}
	death_sound = Mix_LoadWAV("Audio/death.wav");
	if (death_sound == NULL) {
		printf("Failed to load death sound sample!\n");
		success = false;
	}
	dive_attack_sound = Mix_LoadWAV("Audio/dive_attack.wav");
	if (dive_attack_sound == NULL) {
		printf("Failed to load dive attack sound sample!\n");
		success = false;
	}
	dive_attack_finish_sound = Mix_LoadWAV("Audio/dive_attack_finish.wav");
	if (dive_attack_finish_sound == NULL) {
		printf("Failed to load dive attack sound sample!\n");
		success = false;
	}
	fireball_cast_sound = Mix_LoadWAV("Audio/fireball_cast.wav");
	if (fireball_cast_sound == NULL) {
		printf("Failed to load fireball cast sound sample!\n");
		success = false;
	}
	fireball_destruction_sound = Mix_LoadWAV("Audio/fireball_destruction.wav");
	if (fireball_destruction_sound == NULL) {
		printf("Failed to load fireball destruction sound sample!\n");
		success = false;
	}
	jump_sound = Mix_LoadWAV("Audio/jump.wav");
	if (jump_sound == NULL) {
		printf("Failed to load jump sound sample!\n");
		success = false;
	}
	teleport_blast_sound = Mix_LoadWAV("Audio/teleport_blast.wav");
	if (teleport_blast_sound == NULL) {
		printf("Failed to load teleport blast sound sample!\n");
		success = false;
	}
	teleportation_sound = Mix_LoadWAV("Audio/teleportation.wav");
	if (teleportation_sound == NULL) {
		printf("Failed to load teleportation sound sample!\n");
		success = false;
	}
	winning_sound = Mix_LoadWAV("Audio/win.wav");
	if (winning_sound == NULL) {
		printf("Failed to load win sound sample!\n");
		success = false;
	}
	//Load music
	game_music = Mix_LoadWAV("Audio/game_music.wav");
	if (game_music == NULL) {
		printf("Failed to load game_loop music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	pause_music = Mix_LoadWAV("Audio/pause_music.wav");
	if (pause_music == NULL) {
		printf("Failed to load pause_loop music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void free_loaded_media() {
	//Free loaded images
	SDL_DestroyTexture(background_texture);
	background_texture = NULL;

	//Free the music samples
	//Mix_FreeChunk(sound);
	//sound = NULL;
}