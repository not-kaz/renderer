#include "sdl.h"

#include "util.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static struct {
	SDL_Window *window;
	SDL_GLContext gl_ctx;
} sdl;

static struct {
	SDL_DisplayMode *modes;
	unsigned int num_modes;
} display;

static void get_display_modes(void)
{
	display.num_modes = SDL_GetNumDisplayModes(0);

	if (display.num_modes < 1)
		panic("Failed to read display modes. %s\n", SDL_GetError());
	else
		display.modes = malloc(sizeof(SDL_DisplayMode) * display.num_modes);

	for (int i = 0; i < display.num_modes; ++i) {
		if (SDL_GetDisplayMode(0, i, &display.modes[i]) != 0)
			panic("No display data to read! %s\n", SDL_GetError());
	}
}

static void setup_gl_attribs(void)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
	                    SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetSwapInterval(1);
}

void sdl_init(void)
{
	const uint32_t sdl_flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
	const int32_t img_flags = IMG_INIT_JPG | IMG_INIT_PNG;

	if (SDL_WasInit(sdl_flags) & sdl_flags)
		return;

	if (SDL_Init(sdl_flags))
		panic("Failed to initialize SDL. %s\n", SDL_GetError());

	if (IMG_Init(img_flags) != (img_flags))
		panic("Failed to initialize SDL image library. %s\n", IMG_GetError());
}

void sdl_setup(const char *win_title)
{
	if (sdl.window || sdl.gl_ctx)
		return;

#if 1
	sdl.window = SDL_CreateWindow(win_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                              1024, 720, SDL_WINDOW_OPENGL);
#else
	get_display_modes();
	sdl.window = SDL_CreateWindow(win_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								  display.modes[display.num_modes - 1].w,
								  display.modes[display.num_modes - 1].h,
								  SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
#endif

	if (!sdl.window)
		panic("Failed to create SDL window context. %s\n", SDL_GetError());

	sdl.gl_ctx = SDL_GL_CreateContext(sdl.window);
	if (!sdl.gl_ctx)
		panic("Failed to create SDL OpenGL context. %s\n", SDL_GetError());

	setup_gl_attribs();
}

void sdl_shutdown(void)
{
	free(display.modes);
	SDL_GL_DeleteContext(sdl.gl_ctx);
	SDL_DestroyWindow(sdl.window);
	IMG_Quit();
	SDL_Quit();
}

void sdl_present_frame(void)
{
	SDL_GL_SwapWindow(sdl.window);
}

void sdl_poll_events(void)
{
	SDL_Event event;
	const unsigned char *keystate = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			sdl_shutdown();
			exit(EXIT_SUCCESS);
		}
	}
}

int sdl_get_win_width(void)
{
	int w;

	SDL_GetWindowSize(sdl.window, &w, NULL);
	return w;
}

int sdl_get_win_height(void)
{
	int h;

	SDL_GetWindowSize(sdl.window, NULL, &h);
	return h;
}