#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 aTex_coord;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;

out vec2 tex_coord;

void main()
{
	tex_coord = aTex_coord;
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}