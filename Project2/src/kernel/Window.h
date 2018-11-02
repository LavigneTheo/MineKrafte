#pragma once
#include <inc/glew.h>
#include <inc/glfw3.h>
#include <iostream>
#include "Camera.h"

class Window
{
	private:
		GLFWwindow* m_window;
		int WIDTH, HEIGHT;
		static bool m_key_pressed[500];

		static Window* INSTANCE;

		Window() {}
	public:
		void build(const int& width, const int& height, const bool& fullScreen);

		GLFWwindow* get_GLFWWindow() const;

		const int getHeight() const;
		const int getWidth() const;
		
		static Window* get_instance();
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		bool* get_key_pressed() const;
		void close() {
			glfwSetWindowShouldClose(m_window, true);
		}

		~Window();
};
