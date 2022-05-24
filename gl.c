#include "gl.h"

#include "util.h"

#include <glad/gl.h>

void gl_init(void)
{
	if (!gladLoaderLoadGL())
		panic("Failed to load OpenGL library.\n");

	glEnable(GL_DEPTH_TEST);
}

void gl_set_clear_color(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void gl_clear_framebuffer(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_set_viewport(int vw, int vh)
{
	glViewport(0, 0, vw, vh);
}