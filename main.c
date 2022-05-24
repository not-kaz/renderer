#include "sdl.h"
#include "gl.h"

int main(void)
{
	sdl_init();
	sdl_setup("RENDERER");

	gl_init();
	gl_set_viewport(sdl_get_win_width(), sdl_get_win_height());

	while (1) {
		sdl_poll_events();

		gl_clear_framebuffer(.3f, .2f, .2f, 1.f);

		sdl_present_frame();
	}

	return 0;
}
