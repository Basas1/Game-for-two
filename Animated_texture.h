#pragma once
#include "Texture.h"
class Animated_texture : public Texture {
public:
	Animated_texture(SDL_Texture* original_texture, int frames);
	~Animated_texture();

	//Prepare clips from texture
	void set_clips();
	//Set animation frame to next if enough ticks passed
	void next_frame();
	//Set animation frame to listed
	void set_frame(int frame_number);
	//Set ticks per one frame change to listed
	void set_ticks_per_frame(int ticks_count);

	//Return number of current animation frame
	int get_frame_number();

	//Render texture at given point
	void render(int x, int y, double angle = 0.0, SDL_Point* center = NULL);

protected:
	SDL_Rect* sprite_clips;
	SDL_Rect* current_clip;
	int current_frame;
	int total_frames;
	int ticks_per_frame;
	int ticks_counter;
};

