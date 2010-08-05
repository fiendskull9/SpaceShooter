/*
    SpaceShooter is an old-school space shooter game in 2D.
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

#include "SpaceShooter.h"

int main(int argc, char **argv) {
	int i;
	int frames_done = 0;
	int old_time = 0;

	int frames_array[10];
	int frame_index = 0;
	for (i = 0; i < 10; i++)
		frames_array[i] = 0;

	/* Initialize Allegro and variables*/
	allegro_init();
	read_config();
	reset_variables();
	printd(DEBUG_INFO "Allegro initialized");

	/* Set-up input devices */
	install_keyboard();
	install_mouse();
	printd(DEBUG_INFO "Input devices installed");

	/* Set-up sound card */
	reserve_voices(8, 0);
	set_volume_per_voice(2);
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	if (config_disable_audio == 1) 
		set_volume(0, -1);
	else
		set_volume(255, -1);
	printd(DEBUG_INFO "Sound card installed");

	/* Set-up and initialize timers */
	install_timer();
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(UPDATES_PER_SECOND));

	LOCK_VARIABLE(game_ticks);
	LOCK_FUNCTION(game_time_ticker);
	install_int_ex(game_time_ticker, BPS_TO_TIMER(10));
	printd(DEBUG_INFO "Timers installed and initialized");

	/* Set colors*/
	set_color_depth(32);
	set_palette(colors);

	/* Set screen */
	if (config_fullscreen == 1)
		set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	else
		set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	buf = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	set_window_title("SpaceShooter");
	clear(buf);
	printd(DEBUG_INFO "Screen initialized");

	/* Load data */
	dat = load_datafile(DATA_PATH);
	printd(DEBUG_INFO "Datafile loaded");

	background = dat[BMP_BACKGROUND].dat;
	snd_pause = dat[SND_PAUSE].dat;
	font_default = dat[FONT_YANONE].dat;

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

		if (xscroll > SCREEN_WIDTH-1)
			xscroll = 0;

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

		if (game_ticks >= old_time + 1) {
			fps -= frames_array[frame_index];
			frames_array[frame_index] = frames_done;
			fps += frames_done;
 
			frame_index = (frame_index + 1) % 10;
 
			frames_done = 0;
			old_time += 1;
		}

		frames_done++;
	}

	/* Unload datafile, bitmaps and sounds */
	//unload_data();

	return 0;
}

END_OF_MAIN();

void printd(char* format, ...) {
	va_list args;

	if (config_debug == 1) {
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		printf("\n");
	}
}

void prints(char align, int x, int y, char* format, ...) {
	va_list args;
	char buffer[100];
	int bg = -1;
	int color = makecol(TEXT_DEFAULT_RGB_RED,
			    TEXT_DEFAULT_RGB_GREEN,
			    TEXT_DEFAULT_RGB_BLUE);

	va_start(args, format);
	uvszprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	switch (align) {
		case 'l':
			textout_ex(buf, font_default, buffer, x, y, color, bg);
			break;

		case 'c':
			textout_centre_ex(buf, font_default, buffer, x, y, color, bg);
			break;

		case 'r':
			textout_right_ex(buf, font_default, buffer, x, y, color, bg);
			break;
	}
}

void update_screen() {
	blit(buf, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	clear(buf);
}

void set_bg() {
	blit(background, buf, xscroll, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);		
	xscroll++;
}

void print_game_info() {
	int margin = 10;

	/* Show scores... */
	prints('l', margin, margin, "Score: %i", score);

	/* ..record...*/
	prints('l', margin, margin + TEXT_LINE_HEIGHT, "Record: %i", game_record);

	/* ...fps, if enabled.*/
	if (config_show_fps == 1)
		prints('r', SCREEN_WIDTH-50, margin, "FPS: %i", fps);
}

void reset_variables() {
	int i;

	score = 0;
	gameover = 0;
	record_is_broken = 0;

	for (i = 0; i < ENEMIES; i++)
		reset_enemy(i);

	get_record();
	reset_player();

	srand(time(NULL));

	SET_GAME_STATUS(STATUS_START);
}

void check_game_status() {
	int w, h;
	w  = SCREEN_WIDTH/2; /* Screen width middle */
	h = SCREEN_HEIGHT/2; /* Screen height middle */

	switch (game_status) {
		case STATUS_START:
			draw_player();

			prints('c', w, h-TEXT_LINE_HEIGHT, "SpaceShooter " VERSION);
			prints('c', w, h, "Press FIRE to start or H for help.");

			if (mouse_b & 1)
				SET_GAME_STATUS(STATUS_RUN);

			if (key[KEY_H])
				SET_GAME_STATUS(STATUS_HELP);

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

void ticker() {
	ticks++;
}

void game_time_ticker() {
	game_ticks++;
}

void unload_data() {
	int i;

	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	destroy_bitmap(background);
	destroy_bitmap(buf);
	destroy_player();

	for (i = 0; i < ENEMIES; i++)
		destroy_enemy(i);

	unload_datafile(dat);
}
