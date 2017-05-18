#include "Texture.h"
#include "init.h"
#include "tools.h"


Texture::Texture(SDL_Texture* t) {
	//Initialize
	//Get Texture width and height
	SDL_QueryTexture(t, NULL, NULL, &width, &height);
	//New texture to copy in
	SDL_Texture* copy_texture = SDL_CreateTexture(main_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	//Set blend mode to avoid backgound
	SDL_SetTextureBlendMode(copy_texture, SDL_BLENDMODE_BLEND);
	//Change the rendering target
	SDL_SetRenderTarget(main_renderer, copy_texture);
	//Drow to new texture
	SDL_RenderCopy(main_renderer, t, NULL, NULL);
	//Return default render target
	SDL_SetRenderTarget(main_renderer, NULL);
	//Initialize class texture
	original_texture = copy_texture;
	//Set flip to none
	flip = SDL_FLIP_NONE;
}

bool Texture::load_from_file(std::string path) {
	//Get rid of preexisting texture
	free();
	//The final texture
	SDL_Texture* new_texture = NULL;
	new_texture = load_texture(path);
	if (new_texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	original_texture = new_texture;
	return original_texture != NULL;
}

void Texture::change_texture(SDL_Texture* change_to) {
	//New texture to copy in
	SDL_Texture* copy_texture = SDL_CreateTexture(main_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	//Set blend mode to avoid black backgound
	SDL_SetTextureBlendMode(copy_texture, SDL_BLENDMODE_BLEND);
	//Change the rendering target
	SDL_SetRenderTarget(main_renderer, copy_texture);
	//Drow to new texture
	SDL_RenderCopy(main_renderer, change_to, NULL, NULL);
	//Return default render target
	SDL_SetRenderTarget(main_renderer, NULL);
	//Initialize class texture
	original_texture = copy_texture;
}

void Texture::set_ñolor(Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(original_texture, red, green, blue);
}

void Texture::set_flip(SDL_RendererFlip change) {
	flip = change;
}

Texture::~Texture() {
	free();
}

void Texture::set_width(int w) {
	width = w;
}

void Texture::set_height(int h) {
	height = h;
}

int Texture::get_width() {
	return width;
}

int Texture::get_height() {
	return height;
}

void Texture::render(int x, int y, bool flip_right, SDL_Rect* clip, double angle, SDL_Point* center) {
	if (flip_right) {
		flip = SDL_FLIP_NONE;
	}
	else {
		flip = SDL_FLIP_HORIZONTAL;
	}
	//Set rendering space
	SDL_Rect renderQuad = { x - camera->get_x() - (width / 2), y - camera->get_y() - (height / 2), width, height };

	//Render to screen
	SDL_RenderCopyEx(main_renderer, original_texture, clip, &renderQuad, angle, center, flip);
}

void Texture::free() {
	//Free texture if it exists
	if (original_texture != NULL) {
		SDL_DestroyTexture(original_texture);
		original_texture = NULL;
	}
}