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
		printd(DEBUG_WARN "Failed creating %s/%s", getenv("HOME"), CONFIG_DIR);
		
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
		printd(DEBUG_WARN "Unable to open %s file", path);
		return;
	}

	while (fscanf(config_file, "%s %i", var, &val) > 0) {
		if (strcmp(var, CONFIG_DEBUG) == 0) {
			printd(DEBUG_INFO "Config config_debug = %i", val);
			config_debug = val;
		} else if (strcmp(var, CONFIG_NO_AUDIO) == 0) {
			printd(DEBUG_INFO "Config config_disable_audio = %i", val);
			config_disable_audio = val;
		} else if (strcmp(var, CONFIG_FPS) == 0) {
			printd(DEBUG_INFO "Config config_show_fps = %i", val);
			config_show_fps = val;
		} else if (strcmp(var, CONFIG_FULLSCREEN) == 0) {
			printd(DEBUG_INFO "Config config_fullscreen = %i", val);
			config_fullscreen = val;
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
		printd(DEBUG_WARN "Unable to open %s file", path);
		return;
	}
	
	read = fscanf(record_file, "%i", &game_record);
	fclose(record_file);

	printd(DEBUG_INFO "Config record = %i", game_record);
}

void set_record() {
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR) + strlen(RECORD_FILE)];
	FILE *record_file;

	check_config_dir();
	sprintf(path, "%s/%s/%s", getenv("HOME"), CONFIG_DIR, RECORD_FILE);

	record_file = fopen(path, "w+");
	if (record_file == NULL) {
		printd(DEBUG_WARN "Unable to open %s file", path);
		return;
	}
	
	if (fprintf(record_file, "%i", score) < 0)
		printd(DEBUG_WARN "Unable to write to %s file", path);

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
