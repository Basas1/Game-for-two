#pragma once
#include "Texture.h"
class Animated_texture : public Texture {
public:
	Animated_texture(SDL_Texture* original_texture, int frames);
	~Animated_texture();

	void set_clips();
	void next_frame();
	void set_frame(int frame_number);
	void set_ticks_per_frame(int ticks_count);

	int get_frame_number();


	//Render texture at given point
	void render(int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


protected:
	//SDL_Rect sprite_clips[];
	SDL_Rect *sprite_clips;
	SDL_Rect* current_clip;
	int current_frame;
	int total_frames;
	int ticks_per_frame;
	int ticks_counter;

};

