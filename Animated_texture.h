#pragma once
#include "Texture.h"
class Animated_texture : public Texture {
public:
	Animated_texture(SDL_Texture* original_texture, int frames, int x_offset=0, int y_offset=0, int columns=0, int lines=0);
	~Animated_texture();

	//Prepare clips from texture
	void set_clips();
	//Set specific order of frames in animation
	void set_frame_order(int order[], int count);
	//Set animation frame to next if enough ticks passed
	void next_frame();
	//Set animation frame to listed
	void set_frame(int frame_number);
	//Set ticks per one frame change to listed
	void set_ticks_per_frame(int ticks_count);
	//Return number of current animation frame
	int get_frame_number();
	//Return number of replays
	int get_replay_count();
	//Reset counters
	void reset();
	//Render texture at given point
	void render(int x, int y, bool flip_right = true, double angle = 0.0, SDL_Point* center = NULL);


protected:
	int clip_col, clip_line;
	int frame_order[100];
	SDL_Rect* sprite_clips;
	SDL_Rect* current_clip;
	int current_frame;
	int total_frames;
	int ticks_per_frame;
	int ticks_counter;
	int replay_counter;
};

