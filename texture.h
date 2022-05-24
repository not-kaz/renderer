#ifndef TEXTURE_H
#define TEXTURE_H

struct texture {
	unsigned int id;
};

void texture_init(struct texture *tex, const char *imgpath);
void texture_bind(struct texture *tex);

#endif
