#pragma once
#include "media.h"
#include "tools.h"
#include <SDL_image.h>


//Background texture
SDL_Texture* background_texture = NULL;

//Globally used textures
SDL_Texture* map = NULL;


//Map surface
//SDL_Surface* map_surface = NULL;

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
		printf("Failed to load arrow texture!\n");
		success = false;
	}
	//Loading other textures
	map = load_texture("Images/map.jpg");
	
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
	//map_surface = IMG_Load("Images/map3.bmp");

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