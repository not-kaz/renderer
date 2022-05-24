#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void dbg_panic(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	exit(EXIT_FAILURE);
}