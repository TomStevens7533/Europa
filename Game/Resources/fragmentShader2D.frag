#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;	
in vec3 v_Color;
in vec3 v_Light;


uniform sampler2D my_sampler;


void main()
{
	vec4 tempColor;
		
	tempColor = vec4(1,1,1,1);



	color = tempColor;

	

	
}