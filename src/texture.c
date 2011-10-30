#include <GL/glfw.h>

#include "debug.h"

unsigned int texture_load(const char *path) {
	int err;
	GLuint texture;

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	err = glfwLoadTexture2D(path, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	return texture;
}

void texture_free(unsigned int texture) {
	return;
}

void texture_draw(unsigned int texture, int x, int y,
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
