/*
    SpaceShooter is an old-school space shooter game in 2D.
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
#include "game_data.h"
#include "user_data.h"
#include "screen.h"
#include "sound.h"
#include "timers.h"
#include "enemies.h"
#include "player.h"

#define SET_GAME_STATUS(STATUS) game_status = STATUS;

#define STATUS_RUN 		0
#define STATUS_START 		1
#define STATUS_PAUSE 		2
#define STATUS_GAMEOVER 	3
#define STATUS_HELP 		4
#define STATUS_STARTING		5

int gameover, game_status, fps;

void reset_variables();
void check_game_status();
void print_game_info();
void check_for_key();

int main(int argc, char **argv) {
	int i;

	/* Initialize Allegro and variables*/
	allegro_init();
	set_user_data();
	reset_variables();
	printd(DEBUG_INFO "Allegro initialized");

	/* Set-up input devices */
	install_keyboard();
	install_mouse();
	printd(DEBUG_INFO "Input devices installed");

	/* Set-up sound card */
	init_sound();

	/* Set-up and initialize timers */
	init_timers();

	/* Set screen */
	init_screen();

	/* Load data */
	load_game_data();

	load_player();

	for (i = 0; i < ENEMIES; i++)
		load_enemy(i);

	/* Main loop */
	while (!key[KEY_ESC]) {

		while (ticks == 0) 
			rest(100 / UPDATES_PER_SECOND);

		while (ticks > 0) {
			update_screen();
			ticks--;
		}

		set_bg();

		check_for_key();

		if ((game_status == STATUS_RUN) && (gameover == 1)) {
			/* Game Over */
			play_sample(snd_gameover, 255,128,1000, FALSE);
			SET_GAME_STATUS(STATUS_GAMEOVER);
		}

		if (game_status != STATUS_RUN) {
			check_game_status();
			continue;
		}

		print_game_info();

		/* For each enemy do... */
		for (i = 0; i < ENEMIES; i++) {

			/* Check for respawn... */
			if (enemies[i].death == 1)
				enemy_respawn(i);
	
			enemy_motion(i);
			enemy_collision(i);

			/* Check for player collision */
			player_collision(i);
		}

		/* Draw spaceship sprite at mouse position */
		draw_player();

		/* And bullet, if fired */
		player_fire();		

		/* Draw enemies */
		for (i = 0; i < ENEMIES; i++) {
			draw_enemy(i);
			enemy_fire(i);
		}

	}

	/* Unload datafile, bitmaps and sounds */
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	destroy_rle_sprite(background);
	destroy_bitmap(buf);
	

	return 0;
}

END_OF_MAIN();

/*
 * Check for pressed key, and change status accordingly
 */

void check_for_key() {
	if(key[KEY_S])
		take_screenshot();

	if(key[KEY_ALTGR] && key[KEY_G])
		gameover = 2;

	if((game_status == STATUS_RUN) && key[KEY_P]) {
		/* Game pause */
		SET_GAME_STATUS(STATUS_PAUSE);
		play_sample(snd_pause, 255,128,1000, FALSE);
	}
}

/*
 * Show game information
 */

void print_game_info() {
	int margin = 10;

	/* Show scores... */
	prints('l', margin, margin, "Score: %i", score);

	/* ...player lives... */
	prints('l', margin, margin + TEXT_LINE_HEIGHT, "Health: %i/%i",
					player.health, PLAYER_HEALTH);

	/* ..record...*/
	prints('l', margin, margin + TEXT_LINE_HEIGHT*2, "Record: %i",
							user_record);

	/* ...fps, if enabled.*/
	if (config_show_fps == 1)
		prints('r', SCREEN_WIDTH-50, margin, "FPS: %i", fps);
}

/*
 * Reset game variabled to default
 */

void reset_variables() {
	int i;

	score 		 = 0;
	gameover 	 = 0;
	record_is_broken = 0;

	for (i = 0; i < ENEMIES; i++)
		reset_enemy(i);

	set_user_data();
	reset_player();

	start_ticks = START_TIMEOUT_DEFAULT;

	srand(time(NULL));

	SET_GAME_STATUS(STATUS_START);
}

void check_game_status() {
	int w, h;
	w = SCREEN_WIDTH/2;  /* Screen width middle */
	h = SCREEN_HEIGHT/2; /* Screen height middle */

	switch (game_status) {
		case STATUS_START:
			draw_rle_trans(title, w-275, h-23);
			prints('c', w, SCREEN_HEIGHT-TEXT_LINE_HEIGHT*2,
					"Press FIRE to start or H for help.");

			if (mouse_b & 1) {
				SET_GAME_STATUS(STATUS_STARTING);

				LOCK_VARIABLE(start_ticks);
				LOCK_FUNCTION(start_ticker);
				install_int_ex(start_ticker, SECS_TO_TIMER(1));
			}

			if (key[KEY_H])
				SET_GAME_STATUS(STATUS_HELP);

			break;

		case STATUS_STARTING:
			if (start_ticks < 1) {
				remove_int(start_ticker);
				SET_GAME_STATUS(STATUS_RUN);
			}

			prints('c', SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "%i", start_ticks);

			break;

		case STATUS_HELP:
			w -= 100;
			prints('l', w, h-TEXT_LINE_HEIGHT*5, "MOUSE = Control spaceship");
			prints('l', w, h-TEXT_LINE_HEIGHT*4, "LEFT BTN = Fire");
			prints('l', w, h-TEXT_LINE_HEIGHT*3, "P = Pause");
			prints('l', w, h-TEXT_LINE_HEIGHT*2, "S = Take a screenshot");
			prints('l', w, h-TEXT_LINE_HEIGHT, "ESC = Quit");
			prints('l', w, h+TEXT_LINE_HEIGHT, "Press ENTER to continue.");

			if(key[KEY_ENTER])
				SET_GAME_STATUS(STATUS_START);

			w += 100;

			break;

		case STATUS_PAUSE:
			prints('c', w, h-TEXT_LINE_HEIGHT, "Game paused.");
			prints('c', w, h, "Press ENTER to resume.");

			if (key[KEY_ENTER]) 
				SET_GAME_STATUS(STATUS_RUN);

			break;

		case STATUS_GAMEOVER:
			check_record();

			if (record_is_broken == 1)
				prints('c', w, h-TEXT_LINE_HEIGHT*2,
					"Congratulations! You've broken the record.");

			prints('c', w, h-TEXT_LINE_HEIGHT, "Game Over! Score: %d", score);
			prints('c', w, h, "Press ENTER to continue.");

			if(key[KEY_ENTER])
				reset_variables();

			break;
	}
}

int game_running() {
	if (game_status == STATUS_RUN)
		return 1;

	return 0;
}
