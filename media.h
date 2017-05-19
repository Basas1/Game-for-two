#pragma once
#include "init.h"


//Current displayed texture
extern SDL_Texture* background_texture;

//Globally used textures
extern SDL_Texture* map;
extern SDL_Texture* player_texture;
extern SDL_Texture* player_stand_texture;
extern SDL_Texture* player_run_texture;
extern SDL_Texture* player_jump_texture;
extern SDL_Texture* player_hit_texture;
extern SDL_Texture* fireball_texture;

extern SDL_Texture* enemy_stand_texture;
extern SDL_Texture* enemy_run_texture;
extern SDL_Texture* enemy_hit12_texture;



//Map surface
extern SDL_Surface* map_surface;

//Globally used fonts
//extern TTF_Font* font1;

//Globaly used audio samples
//extern Mix_Chunk *sound;


bool load_media();

void free_loaded_media();

