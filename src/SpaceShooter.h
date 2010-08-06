/*
    This file is part of SpaceShooter.
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

#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "config.h"
#include "data.h"
#include "player.h"
#include "enemies.h"

#define DEBUG_INFO 		"INFO: "
#define DEBUG_WARN 		"WARNING: "
#define DEBUG_ERR  		"ERROR: "

#define SET_GAME_STATUS(STATUS) game_status = STATUS;
#define GEN_RAND(SEED)		rand() % SEED

#define CONFIG_DEBUG 		"debug"
#define CONFIG_NO_AUDIO 	"disable_audio"
#define CONFIG_FPS 		"show_fps"
#define CONFIG_FULLSCREEN 	"fullscreen"

#define SCREENSHOT_FORMAT 	"bmp" /* Valid formats are bmp, pcx and tga */

#define STATUS_RUN 		0
#define STATUS_START 		1
#define STATUS_PAUSE 		2
#define STATUS_GAMEOVER 	3
#define STATUS_HELP 		4

#define SCREEN_WIDTH 		768
#define SCREEN_HEIGHT 		536

#define UPDATES_PER_SECOND 	60

#define TEXT_DEFAULT_RGB_RED	125
#define TEXT_DEFAULT_RGB_GREEN	125
#define TEXT_DEFAULT_RGB_BLUE	235
#define TEXT_LINE_HEIGHT	25

#define CONFIG_DIR 		".SpaceShooter"
#define CONFIG_FILE 		"config"
#define RECORD_FILE 		"record"

DATAFILE *dat;

BITMAP *buf, *background;
PALETTE colors;

SAMPLE *snd_pause;

FONT *font_default;

int config_debug, config_disable_audio,
    config_show_fps, config_fullscreen;
int game_status, score, xscroll, fps, gameover;
int game_record, record_is_broken;
volatile int ticks, game_ticks;

void reset_variables();
void printd(char* format, ...);
void prints(char align, int x, int y, char* format, ...);

void check_config_dir();
void read_config();
void get_record();
void set_record();
void check_record();
void take_screenshot();

void update_screen();
void set_bg();
void print_game_info();
void check_game_status();
void ticker();
void game_time_ticker();
void unload_data();
