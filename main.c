#include "sdl.h"
#include "gl.h"
#include "shader.h"
#include "texture.h"

#include "cube.h"

#include <SDL2/SDL.h>
#include <glad/gl.h>
#include <cglm/cglm.h>

/* Filled with temp code to see render a cube for testing. All these third party libraries and calls need to be moved. */
int main(void)
{
	unsigned int vbo, vao;
	struct shader basic_shd;
	struct texture wood_tex;

	sdl_init();
	sdl_setup("RENDERER");

	gl_init();
	gl_set_viewport(sdl_get_win_width(), sdl_get_win_height());

	shader_init(&basic_shd, "../basic_vert.glsl", "../basic_frag.glsl");
	texture_init(&wood_tex, "../container.jpg");

	shader_bind(&basic_shd);
	texture_bind(&wood_tex);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	                      (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	gl_set_clear_color(.3f, .2f, .2f, 1.f);

	while (1) {
		mat4 model, view, projection;

		glm_mat4_identity(model);
		glm_mat4_identity(view);
		glm_mat4_identity(projection);

		glm_rotate(model, ((float) SDL_GetTicks() / 1000.0f) * glm_rad(50.0f),
		           (vec3) {0.5f, 1.0f, 0.0f});
		glm_perspective(glm_rad(45.0f), sdl_get_win_width() / sdl_get_win_height(), 0.1f, 100.0f,
		                projection); // Needs explicit float casts, right now I like the stretch from precision loss.
		glm_translate(view, (vec3) {0.0f, 0.0f, -3.0f});

		shader_set_mat4f(&basic_shd, "model", model[0]);
		shader_set_mat4f(&basic_shd, "view", view[0]);
		shader_set_mat4f(&basic_shd, "projection", projection[0]);

		sdl_poll_events();

		gl_clear_framebuffer();

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		sdl_present_frame();
	}

	return 0;
}
