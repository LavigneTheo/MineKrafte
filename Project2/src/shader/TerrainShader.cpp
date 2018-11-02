#include"TerrainShader.h"

void TerrainShader::get_uniforms_location() {
	add_uniform("projection");
	add_uniform("view");
	add_uniform("transform");
}