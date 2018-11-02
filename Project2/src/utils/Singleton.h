#pragma once

class Singleton {
private:
	static Singleton* INSTANCE;

protected:
	Singleton() {}
	~Singleton() { delete INSTANCE; }
public:
	static auto* get_instance() {
		if (INSTANCE == nullptr)
			INSTANCE = new Singleton;
		return INSTANCE;
	}
};
