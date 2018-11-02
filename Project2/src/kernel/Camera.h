#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "Window.h"

#define _USE_MATH_DEFINES
#include <math.h>

class CameraSubscriber;

class Camera {
private:
	static Camera* INSTANCE;
	glm::mat4 m_view;
	glm::vec3 m_rotation;
	glm::vec3 m_position;

	float m_movement_speed = 10, m_rotation_speed = 70;

	Camera();

	std::vector<CameraSubscriber*> mSubscribers;
public:
	
	static Camera* get_instance();
	void subscribe(CameraSubscriber* cs) {
		mSubscribers.push_back(cs);
	}

	void move(const float z_displacement);
	void rotate_x(const float x_rotation);
	void rotate_y(const float y_rotation);

	void update(const double& elapsed_time);

	glm::vec3* get_position() ;
	glm::vec3* get_rotation() ;
	glm::mat4* get_view_matrix();

	float* get_movement_speed() ;
	float* get_rotation_speed() ;

	void set_movement_speed(const float& speed);
	void set_rotation_speed(const float& speed);
	void setPosition(const float& x, const float& y, const float& z);

	~Camera();
	
};

class CameraSubscriber {
protected:
	Camera* mCamera = Camera::get_instance();
	~CameraSubscriber() {}
	CameraSubscriber() {
		Camera::get_instance()->subscribe(this);
	}
public:
	virtual void onCameraMove() = 0;
	
};
