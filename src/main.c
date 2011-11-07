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
#include "image.h"
#include "window.h"

#define	UPDATE_RATE (1.0 / 120.0)

enum game_status_t {
	START,
	COUNTDOWN,
	RUN,
	PAUSE,
	GAMEOVER
};

int main() {
	double old_time;

	enum game_status_t game_status = START;
	unsigned int game_record = 0, title_texture, pause_sample, gameover_sample;

	/* init */
	window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "SpaceShooter");

	sound_init();

	/* load data */
	background_load_data();
	foes_load_data();
	player_load_data();
	font_load_data();

	title_texture = tga_load("title.tga");
	pause_sample = wav_load("pause.wav");
	gameover_sample = wav_load("gameover.wav");

	old_time = glfwGetTime();

	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {
		int health;
		double new_time = glfwGetTime();

		static int paused_x, paused_y;

		/* game rendering */
		window_clear();

		background_draw();

		switch (game_status) {
			case START: {
				tga_draw(title_texture, 50, 200, 550, 46);
				font_draw(175, 450, "Press S to start");

				if (glfwGetKey('S') == GLFW_PRESS) {
					game_status = COUNTDOWN;
					glfwDisable(GLFW_MOUSE_CURSOR);
				}

				/* TODO: implement diffent difficulty levels */

				break;
			}

			case COUNTDOWN: {
				double new_time;

				static int counter_state = 4;
				static double old_time = 0.0;

				new_time = glfwGetTime();

				if ((new_time - old_time) >= 1.0) {
					counter_state--;
					old_time = new_time;
				}

				if (counter_state == 0) {
					game_status = RUN;
					counter_state = 4;
				} else font_draw(320, 240, "%d", counter_state);

				break;
			}

			case RUN: {
				int health, points;

				foes_draw();
				player_draw();

				player_get_health(&health);
				player_get_points(&points);

				font_draw(10, 20, "Health: %d", health);
				font_draw(10, 40, "Points: %d", points);
				font_draw(10, 60, "Record: %d", game_record);

				if (glfwGetKey('P') == GLFW_PRESS) {
					wav_play(pause_sample);
					game_status = PAUSE;
					glfwGetMousePos(&paused_x, &paused_y);
				}

				break;
			}

			case PAUSE: {
				font_draw(175, 450, "Press S to start");

				foes_draw();
				player_draw();

				if (glfwGetKey('S') == GLFW_PRESS) {
					game_status = RUN;
					glfwSetMousePos(paused_x, paused_y);
				}

				break;
			}

			case GAMEOVER: {
				int i, points;

				player_get_points(&points);

				font_draw(195, 250, "Final score: %d", points);
				font_draw(175, 450, "Press S to restart");

				if (points > game_record) font_draw(205, 220, "New record!!!");

				if (glfwGetKey('S') != GLFW_PRESS)
					break;

				if (points > game_record) game_record = points;

				player_reset_spaceship();
				player_reset_bullet();

				for (i = 0; i < FOES; i++) {
					foes_reset_spaceship(i);
					foes_reset_bullet(i);
				}

				game_status = COUNTDOWN;
			}

			default: { }
		}

		window_swap_buf();

		if ((new_time - old_time) >= UPDATE_RATE) {
			old_time = new_time;

			/* game logic */
			background_scroll();

			if (game_status != RUN) continue;

			player_move_spaceship();

			if (glfwGetKey('Z') == GLFW_PRESS)
				player_fire_bullet();

			player_move_bullet();

			foes_respawn();
			foes_move_spaceship();
			foes_fire_bullet();
			foes_move_bullet();

			player_check_collision();
			foes_check_collision();
		}

		player_get_health(&health);

		if ((health <= 0) && (game_status == RUN)) {
			game_status = GAMEOVER;
			wav_play(gameover_sample);
		}
	}

	window_close();
	sound_close();

	return 0;
}
