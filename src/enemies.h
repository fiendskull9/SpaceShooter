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

#define ENEMIES 3

#define ENEMY_WIDTH 64
#define ENEMY_HEIGHT 64

#define ENEMY_BULLET_WIDTH 16
#define ENEMY_BULLET_HEIGHT 16

extern const int screen_width;
extern const int screen_height;

extern PALETTE colors;
extern BITMAP *buf;
extern int score;

struct enemy {
	int x, y;
	int fire;
	int motion;
	int respawn;
	BITMAP *bmp;

	int bullet_x, bullet_y;
	BITMAP *bullet;
} enemies[ENEMIES];

void load_enemy(int n);
void draw_enemy(int n);
void enemy_respawn(int n);
void enemy_motion(int n);
void enemy_fire(int n);
void enemy_collision(int n);
void destroy_enemy(int n);
