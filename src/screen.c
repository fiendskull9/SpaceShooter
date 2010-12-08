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

#include <allegro.h>

#include "debug.h"
#include "game_data.h"
#include "user_data.h"

#define __SCREEN_C__
#include "screen.h"

BITMAP  *buf;

void prints(char align, int x, int y, char* format, ...) {
	va_list args;
	char buffer[100];
	int bg 	  = -1;

	va_start(args, format);
	uvszprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	switch (align) {
		case 'l':
			textout_ex(buf, font_default, buffer, x, y, 0, bg);
			break;

		case 'c':
			textout_centre_ex(buf, font_default, buffer, x, y, 0, bg);
			break;

		case 'r':
			textout_right_ex(buf, font_default, buffer, x, y, 0, bg);
			break;
	}
}

void set_bg() {
	int x;
	static int xscroll = 0;
	xscroll++;

	blit(background, buf, xscroll, 0, 0, 0, SCREEN_WIDTH*2 - xscroll, SCREEN_HEIGHT);

	for(x = SCREEN_WIDTH*2 - xscroll; x < SCREEN_WIDTH; x += SCREEN_WIDTH*2) {
		blit(background, buf, 0, 0, x, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT);
	}
}

void init_screen() {
	PALETTE colors;

	set_color_depth(32);
	set_palette(colors);
	set_color_conversion(COLORCONV_NONE);

	if (config_fullscreen == 1)
		set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	else
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	buf = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	set_window_title("SpaceShooter");
	clear(buf);
	printd(DEBUG_INFO "Screen initialized");
}
