/*
 * Old-school space shooter game in 2D.
 *
 * Copyright (c) 2011, Alessandro Ghedini
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 *     * Neither the name of the SpaceShooter project, Alessandro Ghedini, nor
 *       the names of its contributors may be used to endorse or promote
 *       products derived from this software without specific prior written
 *       permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>

#include <GL/glfw.h>

#include "debug.h"
#include "foes.h"
#include "player.h"
#include "sound.h"
#include "image.h"
#include "window.h"

#define FOE_MAX_SPEED		7
#define FOE_MIN_SPEED		4

#define FOE_TEXTURES_PER_SHEET	3

#define FOE_DEATH_SCORES	5
#define FOE_OVERTAKE_SCORES	-1

#define FOE_BULLET_SPEED	9

#define GEN_RAND(SEED)		rand() % SEED

typedef struct SPACESHIP {
	int x, y;
	unsigned int fired;
	unsigned int death;
	unsigned int direc;
	unsigned int speed;

	int bullet_x, bullet_y;
} spaceship_t;

spaceship_t *foes[FOES];

static unsigned int texture_sheet, bullet_texture, bullet_sample, explosion_sample;

void foes_load_data() {
	int i = 0;

	texture_sheet = tga_load("enemies.tga");
	bullet_texture = tga_load("rocket.tga");

	bullet_sample = wav_load("rocket.wav");
	explosion_sample = wav_load("explosion.wav");

	for (i = 0; i < FOES; i++) {
		foes[i]			= malloc(sizeof(spaceship_t));

		foes_reset_spaceship(i);
		foes_reset_bullet(i);
	}
}

void foes_draw() {
	int i = 0;

	float cell_division = 1.0 / FOE_TEXTURES_PER_SHEET;

	for (i = 0; i < FOES; i++) {
		float x_cell, x_cell2;

		if (!foes[i] -> death) {
			x_cell	= (
				i < FOE_TEXTURES_PER_SHEET ?
					i :
					i - FOE_TEXTURES_PER_SHEET
				) * cell_division;

			x_cell2	= x_cell + cell_division;

			glBindTexture(GL_TEXTURE_2D, texture_sheet);

			glBegin(GL_QUADS);
				glTexCoord2f(x_cell, 0.0f);
				glVertex2f(foes[i] -> x, foes[i] -> y + FOE_HEIGHT);

				glTexCoord2f(x_cell2, 0.0f);
				glVertex2f(foes[i] -> x + FOE_WIDTH, foes[i] -> y + FOE_HEIGHT);

				glTexCoord2f(x_cell2, 1.0f);
				glVertex2f(foes[i] -> x + FOE_WIDTH, foes[i] -> y);

				glTexCoord2f(x_cell, 1.0f);
				glVertex2f(foes[i] -> x, foes[i] -> y);
			glEnd();
		}

		if (foes[i] -> fired) {
			tga_draw(
				bullet_texture,
				foes[i] -> bullet_x, foes[i] -> bullet_y,
				FOE_BULLET_WIDTH, FOE_BULLET_WIDTH
			);
		}
	}
}

void foes_move_spaceship() {
	int i = 0;

	for (i = 0; i < FOES; i++) {
		if (foes[i] -> death) continue;

		if (foes[i] -> y >= (SCREEN_HEIGHT - FOE_HEIGHT))
			foes[i] -> direc = 0;
		else if (foes[i] -> y <= 0)
			foes[i] -> direc = 1;

		if (foes[i] -> direc == 0)
			foes[i] -> y--;
		else
			foes[i] -> y++;

		foes[i] -> x -= foes[i] -> speed;

		if (foes[i] -> x <= -64) {
			foes[i] -> death = 1;
			player_inc_points(FOE_OVERTAKE_SCORES);
		}
	}
}

void foes_reset_spaceship(int n) { foes[n] -> death = 1; }
void foes_reset_bullet(int n) { foes[n] -> bullet_x = -50; }

void foes_move_bullet() {
	int i, player_x, player_y;

	player_get_spaceship_coord(&player_x, &player_y);

	for (i = 0; i < FOES; i++) {
		if (!foes[i] -> fired) continue;

		foes[i] -> bullet_x -= FOE_BULLET_SPEED;

		if(player_y > foes[i] -> bullet_y)
			foes[i] -> bullet_y++;
		else
			foes[i] -> bullet_y--;

		if (foes[i] -> bullet_x <= 0)
			foes[i] -> fired = 0;
	}
}

void foes_check_collision() {
	int i, player_x, player_y, player_bullet_x, player_bullet_y;

	player_get_spaceship_coord(&player_x, &player_y);
	player_get_bullet_coord(&player_bullet_x, &player_bullet_y);

	for (i = 0; i < FOES; i++) {
		if (foes[i] -> death) continue;

		if (
			((player_bullet_x + PLAYER_BULLET_WIDTH) >= foes[i] -> x) &&
			((player_bullet_x <= (foes[i] -> x + FOE_WIDTH))) &&
			((player_bullet_y + PLAYER_BULLET_HEIGHT) >= foes[i] -> y) &&
			((player_bullet_y <= (foes[i] -> y + FOE_HEIGHT)))
		) {
			foes[i] -> death = 1;
			player_reset_bullet();

			player_inc_points(FOE_DEATH_SCORES);
			wav_play(explosion_sample);
		}
	}
}

void foes_fire_bullet() {
	int i, player_x, player_y;

	player_get_spaceship_coord(&player_x, &player_y);

	for (i = 0; i < FOES; i++) {
		if (!foes[i] -> fired && (foes[i] -> x > player_x) && !foes[i] -> death) {
			foes[i] -> bullet_x	= foes[i] -> x;
			foes[i] -> bullet_y	= foes[i] -> y + (FOE_HEIGHT / 2);
			foes[i] -> fired	= 1;

			wav_play(bullet_sample);
		}
	}
}

void foes_respawn() {
	int i = 0;

	for (i = 0; i < FOES; i++) {
		if (!foes[i] -> death) continue;

		foes[i] -> death	= 0;
		foes[i] -> x		= SCREEN_WIDTH - FOE_HEIGHT;
		foes[i] -> y		= GEN_RAND(SCREEN_HEIGHT);
		foes[i] -> speed 	= GEN_RAND(FOE_MAX_SPEED) + FOE_MIN_SPEED;
	}
}

void foes_get_spaceship_coord(int n, int *x, int *y) {
	if (n > FOES)
		return;

	*x = foes[n] -> x;
	*y = foes[n] -> y;
}

void foes_get_bullet_coord(int n, int *x, int *y) {
	if (n > FOES)
		return;

	*x = foes[n] -> bullet_x;
	*y = foes[n] -> bullet_y;
}
