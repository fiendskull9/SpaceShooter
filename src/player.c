#include <stdlib.h>

#include <GL/glfw.h>

#include "player.h"
#include "texture.h"

#define PLAYER_WIDTH 		43
#define PLAYER_HEIGHT 		48

spaceship_t *player_load() {
	spaceship_t *player = malloc(sizeof(player));

	player -> x	= 0;
	player -> y	= 0;
	player -> health	= 50;

	player -> texture = texture_load("/tmp/spaceshooter/spaceship.tga");

	return player;
}

void player_draw(spaceship_t *player) {
	int x, y;

	glfwGetMousePos(&x, &y);
	texture_draw(player -> texture, x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}
