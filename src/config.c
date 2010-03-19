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

void check_config_dir() {
	int e;
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR)];
	sprintf(path, "%s/%s", getenv("HOME"), CONFIG_DIR);

	e = mkdir(path, 0755);
	
	if ( e < -1) 
		IF_DEBUG
			printf(DEBUG_WARN"Failed creating %s/%s", getenv("HOME"), CONFIG_DIR);
		
}

void read_config() {
	char var[15];
	int val;
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR) + strlen(CONFIG_FILE)];
	FILE *config_file;
	
	check_config_dir();
	sprintf(path, "%s/%s/%s", getenv("HOME"), CONFIG_DIR, CONFIG_FILE);

	config_file = fopen(path, "r");
	if (config_file == NULL) {
		IF_DEBUG
			printf(DEBUG_WARN"Unable to open %s file.\n", path);
		return;
	}

	while (fscanf(config_file, "%s %i", var, &val) > 0) {
		if (strcmp(var, CONFIG_DEBUG) == 0) {
			IF_DEBUG
				printf(DEBUG_INFO"Config debug = %i\n", val);
			debug = val;
		} else if (strcmp(var, CONFIG_NO_AUDIO) == 0) {
			IF_DEBUG
				printf(DEBUG_INFO"Config disable_audio = %i\n", val);
			disable_audio = val;
		} else if (strcmp(var, CONFIG_FPS) == 0) {
			IF_DEBUG
				printf(DEBUG_INFO"Config show_fps = %i\n", val);
			show_fps = val;
		} else if (strcmp(var, CONFIG_FULLSCREEN) == 0) {
			IF_DEBUG
				printf(DEBUG_INFO"Config fullscreen = %i\n", val);
			fullscreen = val;
		}
	}
	fclose(config_file);
}

void get_record() {
	int read;
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR) + strlen(RECORD_FILE)];
	FILE *record_file;
	
	check_config_dir();
	sprintf(path, "%s/%s/%s", getenv("HOME"), CONFIG_DIR, RECORD_FILE);

	record_file = fopen(path, "r");
	if (record_file == NULL) {
		IF_DEBUG
			printf(DEBUG_WARN"Unable to open %s file.n", path);
		return;
	}
	
	read = fscanf(record_file, "%i", &game_record);
	fclose(record_file);

	IF_DEBUG
		printf(DEBUG_INFO"Config record = %i\n", game_record);
}

void set_record() {
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR) + strlen(RECORD_FILE)];
	FILE *record_file;

	check_config_dir();
	sprintf(path, "%s/%s/%s", getenv("HOME"), CONFIG_DIR, RECORD_FILE);

	record_file = fopen(path, "w+");
	if (record_file == NULL) {
		IF_DEBUG
			printf(DEBUG_WARN"Unable to open %s file.n", path);
		return;
	}
	
	fprintf(record_file, "%i", score);
	fclose(record_file);
}

void check_record() {
	if ((game_record < score) && (record_is_broken == 0)) {
		set_record();
		record_is_broken = 1;
	}
}

void take_screenshot() {
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR) + strlen("screen-00.xxx")];
	FILE *screenshot_file;
	int i = 0;
	BITMAP *shot = screen;

	check_config_dir();
	do {
		sprintf(path, "%s/%s/screen-%i.%s", getenv("HOME"), CONFIG_DIR, i, SCREENSHOT_FORMAT);
		i++;
		rest(100);
	} while (fopen(path, "r") != NULL);
	
	screenshot_file = fopen(path, "w+");
	save_bitmap(path, shot, colors);
	fclose(screenshot_file);
}
