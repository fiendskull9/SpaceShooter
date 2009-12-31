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

#include <stdio.h>
#include <allegro.h>

#include "sprites.h"

#define SET_GAME_STATUS(STATUS) game_status = STATUS;

#define STATUS_RUN 0
#define STATUS_START 1
#define STATUS_PAUSE 2
#define STATUS_GAMEOVER 3

#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 536

BITMAP *buf, *background;
PALETTE colors;

SAMPLE *snd_pause;

int game_status, score, xscroll;

void reset_variables();
void check_game_status();
