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

#define PLAYER_WIDTH 		43
#define PLAYER_HEIGHT 		48

#define PLAYER_HEALTH 		20

#define PLAYER_BULLET_WIDTH 	7
#define PLAYER_BULLET_HEIGHT 	7
#define PLAYER_BULLET_SPEED 	12

typedef struct {
	int x, y;
	int fire;
	int health;
	RLE_SPRITE *sprite;

	SAMPLE *snd_fire;

	int bullet_x, bullet_y;
	RLE_SPRITE *bullet;
} hero;

#ifndef __PLAYER_C__
extern hero player;

extern void load_player();
extern void draw_player();
extern void player_fire();
extern void player_collision(int n);
extern void player_death();
extern void reset_player();
extern void reset_player_bullet();
extern void destroy_player();
#endif
