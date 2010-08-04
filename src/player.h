/*
    This file is part of SpaceShooter.
    Copyright (C) 2010 Alessandro Ghedini

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

#define ENEMIES 3

#define PLAYER_WIDTH 59
#define PLAYER_HEIGHT 48

#define PLAYER_BULLET_WIDTH 7
#define PLAYER_BULLET_HEIGHT 7
#define PLAYER_BULLET_SPEED 12

typedef struct {
	int x, y;
	int fire;
	int motion;
	int speed;
	int death;
	BITMAP *bmp;

	SAMPLE *snd_fire, *snd_death;

	int bullet_x, bullet_y;
	int bullet_speed;
	BITMAP *bullet;
} hero;

hero player;

void load_player();
void draw_player();
void player_fire();
void player_collision(int n);
void player_death();
void destroy_player();