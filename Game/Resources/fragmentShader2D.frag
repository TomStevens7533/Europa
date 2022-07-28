#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCord;	
in vec3 v_Color;
in vec3 v_Light;




void main()
{
	vec4 tempColor;
		


	

	tempColor = vec4(1.f, 1.f, 1.f, 1.f);


	color = tempColor;

	

	
}