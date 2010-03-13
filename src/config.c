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

#include "SpaceShooter.h"

void get_record() {
	int read;
	char path[strlen(getenv("HOME")) + strlen(RECORD_FILE)];
	FILE *record_file;

	sprintf(path, "%s/%s", getenv("HOME"), RECORD_FILE);

	record_file = fopen(path, "r");
	if (record_file == NULL) {
		if (DEBUG == 1)
			printf("WARNING: Unable to open %s file.", path);
		return;
	}
	
	read = fscanf(record_file, "%i", &game_record);
	fclose(record_file);
}

void set_record() {
	char path[strlen(getenv("HOME")) + strlen(RECORD_FILE)];
	FILE *record_file;

	sprintf(path, "%s/%s", getenv("HOME"), RECORD_FILE);

	record_file = fopen(path, "w+");
	if (record_file == NULL) {
		if (DEBUG == 1)
			printf("WARNING: Unable to open %s file.", path);
		return;
	}

	printf("lol\n");
	
	fprintf(record_file, "%i", score);
	fclose(record_file);
}

void check_record() {
	if ((game_record < score) && (record_is_broken == 0)) {
		set_record();
		record_is_broken = 1;
	}
}
