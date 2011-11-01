#include <stdio.h>

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

#include <GL/glfw.h>

#include "background.h"
#include "debug.h"
#include "foes.h"
#include "player.h"
#include "sound.h"
#include "text.h"
#include "texture.h"
#include "window.h"

#define	UPDATE_RATE (1.0 / 120.0)

int main() {
	double old_time;
	static unsigned int game_status = 0;

	unsigned int title_texture, gameover_sample;

	/* init */
	window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "SpaceShooter");

	sound_init();

	/* load data */
	background_load_data();
	foes_load_data();
	player_load_data();
	font_load_data();

	title_texture = texture_load("data/graphics/title.tga");
	gameover_sample = sample_load("data/sounds/gameover.wav");

	old_time = glfwGetTime();

	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {
		double new_time = glfwGetTime();

		/* game rendering */
		window_clear();

		background_draw();

		switch (game_status) {
			case 0: {
				texture_draw(title_texture, 50, 200, 550, 46);
				font_draw(175, 450, "Press FIRE to start");

				if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
					game_status = 1;

				break;
			}

			case 1: {
				foes_draw();
				player_draw();

				{
					int health, points;

					player_get_health(&health);
					player_get_points(&points);

					font_draw(10, 20, "Health: %d", health);
					font_draw(10, 40, "Points: %d", points);
				}

				break;
			}

			default: { break; }
		}

		window_swap_buf();

		if ((new_time - old_time) >= UPDATE_RATE) {
			old_time = new_time;

			/* game logic */
			background_scroll();

			if (game_status < 1) continue;

			player_move_spaceship();

			/* FIXME: move mouse and key check elsewhere */
			if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				player_fire_bullet();

			player_move_bullet();

			foes_respawn();
			foes_move_spaceship();
			foes_fire_bullet();
			foes_move_bullet();

			player_check_collision();
			foes_check_collision();
		}

		{
			int health;

			player_get_health(&health);

			if (health <= 0) {
				game_status = 0;
				sample_play(gameover_sample);
				player_reset_spaceship();
			}
		}
	}

	window_close();
	sound_close();

	return 0;
}
