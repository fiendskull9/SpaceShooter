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
#include "game_data.h"
#include "user_data.h"

void init_sound() {
	reserve_voices(8, 0);
	set_volume_per_voice(2);
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);

	if (config_disable_audio == 1) 
		set_volume(0, -1);
	else
		set_volume(255, -1);

	printd(DEBUG_INFO "Sound card installed");
}
