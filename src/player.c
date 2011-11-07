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

#define PLAYER_WIDTH		66
#define PLAYER_HEIGHT		61

#define	PLAYER_FIRE_RATE	(1.0 / 30.0)

#define PLAYER_BULLET_WIDTH	7
#define PLAYER_BULLET_HEIGHT	7
#define PLAYER_BULLET_SPEED	12

typedef struct BULLET {
	int x, y, fired;
} bullet_t;

typedef struct SPACESHIP {
	int x, y, old_x, old_y;
	int fired;
	int health, score;
	unsigned int texture;

	bullet_t bullets[PLAYER_BULLETS];
	unsigned int bullet_texture;
	unsigned int bullet_sample;
} spaceship_t;

spaceship_t *player = NULL;

void player_load_data() {
	int i;
	player = malloc(sizeof(spaceship_t));

	player_reset_spaceship();

	for (i = 0; i < PLAYER_BULLETS; i++)
		player_reset_bullet(i);

	player -> texture = tga_load("spaceship.tga");

	player -> bullet_texture = tga_load("bullet.tga");
	player -> bullet_sample = wav_load("fire.wav");
}

void player_draw(spaceship_t *asd) {
	#define DELTA 1
	int i, n;

	int delta = player -> y - player -> old_y;

	if (delta > DELTA)		n = 1;
	else if (delta < -DELTA)	n = 2;
	else 				n = 0;

	tga_draw_from_sheet(
		player -> texture,
		player -> x, player -> y,
		PLAYER_WIDTH, PLAYER_HEIGHT,
		3, n
	);

	for (i = 0; i < PLAYER_BULLETS; i++) {
		if (player -> bullets[i].fired == 1) {
			tga_draw(
				player -> bullet_texture,
				player -> bullets[i].x, player -> bullets[i].y,
				PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT
			);
		}
	}
}

void player_move_spaceship() {
	#define SPEED	5
	int x, y;

	x = player -> x;
	y = player -> y;

	if (glfwGetKey(GLFW_KEY_UP)	== GLFW_PRESS)	y -= SPEED;
	if (glfwGetKey(GLFW_KEY_DOWN)	== GLFW_PRESS)	y += SPEED;
	if (glfwGetKey(GLFW_KEY_LEFT)	== GLFW_PRESS)	x -= SPEED;
	if (glfwGetKey(GLFW_KEY_RIGHT)	== GLFW_PRESS)	x += SPEED;

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	player -> old_x = player -> x;
	player -> old_y = player -> y;

	player -> x = x;
	player -> y = y;
}

void player_move_bullet() {
	int i;

	for (i = 0; i < PLAYER_BULLETS; i++) {
		if (player -> bullets[i].fired == 1)
			player -> bullets[i].x += PLAYER_BULLET_SPEED;

		if (player -> bullets[i].x > SCREEN_WIDTH)
			player_reset_bullet(i);
	}
}

void player_check_collision() {
	int i;

	for (i = 0; i < FOES; i++) {
		int foe_x, foe_y, foe_bullet_x, foe_bullet_y;

		foes_get_spaceship_coord(i, &foe_x, &foe_y);
		foes_get_bullet_coord(i, &foe_bullet_x, &foe_bullet_y);

		if (
			((foe_bullet_x + FOE_BULLET_WIDTH) >= player -> x) &&
			((foe_bullet_x <= (player -> x + PLAYER_WIDTH))) &&
			((foe_bullet_y + FOE_BULLET_HEIGHT) >= player -> y) &&
			((foe_bullet_y <= (player -> y + PLAYER_HEIGHT)))
		) {
			foes_reset_bullet(i);
			player -> health -= FOE_BULLET_DAMAGE;
		}

		if (
			((foe_x + FOE_WIDTH) >= player -> x) &&
			((foe_x <= (player -> x + PLAYER_WIDTH))) &&
			((foe_y + FOE_HEIGHT) >= player -> y) &&
			((foe_y <= (player -> y + PLAYER_HEIGHT)))
		) {
			foes_reset_spaceship(i);
			player -> health -= FOE_DAMAGE;
		}
	}
}

void player_fire_bullet() {
	int i;
	double new_fire;
	static double old_fire = 0;

	if (player -> fired)
		return;

	new_fire = glfwGetTime();

	if ((new_fire - old_fire) < PLAYER_FIRE_RATE)
		goto update_time;

	for (i = 0; i < PLAYER_BULLETS; i++) {
		if (player -> bullets[i].fired == 0) {
			player -> bullets[i].fired	= 1;
			player -> bullets[i].x		=
						player -> x + PLAYER_WIDTH;
			player -> bullets[i].y		=
						player -> y + (PLAYER_HEIGHT / 2);

			wav_play(player -> bullet_sample);
			break;
		}
	}

update_time:
	old_fire = new_fire;
}

void player_get_health(int *x) {
	*x = player -> health;
}

void player_get_points(int *x) {
	*x = player -> score;
}

void player_inc_points(int x) {
	player -> score += x;
}

void player_get_spaceship_coord(int *x, int *y) {
	*x = player -> x;
	*y = player -> y;
}

void player_get_bullet_coord(int n, int *x, int *y) {
	*x = player -> bullets[n].x;
	*y = player -> bullets[n].y;
}

void player_reset_spaceship() {
	player -> x		= 50;
	player -> y		= (SCREEN_HEIGHT / 2) - (PLAYER_HEIGHT / 2);
	player -> health	= 50;
	player -> fired		= 0;
	player -> score		= 0;
}

void player_reset_bullet(int n) {
	player -> bullets[n].x		= -200;
	player -> bullets[n].y		= -200;
	player -> bullets[n].fired	= 0;
}
