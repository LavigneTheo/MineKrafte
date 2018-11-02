#include "EntityManager.h"

EntityManager::EntityManager(){
	init_shader();
	load_models();
}
EntityManager::~EntityManager() {

	m_shader_program->deleteShaders();
	m_shader_program->stop();

	for (unsigned int i = 0; i < m_models.size(); i++)
		delete m_models.at(i);

	delete m_shader_program;
}

void EntityManager::render() {
	m_shader_program->start();

	m_shader_program->load_mat4x4("view", *Camera::get_instance()->get_view_matrix());
	
	for (unsigned int i = 0; i < m_models.size(); i++) {
		m_shader_program->load_mat4x4("model", *(*m_models[i]).get_model_matrix());
		(*m_models.at(i)).draw();
	}

	m_shader_program->stop();
}
void EntityManager::update() {

}

void EntityManager::init_shader() {
	m_shader_program = new BaseProgram;
	m_shader_program->addVertexShader("shader/base/VS.glsl");
	m_shader_program->addFragmentShader("shader/base/FS.glsl");
	m_shader_program->linkProgram();
	m_shader_program->get_uniforms_location();

	m_shader_program->start();
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)1400 / (float)1050, 0.1f, 1000.f);
	m_shader_program->load_mat4x4("projection", proj);
	m_shader_program->stop();
}

void EntityManager::load_models() {
	m_models.push_back(new Model("res/nano/nanosuit.obj"));
	m_models.at(0)->set_position(glm::vec3(20, 0, -40));

	//m_models.push_back(new Model("res/carac/minecraft-jess.obj"));
	//m_models.at(4)->set_position(glm::vec3(30, 0, -23));

}
