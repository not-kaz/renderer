#include "gl.h"

#include "debug.h"

#include <glad/gl.h>

void gl_init(void)
{
	if (!gladLoaderLoadGL())
		dbg_panic("Failed to load OpenGL library.\n");

	glEnable(GL_DEPTH_TEST);
}

void gl_clear_framebuffer(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_set_viewport(int vw, int vh)
{
	glViewport(0, 0, vw, vh);
}