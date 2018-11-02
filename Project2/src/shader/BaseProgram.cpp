#include "BaseProgram.h"

void BaseProgram::get_uniforms_location() {
	add_uniform("projection");
	add_uniform("model");
	add_uniform("view");
}