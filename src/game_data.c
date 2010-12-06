/*
    This file is part of SpaceShooter.
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

DATAFILE *dat;

BITMAP 	 *background, *title;

FONT     *font_default;

SAMPLE	 *snd_pause, *snd_gameover;

void load_game_data() {
	dat = load_datafile(DATA_PATH "/SpaceShooter.dat");

	background 	= load_bmp(DATA_PATH "/sprites/background.bmp", NULL);
	title	 	= load_tga(DATA_PATH "/sprites/title.tga", NULL);

	snd_pause 	= load_wav(DATA_PATH "/sounds/pause.wav");
	snd_gameover 	= load_wav(DATA_PATH "/sounds/gameover.wav");
	
	font_default 	= load_font(DATA_PATH "/fonts/Yanone_Kafeesatz.pcx", NULL, NULL);
	
	printd(DEBUG_INFO "Datafile loaded");
}
