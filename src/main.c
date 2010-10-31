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

#include "dat.h"
#include "config.h"
#include "debug.h"
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

int main(int argc, char **argv) {
	int i;
	int frames_done = 0;
	int old_time 	= 0;

	int frames_array[10];
	int frame_index = 0;

	for (i = 0; i < 10; i++)
		frames_array[i] = 0;

	config_start_tmout = START_TIMEOUT_DEFAULT;

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
	load_dat();

	background 	= dat[BMP_BACKGROUND].dat;
	snd_pause 	= dat[SND_PAUSE].dat;
	snd_gameover 	= dat[SND_GAMEOVER].dat;
	font_default 	= dat[FONT_YANONE].dat;

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

		if(key[KEY_S])
			take_screenshot();

		if(key[KEY_ALTGR] && key[KEY_G])
			gameover = 2;

		if (game_status == STATUS_RUN) {
			if(key[KEY_P]) {
				/* Game pause */
				SET_GAME_STATUS(STATUS_PAUSE);
				play_sample(snd_pause, 255,128,1000, FALSE);
			} else if (gameover == 1) {
				/* Game Over */
				play_sample(snd_gameover, 255,128,1000, FALSE);
				SET_GAME_STATUS(STATUS_GAMEOVER);
			} 
		} else {
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

		print_game_info();

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

		if (fps_ticks >= old_time + 1) {
			fps 			  -= frames_array[frame_index];
			frames_array[frame_index]  = frames_done;
			fps 			  += frames_done;
 
			frame_index = (frame_index + 1) % 10;
 
			frames_done 	 = 0;
			old_time 	+= 1;
		}

		frames_done++;
	}

	/* Unload datafile, bitmaps and sounds */
	//unload_data();

	return 0;
}

END_OF_MAIN();

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

void reset_variables() {
	int i;

	score 		 = 0;
	gameover 	 = 0;
	record_is_broken = 0;

	for (i = 0; i < ENEMIES; i++)
		reset_enemy(i);

	read_config();
	reset_player();

	start_ticks = config_start_tmout;

	srand(time(NULL));

	SET_GAME_STATUS(STATUS_START);
}

void check_game_status() {
	int w, h;
	w = SCREEN_WIDTH/2;  /* Screen width middle */
	h = SCREEN_HEIGHT/2; /* Screen height middle */

	switch (game_status) {
		case STATUS_START:
			prints('c', w, h-TEXT_LINE_HEIGHT, PACKAGE_STRING);
			prints('c', w, h, "Press FIRE to start or H for help.");

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

/*void unload_data() {
	int i;

	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	destroy_bitmap(background);
	destroy_bitmap(buf);
	destroy_player();

	for (i = 0; i < ENEMIES; i++)
		destroy_enemy(i);

	unload_datafile(dat);
}*/
