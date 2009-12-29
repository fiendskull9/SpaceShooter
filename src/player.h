/*
    This file is part of SpaceShooter.
    Copyright (C) 2009 Alessandro Ghedini

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

#define PLAYER_WIDTH 59
#define PLAYER_HEIGHT 48

#define PLAYER_BULLET_WIDTH 7
#define PLAYER_BULLET_HEIGHT 7

extern const int screen_width;
extern const int screen_height;

extern PALETTE colors;
extern BITMAP *buf;

struct spaceship {
	int x, y;
	int fire;
	int death;
	BITMAP *bmp;

	int bullet_x, bullet_y;
	BITMAP *bullet;
} player;

void load_player();
void draw_player();
void player_fire();
void player_collision(int n);
void destroy_player();
