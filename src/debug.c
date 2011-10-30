<<<<<<< Updated upstream
<<<<<<< Updated upstream
/*
    This file is part of SpaceShooter.
    Copyright (C) 2010 Alessandro Ghedini <al3xbio@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdarg.h>

int config_debug = 0;

void printd(char* format, ...) {
	va_list args;

	if (config_debug == 1) {
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		printf("\n");
	}
=======
=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}
