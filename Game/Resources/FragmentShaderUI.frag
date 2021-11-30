#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;	
in vec4 v_Color;
in vec3 v_Light;

uniform sampler2D u_Texture;


void main()
{
	vec4 tempColor;


	tempColor = v_Color;

	color = v_Color;

	

	
}