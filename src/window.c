#include <GL/glfw.h>

void window_init(int width, int height, const char *title) {
	int err;

	err = glfwInit();

	err = glfwOpenWindow(width, height, 8, 8, 8, 8, 0, 0, GLFW_WINDOW);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 0, 1);

	glDisable(GL_DEPTH_TEST);
	glfwDisable(GLFW_MOUSE_CURSOR);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
