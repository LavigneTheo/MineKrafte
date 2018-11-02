#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader/BaseProgram.h"
#include "../buffer/TextureCache.h"
#include "../buffer/Mesh.h"
#include "../kernel/Camera.h"
#include "../buffer/Model.h"
#include "../kernel/TimeTester.h"

#include <iostream>
#include <vector>


class EntityManager {
private:
	BaseProgram* m_shader_program;
	std::vector<Model*> m_models;
	
	void init_shader();
	void load_models();
public:
	EntityManager();
	~EntityManager();

	void render();
	void update();
};