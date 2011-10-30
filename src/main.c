#include <stdio.h>

#include <GL/glfw.h>

#include "background.h"
#include "foes.h"
#include "player.h"
#include "window.h"

#define ENEMY_BULLET_WIDTH 	17
#define ENEMY_BULLET_HEIGHT 	8

int main() {
	/* init */
	window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "SpaceShooter");

	/* load data */
	background_load_data();
	foes_load_data();
	player_load_data();

	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {
		/* game logic */
		background_scroll();

		player_move_spaceship();

		/* FIXME: move mouse and key check elsewhere */
		if (glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			player_fire_bullet();

		player_move_bullet();

		foes_respawn();
		foes_move_spaceship();
		foes_move_bullet();

		/* game rendering */
		window_clear();

		background_draw();
		foes_draw();
		player_draw();

		window_swap_buf();
	}

	window_close();
}
