#include <GL/glfw.h>

#include "debug.h"

void window_init(int width, int height, const char *title) {
	int err;

	err = glfwInit();

	err = glfwOpenWindow(width, height, 8, 8, 8, 8, 0, 0, GLFW_WINDOW);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);

	glfwDisable(GLFW_MOUSE_CURSOR);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glfwSetWindowTitle(title);
}

void window_clear() {
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void window_swap_buf() {
	glfwSwapBuffers();
}

void window_close() {
	glfwCloseWindow();
	glfwTerminate();
}
