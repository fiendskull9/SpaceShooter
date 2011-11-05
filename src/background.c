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

#include "image.h"
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
	background -> texture	= tga_load("background.tga");
}

void background_draw() {
	tga_draw(
		background -> texture,
		background -> xscroll, 0,
		BACKGROUND_WIDTH, BACKGROUND_HEIGHT
	);

	tga_draw(
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
