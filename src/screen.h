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

#define TEXT_LINE_HEIGHT	25

#define SCREEN_WIDTH 		640
#define SCREEN_HEIGHT 		480

#ifndef __SCREEN_C__
extern BITMAP *buf;

extern void prints(char align, int x, int y, char* format, ...);
extern void set_bg();
extern void init_screen();

void static inline update_screen() {
	blit(buf, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	clear(buf);
}

void static inline draw(BITMAP *bmp, int x, int y) {
	draw_sprite(buf, bmp, x, y);
}

void static inline draw_rle(RLE_SPRITE *rle, int x, int y) {
	draw_rle_sprite(buf, rle, x, y);
}

void static inline draw_trans(BITMAP *bmp, int x, int y) {
	set_alpha_blender();
	draw_trans_sprite(buf, bmp, x, y);
}

void static inline draw_rle_trans(RLE_SPRITE *rle, int x, int y) {
	set_alpha_blender();
	draw_trans_rle_sprite(buf, rle, x, y);
}

#endif
