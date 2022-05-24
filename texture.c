#include "texture.h"

#include "util.h"

#include <glad/gl.h>
#include <SDL2/SDL_image.h>

static void define_gl_texture(unsigned int *id, SDL_Surface *img)
{
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, (*id));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
	             img->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void texture_init(struct texture *tex, const char *imgpath)
{
	SDL_Surface *img;

	img = IMG_Load(imgpath);
	if (!img)
		panic("Failed to load image from path: %s.\n", imgpath);

	define_gl_texture(&tex->id, img);

	SDL_FreeSurface(img);
}

void texture_bind(struct texture *tex)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->id);
}