#include "ShaderProgram.h"


ShaderProgram::ShaderProgram() {
	m_progam_id = glCreateProgram();
}

unsigned int ShaderProgram::load_shader(const char* file_path, const unsigned int shader_type) {
	using namespace std;

	string line;
	string res;
	ifstream myfile;
	myfile.open(file_path);

	if (!myfile.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}

	while (getline(myfile, line))
		res.append(line).append("\n");
	myfile.close();
 
	unsigned int shader_id = glCreateShader(shader_type);

	const char* content = res.c_str();

	glShaderSource(shader_id, 1, &content, NULL);
	glCompileShader(shader_id);


	int  success;
	char infoLog[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader_id;
}

void ShaderProgram::addVertexShader(const char* const file_path) {
	
	unsigned int shader_id = load_shader(file_path, GL_VERTEX_SHADER);
	m_shaderIds.emplace(GL_VERTEX_SHADER, shader_id);
	glAttachShader(m_progam_id, shader_id);

}

void ShaderProgram::addFragmentShader(const char* const file_path) {

	unsigned int shader_id = load_shader(file_path, GL_FRAGMENT_SHADER);
	m_shaderIds.emplace(GL_FRAGMENT_SHADER, shader_id);
	glAttachShader(m_progam_id, shader_id);

}

void ShaderProgram::linkProgram() const {
	glLinkProgram(m_progam_id);

	int  success;
	char infoLog[512];
	glGetProgramiv(m_progam_id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(m_progam_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glValidateProgram(m_progam_id);
	glGetProgramiv(m_progam_id, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_progam_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void ShaderProgram::start() const {
	glUseProgram(m_progam_id);
}
void ShaderProgram::stop() const {
	glUseProgram(0);
}

void ShaderProgram::deleteShaders() {
	for (const auto& shader : m_shaderIds)
		glDeleteShader(shader.second);
}

void ShaderProgram::add_uniform(const char* uniform_name) {
	int uniform_location = glGetUniformLocation(m_progam_id, uniform_name);
	std::string str = uniform_name;
	m_uniforms.emplace(str, uniform_location);
}

void ShaderProgram::load_vec3f(const std::string& uniform_name, const glm::vec3& v) {
	glUniform3f(m_uniforms.at(uniform_name), v.x, v.y, v.z);
}

void ShaderProgram::load_mat4x4(const std::string& uniform_name, const glm::mat4x4& mat) const {
	glUniformMatrix4fv(m_uniforms.at(uniform_name), 1, GL_FALSE, glm::value_ptr(mat));
}