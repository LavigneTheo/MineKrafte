#include "GuiRenderer.h"


GuiRenderer::GuiRenderer(Camera* camera, Window* window, int* fps, bool* pause) : 
	m_camera(camera), m_window(window) {
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->get_GLFWWindow(), false);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	m_widgets.push_back((Widget*)new WOption(this, fps, pause));
	m_widgets.push_back((Widget*)new WCamera(this));
	m_widgets.push_back((Widget*)new WPerlin2D(this));
}

GuiRenderer::~GuiRenderer() {
	for (int i = 0; i < m_widgets.size(); i++)
		free(m_widgets.at(i));
}

void GuiRenderer::update(int& fps, bool& pause) {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < m_widgets.size(); i++)
		m_widgets.at(i)->update();
	
}

void GuiRenderer::render() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Camera* GuiRenderer::get_camera() const {
	return m_camera;
}