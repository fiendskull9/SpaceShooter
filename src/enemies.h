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

#define ENEMIES 3

#define ENEMY_WIDTH 57
#define ENEMY_HEIGHT 40
#define ENEMY_MAX_SPEED 5
#define ENEMY_MIN_SPEED 3
#define ENEMY_DEATH_SCORES 5
#define ENEMY_OVERTAKE_SCORES -1

#define ENEMY_BULLET_WIDTH 17
#define ENEMY_BULLET_HEIGHT 8
#define ENEMY_BULLET_SPEED 8

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
} villain;

villain enemies[ENEMIES];

void load_enemy(int n);
void draw_enemy(int n);
void enemy_respawn(int n);
void enemy_motion(int n);
void enemy_fire(int n);
void enemy_collision(int n);
void destroy_enemy(int n);