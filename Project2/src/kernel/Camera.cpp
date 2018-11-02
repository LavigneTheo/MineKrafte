#include "Camera.h"

Camera* Camera::INSTANCE = nullptr;


Camera::Camera() {
	m_position = glm::vec3(0, 6, 0);
	m_rotation = glm::vec3(0, 0, 0);
	m_view = glm::mat4(1);
}

void Camera::update(const double& elapsed_time) {
	bool* key_pressed = Window::get_instance()->get_key_pressed();
	bool hasMoved = false;
	float move_distance = 0, y_rotation = 0, x_rotation = 0, y_distance = 0;

	if (key_pressed[GLFW_KEY_W])
		move_distance = elapsed_time * m_movement_speed;
	if(key_pressed[GLFW_KEY_S])
		move_distance = -elapsed_time * m_movement_speed;
	if (key_pressed[GLFW_KEY_D])
		y_rotation = -elapsed_time * m_rotation_speed;
	if(key_pressed[GLFW_KEY_A])
		y_rotation = elapsed_time * m_rotation_speed;
	if(key_pressed[GLFW_KEY_R])
		x_rotation = elapsed_time * m_rotation_speed;
	if(key_pressed[GLFW_KEY_T])
		x_rotation = -elapsed_time * m_rotation_speed;
	if (key_pressed[GLFW_KEY_LEFT_SHIFT])
		y_distance = -elapsed_time * m_movement_speed;
	if (key_pressed[GLFW_KEY_SPACE])
		y_distance = elapsed_time * m_movement_speed;

	m_rotation.x += x_rotation;
	m_rotation.y += y_rotation;
	
	float x_move = 0, z_move = 0;
	x_move = sinf(m_rotation.y * (float)M_PI / 180) * move_distance;
	z_move = cosf(m_rotation.y * (float)M_PI / 180) * move_distance;
	
	if (x_move != 0 || z_move != 0)
		hasMoved = true;

	m_position.x += -x_move;
	m_position.y += y_distance;
	m_position.z -= z_move;


	if (hasMoved)
		for (CameraSubscriber* cs : mSubscribers)
			cs->onCameraMove();

	if (key_pressed[GLFW_KEY_ESCAPE])
		Window::get_instance()->close();
}

void Camera::move(const float z_displacement) {
	m_position.z += z_displacement;
}
void Camera::rotate_x(const float x_rotation) {
	m_rotation.x += x_rotation;
	
}
void Camera::rotate_y(const float y_rotation) {
	m_rotation.y += y_rotation;
}

Camera* Camera::get_instance() {
	if (INSTANCE == nullptr)
		INSTANCE = new Camera;
	return INSTANCE;
}

Camera::~Camera() {
	delete INSTANCE;
}

glm::mat4* Camera::get_view_matrix() {
	m_view = glm::mat4(1.0);
	m_view = glm::rotate(m_view, -m_rotation.x * (float)M_PI / 180, glm::vec3(1.0f, .0f, .0f));
	m_view = glm::rotate(m_view, -m_rotation.y * (float)M_PI / 180, glm::vec3(0.0f, 1.0f, .0f));
	m_view = glm::translate(m_view, -m_position);
	return &m_view;
}

glm::vec3* Camera::get_position(){
	return &m_position;
}

glm::vec3* Camera::get_rotation(){
	return &m_rotation;
}

float* Camera::get_movement_speed() {
	return &m_movement_speed;
}
float* Camera::get_rotation_speed() {
	return &m_rotation_speed;
}

void Camera::set_movement_speed(const float& speed) {
	m_movement_speed = speed;
}
void Camera::set_rotation_speed(const float& speed) {
	m_rotation_speed = speed;
}

void Camera::setPosition(const float& x, const float& y, const float& z) {
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}
