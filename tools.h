#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_mixer.h>
#include "init.h"
#include "media.h"




SDL_Texture* load_texture(std::string path);

//void render_text(int x, int y, std::string text, TTF_Font* font = font1);

Uint32 getpixel(SDL_Surface *surface, int x, int y);

