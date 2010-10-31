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

#include "debug.h"

#define UPDATES_PER_SECOND 	60

volatile int ticks, fps_ticks, start_ticks;

void ticker() {
	ticks++;
}
END_OF_FUNCTION(ticker);

void fps_ticker() {
	fps_ticks++;
}
END_OF_FUNCTION(fps_ticker);

void start_ticker() {
	start_ticks--;
}
END_OF_FUNCTION(start_ticker);

void init_timers() {
	/* Set-up and initialize timers */
	install_timer();
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(UPDATES_PER_SECOND));

	LOCK_VARIABLE(fps_ticks);
	LOCK_FUNCTION(fps_ticker);
	install_int_ex(fps_ticker, BPS_TO_TIMER(10));
	printd(DEBUG_INFO "Timers installed and initialized");
}
