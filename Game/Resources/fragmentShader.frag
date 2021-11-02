#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;			

uniform sampler2D u_Texture;


in vec3 v_Position;
in vec4 v_Color;
void main()
{

	vec4 tempColor = texture(u_Texture, v_TexCord); 
	tempColor.a = 1.f;
	color = tempColor;

	

	
}