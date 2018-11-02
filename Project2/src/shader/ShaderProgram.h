#pragma once
#include <inc/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
	private:
		unsigned int m_progam_id;
		std::map<int, unsigned int> m_shaderIds;
		std::map<std::string, unsigned> m_uniforms;

		unsigned int load_shader(const char* file_path, const unsigned int shader_type);

	protected:
		
	public:
		ShaderProgram();

		void addVertexShader(const char* const file_path);
		void addFragmentShader(const char* const file_path);
		void linkProgram() const;

		void start() const;
		void stop() const;
		void deleteShaders();

		//uniform
		void add_uniform(const char* uniform_name);
		void load_vec3f(const std::string& uniform_name, const glm::vec3& v);
		void load_mat4x4(const std::string& uniform_name, const glm::mat4x4& mat) const;

		virtual void get_uniforms_location() = 0;
};