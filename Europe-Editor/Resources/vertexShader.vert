#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_Uv;


uniform mat4 u_ViewProj;


out vec2 v_TexCord;


void main()
{
	v_TexCord = a_Uv;
	gl_Position = u_ViewProj * vec4(a_Position, 1.0);
	
}