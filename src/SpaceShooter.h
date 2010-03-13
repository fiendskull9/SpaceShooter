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

#include "data.h"
#include "sprites.h"

#define VERSION "2.0"
#define DEBUG 1

#define SET_GAME_STATUS(STATUS) game_status = STATUS;

#define STATUS_RUN 0
#define STATUS_START 1
#define STATUS_PAUSE 2
#define STATUS_GAMEOVER 3
#define STATUS_HELP 4

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 536

#define UPDATES_PER_SECOND 60

#define RECORD_FILE ".SpaceShooter.record"

#if (DEBUG == 1)
	#define DATA_PATH "SpaceShooter.dat"
#endif

#if (DEBUG == 0)
	#define DATA_PATH "/opt/SpaceShooter/SpaceShooter.dat"
#endif

DATAFILE *dat;

BITMAP *buf, *background;
PALETTE colors;

SAMPLE *snd_pause;

int game_status, score, xscroll;
int game_record, record_is_broken;
volatile int ticks;

void reset_variables();
void get_record();
void set_record();
void check_record();
void update_screen();
void print_basic();
void check_game_status();
void ticker();
void unload_data();
