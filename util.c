#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warn(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

/* Duplicate of warn() that calls exit() at the end. Bad practice to repeat yourself. */
void panic(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	exit(EXIT_FAILURE);
}

/* Consider avoiding strncat(), performance and security issues? */
char *file_to_str(const char *filename)
{
	FILE *fp;
	char *src, buf;
	size_t len;

	fp = fopen(filename, "r");
	if (!fp) {
		warn("Failed to open file %s.", filename);
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	src = calloc(len + 1, sizeof(char));
	if (!src)
		return NULL;

	len = 0;
	while (1) {
		buf = (char) fgetc(fp);
		if (buf == EOF)
			break;

		src[len] = buf;
		src[len + 1] = '\0';
		++len;
	}
	fclose(fp);
	return src;
}