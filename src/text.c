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

#include <stdarg.h>

#include <GL/glfw.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include "debug.h"

#ifndef DATA_PATH
# define DATA_PATH ""
#endif

#define FONT_DATA_PATH		DATA_PATH "/graphics"

typedef struct CHAR {
	int		w,h;
	int		advance;
	int		left;
	int		move_up;
	unsigned char	*data;
} char_t;

static inline void move_raster_x(int x) { glBitmap(0, 0, 0, 0, x, 0, NULL); }
static inline void move_raster_y(int y) { glBitmap(0, 0, 0, 0, 0, y, NULL); }

static char_t		**chars;

static char_t **font_load(const char *path) {
	int		i;

	FT_Face		face;
	FT_Library	library;

	static char_t	*new_chars[128];

	char *full_path;

	full_path = malloc(strlen(path) + strlen(FONT_DATA_PATH) + 2);
	sprintf(full_path, "%s/%s", FONT_DATA_PATH, path);

	ok_printf("Loaded '%s'", full_path);

	FT_Init_FreeType(&library);

	FT_New_Face(library, full_path, 0, &face);
	FT_Set_Char_Size(face, 1000, 1000, 96, 96);

	for (i = 0; i < 128; i++) {
		int		w,h;
		int		advance;
		int		left;
		int		move_up;
		unsigned char	*data;

		int		x, y;
		FT_Glyph	glyph;
		FT_BitmapGlyph	bitmap_glyph;

		char_t *current_char = malloc(sizeof(char_t));

		FT_Load_Glyph(face, FT_Get_Char_Index(face, i), FT_LOAD_DEFAULT);
		FT_Get_Glyph(face -> glyph, &glyph);


		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		bitmap_glyph = (FT_BitmapGlyph) glyph;

		advance	= face -> glyph -> advance.x >> 6;
		left	= bitmap_glyph -> left;
		w	= bitmap_glyph -> bitmap.width;
		h	= bitmap_glyph -> bitmap.rows;
		move_up	= bitmap_glyph -> top - h;

		data = malloc((2 * w * h) * sizeof(unsigned char));

		for (x = 0; x < w; x++) {
			for (y = 0; y < h; y++) {
				const int my = h - 1 - y;

				data[2 * (x + w * my)] = 255;
				data[2 * (x + w * my) + 1] = bitmap_glyph -> bitmap.buffer[x + w * y];
			}
		}

		current_char -> w	= w;
		current_char -> h	= h;
		current_char -> advance	= advance;
		current_char -> left	= left;
		current_char -> move_up	= move_up;
		current_char -> data	= data;

		new_chars[i] = current_char;

		FT_Done_Glyph(glyph);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	ok_printf("Loaded '%s'", full_path);

	return new_chars;
}

/* TODO: apply texture to text */
void font_draw(int x, int y, const char *fmt, ...) {
	va_list	args;

	int	i;
	float	color[4];
	char	text[256];

	va_start(args, fmt);
	vsprintf(text, fmt, args);
	va_end(args);

	glPushAttrib(GL_CURRENT_BIT | GL_PIXEL_MODE_BIT | GL_ENABLE_BIT);

	glGetFloatv(GL_CURRENT_COLOR, color);

	glPixelTransferf(GL_RED_SCALE, color[0]);
	glPixelTransferf(GL_GREEN_SCALE, color[1]);
	glPixelTransferf(GL_BLUE_SCALE, color[2]);
	glPixelTransferf(GL_ALPHA_SCALE, color[3]);

	glRasterPos2i(x, y);

	for(i = 0; text[i]; i++) {
		const char_t *cdata = chars[(int) text[i]];

		move_raster_x(cdata -> left);
		move_raster_y(cdata -> move_up);

		glDrawPixels(
			cdata -> w, cdata -> h,
			GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE,
			cdata -> data
		);

		move_raster_y(-cdata -> move_up);
		move_raster_x(cdata -> advance - cdata -> left);
	}

	glPopAttrib();
}

void font_load_data() {
	chars = font_load("font.ttf");
}
