#pragma once

#include <iostream>
#include <inc/glfw3.h>

class TimeTester {
	
private:
	double now;
	std::string testName;
public:
	void start(std::string name) { now = glfwGetTime(); testName = name; }
	void stop() { std::cout << testName.c_str() << " : " << (glfwGetTime() - now) << std::endl; }
};