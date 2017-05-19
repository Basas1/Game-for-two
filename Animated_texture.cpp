#include "Animated_texture.h"



Animated_texture::Animated_texture(SDL_Texture* original_texture, int frames) : Texture(original_texture) {
	all_frame_width = width;
	all_frame_height = height;


	sprite_clips = new SDL_Rect[frames];
	total_frames = frames;
	current_frame = 0;
	ticks_per_frame = 15;
	ticks_counter = ticks_per_frame;
	width /= frames;
	set_clips();
	int i;
	for (i = 0; i < frames; i++) {
		frame_order[i] = i;
	}
	for (i; i < (sizeof(frame_order) / sizeof(*frame_order)); i++) {
		frame_order[i] = -1;
	}
}

void Animated_texture::set_clips() {
	for (int i = 0; i < total_frames; i++) {
		sprite_clips[i].x = i * width;
		sprite_clips[i].y = 0;
		sprite_clips[i].w = width;
		sprite_clips[i].h = height;
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
}

void Animated_texture::next_frame() {
	if (ticks_counter <= 0) {
		if (frame_order[current_frame + 1] == -1) {
			current_frame = 0;
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

void Animated_texture::render(int x, int y, bool flip_right, double angle, SDL_Point* center) {
	Texture::render(x, y, flip_right, current_clip, angle, center);
}


Animated_texture::~Animated_texture() {
	delete sprite_clips;
	sprite_clips = NULL;
}
