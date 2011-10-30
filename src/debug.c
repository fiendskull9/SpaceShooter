#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define COLOR_GREEN      "[1;32m"
#define COLOR_YELLOW     "[1;33m"
#define COLOR_RED        "[1;31m"
#define COLOR_OFF        "[0m"

void ok_printf(const char *fmt, ...) {
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "[" COLOR_GREEN "ok" COLOR_OFF "] ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}

void debug_printf(const char *fmt, ...) {
#ifndef DEBUG
	va_list args;

	va_start(args, fmt);
	fprintf(stderr,  "[" COLOR_YELLOW "db" COLOR_OFF "] ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
#endif
}

void err_printf(const char *fmt, ...) {
	va_list args;

	va_start(args, fmt);
	fprintf(stderr,  "[" COLOR_RED "no" COLOR_OFF "] ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}

void fail_printf(const char *fmt, ...) {
	va_list args;

	va_start(args, fmt);
	fprintf(stderr,  "[" COLOR_RED "no" COLOR_OFF "] ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");

	exit(-1);
}
