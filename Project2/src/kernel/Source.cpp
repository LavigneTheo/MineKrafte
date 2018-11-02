#include <inc/glew.h>
#include <inc/glfw3.h>
#include <iostream>
#include <math.h>
#include "Window.h"
#include "Renderer.h"
#include "../gui/GuiRenderer.h"
#include "../utils/algo/Perlin2D.h"
#include "TimeTester.h"

TimeTester* TimeTester::INSTANCE = nullptr;

int main(void)
{

	Window* window = Window::get_instance();
	window->build(1400, 1050, false);

	Camera* camera = Camera::get_instance();
	camera->setPosition(0, 11, 0);

	Renderer renderer;
	TextureCache* texture_cache = TextureCache::getInstance();
	

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.2f, 0.2f, 1);

	double time = glfwGetTime();

	double now = time;
	double last_time = time, delta = 0, timer = 0, last_tick = time;
	int tick = 0;
	int fps = 30;

	bool pause = false;
	
	GuiRenderer gui_renderer(camera, window, &fps, &pause);

	int count = 0;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window->get_GLFWWindow()))
	{
		now = glfwGetTime();
		delta += (now - last_time) * fps;
		last_time = now;

		if (delta >= 1.0f) {
			delta--;

			if (!pause) {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				camera->update(last_time - last_tick);

				renderer.update();
				renderer.render();
			}

			gui_renderer.update(fps, pause);
			
			gui_renderer.render();

			last_tick = last_time;
			tick++;
			if (last_time - timer >= 1.0f) {
				timer = last_time;
				tick = 0;
			}
			if(!pause)
				glfwSwapBuffers(window->get_GLFWWindow());

			glfwPollEvents();
		}

			
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	TimeTester::getInstance()->save();
	return 0;
}