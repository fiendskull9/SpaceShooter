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

#include "SpaceShooter.h"

int main(){

	int i;
	
	/* Initialize Allegro and variables*/
	allegro_init();
	reset_variables();
	
	/* Set-up input devices */
	install_keyboard();
	install_mouse();

	/* Set-up sound card */
	reserve_voices(8, 0);
	set_volume_per_voice(2);
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	set_volume(255, -1);

	/* Set-up and initialize timer */
	install_timer();
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(UPDATES_PER_SECOND));
	
	/* Set colors*/
	set_color_depth(32);
	set_palette(colors);
	
	/* Set screen */
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	buf = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	set_window_title("SpaceShooter");
	clear(buf);
	
	/* Load data */
	dat = load_datafile(DATA_PATH);
	
	background = dat[BMP_BACKGROUND].dat;
	snd_pause = dat[SND_PAUSE].dat;

	load_player();

	for (i = 0; i < ENEMIES; i++)
		load_enemy(i);
	
	/* Main loop */
	while (!key[KEY_ESC]) {

		while (ticks == 0) {
			rest(100 / UPDATES_PER_SECOND);
		}

		while (ticks > 0) 
			update_screen();
				
		print_basic();

		if (xscroll > SCREEN_WIDTH-1)
			xscroll = 0;

		/* Game pause */
		if(key[KEY_P]) {
			SET_GAME_STATUS(STATUS_PAUSE);
			play_sample(snd_pause, 255,128,1000, FALSE);
		}

		/* Game Over */
		if (player.death == 1) 
			SET_GAME_STATUS(STATUS_GAMEOVER);	

		if (game_status != STATUS_RUN) {
			check_game_status();
			continue;
		}
		
		/* For each enemy do... */
		for (i = 0; i < ENEMIES; i++) {

			/* Check for respawn... */
			if (enemies[i].death == 1)
				enemy_respawn(i);
	
			enemy_motion(i);

			enemy_collision(i);

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

		/* Draw enemies */
		for (i = 0; i < ENEMIES; i++) {
			draw_enemy(i);
			enemy_fire(i);
		}

	}

	/* Unload datafile, bitmaps and sounds */
	unload_data();
	
	return 0;
}

END_OF_MAIN ();

void update_screen() {
	blit(buf, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	clear(buf);
}

void print_basic() {
	/* Set backgound */
	blit(background, buf, xscroll, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);		
	xscroll++;

	/* Print help */
	textprintf_ex(buf, font, 10, SCREEN_HEIGHT-15, makecol(138, 153, 200), 
		-1, "Press ESC to exit or P to pause.");
}

void reset_variables() {
	int i;
	
	score = 0;
	xscroll = 0;

	player.death = 0;

	for (i = 0; i < ENEMIES; i++) {
		enemies[i].fire = 0;
		enemies[i].death = 1;
	}

	SET_GAME_STATUS(STATUS_START);

}

void check_game_status() {

	switch (game_status) {
		case STATUS_START:
			textprintf_ex(buf, font, SCREEN_WIDTH/2-70, SCREEN_HEIGHT/2, 
				makecol(138, 153, 200), -1, "Press ENTER to start.");

			if(key[KEY_ENTER])
				SET_GAME_STATUS(STATUS_RUN);

			break;

		case STATUS_PAUSE:
			textprintf_ex(buf, font, SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2, 
				makecol(138, 153, 200), -1, "Game paused.");
			textprintf_ex(buf, font, SCREEN_WIDTH/2 - 90, SCREEN_HEIGHT/2 + 15, 
				makecol(138, 153, 200), -1, "Press ENTER to resume.");

			if(key[KEY_ENTER])
				SET_GAME_STATUS(STATUS_RUN);

			break;

		case STATUS_GAMEOVER:
			textprintf_ex(buf, font, SCREEN_WIDTH/2-70, SCREEN_HEIGHT/2, 
				makecol(138, 153, 200), -1, "Game Over! Score: %d.", score);
			textprintf_ex(buf, font, SCREEN_WIDTH/2-90, SCREEN_HEIGHT/2+15, 
				makecol(138, 153, 200), -1, "Press ENTER to continue.");

			if(key[KEY_ENTER]) {
				reset_variables();
				SET_GAME_STATUS(STATUS_RUN);
			}
			
			break;
	}
	
}

void ticker() {
	ticks++;
}

void unload_data() {
	int i;
	
	unload_datafile(dat);

	destroy_bitmap(buf);
	destroy_bitmap(background);

	destroy_player();

	for (i = 0; i < ENEMIES; i++)
		destroy_enemy(i);
}
