#include <stdio.h>

#include <GL/glfw.h>

#include "background.h"
#include "debug.h"
#include "foes.h"
#include "player.h"
#include "sound.h"
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

			foes_check_collision();
		}

		/* game rendering */
		window_clear();

		background_draw();
		foes_draw();
		player_draw();

		window_swap_buf();
	}

	window_close();
	sound_close();

	return 0;
}
