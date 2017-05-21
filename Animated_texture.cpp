#include "Animated_texture.h"



Animated_texture::Animated_texture(SDL_Texture* original_texture, int frames, int x_offset, int y_offset, int columns, int lines) : Texture(original_texture, x_offset, y_offset) {
	if (lines == 0) {
		clip_col = frames;
		clip_line = 1;
		width /= frames;
	}
	else {
		clip_col = columns;
		clip_line = lines;
		width /= columns;
		height /= lines;
	}

	sprite_clips = new SDL_Rect[clip_col*clip_line];
	total_frames = clip_col*clip_line;
	current_frame = 0;
	replay_counter = 0;
	ticks_per_frame = 15;
	ticks_counter = ticks_per_frame;
	set_clips();
	int i;
	for (i = 0; i < total_frames; i++) {
		frame_order[i] = i;
	}
	for (i; i < (sizeof(frame_order) / sizeof(*frame_order)); i++) {
		frame_order[i] = -1;
	}
}

void Animated_texture::set_clips() {
	int c=0;
	for (int j = 0; j < clip_line; j++) {
		for (int i = 0; i < clip_col; i++) {
			sprite_clips[c].x = i * width;
			sprite_clips[c].y = j * height;
			sprite_clips[c].w = width;
			sprite_clips[c].h = height;
			c++;
		}
	}
	current_clip = &sprite_clips[frame_order[current_frame]];
}

void Animated_texture::set_frame_order(int order[], int count) {
	int i;
	for (i = 0; i < count; i++) {
		frame_order[i] = order[i];
	}
	for (i; i < (sizeof(frame_order) / sizeof(*frame_order)); i++) {
		frame_order[i] = -1;
	}
}


void Animated_texture::set_ticks_per_frame(int ticks) {
	ticks_per_frame = ticks;
	ticks_counter = ticks_per_frame;
}

void Animated_texture::next_frame() {
	if (ticks_counter <= 0) {
		if (frame_order[current_frame + 1] == -1) {
			current_frame = 0;
			replay_counter++;
		}
		else {
			current_frame++;
		}
		current_clip = &sprite_clips[frame_order[current_frame]];
		ticks_counter = ticks_per_frame;
	}
	else {
		ticks_counter--;
	}
}


void Animated_texture::set_frame (int frame_number) {
	current_frame = frame_number;
	current_clip = &sprite_clips[frame_order[current_frame]];
	ticks_counter = ticks_per_frame;
}

int Animated_texture::get_frame_number() {
	return current_frame;
}

int Animated_texture::get_replay_count() {
	return replay_counter;
}


void Animated_texture::render(int x, int y, bool flip_right, double angle, SDL_Point* center) {
	Texture::render(x, y, flip_right, current_clip, angle, center);
}


Animated_texture::~Animated_texture() {
	delete sprite_clips;
	sprite_clips = NULL;
}

void Animated_texture::reset() {
	current_frame = 0;
	replay_counter = 0;
	ticks_counter = ticks_per_frame;
}