#pragma once
#include "init.h"


//Current displayed texture
extern SDL_Texture* background_texture;

//Globally used textures
extern SDL_Texture* map;


//Map surface
//extern SDL_Surface* map_surface;

//Globally used fonts
//extern TTF_Font* font1;

//Globaly used audio samples
//extern Mix_Chunk *sound;


bool load_media();

void free_loaded_media();

