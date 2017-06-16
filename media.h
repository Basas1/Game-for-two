#pragma once
#include "init.h"

//Current displayed texture
extern SDL_Texture* background_texture;
extern SDL_Texture* menu_background_texture;

//Globally used textures
extern SDL_Texture* map;
extern SDL_Texture* platform_texture;

//Menu textures
extern SDL_Texture* menu_play_t;
extern SDL_Texture* menu_or_t;
extern SDL_Texture* menu_leave_t;
extern SDL_Texture* pmenu_exit_t;
extern SDL_Texture* pmenu_paused_t;
extern SDL_Texture* pmenu_continue_t;
extern SDL_Texture* pmenu_restart_t;
extern SDL_Texture* emenu_congratulations_t;
extern SDL_Texture* emenu_p1w_t;
extern SDL_Texture* emenu_p2w_t;
extern SDL_Texture* emenu_play_again_t;
extern SDL_Texture* emenu_quit_t;


//Players textures
extern SDL_Texture* player_texture;
extern SDL_Texture* player_idle_texture;
extern SDL_Texture* player_run_texture;
extern SDL_Texture* player_jump_rise_texture;
extern SDL_Texture* player_jump_fall_texture;
extern SDL_Texture* player_jump_effect_ground_texture;
extern SDL_Texture* player_jump_effect_air_texture;
extern SDL_Texture* player_charge_texture;
extern SDL_Texture* player_cast_fireball_texture1;
extern SDL_Texture* player_cast_fireball_texture2;
extern SDL_Texture* player_dive_texture;
extern SDL_Texture* player_fireball_texture;
extern SDL_Texture* player_fireball_trail_texture;
extern SDL_Texture* player_t_ball_trail_texture;
extern SDL_Texture* player_t_ball_blast_texture;
extern SDL_Texture* player_blast_smoke_texture;


extern SDL_Texture* player2_texture;
extern SDL_Texture* player2_idle_texture;
extern SDL_Texture* player2_run_texture;
extern SDL_Texture* player2_jump_rise_texture;
extern SDL_Texture* player2_jump_fall_texture;
extern SDL_Texture* player2_cast_fireball_texture1;
extern SDL_Texture* player2_cast_fireball_texture2;
extern SDL_Texture* player2_hit_texture;
extern SDL_Texture* player2_dive_texture;
extern SDL_Texture* player2_fireball_texture;
extern SDL_Texture* player2_fireball_trail_texture;
extern SDL_Texture* player2_t_ball_trail_texture;
extern SDL_Texture* player2_t_ball_blast_texture;
extern SDL_Texture* player2_blast_smoke_texture;



extern SDL_Texture* arrow_texture;
extern SDL_Texture* tp_trail_texture;
extern SDL_Texture* tp_trail2_texture;
extern SDL_Texture* help_texture;

extern SDL_Texture* t_ball_opening_texture;
extern SDL_Texture* t_ball_opened_texture;
extern SDL_Texture* t_ball_opening_texture2;
extern SDL_Texture* t_ball_opened_texture2;
extern SDL_Texture* blast_texture;

extern SDL_Texture* enemy_stand_texture;
extern SDL_Texture* enemy_run_texture;
extern SDL_Texture* enemy_hit_texture;

extern SDL_Texture* digits_texture;
extern SDL_Texture* player1_score_texture;
extern SDL_Texture* player2_score_texture;

extern SDL_Texture* map_texture;


//Map surface
extern SDL_Surface* map_surface;

//Globaly used audio samples
//extern Mix_Chunk *sound;


bool load_media();

void free_loaded_media();

