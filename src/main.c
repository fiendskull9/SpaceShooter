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
#include "window.h"

#define	UPDATE_RATE (1.0 / 120.0)

int main() {
	double old_time;

	/* init */
	window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "SpaceShooter");

	sound_init();

	/* load data */
	background_load_data();
	foes_load_data();
	player_load_data();
	font_load_data();

	old_time = glfwGetTime();

	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {
		double new_time = glfwGetTime();

		if ((new_time - old_time) >= UPDATE_RATE) {
			old_time = new_time;

			/* game logic */
			background_scroll();

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

		/* game rendering */
		window_clear();

		background_draw();
		foes_draw();
		player_draw();

		font_draw(50, 50, "asd: %d", 5);

		window_swap_buf();
	}

	window_close();
	sound_close();

	return 0;
}
