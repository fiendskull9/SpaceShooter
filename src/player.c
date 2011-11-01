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
#include "texture.h"
#include "window.h"

#define PLAYER_WIDTH		43
#define PLAYER_HEIGHT		48

#define	PLAYER_FIRE_RATE	(1.0 / 5.0)

#define PLAYER_BULLET_WIDTH	7
#define PLAYER_BULLET_HEIGHT	7
#define PLAYER_BULLET_SPEED	12

typedef struct SPACESHIP {
	int x, y;
	int fired;
	int health, score;
	unsigned int texture;

	int bullet_x, bullet_y;
	unsigned int bullet_texture;
	unsigned int bullet_sample;
} spaceship_t;

spaceship_t *player = NULL;

void player_load_data() {
	player = malloc(sizeof(spaceship_t));

	player_reset_spaceship();
	player_reset_bullet();

	player -> texture = texture_load("data/graphics/spaceship.tga");
	player -> bullet_texture = texture_load("data/graphics/bullet.tga");

	player -> bullet_sample = sample_load("data/sounds/fire.wav");
}

void player_draw(spaceship_t *asd) {
	texture_draw(
		player -> texture,
		player -> x, player -> y,
		PLAYER_WIDTH, PLAYER_HEIGHT
	);

	if (player -> fired) {
		texture_draw(
			player -> bullet_texture,
			player -> bullet_x, player -> bullet_y,
			PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT
		);
	}
}

void player_move_spaceship() {
	int x, y;

	glfwGetMousePos(&x, &y);

	if (x < 0) x = 0;
	if (y < 0) y = 0;

	player -> x = x;
	player -> y = y;
}

void player_move_bullet() {
	if (!player -> fired)
		return;

	player -> bullet_x += PLAYER_BULLET_SPEED;

	if (player -> bullet_x > SCREEN_WIDTH) {
		player -> bullet_x	= -200;
		player -> bullet_y	= -200;
		player -> fired		= 0;
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
	double new_fire;
	static double old_fire = 0;

	if (player -> fired)
		return;

	new_fire = glfwGetTime();

	if ((new_fire - old_fire) < PLAYER_FIRE_RATE)
		goto update_time;

	player -> fired		= 1;
	player -> bullet_x	= player -> x + PLAYER_WIDTH;
	player -> bullet_y	= player -> y + (PLAYER_HEIGHT / 2);

	sample_play(player -> bullet_sample);

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

void player_get_bullet_coord(int *x, int *y) {
	*x = player -> bullet_x;
	*y = player -> bullet_y;
}

void player_reset_spaceship() {
	player -> x		= 0;
	player -> y		= 0;
	player -> health	= 50;
	player -> fired		= 0;
	player -> score		= 0;
}

void player_reset_bullet() {
	player -> bullet_x = -200;
	player -> bullet_x = -200;

	player -> fired = 0;
}
