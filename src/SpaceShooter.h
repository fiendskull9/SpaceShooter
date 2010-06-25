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

#include <sys/stat.h>
#include <sys/types.h>

#include "data.h"
#include "sprites.h"

#define VERSION "2.3"
#define IF_DEBUG if (debug == 1)
#define DEBUG_INFO "INFO: "
#define DEBUG_WARN "WARNING: "
#define DEBUG_ERR "ERROR: "

#define SET_GAME_STATUS(STATUS) game_status = STATUS;

#define CONFIG_DEBUG "debug"
#define CONFIG_NO_AUDIO "disable_audio"
#define CONFIG_FPS "show_fps"
#define CONFIG_FULLSCREEN "fullscreen"

#define SCREENSHOT_FORMAT "bmp" /* Valid formats are bmp, pcx and tga */

#define STATUS_RUN 0
#define STATUS_START 1
#define STATUS_PAUSE 2
#define STATUS_GAMEOVER 3
#define STATUS_HELP 4

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 536

#define UPDATES_PER_SECOND 60

#define CONFIG_DIR ".SpaceShooter"
#define CONFIG_FILE "config"
#define RECORD_FILE "record"

#define DATA_PATH "data/SpaceShooter.dat"

DATAFILE *dat;

BITMAP *buf, *background;
PALETTE colors;

SAMPLE *snd_pause;

int debug, disable_audio, show_fps, fullscreen;
int game_status, score, xscroll, fps;
int game_record, record_is_broken;
volatile int ticks, game_ticks;

void reset_variables();

void check_config_dir();
void read_config();
void get_record();
void set_record();
void check_record();
void take_screenshot();

void update_screen();
void print_basic();
void print_game_info();
void check_game_status();
void ticker();
void game_time_ticker();
void unload_data();
