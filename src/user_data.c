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

#define CONFIG_DEBUG 		"debug"
#define CONFIG_NO_AUDIO 	"disable_audio"
#define CONFIG_FPS 		"show_fps"
#define CONFIG_FULLSCREEN 	"fullscreen"

#define CONFIG_DIR 		".SpaceShooter"
#define CONFIG_FILE 		"config"
#define RECORD_FILE 		"record"

#define SCREENSHOT_FORMAT 	"bmp" /* Valid formats: bmp, pcx and tga */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/stat.h>
#include <allegro.h>

#include "debug.h"

int config_disable_audio, config_show_fps, config_fullscreen;

int user_record, record_is_broken, score;

static char *get_path(char *file) {
	char *path;
	char *home = getenv("HOME");

	path = (char *) malloc(strlen(home)+1 + strlen(CONFIG_DIR)+1 +
				strlen(file)+1 + 2 * sizeof(char));

	sprintf(path, "%s/%s/%s", home, CONFIG_DIR, file);

	return path;
}

static void check_config_dir() {
	char *path = get_path("");
	struct stat st;
	
	if ((stat(path, &st) != 0) && (mkdir(path, 0755) < 0)) 
		printd(DEBUG_WARN "Unable to create %s/%s",
				getenv("HOME"), CONFIG_DIR);	
}

static void read_config() {
	int val;
	char var[15];
	char *path = get_path(CONFIG_FILE);
	FILE *config_file;

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

static void read_record() {
	int read;
	char *path = get_path(RECORD_FILE);;
	FILE *record_file = fopen(path, "r");

	if (record_file == NULL) {
		printd(DEBUG_WARN "Unable to open %s file", path);
		return;
	}
	
	read = fscanf(record_file, "%i", &user_record);
	fclose(record_file);

	printd(DEBUG_INFO "Config record = %i", user_record);
}

static void set_record() {
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

	printd(DEBUG_INFO "New record set to %i", score);
}

void check_record() {
	if ((user_record < score) && (record_is_broken == 0)) {
		record_is_broken = 1;

		printd(DEBUG_INFO "Setting new record");

		set_record();
	}
}

void set_user_data() {
	check_config_dir();
	read_config();
	read_record();
}

void take_screenshot() {
	char path[strlen(getenv("HOME")) + strlen(CONFIG_DIR) + strlen("screen-00.xxx")];
	FILE *screenshot_file;
	int i = 0;
	BITMAP *shot = screen;
	PALETTE colors;

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
