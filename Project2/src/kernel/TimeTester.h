#pragma once

#include <iostream>
#include <vector>
#include <inc/glfw3.h>
#include <fstream> 


class TimeTester {
	
private:
	static TimeTester* INSTANCE;

	double now;
	std::string testName;
	std::vector<double> mTimes;
	
	TimeTester() {}
public:
	~TimeTester() { free(INSTANCE); }

	static TimeTester* getInstance() {
		if (INSTANCE == nullptr)
			INSTANCE = new TimeTester;
		return INSTANCE;
	}
	
	void start(const char* str) { testName = std::string(str);  now = glfwGetTime(); }
	void stop() { 
		double time = (glfwGetTime() - now); 
		mTimes.push_back(time);
		std::cout << testName.c_str() << " : " << time << std::endl; 
	}
	void save();

};