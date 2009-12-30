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

#include "entities.h"

void load_player() {
	player.bmp = load_bmp("data/sprites/spaceship.bmp", colors);
	player.bullet = load_bmp("data/sprites/bullet.bmp", colors);

	player.snd_fire = load_sample("data/sounds/fire.wav");
	player.snd_death = load_sample("data/sounds/death.wav");
}

void draw_player() {
	player.x = mouse_x;

	if ( (mouse_y + PLAYER_HEIGHT) <= SCREEN_HEIGHT) player.y = mouse_y;
	else player.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
	
	draw_sprite(buf, player.bmp, player.x, player.y);
}

void player_fire() {
	if (mouse_b & 1)
		if (player.fire == 0) { 
			player.fire = 1;
			player.bullet_x = player.x+32;
			player.bullet_y = player.y;
			play_sample(player.snd_fire, 255,128,1000, FALSE);
		}
		
	if (player.fire == 1) {
		draw_sprite(buf, player.bullet, player.bullet_x, player.bullet_y);
		player.bullet_x += 3;
			
		if (player.bullet_x > SCREEN_WIDTH)
			player.fire = 0;
	}
}

void player_collision(int n) {

	if ( ((player.x + PLAYER_WIDTH) >= enemies[n].x) && (player.x <= (enemies[n].x + ENEMY_WIDTH)) )
		if ( ((player.y + PLAYER_HEIGHT) >= enemies[n].y) && ((player.y <= enemies[n].y + ENEMY_HEIGHT) )) {
			player.death = 1;
			play_sample(player.snd_death, 255,128,1000, FALSE);
		}


	if ( ((player.x + PLAYER_WIDTH) >= enemies[n].bullet_x) && (player.x <= (enemies[n].bullet_x + ENEMY_BULLET_WIDTH)) ) 
		if ( ((player.y + PLAYER_HEIGHT) >= enemies[n].bullet_y) && ((player.y <= enemies[n].bullet_y + ENEMY_BULLET_HEIGHT) )) {
			player.death = 1;
			play_sample(player.snd_death, 255,128,1000, FALSE);
		}
}

void destroy_player() {

	destroy_bitmap(player.bmp);
	destroy_bitmap(player.bullet);
	
}
