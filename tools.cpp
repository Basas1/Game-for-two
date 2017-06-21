#pragma once
#include "tools.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


//Load Texture
SDL_Texture* load_texture(std::string path) {
	//The final texture
	SDL_Texture* new_texture = NULL;
	//Load image at specified path
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
		//Create texture from surface pixels
		new_texture = SDL_CreateTextureFromSurface(main_renderer, loaded_surface);
		if (new_texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	return new_texture;
}

//Copy-pasted from "http://sdl.beuc.net/sdl.wiki/Pixel_Access"
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

void render_number(int x, int y, int number) {
	if (number == 0) {
		digits->set_frame(0);
		digits->render(x, y);
	}
	else {
		int digit_count = 0;
		int k,j;
		int render_x = x;
		int render_y = y;
		int digit_list[10];
		for (int i = 0; i < 10; i++) {
			digit_list[i] = -1;
		}
		j = 9;
		for (int i = number; i > 0; i /= 10) {
			k = i % 10;
			digit_list[j] = k;
			j--;
			digit_count++;
		}
		for (int m = 0; m < 10; m++) {
			if (digit_list[m] == -1) continue;
			//printf("d[m]=%d\n", digit_list[m]);
			digits->set_frame(digit_list[m]);
			digits->render(render_x, render_y);
			render_x += digits->get_width();
		}
	}
}

