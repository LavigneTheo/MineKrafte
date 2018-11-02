#pragma once
#include "Widgets.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <inc/glew.h>
#include <math.h>
#include "../kernel/Camera.h"
#include "../kernel/Window.h"
#include <iostream>
#include <iostream>
#include "Utils.h"
#include "../manager/TerrainManager.h"


class GuiRenderer;

class Widget {
protected:
	GuiRenderer* m_gui_renderer;
	Widget(GuiRenderer* gui_renderer);
public:

	virtual void update() = 0;
};

class WOption : Widget {
private:
	bool m_depth_test = true,
		m_cull_face = true,
		m_polygon_mode = false;
	bool* m_pause;
	int* m_fps;

public:
	WOption(GuiRenderer* gui_renderer, int* fps, bool* pause);
	void update();
};

class WCamera : Widget {
private:

public:
	WCamera(GuiRenderer* gui_renderer);
	void update();
};

class WPerlin2D : Widget {
private:
	int m_size = 2;
	float m_ratio;
	std::string test;
public:
	WPerlin2D(GuiRenderer* gui_renderer);
	void update();
};

