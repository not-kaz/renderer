#include "shader.h"

#include "util.h"

#include <stdlib.h>

#include <glad/gl.h>

#define INFO_MSG_MAX_LEN 1024

static unsigned int compile(const char *filepath, GLenum shd_type)
{
	int res;
	unsigned int shd;
	const char *src;
	char msg[INFO_MSG_MAX_LEN];

	src = file_to_str(filepath);
	if (!src)
		panic("Failed to create source from shader file %s.\n", filepath);

	shd = glCreateShader(shd_type);
	glShaderSource(shd, 1, &src, NULL);
	glCompileShader(shd);

	free((char *) src);

	glGetShaderiv(shd, GL_COMPILE_STATUS, &res);
	if (!res) {
		glGetShaderInfoLog(shd, INFO_MSG_MAX_LEN, NULL, msg);
		panic("Shader compile error: %s\n", msg);
	}
	return shd;
}

/* Apparently, it is not necessary to pass these args as pointers. Internally, GL is supposed to handle it. */
static void link(unsigned int sp, unsigned int vs, unsigned int fs)
{
	int res;
	char msg[INFO_MSG_MAX_LEN];

	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);

	glGetProgramiv(sp, GL_LINK_STATUS, &res);
	if (!res) {
		glGetProgramInfoLog(sp, INFO_MSG_MAX_LEN, NULL, msg);
		panic("Shader program link error: %s\n", msg);
	}
}

void shader_init(struct shader *s, const char *vert_file, const char *frag_file)
{
	unsigned int vs, fs;

	s->program = glCreateProgram();

	vs = compile(vert_file, GL_VERTEX_SHADER);
	fs = compile(frag_file, GL_FRAGMENT_SHADER);
	link(s->program, vs, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void shader_bind(struct shader *s)
{
	glUseProgram(s->program);
}

void shader_set_mat4f(struct shader *s, const char *name, const float *val)
{
	int loc;

	loc = glGetUniformLocation(s->program, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, val);
}