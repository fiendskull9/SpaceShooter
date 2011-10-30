#include <stdlib.h>

#include <GL/glfw.h>

#include "texture.h"
#include "window.h"

#define PLAYER_WIDTH 		43
#define PLAYER_HEIGHT 		48

#define PLAYER_BULLET_WIDTH 	7
#define PLAYER_BULLET_HEIGHT 	7
#define PLAYER_BULLET_SPEED 	12

typedef struct SPACESHIP {
	int x, y;
	int fire;
	int health;
	unsigned int texture;


	int bullet_x, bullet_y;
	unsigned int bullet_texture;
} spaceship_t;

spaceship_t *player = NULL;

void player_load_data() {
	player = malloc(sizeof(spaceship_t));

	player -> x		= 0;
	player -> y		= 0;
	player -> health	= 50;
	player -> fire		= 0;

	player -> texture = texture_load("data/graphics/spaceship.tga");
	player -> bullet_texture = texture_load("data/graphics/bullet.tga");

	player -> bullet_x = -200;
	player -> bullet_y = -200;
}

void player_draw(spaceship_t *asd) {
	texture_draw(
		player -> texture,
		player -> x, player -> y,
		PLAYER_WIDTH, PLAYER_HEIGHT
	);

	if (player -> fire) {
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
	if (!player -> fire)
		return;

	player -> bullet_x += PLAYER_BULLET_SPEED;

	if (player -> bullet_x > SCREEN_WIDTH) {
		player -> bullet_x	= -200;
		player -> bullet_y	= -200;
		player -> fire		= 0;
	}
}

void player_fire_bullet() {
	if (player -> fire)
		return;

	player -> fire		= 1;
	player -> bullet_x	= player -> x + PLAYER_WIDTH;
	player -> bullet_y	= player -> y + (PLAYER_HEIGHT / 2);

	/* play_sample(player.snd_fire, 255,128,1000, FALSE); */
}

void player_get_coord(int *x, int *y) {
	*x = player -> x;
	*y = player -> y;
}
