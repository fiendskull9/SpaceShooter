/*
    SpaceShooter is an old-school space shooter game in 2D.
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

#include "main.h"

int main(){

	int i;
	
	/* Initialize Allegro and variables*/
	allegro_init();
	reset_variables();
	
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
	background = load_bmp("data/sprites/background-double.bmp", colors);

	load_player();

	for (i = 0; i < ENEMIES; i++)
		load_enemy(i);
	
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
		if (player.death == 1) {
			textprintf_ex(buf, font, screen_width/2-70, screen_height/2, 
				makecol(138, 153, 200), -1, "Game Over! Score: %d.", score);
			textprintf_ex(buf, font, screen_width/2-90, screen_height/2+15, 
				makecol(138, 153, 200), -1, "Press ENTER to continue.");
			
			if(key[KEY_ENTER]) reset_variables();

			continue;	
		}
		
		if((start != 1) && (player.death !=1)) {
			textprintf_ex(buf, font, screen_width/2-70, screen_height/2, 
				makecol(138, 153, 200), -1, "Press ENTER to start.");
			if(key[KEY_ENTER]) start = 1;
		
			continue;
		}
		
		/* Show scores */
		textprintf_ex(buf, font, 10, 10, makecol(138, 153, 200), -1, "Score: %d", score);
		
		/* Draw spaceship sprite at mouse position */
		draw_player();
		
		/* And bullet, if fired */
		player_fire();

		/* Player collision with each enemy */
		for (i = 0; i < ENEMIES; i++)
			player_collision(i);
		
		/* For each enemy do... */
		for (i = 0; i < ENEMIES; i++) {

			/* Check for respawn... */
			if (enemies[i].respawn == 1)
				enemy_respawn(i);

			/* ...then draw enemies... */
			draw_enemy(i);
			
		
			/* ...move them... */
			enemy_motion(i);

			/* ...make them kill... */
			enemy_fire(i);

			/* ...and die. */
			enemy_collision(i);
		}

	}

	/* Destroy bitmaps */
	destroy_bitmap(buf);
	destroy_bitmap(background);

	destroy_player();

	for (i = 0; i < ENEMIES; i++)
		destroy_enemy(i);
	
	return 0;
}

END_OF_MAIN ();

void reset_variables() {
	int i;
	
	start = 0;
	score = 0;
	xscroll = 0;

	player.death = 0;

	for (i = 0; i < ENEMIES; i++) {
		enemies[i].fire = 0;
		enemies[i].respawn = 1;
	}

}
