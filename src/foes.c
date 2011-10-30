#include <stdlib.h>

#include <GL/glfw.h>

#include "debug.h"
#include "foes.h"
#include "player.h"
#include "sound.h"
#include "texture.h"
#include "window.h"

#define FOE_WIDTH		57
#define FOE_HEIGHT		40
#define FOE_MAX_SPEED		7
#define FOE_MIN_SPEED		4

#define FOE_TEXTURES_PER_SHEET	3

#define FOE_DEATH_SCORES	5
#define FOE_OVERTAKE_SCORES	-1

#define FOE_DAMAGE		10
#define FOE_BULLET_DAMAGE	2

#define FOE_BULLET_WIDTH	17
#define FOE_BULLET_HEIGHT	8
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

static unsigned int texture_sheet, bullet_texture, bullet_sample;

void foes_load_data() {
	int i = 0;

	texture_sheet = texture_load("data/graphics/enemies.tga");
	bullet_texture = texture_load("data/graphics/rocket.tga");

	bullet_sample = sample_load("data/sounds/rocket.wav");

	for (i = 0; i < FOES; i++) {
		foes[i]			= malloc(sizeof(spaceship_t));
		foes[i] -> fired	= 0;
		foes[i] -> death	= 1;
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
			texture_draw(
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

			/* TODO: score += FOE_OVERTAKE_SCORES */
		}
	}
}

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
			/* TODO: score += ENEMY_DEATH_SCORES; */

			foes[i] -> death = 1;
			player_reset_bullet();

			/* TODO: play_sample */
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

			sample_play(bullet_sample);
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

void foes_get_spaceship_coord(int *x, int *y) {
	int i, arx[FOES], ary[FOES];

	for (i = 0; i < FOES; i++) {
		arx[i] = foes[i] -> x;
		ary[i] = foes[i] -> y;
	}

	x = arx;
	y = ary;
}

void foes_get_bullet_coord(int *x, int *y) {
	int i, arx[FOES], ary[FOES];

	for (i = 0; i < FOES; i++) {
		arx[i] = foes[i] -> bullet_x;
		ary[i] = foes[i] -> bullet_y;
	}

	x = arx;
	y = ary;
}
