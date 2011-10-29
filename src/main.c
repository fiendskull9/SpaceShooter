#include <stdio.h>

#include <GL/glfw.h>

#include "player.h"
#include "window.h"

#define SCREEN_WIDTH		640
#define SCREEN_HEIGHT		480

#define ENEMY_BULLET_WIDTH 	17
#define ENEMY_BULLET_HEIGHT 	8

int main() {
	int err;
	spaceship_t *player;

	window_init(SCREEN_WIDTH, SCREEN_HEIGHT, "SpaceShooter");

	/* load data */
	player = player_load();

	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS) {
		/* rendering */
		window_clear();

		player_draw(player);

		window_swap_buf();
	}

	window_close();
}
