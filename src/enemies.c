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

void load_enemy(int n) {
	enemies[n].bmp = load_bmp("data/sprites/enemy.bmp", colors);
	enemies[n].bullet = load_bmp("data/sprites/rocket.bmp", colors);

	enemies[n].snd_fire = load_sample("data/sounds/rocket.wav");
	enemies[n].snd_death = load_sample("data/sounds/explosion.wav");
}

void draw_enemy(int n) {
	draw_sprite(buf, enemies[n].bmp, enemies[n].x, enemies[n].y);
}

void enemy_respawn(int n) {
	enemies[n].x = SCREEN_WIDTH-64; 
	enemies[n].y = rand() % (SCREEN_HEIGHT);
	enemies[n].death = 0;
}

void enemy_motion(int n) {
	if (enemies[n].y >= 448) enemies[n].motion = 0;
		
	if (enemies[n].y <= 0) enemies[n].motion = 1;
		
	if (enemies[n].motion == 0) enemies[n].y--;
	else enemies[n].y++;
		
	enemies[n].x--;
		
	if (enemies[n].x <= -64){
		enemies[n].death = 1;
		score--;
	}
}

void enemy_fire(int n) {
	if ( (enemies[n].fire == 0) && (enemies[n].x > player.x) ){
		enemies[n].bullet_x = enemies[n].x;
		enemies[n].bullet_y = enemies[n].y+32;
		enemies[n].fire = 1;
		play_sample(enemies[n].snd_fire, 255,128,1000, FALSE);
	}
		
	if (enemies[n].fire == 1) {
		draw_sprite(buf, enemies[n].bullet, enemies[n].bullet_x, enemies[n].bullet_y);
		enemies[n].bullet_x -= 2;

		if(player.y > enemies[n].bullet_y) enemies[n].bullet_y++;
		else enemies[n].bullet_y--;
						
		if (enemies[n].bullet_x <= 0) enemies[n].fire = 0;
	}
}

void enemy_collision(int n) {

	if ( ((player.bullet_x + PLAYER_BULLET_WIDTH) >= enemies[n].x) && (player.bullet_x <= (enemies[n].x + ENEMY_WIDTH)) )
		if ( ((player.bullet_y + PLAYER_BULLET_HEIGHT) >= enemies[n].y) && ((player.bullet_y <= enemies[n].y + ENEMY_HEIGHT) )) {
			enemies[n].death = 1;
			player.fire = 0;
			score++;
			play_sample(enemies[n].snd_death, 255,128,1000, FALSE);
		}
}

void destroy_enemy(int n) {
	destroy_bitmap(enemies[n].bmp);
	destroy_bitmap(enemies[n].bullet);
}
