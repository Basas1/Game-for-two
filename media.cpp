#pragma once
#include "media.h"
#include "tools.h"
#include <SDL_image.h>


//Background texture
SDL_Texture* background_texture = NULL;

//Globally used textures
SDL_Texture* map = NULL;
SDL_Texture* platform = NULL;
//Player textures
SDL_Texture* player_texture = NULL;
SDL_Texture* player_stand_texture = NULL;
SDL_Texture* player_run_texture = NULL;
SDL_Texture* player_jump_rise_texture = NULL;
SDL_Texture* player_jump_fall_texture = NULL;
SDL_Texture* player_hit_texture = NULL;
SDL_Texture* player_dive_texture = NULL;
//Player2 textures
SDL_Texture* player2_texture = NULL;
SDL_Texture* player2_stand_texture = NULL;
SDL_Texture* player2_run_texture = NULL;
SDL_Texture* player2_jump_rise_texture = NULL;
SDL_Texture* player2_jump_fall_texture = NULL;
SDL_Texture* player2_hit_texture = NULL;
SDL_Texture* player2_dive_texture = NULL;


SDL_Texture* fireball_texture = NULL;
SDL_Texture* fireball_trail_texture = NULL;
SDL_Texture* blast_texture = NULL;
//Enemy1 textures
SDL_Texture* enemy_stand_texture = NULL;
SDL_Texture* enemy_run_texture = NULL;
SDL_Texture* enemy_hit_texture = NULL;

SDL_Texture* digits_texture = NULL;
SDL_Texture* player1_score_texture = NULL;
SDL_Texture* player2_score_texture = NULL;




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
	background_texture = load_texture("Images/kek.jpg");
	//background_texture = load_texture("Images/space.jpg");
	if (background_texture == NULL) {
		printf("Failed to load bg texture!\n");
		success = false;
	}
	//Loading other textures
	map = load_texture("Images/map_box_transparent.png");
	//map = load_texture("Images/map_box.bmp");
	if (map == NULL) {
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
	player_jump_fall_texture = load_texture("Images/airborne_rise.gif");
	if (player_jump_fall_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_hit_texture = load_texture("Images/stab.png");
	if (player_hit_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_dive_texture = load_texture("Images/diveattack.gif");
	if (player_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
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
	player2_jump_rise_texture = load_texture("Images/airborne_rise.gif");
	if (player2_jump_rise_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_jump_fall_texture = load_texture("Images/airborne_rise.gif");
	if (player2_jump_fall_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_hit_texture = load_texture("Images/stab2.png");
	if (player2_hit_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player2_dive_texture = load_texture("Images/diveattack.gif");
	if (player2_dive_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}



	//ENEMY1 TEXTURES
	//enemy_stand_texture = load_texture("Images/stand12f12.png");
	//if (enemy_stand_texture == NULL) {
	//	printf("Failed to load player texture!\n");
	//	success = false;
	//}
	enemy_run_texture = load_texture("Images/run.jpg");
	//if (enemy_run_texture == NULL) {
	//	printf("Failed to load player texture!\n");
	//	success = false;
	//}
	//enemy_hit_texture = load_texture("Images/attack123.png");
	//if (enemy_hit_texture == NULL) {
	//	printf("Failed to load player texture!\n");
	//	success = false;
	//}

	//Score textures
	player1_score_texture = load_texture("Images/player1score.png");
	player2_score_texture = load_texture("Images/player2score.png");
	digits_texture = load_texture("Images/digits.png");




	fireball_texture = load_texture("Images/fireball.gif");
	if (fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	fireball_trail_texture = load_texture("Images/fireball_trail.png");
	if (fireball_trail_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}
	blast_texture = load_texture("Images/blast.png");
	if (blast_texture == NULL) {
		printf("Failed to load blast texture!\n");
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