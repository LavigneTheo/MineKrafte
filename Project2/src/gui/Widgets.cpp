#pragma once
#include "Widgets.h"
#include "GuiRenderer.h"



Widget::Widget(GuiRenderer* gui_renderer) : m_gui_renderer(gui_renderer) {}

/******************************* Option ******************************************/

WOption::WOption(GuiRenderer* gui_renderer, int* fps, bool* pause)
	: Widget(gui_renderer), m_pause(pause), m_fps(fps) {}

void WOption::update() {
	ImGui::Begin("Options");

	ImGui::Checkbox("Depth Test", &m_depth_test);
	ImGui::SameLine();
	ImGui::Checkbox("Pause", m_pause);

	ImGui::Checkbox("Cull face", &m_cull_face);
	ImGui::Checkbox("Polygon mode", &m_polygon_mode);

	if (m_polygon_mode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (m_cull_face)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (m_depth_test)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	ImGui::Text("FPS : ");
	ImGui::SameLine();
	ImGui::SliderInt("", m_fps, 1, 100);            // Edit 1 float using a slider from 0.0f to 1.0f
	//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color



	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Number of chunk vertices :%d", TerrainManager::vertexCount);

	ImGui::End();
}

WCamera::WCamera(GuiRenderer* gui_renderer)
	: Widget(gui_renderer){

}

void WCamera::update() {

	ImGui::Begin("Camera");

	ImGui::Text("Position : [%.3f, %.3f, %.3f]", m_gui_renderer->get_camera()->get_position()->x, -m_gui_renderer->get_camera()->get_position()->y, m_gui_renderer->get_camera()->get_position()->z);
	ImGui::Text("Rotation : [%.3f, %.3f, %.3f]",
		acosf(cosf(m_gui_renderer->get_camera()->get_rotation()->x * M_PI / 180)) / M_PI * 180,
		acosf(cosf(m_gui_renderer->get_camera()->get_rotation()->y * M_PI / 180)) / M_PI * 180,
		acosf(cosf(m_gui_renderer->get_camera()->get_rotation()->z * M_PI / 180)) / M_PI * 180
	);

	ImGui::Text("Movement speed (s) :     ");
	ImGui::SameLine();
	ImGui::PushItemWidth(100);
	ImGui::SliderFloat("", m_gui_renderer->get_camera()->get_movement_speed(), 5, 100);

	ImGui::Text("Rotation speed (deg/s) : ");
	ImGui::SameLine();
	ImGui::PushItemWidth(100);
	ImGui::SliderFloat(" ", m_gui_renderer->get_camera()->get_rotation_speed(), 5, 100);

	ImGui::End();
}


WPerlin2D::WPerlin2D(GuiRenderer* gui_renderer)
	: Widget(gui_renderer) {
}

void WPerlin2D::update() {
	ImGui::Begin("Perlin noise 2D");
	
	static ImGuiComboFlags flags = 0;


	// General BeginCombo() API, you have full control over your selection data and display type.
	// (your selection data could be an index, a pointer to the object, an id for the object, a flag stored in the object itself, etc.)
	const char* methods[] = { "Array (128 max)", "Hash table", "Hash table + gradient" };
	static const char* current_method = methods[0];
	
	ImGui::Text("Method : ");
	ImGui::SameLine();
	ImGui::PushItemWidth(200);
	if (ImGui::BeginCombo("", current_method, flags)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < IM_ARRAYSIZE(methods); n++)
		{
			bool is_selected = (current_method == methods[n]);
			if (ImGui::Selectable(methods[n], is_selected))
				current_method = methods[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		ImGui::EndCombo();
	}
	ImGui::SameLine();


	const char* modes[] = { "Linear", "Cosine", "Smoothstep" };
	static const char* current_mode = modes[0];

	ImGui::Text("Mode : ");
	ImGui::SameLine();
	
	ImGui::PushItemWidth(200);
	if (ImGui::BeginCombo(" ", current_mode, flags)) // The second parameter is the label previewed before opening the combo.
	{
		for (int n = 0; n < IM_ARRAYSIZE(modes); n++)
		{
			bool is_selected = (current_mode == modes[n]);
			if (ImGui::Selectable(modes[n], is_selected))
				current_mode = modes[n];
			if (is_selected)
				ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
		}
		ImGui::EndCombo();
	}

	//
	ImGui::Columns(3);
	ImGui::SetColumnWidth(0, 100);
	ImGui::Text("Size :   %d", m_size);
	

	ImGui::NextColumn();
	ImGui::SetColumnWidth(1, 52);

	if (ImGui::Button("+"))
		if(m_size < 2048)
			m_size *= 2;
	ImGui::SameLine();
	if (ImGui::Button("-"))
		if(m_size > 2)
			m_size /= 2;
	
	ImGui::NextColumn();
	ImGui::Text("Ratio :   %.4f", m_ratio);
	ImGui::SameLine();
	ImGui::SliderFloat("  ", &m_ratio, 1
		, 100);
	ImGui::Columns(1);

	if (ImGui::Button("See"))
		std::cout << "To do :)" << std::endl;

	ImGui::SameLine();
	if (ImGui::Button("Save image (.ppm)"))
		std::cout << "To do :)" << std::endl;
	ImGui::SameLine();
	if (ImGui::Button("Save data (.txt)")) {
		test = BrowseFolder("");
		
	}
	ImGui::Text("Path : %s", test.c_str());
		

	ImGui::End();
}

