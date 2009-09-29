/*
    Basic example of the use of Allegro library in C for 2D game programming.
    Copyright (C) 2008 Alessandro Ghedini

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

#include <stdio.h>
#include <allegro.h>

/* Global Variables */
const int screen_width = 512;
const int screen_height = 512;

BITMAP *buf, *background, *spaceship, *bullet, *enemy, *enemy_bullet;
PALETTE colors;

int start, gameover, score, xscroll, ship_x, ship_y, enemy_x, enemy_y, enemy_moving, bullet_x, 
	bullet_y, enemy_bullet_x, enemy_bullet_y, enemy_respawn, fire, enemy_fire;

#define reset_variables(void) start = xscroll = fire = enemy_fire = enemy_respawn = score = gameover = 0;

int main(){
	
	/* Initialize Allegro and variables*/
	allegro_init(); reset_variables();
	
	/* Set-up input devices */
	install_keyboard();
	install_mouse();
	
	/* Set colors*/
	set_color_depth(32);
	set_palette(colors);
	
	/* Set screen */
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_width, screen_height, 0, 0);
	buf = create_bitmap(screen_width, screen_height);
	clear(buf);
	
	/* Load bitmaps */
	background = load_bmp("res/background-double.bmp", colors);
	spaceship = load_bmp("res/spaceship.bmp", colors);
	enemy = load_bmp("res/enemy.bmp", colors);
	bullet = load_bmp("res/bullet.bmp", colors);
	enemy_bullet = load_bmp("res/rocket.bmp", colors);
	
	/* Main loop */
	while (!key[KEY_ESC]) {

		/* Update screen */
		blit(buf, screen, 0, 0, 0, 0, screen_width, screen_height);
		clear(buf);
		
		/* Set backgound */
		blit(background, buf, xscroll, 0, 0, 0, screen_width, screen_height);		
		xscroll++;

		if (xscroll>screen_width-1)
   			xscroll = 0;
				
		textprintf_ex(buf, font, 10, screen_height-15, makecol(138, 153, 200), 
			-1, "Press ESC to exit.");
			
		/* Game Over */
		if (gameover == 1) {
			textprintf_ex(buf, font, screen_width/2-70, screen_height/2, 
				makecol(138, 153, 200), -1, "Game Over! Score: %d.", score);
			textprintf_ex(buf, font, screen_width/2-90, screen_height/2+15, 
				makecol(138, 153, 200), -1, "Press ENTER to continue.");
			
			if(key[KEY_ENTER]) reset_variables();

			continue;	
		}
		
		if((start != 1) && (gameover !=1)) {
			textprintf_ex(buf, font, screen_width/2-70, screen_height/2, 
				makecol(138, 153, 200), -1, "Press ENTER to start.");
			if(key[KEY_ENTER]) start = 1;
		
			continue;
		}
		
		/* Show scores */
		textprintf_ex(buf, font, 10, 10, makecol(138, 153, 200), -1, "Score: %d", score);
		
		/* Draw spaceship sprite at mouse position */
		ship_x = mouse_x; ship_y = mouse_y;
		draw_sprite(buf, spaceship, ship_x, ship_y);
		
		//Fire
		if (mouse_b & 1)
			if (fire == 0) { 
				fire = 1;
				bullet_x = ship_x+32;
				bullet_y = ship_y;
			}
		
		if (fire == 1) {
			draw_sprite(buf, bullet, bullet_x, bullet_y);
			bullet_x++;
			
			if (bullet_x>=screen_width) fire = 0;
		}
		
		//Death
		if ( ((ship_x+32) >= enemy_x) && (ship_x <= (enemy_x+64)) )
			if ( ((ship_y+26) >= enemy_y) && ((ship_y <= enemy_y+64) ))
				gameover = 1;


		if ( ((ship_x+32) >= enemy_bullet_x) && (ship_x <= (enemy_bullet_x+16)) ) 
			if ( ((ship_y+26) >= enemy_bullet_y) && ((ship_y <= enemy_bullet_y+16) )) 
				gameover = 1;	
		
		/* Draw enemy */
		if (enemy_respawn == 0)	{
			enemy_x = screen_width-64; 
			enemy_y = rand() % (screen_height);
			enemy_respawn = 1;
		}
		
		draw_sprite(buf, enemy, enemy_x, enemy_y);
		
		//Movement
		if (enemy_y >= 448) enemy_moving = 0;
		
		if (enemy_y <= 0) enemy_moving = 1;
		
		if (enemy_moving == 0) enemy_y--;
		else enemy_y++;
		
		enemy_x--;
		
		if (enemy_x <= -64){ enemy_respawn = 0; score--;}

		//Fire
		if ((enemy_fire == 0) && (enemy_x > ship_x)){
			enemy_bullet_x = enemy_x;
			enemy_bullet_y = enemy_y+32;
			enemy_fire = 1;
		}
		
		if (enemy_fire == 1) {
			draw_sprite(buf, enemy_bullet, enemy_bullet_x, enemy_bullet_y);
			enemy_bullet_x -= 2;
			if(ship_y>enemy_bullet_y) enemy_bullet_y++;
			else enemy_bullet_y--;
						
			if (enemy_bullet_x<=0) enemy_fire = 0;
		}
						
		//Death
		if ( ((bullet_x+7) >= enemy_x) && (bullet_x <= (enemy_x+64)) )
			if ( ((bullet_y+7) >= enemy_y) && ((bullet_y <= enemy_y+64) )) {
				enemy_respawn = 0;
				fire = 0;
				score++;
			}
	}
	
	destroy_bitmap(buf);
	destroy_bitmap(background);
	destroy_bitmap(spaceship);
	destroy_bitmap(enemy);
	destroy_bitmap(bullet);
	destroy_bitmap(enemy_bullet);
	
	return 0;
}

END_OF_MAIN ();
