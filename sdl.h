#ifndef SDL_H
#define SDL_H

void sdl_init(void);
void sdl_setup(const char *win_title);
void sdl_shutdown(void);
void sdl_present_frame(void);
void sdl_poll_events(void);
int sdl_get_win_width(void);
int sdl_get_win_height(void);

#endif
