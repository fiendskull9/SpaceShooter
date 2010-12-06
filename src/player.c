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

#include "config.h"
#include "debug.h"
#include "screen.h"
#include "game_data.h"
#include "user_data.h"
#include "enemies.h"

#define  __PLAYER_C__
#include "player.h"

hero player;

extern int game_status, gameover;

void draw_player() {

	if (player.health <= 0) {
		gameover = 1;
		return;
	}

	player.x = mouse_x;

	if ( (mouse_y + PLAYER_HEIGHT) <= SCREEN_HEIGHT)
		player.y = mouse_y;
	else
		player.y = SCREEN_HEIGHT - PLAYER_HEIGHT;

	draw_trans(player.bmp, player.x, player.y);
}

void player_fire() {
	if ((mouse_b & 1) /*&& (game_status == STATUS_RUN)*/)
		if (player.fire == 0) { 
			player.fire 	= 1;
			player.bullet_x = player.x + PLAYER_WIDTH;
			player.bullet_y = player.y;

			play_sample(player.snd_fire, 255,128,1000, FALSE);
		}

	if (player.fire == 1) {
		draw_trans(player.bullet, player.bullet_x, player.bullet_y);
		player.bullet_x += PLAYER_BULLET_SPEED;

		if (player.bullet_x > SCREEN_WIDTH) {
			player.bullet_x = 0;
			player.bullet_y = 0;
			player.fire 	= 0;
		}
	}
}

void player_collision(int n) {
	if (((player.x + PLAYER_WIDTH) >= enemies[n].x) &&
	     (player.x <= (enemies[n].x + ENEMY_WIDTH)) &&
	      enemies[n].death == 0)
		if (((player.y + PLAYER_HEIGHT) >= enemies[n].y) &&
		     ((player.y <= enemies[n].y + ENEMY_HEIGHT))) {
			player.health 	-= ENEMY_DAMAGE;
			enemies[n].death = 1;
		}

	if (((player.x + PLAYER_WIDTH) >= enemies[n].bullet_x) &&
	     (player.x <= (enemies[n].bullet_x + ENEMY_BULLET_WIDTH))) 
		if (((player.y + PLAYER_HEIGHT) >= enemies[n].bullet_y) &&
		    ((player.y <= enemies[n].bullet_y + ENEMY_BULLET_HEIGHT))) {
			player.health -= ENEMY_BULLET_DAMAGE;

			reset_enemy_bullet(n);
		}
}

void reset_player_bullet() {
	player.fire 	= 0;
	player.bullet_x = -100;
	player.bullet_y = -100;
}

void reset_player() {
	player.x 	= 0;
	player.y 	= 0;
	player.health 	= PLAYER_HEALTH;

	reset_player_bullet();
}

void load_player() {
	player.bmp 	= load_tga(DATA_PATH "/sprites/spaceship.tga", NULL);
	player.bullet 	= load_tga(DATA_PATH "/sprites/bullet.tga", NULL);
	player.snd_fire = load_wav(DATA_PATH "/sounds/fire.wav");

	reset_player();
}

void destroy_player() {
	destroy_bitmap(player.bmp);
	destroy_bitmap(player.bullet);
}
