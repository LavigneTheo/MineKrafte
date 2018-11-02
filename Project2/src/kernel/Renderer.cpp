#include "Renderer.h"

Renderer::Renderer() {
	
}
Renderer::~Renderer() {

}

void Renderer::render() {

	m_terrain_manager.draw();
	m_entity_manager.render();

}
void Renderer::update() {

	m_entity_manager.update();
}