#include "sdl.h"
#include "gl.h"
#include "shader.h"

int main(void)
{
	struct shader basic_shd;

	sdl_init();
	sdl_setup("RENDERER");

	gl_init();
	gl_set_viewport(sdl_get_win_width(), sdl_get_win_height());

	shader_build(&basic_shd, "../basic_vert.glsl", "../basic_frag.glsl");

	while (1) {
		sdl_poll_events();

		gl_clear_framebuffer(.3f, .2f, .2f, 1.f);

		sdl_present_frame();
	}

	return 0;
}
