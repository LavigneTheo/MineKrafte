#version 330 core
out vec4 FragColor;

uniform vec3 color;
uniform mat4 merde;

in vec2 tex_coord;

uniform sampler2D texture_diffuse;

void main()
{
    FragColor = texture(texture_diffuse, tex_coord);
} 
