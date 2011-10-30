#include <stdlib.h>

#include "texture.h"
#include "window.h"

#define BACKGROUND_WIDTH	1280
#define BACKGROUND_HEIGHT	480

#define BACKGROUND_SCROLL_SPEED	2

typedef struct SPACESHIP {
	int xscroll;
	unsigned int texture;
} background_t;

background_t *background = NULL;

void background_load_data() {
	background = malloc(sizeof(background_t));

	background -> xscroll	= 0;
	background -> texture	= texture_load("data/graphics/background.tga");
}

void background_draw() {
	texture_draw(
		background -> texture,
		background -> xscroll, 0,
		BACKGROUND_WIDTH, BACKGROUND_HEIGHT
	);

	texture_draw(
		background -> texture,
		background -> xscroll + BACKGROUND_WIDTH, 0,
		BACKGROUND_WIDTH, BACKGROUND_HEIGHT
	);
}

void background_scroll() {
	if (background -> xscroll <= -BACKGROUND_WIDTH)
		background -> xscroll = 0;

	background -> xscroll -= BACKGROUND_SCROLL_SPEED;
}
