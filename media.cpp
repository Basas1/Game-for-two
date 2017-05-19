#pragma once
#include "media.h"
#include "tools.h"
#include <SDL_image.h>


//Background texture
SDL_Texture* background_texture = NULL;

//Globally used textures
SDL_Texture* map = NULL;
//Player textures
SDL_Texture* player_texture = NULL;
SDL_Texture* player_stand_texture = NULL;
SDL_Texture* player_run_texture = NULL;
SDL_Texture* player_jump_texture = NULL;
SDL_Texture* player_hit_texture = NULL;
SDL_Texture* fireball_texture = NULL;
//Enemy1 textures
SDL_Texture* enemy_stand_texture = NULL;
SDL_Texture* enemy_run_texture = NULL;
SDL_Texture* enemy_hit12_texture = NULL;



//Map surface
SDL_Surface* map_surface = NULL;

//Globally used font
//TTF_Font* font1 = NULL;

//Globally used audio samples
//Mix_Chunk *sound = NULL;


bool load_media() {
	//Loading success flag
	bool success = true;

	//Load background texture
	background_texture = load_texture("Images/background.jpg");
	if (background_texture == NULL) {
		printf("Failed to load bg texture!\n");
		success = false;
	}
	//Loading other textures
	map = load_texture("Images/map.jpg");
	//map = load_texture("Images/testmap.bmp");
	if (map == NULL) {
		printf("Failed to load map texture!\n");
		success = false;
	}
	//PLAYER TEXTURES:
	player_texture = load_texture("Images/stand.gif");
	if (player_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_stand_texture = load_texture("Images/stand.png");
	if (player_stand_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_run_texture = load_texture("Images/run.png");
	if (player_run_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_jump_texture = load_texture("Images/jump.png");
	if (player_jump_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	player_hit_texture = load_texture("Images/stab.gif");
	if (player_hit_texture == NULL) {
		printf("Failed to load player texture!\n");
		success = false;
	}
	//ENEMY1 TEXTURES
	//enemy_stand_texture = load_texture("Images/stand12f12.png");
	//if (enemy_stand_texture == NULL) {
	//	printf("Failed to load player texture!\n");
	//	success = false;
	//}
	//enemy_run_texture = load_texture("Images/runf.png");
	//if (enemy_run_texture == NULL) {
	//	printf("Failed to load player texture!\n");
	//	success = false;
	//}
	//enemy_hit12_texture = load_texture("Images/attack12f35.png");
	//if (enemy_hit12_texture == NULL) {
	//	printf("Failed to load player texture!\n");
	//	success = false;
	//}



	fireball_texture = load_texture("Images/fireball.gif");
	if (fireball_texture == NULL) {
		printf("Failed to load fireball texture!\n");
		success = false;
	}


	//Open fonts
	//font1 = TTF_OpenFont("Fonts/arial.ttf", 28);
	//if (font1 == NULL ) {
	//	printf("Failed to load fonts!\n");
	//	success = false;
	//}
	
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