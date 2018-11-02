#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <inc/glew.h>
#include <math.h>
#include "../kernel/Camera.h"
#include "../kernel/Window.h"
#include "Widgets.h"
#include <iostream>
#include <vector>

class GuiRenderer {
private:
	Camera* m_camera;
	Window* m_window;

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	float f = 0.0f;
	
	std::vector<Widget*> m_widgets;
public:

	GuiRenderer(Camera* camera, Window* window, int* fps, bool* pause);
	~GuiRenderer();

	void update(int& fps, bool& pause);
	void render();

	Camera* get_camera() const;

	//std::vector<Widget*> get_widgets();
	//std::vector<Widget*> add_widget(const Widget* widget);
};


