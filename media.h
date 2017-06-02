#pragma once
#include "init.h"

//Current displayed texture
extern SDL_Texture* background_texture;
extern SDL_Texture* menu_background_texture;

//Globally used textures
extern SDL_Texture* map;
extern SDL_Texture* platform;

//Menu textures
extern SDL_Texture* menu_play_t;
extern SDL_Texture* menu_or_t;
extern SDL_Texture* menu_leave_t;
extern SDL_Texture* pmenu_paused_t;
extern SDL_Texture* pmenu_continue_t;
extern SDL_Texture* pmenu_restart_t;
extern SDL_Texture* pmenu_exit_t;


//Players textures
extern SDL_Texture* player_texture;
extern SDL_Texture* player_stand_texture;
extern SDL_Texture* player_run_texture;
extern SDL_Texture* player_jump_rise_texture;
extern SDL_Texture* player_jump_fall_texture;
extern SDL_Texture* player_jump_effect_texture1;
extern SDL_Texture* player_jump_effect_texture2;
extern SDL_Texture* player_hit_texture;
extern SDL_Texture* player_cast_fireball_texture1;
extern SDL_Texture* player_cast_fireball_texture2;
extern SDL_Texture* player_dive_texture;

extern SDL_Texture* player2_texture;
extern SDL_Texture* player2_stand_texture;
extern SDL_Texture* player2_run_texture;
extern SDL_Texture* player2_jump_rise_texture;
extern SDL_Texture* player2_jump_fall_texture;
extern SDL_Texture* player2_hit_texture;
extern SDL_Texture* player2_dive_texture;

extern SDL_Texture* arrow_texture;

extern SDL_Texture* fireball_texture;
extern SDL_Texture* fireball_trail_texture;
extern SDL_Texture* t_ball_opening_texture;
extern SDL_Texture* t_ball_opened_texture;
extern SDL_Texture* blast_texture;

extern SDL_Texture* enemy_stand_texture;
extern SDL_Texture* enemy_run_texture;
extern SDL_Texture* enemy_hit_texture;

extern SDL_Texture* digits_texture;
extern SDL_Texture* player1_score_texture;
extern SDL_Texture* player2_score_texture;


//Map surface
extern SDL_Surface* map_surface;

//Globally used fonts
extern TTF_Font* font1;

//Globaly used audio samples
//extern Mix_Chunk *sound;


bool load_media();

void free_loaded_media();

