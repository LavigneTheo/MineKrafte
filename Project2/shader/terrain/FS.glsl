#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D blockSprite;

void main()
{
    //FragColor = vec4(0, 1, 0, 1.0f);
    FragColor = texture(blockSprite, texCoord);
} 
