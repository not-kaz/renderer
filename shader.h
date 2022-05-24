#ifndef SHADER_H
#define SHADER_H

struct shader {
	unsigned int program;
};

void shader_init(struct shader *s, const char *vert_file, const char *frag_file);
void shader_bind(struct shader *s);
void shader_set_mat4f(struct shader *s, const char *name, const float *val);

#endif
