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
#include "player.h"

#define  __ENEMIES_C__
#include "enemies.h"

#define ENEMY_EXPLOSION_FRAMES		40
#define ENEMY_EXPLOSION_FRAME_WIDTH	64
#define ENEMY_EXPLOSION_FRAME_HEIGHT	64

#define GEN_RAND(SEED)		rand() % SEED

villain enemies[ENEMIES];

BITMAP *explosion_sheet;

void load_enemy(int n) {
	if (n == 0)
		enemies[n].bmp = dat[BMP_ENEMY1].dat;
	else if (n == 1)
		enemies[n].bmp = dat[BMP_ENEMY2].dat;
	else if (n == 2)
		enemies[n].bmp = dat[BMP_ENEMY3].dat;

	enemies[n].bullet    = dat[BMP_ROCKET].dat;
	enemies[n].snd_fire  = dat[SND_ROCKET].dat;
	enemies[n].snd_death = dat[SND_EXPLOSION].dat;

	explosion_sheet = load_tga(DATA_PATH "/sprites/explosion.tga", NULL);
}

void draw_enemy(int n) {
	if (enemies[n].death == 0) {
		draw(enemies[n].bmp, enemies[n].x, enemies[n].y);
	} else if (enemies[n].x > 0) {
		BITMAP *tmp 	= create_bitmap(64, 64);

		int height 	= (enemies[n].expl_frame / (8 + 1)) * 64;
		int width  	= ((enemies[n].expl_frame % 8) - 1) * 64;

		blit(explosion_sheet, tmp, width, height, 0, 0, 64, 64);
		draw_trans(tmp, enemies[n].x, enemies[n].y);

		destroy_bitmap(tmp);
	}
}

void enemy_respawn(int n) {
	if ((enemies[n].expl_frame < ENEMY_EXPLOSION_FRAMES) &&
					(enemies[n].x > 0)) {
		enemies[n].expl_frame++;
	} else {
		enemies[n].expl_frame 	= 0;
		enemies[n].death 	= 0;
		enemies[n].x 		= SCREEN_WIDTH - ENEMY_HEIGHT; 
		enemies[n].y 		= GEN_RAND(SCREEN_HEIGHT);
		enemies[n].speed 	= GEN_RAND(ENEMY_MAX_SPEED) + ENEMY_MIN_SPEED;
		enemies[n].bullet_speed = ENEMY_BULLET_SPEED;

		printd(DEBUG_INFO "Enemy %i spawned at %i with speed %i", n,
						enemies[n].y, enemies[n].speed);
	}
}

void enemy_motion(int n) {
	if (enemies[n].death == 1)
		return;

	if (enemies[n].y >= SCREEN_HEIGHT - ENEMY_HEIGHT)
		enemies[n].motion = 0;

	if (enemies[n].y <= 0)
		enemies[n].motion = 1;

	if (enemies[n].motion == 0)
		enemies[n].y--;
	else
		enemies[n].y++;

	enemies[n].x -= enemies[n].speed;

	if (enemies[n].x <= -64){
		enemies[n].death = 1;
		score += ENEMY_OVERTAKE_SCORES;
	}
}

void enemy_fire(int n) {
	if ( (enemies[n].fire == 0) && (enemies[n].x > player.x) &&
						(enemies[n].death == 0)){
		enemies[n].bullet_x 	= enemies[n].x;
		enemies[n].bullet_y 	= enemies[n].y+32;
		enemies[n].fire 	= 1;

		play_sample(enemies[n].snd_fire, 255,128,1000, FALSE);
	}

	if (enemies[n].fire == 1) {
		draw(enemies[n].bullet, enemies[n].bullet_x, enemies[n].bullet_y);

		enemies[n].bullet_x -= enemies[n].bullet_speed;

		if(player.y > enemies[n].bullet_y)
			enemies[n].bullet_y++;
		else
			enemies[n].bullet_y--;
			
		if (enemies[n].bullet_x <= 0)
			enemies[n].fire = 0;
	}
}

void enemy_collision(int n) {
	if (((player.bullet_x + PLAYER_BULLET_WIDTH) >= enemies[n].x) &&
	     (player.bullet_x <= (enemies[n].x + ENEMY_WIDTH)))
		if (((player.bullet_y + PLAYER_BULLET_HEIGHT) >= enemies[n].y) &&
		     (player.bullet_y <= (enemies[n].y + ENEMY_HEIGHT))) {
			score 		 += ENEMY_DEATH_SCORES;
			enemies[n].death = 1;

			play_sample(enemies[n].snd_death, 255,128,1000, FALSE);
			reset_player_bullet();
			printd(DEBUG_INFO "Enemy %i has been hit", n);
		}
}

void reset_enemy_bullet(int n) {
	enemies[n].bullet_x 	= -100;
	enemies[n].bullet_y 	= -100;
	enemies[n].fire 	= 0;
}

void reset_enemy(int n) {
	enemies[n].death 	= 1;
	enemies[n].expl_frame 	= 0;
	enemies[n].x 		= -200;
	enemies[n].y 		= -200;

	reset_enemy_bullet(n);
}

void destroy_enemy(int n) {
	destroy_bitmap(enemies[n].bmp);
	destroy_bitmap(enemies[n].bullet);
}
