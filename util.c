#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

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
	size_t sz;

	fp = fopen(filename, "r");
	if (!fp) {
		warn("Failed to open file %s: %s.\n", filename, strerror(errno));
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	src = calloc(sz + 1, sizeof(char));
	if (!src)
		return NULL;

	while (1) {
		buf = (char) fgetc(fp);
		if (buf == EOF)
			break;
		strncat(src, &buf, 1);
	}
	fclose(fp);
	return src;
}