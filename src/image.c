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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <GL/glfw.h>

#include "config.h"
#include "debug.h"

#define IMAGE_DATA_PATH		"/graphics"

unsigned int tga_load(const char *path) {
	int err;
	GLuint texture;

	char *full_path;

	full_path = malloc(strlen(path) + strlen(IMAGE_DATA_PATH) + strlen(DATA_PATH) + 3);
	sprintf(full_path, "%s/%s/%s", DATA_PATH, IMAGE_DATA_PATH, path);

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	err = glfwLoadTexture2D(full_path, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	ok_printf("Loaded '%s'", full_path);

	return texture;
}

void tga_free(unsigned int texture) {
	return;
}

void tga_draw(unsigned int texture, int x, int y,
			unsigned int width, unsigned int height) {
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(x, y + height);

		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(x + width, y + height);

		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(x + width, y);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(x, y);
	glEnd();
}

void tga_draw_from_sheet(unsigned int texture, int x, int y,
			unsigned int width, unsigned int height, int max, int n) {

	float x_cell, x_cell2;
	float cell_division = 1.0 / max;

	x_cell	= n * cell_division;
	x_cell2	= x_cell + cell_division;

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		glTexCoord2f(x_cell, 0.0f);
		glVertex2f(x, y + height);

		glTexCoord2f(x_cell2, 0.0f);
		glVertex2f(x + width, y + height);

		glTexCoord2f(x_cell2, 1.0f);
		glVertex2f(x + width, y);

		glTexCoord2f(x_cell, 1.0f);
		glVertex2f(x, y);
	glEnd();
}
