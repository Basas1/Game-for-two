#pragma once
#include <SDL.h>
#include <string>

class Texture {
public:
	//Initializes variables
	Texture(SDL_Texture* original_texture, int x_offset = 0, int y_offset = 0);

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool load_from_file(std::string path);

	//Change texture
	void change_texture(SDL_Texture* change_to);

	//Set color modulation
	void set_color(Uint8 red, Uint8 green, Uint8 blue);

	//Set alpha mod
	void set_alpha(Uint8 alpha);

	//Change texture width
	void set_width(int w);

	//Change texture height
	void set_height(int h);

	//Set texture flip
	void set_flip(SDL_RendererFlip change);

	//Set absolute coordinate system
	void set_absolute_coord();

	//Deallocates texture
	void free();

	//Render texture at given point
	void render(int x, int y, bool flip_right = true, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL);

	//Gets image dimensions
	int get_width();
	int get_height();

	//Image dimensions
	int width, height;

protected:
	//Actual SDL texture
	SDL_Texture* original_texture;

	//Flip flag
	SDL_RendererFlip flip;

	//Set offsets for texture from actual player position
	int x_off, y_off;

	bool relative_coord;
};

	