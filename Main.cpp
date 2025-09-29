// This code creates a window with GLAD and GLFW
// It's a bit of a robust code

#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "PixelEngine.h"

static void glfw_error_callback(int code, const char* desc) {
	std::fprintf(stderr, "[GLFW error %d] %s\n", code, desc);
}

static void framebuffer_size_callback(GLFWwindow* win, int w, int h) {
	(void)win;
	glViewport(0, 0, w, h);
	std::fprintf(stderr, "[INFO] Reasize: %dx%d\n", w, h);
}

static void window_close_callback(GLFWwindow* w) {
	std::fprintf(stderr, "[INFO] Close requested\n");
	glfwSetWindowShouldClose(w, 1);
}

int main() {
	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit()) {
		std::fprintf(stderr, "[FATAL] glfwInit failed\n");
		return 2;
	}

	// Context 3.3 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Pixel Engine", nullptr, nullptr);
	if (!window) {
		std::fprintf(stderr, "[FATAL] glfwCreateWindow failed\n");
		glfwTerminate();
		return 3;
	}
	std::fprintf(stderr, "[INFO] Window created\n");

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // vsync

	// load OpenGL function pointers via GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::fprintf(stderr, "[FATAL] gladLoadGLLoader failed\n");
		glfwDestroyWindow(window);
		glfwTerminate();
		return 4;
	}
	std::fprintf(stderr, "[INFO] Gl loaded: %s, vendor: %s\n", glGetString(GL_VERSION), glGetString(GL_VENDOR));

	// initial viewport and resize callback
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowCloseCallback(window, window_close_callback);

	// main loop - keeps the window alive
	while (!glfwWindowShouldClose(window)) {
		// Example: ESC closes
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			std::fprintf(stderr, "[INFO] Esc pressed -> closing\n");
			glfwSetWindowShouldClose(window, 1);
		}

		glClearColor(0.12f, 0.15f, 0.22f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window); // NEED
		glfwPollEvents(); // NEED
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
